#include <Windows.h>

#include <Cap.h>
#include <Console.h>

#include <imgui.h>
#include <imgui_tabs.h>

namespace cap
{
bool ConsoleActive_ = false;

console_t Console_()
{
	return console_ = new Console();
}

console_t console_ = nullptr;

Console::Console()
{
}

void Console::Log(const std::string &x)
{
	_deq.push_back(x);

	if (_deq.size() > 20)
		_deq.pop_front();
}

void Console::Draw()
{
	ImGuiIO &io = ImGui::GetIO();

	ImVec2 window_pos = ImVec2(10, io.DisplaySize.y - 10);
	ImVec2 window_pos_pivot = ImVec2(0.0f, 1.0f);
	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	ImGui::SetNextWindowSize(ImVec2(700, 150));

	auto flags = ImGuiWindowFlags_NoMove |
				 ImGuiWindowFlags_NoTitleBar |
				 ImGuiWindowFlags_NoResize |
				 //ImGuiWindowFlags_NoSavedSettings |
				 ImGuiWindowFlags_NoFocusOnAppearing |
				 ImGuiWindowFlags_NoNav;

	ImGui::Begin("ShieldMod Console", &ConsoleActive_, flags);

	ImGui::Text("ShieldMod Console");

	ImGui::Separator();
	ImGui::Separator();

	ImGui::BeginChild("scrolling", ImVec2(0,0));

	size_t i = 0;
	for (; i < _deq.size(); i++)
	{
		ImGui::TextUnformatted(_deq[i].c_str());
	}

	auto y = ImGui::GetScrollMaxY();
	ImGui::SetScrollY(y);

	ImGui::EndChild();

	ImGui::End();
}

} // namespace cap