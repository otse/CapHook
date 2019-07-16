#pragma once

#include "log.h"

#include "fs_1.h"
#include "dt.h"
#include "bt.h"

#include "banner_1.h"

#include <chrono>

namespace cap
{
extern bool cap_active_;
extern bool startup_notice_active_;

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

	void Key(unsigned __int64);

	/// Load our own game scripts
	void LoadLuas();

	void Draw();
};

typedef void CAPTEST;

CAPTEST TestFindScripts();

void StartupNotice();



} // namespace cap