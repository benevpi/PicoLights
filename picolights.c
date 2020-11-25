/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
#include "pico/multicore.h"

#define STRING_LEN 32

int bit_depth=12;
const int PIN_TX = 1;

uint32_t pixels[STRING_LEN];
uint32_t errors[STRING_LEN];

static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
            ((uint32_t) (r) << 8) |
            ((uint32_t) (g) << 16) |
            (uint32_t) (b);
}

void ws2812b_core() {
	int value;
	int shift = bit_depth-8;
	
    while (1){
		//let's keep this simple and just do it all white will have to be a bit more careful about the timings when doing RGB
		/**
		for(int i=0; i<STRING_LEN; i++) {
			value=(pixels[i] + errors[i]) >> shift;
			put_pixel(urgb_u32(0, 0, value));
			errors[i] = (pixels[i] + errors[i]) - (value << shift); // is this correct?
		}
		**/
		for(int i=0; i<STRING_LEN; i++) {
			value=(pixels[i] + errors[i]) >> shift;
			//printf("pixels[i] = %d", pixels[i]);
			put_pixel(urgb_u32(0, 0, value));
			errors[i] = (pixels[i] + errors[i]) - (value << shift); // is this correct?
		}
		sleep_us(400);
	}
}	
		


int main() {
	
	setup_default_uart();
	
	PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, PIN_TX, 800000, false);
	
	for(int i=0; i< STRING_LEN; ++i) {
		pixels[i]=0;
	}
 
	multicore_launch_core1(ws2812b_core);
   
    while (1) {
        for (int i = 0; i < 30; ++i) {
			
			pixels[i] = i;
			
			for (int j=0;j<100;++j){
				pixels[0] = j;
				if(j%8 == 0) { pixels[1] = j; }
				sleep_ms(50);
			}
			for (int j=100;j>0;--j){
				pixels[0] = j;
				if(j%8 == 0) { pixels[1] = j; }
				sleep_ms(50);
			}
        }
    }
}
