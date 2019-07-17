/*
 * ShieldMod file
 * 
 * Tse Ojeng
 */

#include <Windows.h>

#include "ShieldMod.h"

#include <imgui.h>
#include <imgui_tabs.h>

#include <Utility/PathUtils.h>

namespace shieldmod
{
luas_t Luas_(const std::wstring rel)
{
	return new Luas(rel);
}

Luas::Luas(const std::wstring rel)
	: _rel(rel)
{
}

void Luas::Reload()
{
	_num = 0;
	_abs.clear();
	_dis.clear();

	auto path = Utility::MakeAbsolutePathW(_rel);

	WIN32_FIND_DATAW data;
	HANDLE handle = FindFirstFileW((path + L"\\*.lua").c_str(), &data);

	if (handle != INVALID_HANDLE_VALUE)
	{
		do
		{
			bool fol = data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
			if (fol)
				continue;

			_num++;

			_abs.push_back(path + L"\\" + data.cFileName);

			std::wstring wstr = data.cFileName;

			_dis.push_back(std::string(wstr.begin(), wstr.end()));

		} while (FindNextFileW(handle, &data));

		FindClose(handle);
	}
}

static bool ScriptItemSelector(void *data, int idx, const char **out_text)
{
	const auto vec = (std::vector<std::string> *)data;

	if (out_text)
		*out_text = vec->at(idx).c_str();

	return true;
}

void Luas::Draw()
{
	static int current_item = 0;

	static char *desc = "Selecting these items\ndoes nothing";
	if (ImGui::ListBox(
			desc,
			&current_item,
			ScriptItemSelector,
			&_dis,
			(int)_dis.size()))
	{
		//std::puts(std::string("Selected ") + DIS[current_item]);
		//auto dir = (Utility::MakeAbsolutePathW(L"caphook\\luas") + DIS[current_item]).c_str();
		//Lua::RunFile(dir);
	}
}

} // namespace shielmod
