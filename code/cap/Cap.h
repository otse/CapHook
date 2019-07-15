#pragma once

#include "Fs.h"

#include <chrono>

using namespace std::chrono;

using FOCS_1 = high_resolution_clock;
using FOCS_1_2 = FOCS_1::time_point;

namespace cap
{
typedef void VOID;

typedef struct
{
	FOCS_1_2 a, b;
	float _s = 0, _ms = 0;
	void Set()
	{
		a = FOCS_1::now();
		auto duration =
			duration_cast<microseconds>(a - b).count();
		_s = duration / 1000000.f;
		_ms = duration / 1000.f;
		b = a;
	}

} gamma_time_t;

extern gamma_time_t gamma_time_;

#define CAP_GAMMA_TIME_SET() gamma_time_.Set();

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

	void Key(WPARAM);

	/// Load our own game scripts
	void LoadLuas();

	void Draw();
};

typedef void CAPTEST;

CAPTEST TestFindScripts();

void StartupNotice();

} // namespace cap