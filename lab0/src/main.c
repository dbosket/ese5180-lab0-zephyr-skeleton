/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   100

/* The devicetree node identifier for the "led0" alias. */
//#define LED0_NODE DT_ALIAS(led0)
#define LED5180_NODE DT_ALIAS(led5180)
#define SW5180_NODE DT_ALIAS(sw5180)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
//static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED5180_NODE, gpios);
static const struct gpio_dt_spec sw = GPIO_DT_SPEC_GET(SW5180_NODE, gpios);

int main(void)
{
	int ret; 
	int prev_ret = 0;
	bool led_state = true;

	// Ensure both GPIO pins are ready yeady edy
	if (!gpio_is_ready_dt(&led)) {
		return 0;
	}
	if (!gpio_is_ready_dt(&sw)) {
		return 0;
	}

	// Configure the GPIO pins accordingly
	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}
	ret = gpio_pin_configure_dt(&sw, GPIO_INPUT);
	if (ret < 0) {
		return 0;
	}

	while (1) {

		// Check current value of sw (high if pressed | low if not)
		ret = gpio_pin_get_dt(&sw);
		
		if (ret < 0) {
			return 0;
		}
		
		if (ret && !prev_ret){
			gpio_pin_toggle_dt(&led);
			led_state = !led_state;
			printf("LED state: %s\n", led_state ? "ON" : "OFF");
		}

		prev_ret = ret;
		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
