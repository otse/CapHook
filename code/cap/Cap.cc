// Add the Cap code here.

#include <Windows.h>

#include <Cap.h>
//#include <Menu.h>

#include <imgui.h>
#include <imgui_tabs.h>

#include <ScriptSystem.h>

#include <Utility/PathUtils.h>

namespace cap
{
bool CapeActive_ = true;

cap_t Cap_()
{
	return cap_ = new Cap();
}

cap_t cap_ = nullptr;

Cap::Cap()
	: _luas(fsList_(L"caphook\\luas"))
{
	auto check = [](const std::wstring &path) {
		auto abs = Utility::MakeAbsolutePathW(path);

		if (GetFileAttributesW(abs.c_str()) == INVALID_FILE_ATTRIBUTES)
			CreateDirectoryW(abs.c_str(), nullptr);
	};

	check(L"caphook");
	check(L"caphook\\luas");

	LoadLuas();
}

Cap::~Cap()
{
}

void Cap::Key(WPARAM w)
{
	// http://www.kbdedit.com/manual/low_level_vk_list.html

	auto &v = _luas->_dis;

	auto has_lua = ([&](const std::string &x) {
		bool found = std::find(v.begin(), v.end(), x) != v.end();
		return found;
	});

	if (w == VK_NUMPAD5)
	{
		auto x = "spawn_shield.lua";

		if (!has_lua(x))
			return;

		std::puts("Spawn shield");

		auto path = Utility::MakeAbsolutePathW(L"caphook\\luas\\spawn_shield.lua");

		Lua::RunFile(path.c_str());
	}

	if (w == VK_NUMPAD8)
	{
		auto x = "pull_shield.lua";

		if (!has_lua(x))
			return;

		std::puts("Pull shield");

		auto path = Utility::MakeAbsolutePathW(L"caphook\\luas\\pull_shield.lua");

		Lua::RunFile(path.c_str());
	}
}

/// Load our own game scripts
void Cap::LoadLuas()
{
	std::puts("Load the luas");

	_luas->Reload();
}

void Cap::Draw()
{
	ImGui::SetWindowPos(ImVec2(600, 300));
	ImGui::SetNextWindowSize(ImVec2(600, 300), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Captain America mod", &CapeActive_, 0);

	ImGui::Text("Thanks for playing! CapHook is a fork of DawnHook. Press / to toggle menu.\n");

	ImGui::BeginTabBar("#MyTabBar"); // what does this do
	ImGui::DrawTabsBackground();

	if (ImGui::AddTab("Info & Settings"))
	{
		std::string ver = "Version: 0.75%";
		ImGui::Text(ver.c_str());

		std::string num_lua = "Num lua files: " + std::to_string(_luas->_num);
		ImGui::Text(num_lua.c_str());

		std::string spawn_shield = "Spawn Shield: <Numpad 5>";
		ImGui::Text(spawn_shield.c_str());

		std::string spawn_shield = "Spawn Shield Delay: <Numpad 5>";
		//ImGui::Label(spawn_shield.c_str());
	}

	if (ImGui::AddTab("Luas"))
	{
		if (ImGui::Button("Reload luas"))
		{
			LoadLuas();
		}

		_luas->Draw();
	}

	ImGui::EndTabBar();
	ImGui::End();
}

} // namespace cap