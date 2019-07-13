#pragma once

#include "Fs.h"

namespace cap
{
class Cap;
typedef Cap *cap_t;

extern bool CapeActive_;
extern cap_t cap_;

cap_t Cap_();

class Cap
{
public:
	Cap();
	~Cap();

	fs_list_t const _luas;
	
	void Key(WPARAM);

	/// Load our own game scripts
	void LoadLuas();

	void Draw();
};

typedef void CAPTEST;

CAPTEST TestFindScripts();
} // namespace cap