# PicoLights

A dithering WS2812b (Neopixel) controller. One core handles the calculations for the dithering, the other core is free to create whatever animations you like. The pixels are pushed out with PIO.

The virtual bit depth is configurable. It's currently set to 12 which seems to work well with short-ish (under 100 pixel) strings.

This is very simplistic, and really just a demonstration of what Pico can do with PIO and dual core. A much more efficient version could easily drive significantly more strings of pixels. See the parallel example in pio-examples for more details on this.

The initial version fades in reg, green, blue and white showing both their dithered and non-dithered brightnesses. Just use the while(1) loop in main to add whatever animations you like and they'll be picked up automatically.

# Wiring
Connect Vin to VBUS, GND to GND and Data In to GPIO 1 (note NOT 0)
