/*
 * ShieldMod file
 * 
 * Tse Ojeng
 */

#include <Windows.h>

#include "ShieldMod.h"

//#include <Menu.h>

#include <imgui.h>
#include <imgui_tabs.h>

#include <ScriptSystem.h>

#include <Utility/PathUtils.h>

namespace shieldmod
{
Dt_t<float> delta_time_;

bool cap_wnd_ = false;
bool startup_wnd_ = true;

cap_t Cap_()
{
	return cap_ = new Cap();
}

cap_t cap_ = nullptr;

Cap::Cap()
	: _luas(fsList_(L"shieldmod\\luas"))
{
	auto check = [](const std::wstring &path) {
		auto abs = Utility::MakeAbsolutePathW(path);

		if (GetFileAttributesW(abs.c_str()) == INVALID_FILE_ATTRIBUTES)
			CreateDirectoryW(abs.c_str(), nullptr);
	};

	check(L"shieldmod");
	check(L"shieldmod\\luas");

	Log_();

	CAPCONSOLELOG("Starting");

	LoadLuas();

	delta_time_.a = high_resolution_clock::now();
	delta_time_.b = high_resolution_clock::now();
}

Cap::~Cap()
{
}

void Cap::Key(WPARAM w)
{
	// http://www.kbdedit.com/manual/low_level_vk_list.html

	auto &v = _luas->_dis;

	auto HasLua = ([&](const std::string &x) {
		bool found = std::find(v.begin(), v.end(), x) != v.end();
		return found;
	});

	if (w == VK_MULTIPLY)
	{
		log_active_ = !log_active_;
	}

#define SCRIPTMAC(x)                                                            \
	{                                                                           \
		if (!HasLua(x ".lua"))                                                  \
			return;                                                             \
                                                                                \
		CAPCONSOLELOG("run " x);                                                \
                                                                                \
		auto path = Utility::MakeAbsolutePathW(L"shieldmod\\luas\\" x L".lua"); \
                                                                                \
		bool result = Lua::RunFile(path.c_str());                               \
		if (result)                                                             \
			CAPCONSOLELOG(x " error");                                          \
	}

	if (w == VK_NUMPAD5)

		SCRIPTMAC("spawn_shield");

	if (w == VK_NUMPAD8)

		SCRIPTMAC("pull_shield");

	if (w == VK_F1)

		Bt_Toggle();
}

/// Load our own game scripts
void Cap::LoadLuas()
{
	std::puts("Load the luas");

	_luas->Reload();
}

bool upload = false;

void Cap::Draw()
{
	/*if (!upload) {
		CAPUPLOADBANNER();
		upload = true;
	}*/

	CAPDRAWBANNER();

	ImGui::SetWindowPos(ImVec2(600, 300));
	ImGui::SetNextWindowSize(ImVec2(600, 300), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("ShieldMod for ND", &cap_wnd_, 0);

	///ImGui::Text("Thanks for playing! ShieldMod is a fork of DawnHook. Press / to toggle menu.\n");

	ImGui::BeginTabBar("#MyTabBar"); // what does this do
	ImGui::DrawTabsBackground();

	if (ImGui::AddTab("Combat Stance"))
	{
		ImGui::TextColored(ImVec4(1, 0, 1, 1), "Choose your stance here.");
	}

	if (ImGui::AddTab("Info & Settings"))
	{
		std::string ver = "Version: 0.75%";
		ImGui::Text(ver.c_str());

		std::string num_lua = "Num lua files: " + std::to_string(_luas->_num);
		ImGui::Text(num_lua.c_str());

		std::string spawn_shield = "Spawn Shield: <Numpad 5>";
		ImGui::Text(spawn_shield.c_str());

		//std::string spawn_shield = "Spawn Shield Delay: ";
		//ImGui::Label(spawn_shield.c_str());

		ImGui::Separator();

		if (ImGui::Button("Reload Banner Art"))
		{
			CAPCONSOLELOG("Reploading banner art");

			shieldmod::CAPUPLOADBANNER(L"pink captain america");
			shieldmod::CAPUPLOADBANNER(L"pink winter soldier");
			//shieldmod::CAPUPLOADBANNER(L"pink winter soldier 2");
		}

		if (ImGui::Button("Toggle ShieldMod Log"))
		{
			log_active_ = !log_active_;
		}

		std::string falsy = show_hourglass_ ? "true": "false";
		if (ImGui::Button(("Bullet Time UI Bar: " + falsy).c_str()))
		{
			show_hourglass_ = !show_hourglass_;
			til.in = 0;
			til.out = 0;
			til.in_s = 2;
			til.out_s = 2;
		}
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

	//ID3D11ShaderResourceView* my_texture_view;
	//device->CreateShaderResourceView(my_texture, &my_shader_resource_view_desc, &my_texture_view);
	//ImGui::Image((void*)my_texture_view, ImVec2(512,512));
	ImGui::End();
}

} // namespace shieldmod