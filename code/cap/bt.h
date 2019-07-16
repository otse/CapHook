#pragma once

#include "cap_1.h"

namespace cap
{
	extern bool bt_draw_;
	extern bool show_hourglass_;
    
    typedef void Void;
    Void Bt_In();
    Void Bt_Out();
    Void Bt_Toggle();
    Void Bt_Frame();
    Void Bt_Draw();

	struct til_t
	{
		bool til = false;
		float in = 0, out = 0, in_s = 2, out_s = 2;
	};

	extern til_t til;
}