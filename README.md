# PicoLights

A dithering WS2812b (Neopixel) controller. One core handles the calculations for the dithering, the other core is free to create whatever animations you like. The pixels are pushed out with PIO.

The virtual bit depth is configurable. It's currently set to 12 which seems to work well with short-ish (under 100 pixel) strings.

This is very simplistic, and really just a demonstration of what Pico can do with PIO and dual core. A much more efficient version could easily drive significantly more strings of pixels. See the parallel example in pio-examples for more details on this.

# TODO
Add more colours -- currently blue only
