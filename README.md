# `colr`: a Pebble Time watchface

![](https://github.com/TheBlackParrot/pebble-time-watchface-colr/blob/master/screenshots/wf1.png?raw=true)![](https://github.com/TheBlackParrot/pebble-time-watchface-colr/blob/master/screenshots/wf2.png?raw=true)![](https://github.com/TheBlackParrot/pebble-time-watchface-colr/blob/master/screenshots/wf3.png?raw=true)![](https://github.com/TheBlackParrot/pebble-time-watchface-colr/blob/master/screenshots/wf4.png?raw=true)![](https://github.com/TheBlackParrot/pebble-time-watchface-colr/blob/master/screenshots/wf5.png?raw=true)![](https://github.com/TheBlackParrot/pebble-time-watchface-colr/blob/master/screenshots/wf6.png?raw=true)![](https://github.com/TheBlackParrot/pebble-time-watchface-colr/blob/master/screenshots/wf7.png?raw=true)![](https://github.com/TheBlackParrot/pebble-time-watchface-colr/blob/master/screenshots/wf8.png?raw=true)![](https://github.com/TheBlackParrot/pebble-time-watchface-colr/blob/master/screenshots/wf9.png?raw=true)![](https://github.com/TheBlackParrot/pebble-time-watchface-colr/blob/master/screenshots/wf10.png?raw=true)![](https://github.com/TheBlackParrot/pebble-time-watchface-colr/blob/master/screenshots/wf11.png?raw=true)![](https://github.com/TheBlackParrot/pebble-time-watchface-colr/blob/master/screenshots/wf12.png?raw=true)![](https://github.com/TheBlackParrot/pebble-time-watchface-colr/blob/master/screenshots/wf13.png?raw=true)![](https://github.com/TheBlackParrot/pebble-time-watchface-colr/blob/master/screenshots/wf14.png?raw=true)![](https://github.com/TheBlackParrot/pebble-time-watchface-colr/blob/master/screenshots/wf15.png?raw=true)![](https://github.com/TheBlackParrot/pebble-time-watchface-colr/blob/master/screenshots/wf16.png?raw=true)![](https://github.com/TheBlackParrot/pebble-time-watchface-colr/blob/master/screenshots/wf17.png?raw=true)![](https://github.com/TheBlackParrot/pebble-time-watchface-colr/blob/master/screenshots/wf18.png?raw=true)![](https://github.com/TheBlackParrot/pebble-time-watchface-colr/blob/master/screenshots/wf19.png?raw=true)![](https://github.com/TheBlackParrot/pebble-time-watchface-colr/blob/master/screenshots/wf20.png?raw=true)

## Building/installing
```
git clone https://github.com/TheBlackParrot/pebble-time-watchface-colr.git
cd pebble-time-watchface-colr

export PEBBLE_PHONE=192.168.x.x

pebble build
pebble install
```

## Configuring
All configuration is done upon building.

Gradients can be added/removed as long as `COLOR_PALETTES` is updated to reflect modifications. [for a list of colors the Pebble Time supports, head to the Color Picker Tool on the Pebble SDK documentation](https://developer.pebble.com/guides/tools-and-resources/color-picker/)  
Number drawing can be changed by toggling booleans in the `colors` array.  
Dark/light numbers can be toggled by modifiying the `is_dark` array.

#### Disclaimer
I don't know C well at all, so the code is probably incredibly shoddy. :(