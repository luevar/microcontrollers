#include <stdio.h>
#include "xtimer.h"
#include "timex.h"

#define INTERVAL (1U * US_PER_SEC)

int main(void) {
	xtimer_ticks32_t last_wakeup = xtimer_now();

	while(1) {
		xtimer_periodic_wakeup(&last_wakeup, INTERVAL);
		printf("Slept until %" PRIu32 "\n", xtimer_usec_from_ticks(xtimer_now()));
	}
	return 0;
}
