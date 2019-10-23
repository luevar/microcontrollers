#include <stdio.h>
#include "periph/gpio.h"
#include "xtimer.h"
#include "board.h"
#define INTERVAL (1U * US_PER_SEC)

uint32_t last_button_press;

static void btn_handler(void *arg) {
    (void)arg;
    uint32_t current_time = xtimer_usec_from_ticks(xtimer_now());
    if (current_time > last_button_press + INTERVAL/3) {
        gpio_toggle(GPIO_PIN(PORT_A, 1));
        puts("Hello World!");
        //gpio_toggle(LED1_PIN);
        last_button_press = current_time;
    } 
}

int main(void) {
    gpio_init(GPIO_PIN(PORT_A, 1),GPIO_OUT);
    //gpio_init(LED1_PIN,GPIO_OUT);
    gpio_init_int(GPIO_PIN(PORT_A, 4), GPIO_IN_PU, GPIO_FALLING, btn_handler, NULL);
    return 0;
}
