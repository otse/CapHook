/*
 * ShieldMod file
 * 
 * Tse Ojeng
 */

#ifndef shieldmod_fs_h
#define shieldmod_fs_h

#include <string>
#include <vector>

// Todo, completely nuke this file

namespace fs
{
struct List;

struct List
{
	int _num = 0;

	std::vector<std::wstring> _abs;
	std::vector<std::string> _dis;

	const std::wstring _rel;

	List(const std::wstring);

	void Reload();

	void Draw();
};
} // namespace fs

typedef fs::List *fs_list_t;

fs_list_t fsList_(const std::wstring);

#endif