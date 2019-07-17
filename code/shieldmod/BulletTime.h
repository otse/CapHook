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

	typedef void Bt;

	Bt BtIn();
	Bt BtOut();
	Bt BtToggle();
	Bt BtFrame();
	Bt BtDraw();

	// Bullet Time Bar

	struct Bar;
	extern Bar bar;

	struct Bar
	{
		bool full = false;

		float in = 0;
		float out = 0;
		float in_s = 2;
		float out_s = 2;

		float Get()
		{
			float fade = 0;

			if (in > 0)
			{
				in -= delta_time_.s / in_s;
				if (in <= 1)
					fade = 1 - in;
				if (in <= 0)
				{
					fade = 1;
					in = 0;
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
			else
				fade = -1;

			return fade;
		}
	};
}

#endif