// Add the Cap code here.

#include <Cap.h>
#include <Menu.h>

#include <imgui.h>
#include <imgui_tabs.h>

namespace cap
{
	bool CapeActive_ = true;

cap_t Cap_()
{
	return cap_ = new Cap();
}

cap_t cap_ = nullptr;

Cap::Cap()
{
}

Cap::~Cap()
{
}

void Cap::Draw()
{
	ImGui::SetWindowPos(ImVec2(300, 300));
	ImGui::SetNextWindowSize(ImVec2(600, 300), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Captain America mod", &CapeActive_, 0);

	ImGui::Text("Thanks for playing!");

	ImGui::End();

}

} // namespace cap