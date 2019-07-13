#pragma once

#include "Fs.h"

namespace cap
{
extern bool CapActive_, StartupNoticeActive_;

class Cap;

typedef Cap *cap_t;

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

void StartupNotice();

} // namespace cap