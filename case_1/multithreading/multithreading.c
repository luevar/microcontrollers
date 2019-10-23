#include <stdio.h>
#include <string.h>
#include "periph/gpio.h"
#include "xtimer.h"
#include "thread.h"

#define INTERVAL (1U * US_PER_SEC)

uint32_t last_button_press;
char stack[THREAD_STACKSIZE_MAIN];

static void btn_handler(void *arg) {
    (void)arg;
    uint32_t current_time = xtimer_usec_from_ticks(xtimer_now());
    if (current_time > last_button_press + INTERVAL/3) {
        gpio_toggle(GPIO_PIN(PORT_A, 2));
        last_button_press = current_time;
    } 
}

void *thread_handler(void *arg) {
    (void) arg;
    gpio_init_int(GPIO_PIN(PORT_A, 4), GPIO_IN_PU, GPIO_FALLING, btn_handler, NULL);
    return NULL;
}

int main(void) {
    gpio_init(GPIO_PIN(PORT_A, 1), GPIO_OUT);
    gpio_init(GPIO_PIN(PORT_A, 2), GPIO_OUT);

    thread_create(stack, sizeof(stack),
        THREAD_PRIORITY_MAIN - 1,
        THREAD_CREATE_STACKTEST,
        thread_handler,
        NULL, "blink");

    xtimer_ticks32_t last_wakeup = xtimer_now();
    while(1) {
        xtimer_periodic_wakeup(&last_wakeup, INTERVAL * 3);
        gpio_toggle(GPIO_PIN(PORT_A, 1));
    }
    return 0;
}
