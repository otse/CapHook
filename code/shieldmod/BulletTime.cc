/*
 * ShieldMod file
 * 
 * Tse Ojeng
 */

#include "ShieldMod.h"

#include <algorithm>

#include "imgui.h"

#include <ScriptSystem.h>
#include <Utility/PathUtils.h>

namespace shieldmod
{
bool show_hourglass_ = true;

bool slow = false;
float hourglass = 0;

Bt BtIn()
{
	auto path = Utility::MakeAbsolutePathW(L"shieldmod\\luas\\bt_in.lua");

	bool result = Lua::RunFile(path.c_str());

	slow = true;
}

Bt BtOut()
{
	auto path = Utility::MakeAbsolutePathW(L"shieldmod\\luas\\bt_out.lua");

	bool result = Lua::RunFile(path.c_str());

	slow = false;
}

Bt BtToggle()
{
	if (!slow && hourglass > .25f)
	{
		slow = true;
		bar.in_s = bar.in = 1;
		bar.out_s = 0;

		BtIn();
	}
}

Bt BtFrame()
{
	if (slow)
	{
		hourglass -= delta_time_.s / 5;

		if (hourglass <= 0)
		{
			BtOut();
			bar.til = false;
			bar.in = 0;
			bar.out = 1;
			bar.out_s = 2;
		}
	}

	else if (!slow)
	{
		hourglass += delta_time_.s / 20;
		// ALmost recharged
		if (hourglass >= .9f && !bar.til)
		{
			bar.til = true;
			bar.in = 1;
			bar.out_s = bar.in_s = 2;
			bar.out = -2;
		}
	}

	hourglass = std::clamp(hourglass, 0.f, 1.f);
}

bool bt_draw_ = true;
bool show_hourglass = true;

Bar bar;

Bt BtDraw()
{
	float fade = bar.Get();

	if (-1 == fade && slow)
		fade = 1;

	if (fade < 0 || !show_hourglass_)
		return;

	ImGuiIO &io = ImGui::GetIO();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 0.f);
	ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, hourglass * 200);

	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(1, 1, 1, 0));
	ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(1, 1, 1, 0));
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(1, 1, 1, 0));
	ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(1, 1, 1, .8f * fade));
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(255, 255, 255, 0));

	ImGui::SetNextWindowBgAlpha(0.0f);

	ImVec2 window_pos = ImVec2(
		io.DisplaySize.x - 20,
		io.DisplaySize.y - 20);
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
	ImGui::VSliderFloat("##bt", ImVec2(25, 200), &v, 0.f, 1.f, "");

	ImGui::End();

	ImGui::PopStyleColor(5);

	ImGui::PopStyleVar(3);
}

} // namespace shieldmod
