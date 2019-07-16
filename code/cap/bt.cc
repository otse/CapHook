#include "cap_1.h"

#include <algorithm>

#include "imgui.h"

#include <ScriptSystem.h>
#include <Utility/PathUtils.h>

namespace cap
{
float hourglass = 0;

bool slow = false;

Void Bt_In()
{
	auto path = Utility::MakeAbsolutePathW(L"shieldmod\\luas\\bt_in.lua");

	bool result = Lua::RunFile(path.c_str());

	slow = true;
}

Void Bt_Out()
{
	auto path = Utility::MakeAbsolutePathW(L"shieldmod\\luas\\bt_out.lua");

	bool result = Lua::RunFile(path.c_str());

	slow = false;
}

Void Bt_Toggle()
{
	if (hourglass > .25f)
	{
		slow = true;

		Bt_In();
	}
}

bool til = false;
float til_in = 0;
float til_out = 0;

Void Bt_Frame()
{
	if (slow)
	{
		hourglass -= delta_time_.s / 5;

		if (hourglass < 0) {
			Bt_Out();
			til = false;
		}
	}
	
	if (!slow)
	{
		hourglass += delta_time_.s / 20;

		if (hourglass >= .9f && !til)
		{
			til = true;
			til_in = 1.0f;
		}
	}

	hourglass = std::clamp(hourglass, 0.f, 1.f);
}

bool bt_draw_ = true;

Void Bt_Draw()
{
	float fade = 0;

	if (til_in)
	{
		til_in -= delta_time_.s / 2;
		if (til_in <= 1)
			fade = 1 - til_in;
		if (til_in <= 0)
		{
			til_in = 0;
			til_out = 2.0;
		}
	}
	else if (til_out)
	{
		fade = 1;
		til_out -= delta_time_.s / 2;
		if (til_out <= 1)
			fade = til_out;
		if (til_out <= 0)
		{
			til_out = 0;
		}
	}

	//if (!fade)
	//	return;

	ImGuiIO &io = ImGui::GetIO();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(15, 15));
	ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 0.f);
	ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, hourglass * 200);

	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(1, 1, 1, 0));
	ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(1, 1, 1, 0));
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(1, 1, 1, 0));
	ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(fade, fade, fade, .75f));
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(255, 255, 255, 0));

	ImGui::SetNextWindowBgAlpha(0.0f);

	ImVec2 window_pos = ImVec2(
		io.DisplaySize.x - 50,
		io.DisplaySize.y - 100);
	ImVec2 window_pos_pivot = ImVec2(1.0f, 1.0f);
	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);

	auto flags = ImGuiWindowFlags_NoMove |
				 ImGuiWindowFlags_NoTitleBar |
				 ImGuiWindowFlags_AlwaysAutoResize |
				 ImGuiWindowFlags_NoSavedSettings |
				 ImGuiWindowFlags_NoFocusOnAppearing |
				 ImGuiWindowFlags_NoNav;

	ImGui::Begin("Bullet Time", &bt_draw_, flags);

	//ImGui::Separator();

	//const std::string bt = "Bullet Time: " + std::to_string(hourglass);
	//ImGui::Text(bt.c_str());

	float v = 0;
	ImGui::VSliderFloat("##bt", ImVec2(20, 200), &v, 0.f, 1.f, "");

	ImGui::End();

	ImGui::PopStyleColor(5);

	ImGui::PopStyleVar(3);
}
} // namespace cap
