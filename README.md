# Super Mario Odyssey - Visible Hit-Sensors

Please note that the custom models do not work on console yet! 

This mod allows you to see Mario and Cappy's `HitSensors`, or hit boxes, during gameplay, as well as their positions, marked with a purple coin. 
In order for this to show anything, you'll have to edit your own stage to add in `Coin` objects with the following names (in UnitConfig -> DisplayName):

`pos`
`head`
`body`
`foot`
`capPos`
`Trample`
`SpiralTail1`
`SpiralTail2`
`SpiralTail3`
`SpiralTail4`
`SpiralTail5`

Both `pos` and `capPos` should have a model name of `CoinPink`, while everything else should have a model name of `HitSensor`. An example of these objects is in the included `romfs` folder, in `CapWorldHomeStageMap.szs`, Scenario 3 (post-moon rock).

You can toggle the visibility of Mario and Cappy by holding ZL and pressing ZR. 

A known issue currently is that if one of the objects goes too far offscreen, it will unload. A fix is currently being worked on.

## Prerequisites

- [devkitPro](https://devkitpro.org/) 
- Python 3
- The [Keystone-Engine](https://www.keystone-engine.org/) Python Module

## Building

Build has only been tested on WSL2 running Ubuntu 20.04.1.

Just run:
```
DEVKITPRO={path_to_devkitpro} make
```

On Ubuntu (and other Debian-based systems), devkitPro will be installed to `/opt/devkitpro` by default:

```
DEVKITPRO=/opt/devkitpro/ make
```

## Installing (Atmosphère)

After a successful build, simply transfer the `atmosphere` folder located inside `starlight_patch_100` to the root of your switch's SD card.

---

# Credits
- [OdysseyDecomp](https://github.com/shibbo/OdysseyDecomp)
- [OdysseyReversed](https://github.com/shibbo/OdysseyReversed)
- [open-ead](https://github.com/open-ead/sead) sead Headers
- [Bryce](https://github.com/brycewithfiveunderscores/Starlight-SMO-Example/) Original Starlight fork for SMO
- [CraftyBoss](https://github.com/CraftyBoss/Starlight-SMO-LayoutEditing) Basis of this project

# Starlight (Original README)
An enviroment for linking to Splatoon 2 executable and implementing hooks.

# Starlight Contributors
- [3096](https://github.com/3096)
- [khang06](https://github.com/khang06)
- [OatmealDome](https://github.com/OatmealDome)
- [Random0666](https://github.com/random0666)
- [shadowninja108](https://github.com/shadowninja108)
- [shibbo](https://github.com/shibbo) - Repo based on their work on OdysseyReversed
- [Thog](https://github.com/Thog) - Expertise in how rtld is implemented

# Starlight Credits
- devkitA64
- libnx - switch build rules
