/*
 * ShieldMod file
 * 
 * Tse Ojeng
 */

#ifndef shieldmod_delta_time_h
#define shieldmod_delta_time_h

#include <chrono>

using namespace std::chrono;
using namespace std::chrono_literals; // ?

namespace shieldmod
{
template <typename T>
struct Dt
{
	T s;
	nanoseconds d;
	high_resolution_clock::time_point a, b;
	void Tick()
	{
		a = high_resolution_clock::now();
		d = a - b;
		s = d.count() / 1000000000.f;
		b = a;
	}
};

extern Dt<float> delta_time_;

} // namespace shieldmod

#endif