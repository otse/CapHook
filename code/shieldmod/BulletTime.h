/*
 * ShieldMod file
 * 
 * Tse Ojeng
 */

#ifndef shieldmod_bullet_time_h
#define shieldmod_bullet_time_h

#include "ShieldMod.h"

namespace shieldmod
{
extern bool bt_draw_;
extern bool show_hourglass_;

typedef void Void;
Void Bt_In();
Void Bt_Out();
Void Bt_Toggle();
Void Bt_Frame();
Void Bt_Draw();

struct til_t;
extern til_t til;

struct til_t
{
	bool til = false;

	float in = 0;
	float out = 0;
	float in_s = 2;
	float out_s = 2;

	float Get()
	{
		float fade = -1;

		if (in > 0)
		{
			in -= delta_time_.s / in_s;
			if (in <= 1)
				fade = 1 - in;
			if (in <= 0)
			{
				fade = 1;
				in = 0;
				if (out_s)
					out = -out;
			}
		}
		else if (out > 0)
		{
			fade = 1;
			out -= delta_time_.s / out_s;
			if (out <= 1)
				fade = out;
			if (out <= 0)
			{
				fade = 0;
				out = 0;
			}
		}

		return fade;
	;

};
}; // namespace shieldmod

#endif