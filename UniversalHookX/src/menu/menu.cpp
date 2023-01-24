#include "menu.hpp"

#include "../dependencies/imgui/imgui.h"
#include "../dependencies/imgui/imgui_impl_win32.h"

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

        ImGui::Begin("ImGui Menu", &bShowMenu);

        ImGui::PushItemWidth(ImGui::GetWindowWidth( ) * 0.65f);
        ImGui::PushItemWidth(-140);

        if (ImGui::CollapsingHeader("MENU")) {
            if (ImGui::TreeNode("SUB MENU")) {
                ImGui::Text("Text Test");
                if (ImGui::Button("Button Test")) {
                }
                ImGui::Checkbox("CheckBox Test", &no_titlebar);
                ImGui::SliderFloat("Slider Test", &test, 1.0f, 100.0f);

                ImGui::TreePop( );
            }
        }

        ImGui::End( );
        //ig::ShowDemoWindow( );
        ImGui::Render( );
    }

} // namespace Menu
