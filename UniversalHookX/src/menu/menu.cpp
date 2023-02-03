#include "menu.hpp"

//#include "../dependencies/imgui/imgui_memory_editor.h"
#include "../headers/configs.h"
#include "../dependencies/imgui/imgui.h"
#include "../dependencies/imgui/imgui_impl_win32.h"

#include "../headers/Extras.h"
#include "../headers/presetthemes.h"

namespace ig = ImGui;

float test = 1;

static bool no_titlebar = false;
static bool no_border = true;
static bool no_resize = false;
static bool auto_resize = false;
static bool no_move = false;
static bool no_scrollbar = false;
static bool no_collapse = false;
static bool no_menu = true;
static bool start_pos_set = false;


namespace Menu {
    void InitializeContext(HWND hwnd) {
        if (ig::GetCurrentContext( ))
            return;

        ImGui::CreateContext( );
        ImGui_ImplWin32_Init(hwnd);

        ImGuiIO& io = ImGui::GetIO( );
        io.IniFilename = io.LogFilename = nullptr;
    }

    void Render( ) {
        if (!bShowMenu)
            return;

        ImGui::SetNextWindowSize(ImVec2(1280, 720), ImGuiCond_Once);
        ImGui::Begin("Master Bastard Pre-Alpha 0.01 By Xolara", &bShowMenu);
        
        /* ImGuiStyle* style = &ImGui::GetStyle( );
        style->WindowPadding = ImVec2(8, 8);
        style->WindowRounding = 7.0f;
        style->FramePadding = ImVec2(4, 3);
        style->FrameRounding = 0.0f;
        style->ItemSpacing = ImVec2(6, 4);
        style->ItemInnerSpacing = ImVec2(4, 4);
        style->IndentSpacing = 20.0f;
        style->ScrollbarSize = 14.0f;
        style->ScrollbarRounding = 9.0f;
        style->GrabMinSize = 5.0f;
        style->GrabRounding = 0.0f;
        style->WindowBorderSize = 0;
        style->WindowTitleAlign = ImVec2(0.0f, 0.5f);
        style->FramePadding = ImVec2(4, 3);
        style->Colors[ImGuiCol_TitleBg] = ImColor(75, 5, 150, 225);
        style->Colors[ImGuiCol_TitleBgActive] = ImColor(75, 75, 150, 225);
        style->Colors[ImGuiCol_Button] = ImColor(75, 5, 150, 225);
        style->Colors[ImGuiCol_ButtonActive] = ImColor(75, 75, 150, 225);
        style->Colors[ImGuiCol_ButtonHovered] = ImColor(41, 40, 41, 255);
        style->Colors[ImGuiCol_Separator] = ImColor(70, 70, 70, 255);
        style->Colors[ImGuiCol_SeparatorActive] = ImColor(76, 76, 76, 255);
        style->Colors[ImGuiCol_SeparatorHovered] = ImColor(76, 76, 76, 255);
        style->Colors[ImGuiCol_Tab] = ImColor(75, 5, 150, 225);
        style->Colors[ImGuiCol_TabHovered] = ImColor(75, 75, 150, 225);
        style->Colors[ImGuiCol_TabActive] = ImColor(110, 110, 250, 225);
        style->Colors[ImGuiCol_SliderGrab] = ImColor(75, 75, 150, 225);
        style->Colors[ImGuiCol_SliderGrabActive] = ImColor(110, 110, 250, 225);
        style->Colors[ImGuiCol_MenuBarBg] = ImColor(76, 76, 76, 255);
        style->Colors[ImGuiCol_FrameBg] = ImColor(37, 36, 37, 255);
        style->Colors[ImGuiCol_FrameBgActive] = ImColor(37, 36, 37, 255);
        style->Colors[ImGuiCol_FrameBgHovered] = ImColor(37, 36, 37, 255);
        style->Colors[ImGuiCol_Header] = ImColor(0, 0, 0, 0);
        style->Colors[ImGuiCol_HeaderActive] = ImColor(0, 0, 0, 0);
        style->Colors[ImGuiCol_HeaderHovered] = ImColor(46, 46, 46, 255);
        */

        ImGui::PushItemWidth(ImGui::GetWindowWidth( ) * 0.65f);
        ImGui::PushItemWidth(-140);
        if (ImGui::BeginTabBar("Master Bars")) {
            if (ImGui::BeginTabItem("Menu")) {

                ImGui::Text("");
                if (ImGui::Button("Save Settings")) {
                    do {
                        wchar_t buf[MAX_PATH];
                        GetModuleFileNameW(g_hInstance, buf, MAX_PATH);
                        fs::path path = fs::path(buf).remove_filename( ) / ".settings";
                        auto file = CreateFileW(path.wstring( ).c_str( ), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                        if (file == INVALID_HANDLE_VALUE)
                            break;
                        DWORD written;
                        if (WriteFile(file, &Config::cfg, sizeof(Config::cfg), &written, 0))
                            ImGui::OpenPopup("##SettingsSaved");
                        CloseHandle(file);
                    } while (false);
                }
                ImGui::SameLine( );
                if (ImGui::Button("Load Settings")) {
                    do {
                        wchar_t buf[MAX_PATH];
                        GetModuleFileNameW(g_hInstance, buf, MAX_PATH);
                        fs::path path = fs::path(buf).remove_filename( ) / ".settings";
                        auto file = CreateFileW(path.wstring( ).c_str( ), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                        if (file == INVALID_HANDLE_VALUE)
                            break;
                        DWORD readed;
                        if (ReadFile(file, &Config::cfg, sizeof(Config::cfg), &readed, 0))
                            ImGui::OpenPopup("##SettingsLoaded");
                        CloseHandle(file);
                    } while (false);
                }

                ImVec2 center(ImGui::GetIO( ).DisplaySize.x * 0.5f, ImGui::GetIO( ).DisplaySize.y * 0.5f);
                ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
                if (ImGui::BeginPopupModal("##SettingsSaved", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar)) {
                    ImGui::Text("\nSettings Saved!\n\n");
                    ImGui::Separator( );
                    if (ImGui::Button("OK", {170.f, 0.f})) {
                        ImGui::CloseCurrentPopup( );
                    }
                    ImGui::EndPopup( );
                }

                ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
                if (ImGui::BeginPopupModal("##SettingsLoaded", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar)) {
                    ImGui::Text("\nSettings Loaded!\n\n");
                    ImGui::Separator( );
                    if (ImGui::Button("OK", {170.f, 0.f})) {
                        ImGui::CloseCurrentPopup( );
                    }
                    ImGui::EndPopup( );
                }

                ImGui::Text("");
                ImGui::Separator( );

            if (ImGui::CollapsingHeader("Menu Customization")) {
                if (ImGui::TreeNode("Preset Themes")) {                   
                        static int style_idx = -1;
                            if (ImGui::Combo("Preset Themes", &style_idx, "Dark\0Light\0Classic\0Shadow The Hedgehog\0Sonic The Hedgehog\0Royal Light\0Royal Dark")) {
                                switch (style_idx) {
                                    case 0: ThemesPresets::StyleColorsDark(); break;
                                    case 1: ThemesPresets::StyleColorsLight(); break;
                                    case 2: ThemesPresets::StyleColorsClassic(); break;
                                    case 3: ThemesPresets::ShadowTheHedgeHogTheme(); break;
                                    case 4: ThemesPresets::SonicTheHedgehog(); break;
                                    case 5: ThemesPresets::LightRoyalTheme(); break;
                                    case 6: ThemesPresets::DarkRoyalTheme(); break;
                                }            
                            }
                    ImGui::TreePop( );
                    }

                if (ImGui::TreeNode("Theme Customizer")) {

                    ImGui::TreePop( );
                    
                    }
                }
            ImGui::EndTabItem( );

            }
            if (ImGui::BeginTabItem("Tab 2")) {

            ImGui::Columns(3, "ActorEspCol", false);

            ImGui::Text("Section 1");
            if (ImGui::BeginChild("Section 1", ImVec2(0.f, 0.f), true, 0)) {
                    ImGui::Checkbox("Checkbox 1", &Config::cfg.MainSection1.Section1.checkbox1);
                    ImGui::SliderFloat("Slider 1", &Config::cfg.MainSection1.Section1.slider1, 1.f, 5000.f, "%.0f");
                    ImGui::Checkbox("CheckBox 2", &Config::cfg.MainSection1.Section1.checkbox2);
                    ImGui::Checkbox("CheckBox 3", &Config::cfg.MainSection1.Section1.checkbox3);
                    ImGui::Checkbox("CheckBox 4", &Config::cfg.MainSection1.Section1.checkbox4);
                    ImGui::Checkbox("Checkbox 5", &Config::cfg.MainSection1.Section1.checkbox5);
                    ImGui::Checkbox("Checkbox 6", &Config::cfg.MainSection1.Section1.checkbox6);
                    ImGui::SliderFloat("Slider 2", &Config::cfg.MainSection1.Section1.slider2, 0.f, 1000.f, "%.0f");
                    ImGui::SliderFloat("Slider 3", &Config::cfg.MainSection1.Section1.slider3, -10.f, 20.f, "%.0f");
            }
            ImGui::EndChild( );

            ImGui::NextColumn( );

            ImGui::Text("Section 2");
            if (ImGui::BeginChild("Section 2", ImVec2(0.f, 0.f), true, 0)) {
                    ImGui::Checkbox("Checkbox 7", &Config::cfg.MainSection1.Section2.checkbox7);
                    ImGui::SliderFloat("Slider 4", &Config::cfg.MainSection1.Section2.slider4, 1.f, 5000.f, "%.0f");
                    ImGui::Checkbox("CheckBox 8", &Config::cfg.MainSection1.Section2.checkbox8);
                    ImGui::Checkbox("CheckBox 9", &Config::cfg.MainSection1.Section2.checkbox9);
                    ImGui::Checkbox("CheckBox 10", &Config::cfg.MainSection1.Section2.checkbox10);
                    ImGui::Checkbox("Checkbox 11", &Config::cfg.MainSection1.Section2.checkbox11);
                    ImGui::Checkbox("Checkbox 12", &Config::cfg.MainSection1.Section2.checkbox12);
                    ImGui::SliderFloat("Slider 5", &Config::cfg.MainSection1.Section2.slider5, 0.f, 1000.f, "%.0f");
                    ImGui::SliderFloat("Slider 6", &Config::cfg.MainSection1.Section2.slider6, -10.f, 20.f, "%.0f");
            }
                 ImGui::EndChild( );

                 ImGui::NextColumn( );

                 ImGui::Text("Section 3");
                 if (ImGui::BeginChild("Section 3", ImVec2(0.f, 0.f), true, 0)) {
                    ImGui::Checkbox("Checkbox 13", &Config::cfg.MainSection1.Section3.checkbox13);
                    ImGui::SliderFloat("Slider 7", &Config::cfg.MainSection1.Section3.slider7, 1.f, 5000.f, "%.0f");
                    ImGui::Checkbox("CheckBox 14", &Config::cfg.MainSection1.Section3.checkbox14);
                    ImGui::Checkbox("CheckBox 15", &Config::cfg.MainSection1.Section3.checkbox15);
                    ImGui::Checkbox("CheckBox 16", &Config::cfg.MainSection1.Section3.checkbox16);
                    ImGui::Checkbox("Checkbox 17", &Config::cfg.MainSection1.Section3.checkbox17);
                    ImGui::Checkbox("Checkbox 18", &Config::cfg.MainSection1.Section3.checkbox18);
                    ImGui::SliderFloat("Slider 8", &Config::cfg.MainSection1.Section3.slider8, 0.f, 1000.f, "%.0f");
                    ImGui::SliderFloat("Slider 9", &Config::cfg.MainSection1.Section3.slider9, -10.f, 20.f, "%.0f");
                 }

                 ImGui::EndChild( );

                 ImGui::Columns( );

                 ImGui::EndTabItem( );
            }

            if (ImGui::BeginTabItem("Tab 3")) {
             //static MemoryEditor mem_edit;
             //mem_edit.DrawWindow("Memory Editor", data, data_size);
             ImGui::EndTabItem( );
            }

            if (ImGui::BeginTabItem("Tab 4")) {

             ImGui::EndTabItem( );
            }

            if (ImGui::BeginTabItem("Tab 5")) {

             ImGui::EndTabItem( );
            }

            if (ImGui::BeginTabItem("Tab 6")) {
             ig::ShowDemoWindow( );
             ImGui::EndTabItem( );
            }
            
            ImGui::EndTabBar( );
        
        }
        ImGui::End( );
        //ig::ShowDemoWindow( );
        ImGui::Render( );
    }

} // namespace Menu



void ShadowTheHedgeHogTheme(ImGuiStyle* dst) {
    ImGuiStyle* style = dst ? dst : &ImGui::GetStyle( );
    ImVec4* colors = style->Colors;
    colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.940f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.11f, 0.11f, 0.14f, 0.92f);
    colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.525f, 0.00f, 0.00f, 0.414f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(1.00f, 0.00f, 0.00f, 0.400f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.448f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.27f, 0.27f, 0.54f, 0.83f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.40f, 0.40f, 0.55f, 0.80f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.40f, 0.40f, 0.80f, 0.30f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.80f, 0.40f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.41f, 0.39f, 0.80f, 0.60f);
    colors[ImGuiCol_CheckMark] = ImVec4(1.00, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.871f, 0.784f, 0.00f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.475f, 0.428f, 0.00f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.564f, 0.00f, 0.00f, 0.400f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.46f, 0.54f, 0.80f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.565f, 0.00f, 0.00f, 0.400f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(1.00f, 0.00f, 0.00f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.890, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 0.00f, 0.00f, 0.696f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_Tab] = ImLerp(colors[ImGuiCol_Header], colors[ImGuiCol_TitleBgActive], 0.851f);
    colors[ImGuiCol_TabHovered] = colors[ImGuiCol_HeaderHovered];
    colors[ImGuiCol_TabActive] = ImLerp(colors[ImGuiCol_HeaderActive], colors[ImGuiCol_TitleBgActive], 0.241f);
    colors[ImGuiCol_TabUnfocused] = ImLerp(colors[ImGuiCol_Tab], colors[ImGuiCol_TitleBg], 0.80f);
    colors[ImGuiCol_TabUnfocusedActive] = ImLerp(colors[ImGuiCol_TabActive], colors[ImGuiCol_TitleBg], 0.40f);
    colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.27f, 0.27f, 0.38f, 1.00f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.45f, 1.00f); // Prefer using Alpha=1.0 here
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.26f, 0.26f, 0.28f, 1.00f);  // Prefer using Alpha=1.0 here
    colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = colors[ImGuiCol_HeaderHovered];
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}
