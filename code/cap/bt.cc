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
	if (slow)
	{
		slow = false;
		Bt_Out();
	}
	else if (hourglass > .25f)
	{
		slow = true;
		Bt_In();
	}
}

Void Bt_Frame()
{
	if (slow)
	{
		// Drain
		hourglass -= delta_time_.s / 4.f;
		if (hourglass < 0)
			Bt_Out();
	}
	else
	{
		// Recharge
		hourglass += delta_time_.s / 20.f;
	}

	hourglass = std::clamp(hourglass, 0.f, 1.f);
}

bool bt_draw_ = true;

Void Bt_Draw()
{
	ImGuiIO &io = ImGui::GetIO();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(15, 15));

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

	ImGui::SetNextWindowBgAlpha(0.0f);

	ImGui::Begin("Startup Notice", &bt_draw_, flags);

	ImGui::Separator();

	//const std::string bt = "Bullet Time: " + std::to_string(hourglass);
	//ImGui::Text(bt.c_str());

	float v = hourglass;
	ImGui::VSliderFloat("##bt", ImVec2(18, 160), &v, 0.f, 1.f, "");

	ImGui::End();

	ImGui::PopStyleVar(1);
}
} // namespace cap
