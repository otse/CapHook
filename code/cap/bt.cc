#include "cap_1.h"

#include <algorithm>

#include "imgui.h"

#include <ScriptSystem.h>
#include <Utility/PathUtils.h>

namespace cap
{
// externs
bool show_hourglass_ = true; // bar

// locals
bool slow = false;
float hourglass = 0;

til_t til;

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
		til.in_s = til.in = 1;
		til.out_s = 0;

		Bt_In();
	}
}

Void Bt_Frame()
{
	if (slow)
	{
		hourglass -= delta_time_.s / 5;

		if (hourglass <= 0)
		{
			Bt_Out();
			til.til = false;
			til.in = 0;
			til.out = 1;
			til.out_s = 2;
		}
	}

	else if (!slow)
	{
		hourglass += delta_time_.s / 20;
		// ALmost recharged
		if (hourglass >= .9f && !til.til)
		{
			til.til = true;
			til.in = 1;
			til.out_s = til.in_s = 2;
			til.out = -2;
		}
	}

	hourglass = std::clamp(hourglass, 0.f, 1.f);
}

bool bt_draw_ = true;
bool show_hourglass = true;

Void Bt_Draw()
{
	float fade = 0;

	if (til.in > 0)
	{
		til.in -= delta_time_.s / til.in_s;
		if (til.in <= 1)
			fade = 1 - til.in;
		if (til.in <= 0)
		{
			til.in = 0;
			if (til.out_s)
				til.out = -til.out;
		}
	}
	else if (til.out > 0)
	{
		fade = 1;
		til.out -= delta_time_.s / til.out_s;
		if (til.out <= 1)
			fade = til.out;
		if (til.out <= 0)
			til.out = 0;
	}
	else if (slow)
	{
		fade = 1;
	}

	if (!fade || !show_hourglass_)
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

} // namespace cap
