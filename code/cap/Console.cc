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
	ImGui::SetWindowPos(ImVec2(800, 800));
	ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiSetCond_FirstUseEver);

	ImGui::Begin("ShieldMod Console", &ConsoleActive_, 0);

	ImGui::Text("Gayo");

	ImGui::Separator();

	size_t i = 0;
	for (; i < _deq.size(); i++)
	{
		ImGui::TextUnformatted(_deq[i].c_str());
	}

	auto y = ImGui::GetScrollMaxY();
	ImGui::SetScrollY(y);

	ImGui::End();
}

} // namespace cap