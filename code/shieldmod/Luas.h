/*
 * ShieldMod file
 * 
 * Tse Ojeng
 */

#ifndef shieldmod_luas_h
#define shieldmod_luas_h

#include <string>
#include <vector>

// Todo, completely nuke this file

namespace shieldmod
{
struct Luas;

typedef Luas *luas_t;

luas_t Luas_(const std::wstring);

struct Luas
{
	int _num = 0;

	std::vector<std::wstring> _abs;
	std::vector<std::string> _dis;

	const std::wstring _rel;

	Luas(const std::wstring);

	void Reload();

	void Draw();
};

} // namespace shieldmod



#endif