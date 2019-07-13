// Add the Cap code here.

#include <Windows.h>

#include <Cap.h>
//#include <Menu.h>

#include <imgui.h>
#include <imgui_tabs.h>

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
	auto check = [](const std::wstring &path)
	{
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

	ImGui::BeginTabBar("Info#MyTabBar"); // what does this do
	ImGui::DrawTabsBackground();
	
	if (ImGui::AddTab("Info"))
	{
		std::string ver = "Version: 0.5";
		ImGui::Text(ver.c_str());

		std::string num_lua = "Num lua files: " + std::to_string(_luas->_num);
		ImGui::Text(num_lua.c_str());
	}

	if (ImGui::AddTab("Luas"))
	{
		if (ImGui::Button("Reload from disk"))
		{
			LoadLuas();
		}

		_luas->Draw();
	}

	ImGui::EndTabBar();
	ImGui::End();
}

} // namespace cap