/*
 * ShieldMod file
 * 
 * Tse Ojeng
 */

#ifndef shieldmod_shieldmod_h
#define shieldmod_shieldmod_h

#include "Dt.h"
#include "Log.h"

#include "fs.h"
#include "BulletTime.h"

#include "Art.h"

#include <chrono>

#define CAP_DELTA_TIME_SET() delta_time_.Tick();

namespace shieldmod
{
extern bool cap_wnd_;
extern bool startup_wnd_;

class Cap;

typedef Cap *cap_t;

cap_t Cap_();

extern cap_t cap_;

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

} // namespace shieldmod

#endif