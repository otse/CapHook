#pragma once

#include <chrono>

using namespace std::chrono;
using namespace std::chrono_literals;

constexpr std::chrono::nanoseconds timestep(16ms);

#define CAP_DELTA_TIME_SET() delta_time_.Set();

namespace cap
{
//typedef std::chrono::duration<float> float_duration;

template <typename T>
struct delta_time_t
{
	nanoseconds d;
	high_resolution_clock::time_point a, b;
	T s, ms;
	void Set()
	{
		a = high_resolution_clock::now();
		d = a - b;
		s = d.count() / 1000000000.f;
		b = high_resolution_clock::now();
		CAPCONSOLELOG("dt s " + std::to_string(s));
	}
};

extern delta_time_t<float> delta_time_;

} // namespace cap