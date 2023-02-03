#pragma once

//#include <imgui/imgui.h> need to fix this shit

class Config
{
public:
	static inline struct Configuration {
		enum class ECrosshairs : int {

		};
		struct
		{
          bool fovEnable = true;
		}client;
		struct
		{
			bool enable = false;
			struct
			{

			}players;
			struct
			{
              bool shadowthehedgehogtheme = false;
              bool SonicTheHedgehogtheme = false;
              bool LightRoyalTheme = false;
              bool DarkRoyalTheme = false;

			}PresetThemeSelection;
			struct
			{
              bool checkbox1 = false;
              bool checkbox2 = false;
              bool checkbox3 = false;
              bool checkbox4 = false;
              bool checkbox5 = false;
              bool checkbox6 = false;
              float slider1 = 100.f;
              float slider2 = 0.f;
              float slider3 = 0.f;
			}Section1;
			struct
			{
              bool checkbox7 = false;
              bool checkbox8 = false;
              bool checkbox9 = false;
              bool checkbox10 = false;
              bool checkbox11 = false;
              bool checkbox12 = false;
              float slider4 = 100.f;
              float slider5 = 0.f;
              float slider6 = 0.f;
			}Section2;
			struct
			{
              bool checkbox13 = false;
              bool checkbox14 = false;
              bool checkbox15 = false;
              bool checkbox16 = false;
              bool checkbox17 = false;
              bool checkbox18 = false;
              float slider7 = 100.f;
              float slider8 = 0.f;
              float slider9 = 0.f;
			}Section3;
			struct 
			{

			}others;
		}MainSection1;
		struct
		{
			bool enable = false;
			struct
			{

			}weapon;
			struct
			{

			}cannon;
			struct
			{

			}others;
		}aim;
		struct
		{

		}game;
		struct
		{

		}dev;
	}cfg;
};
