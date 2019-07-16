/*
 * ShieldMod file
 * 
 * Tse Ojeng
 */

#include <Windows.h>

#include "ShieldMod.h"

#include <imgui.h>
#include <imgui_tabs.h>

namespace shieldmod
{
int fr = 0;
void StartupNotice()
{
	if (++fr > 8000)
		startup_wnd_ = false;

	const float DISTANCE = 30.0f;
	static int corner = 3;
	ImGuiIO &io = ImGui::GetIO();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(15, 15));

	ImVec2 window_pos = ImVec2(
		io.DisplaySize.x - DISTANCE,
		io.DisplaySize.y - DISTANCE);
	ImVec2 window_pos_pivot = ImVec2(1.0f, 1.0f);
	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);

	auto flags = ImGuiWindowFlags_NoMove |
				 ImGuiWindowFlags_NoTitleBar |
				 ImGuiWindowFlags_AlwaysAutoResize |
				 ImGuiWindowFlags_NoSavedSettings |
				 ImGuiWindowFlags_NoFocusOnAppearing |
				 ImGuiWindowFlags_NoNav;

	ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
	ImGui::Begin("Startup Notice", &startup_wnd_, flags);

	ImGui::TextColored(ImVec4(1, 0, 1, 1), "ShieldMod");
	ImGui::Separator();
	ImGui::Text("Numpad Slash for mod menu");

	ImGui::End();

	ImGui::PopStyleVar(1);
}
} // namespace shieldmod