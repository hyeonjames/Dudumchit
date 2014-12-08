#include "TIMER3.h"

unsigned volatile char TIMER3_tick;

unsigned int TIMER3_current_frame;

SIGNAL(SIG_OUTPUT_COMPARE3A)
{
	++TIMER3_tick;
}
