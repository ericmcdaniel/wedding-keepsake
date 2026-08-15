# Wedding Keychain Keepsake

This is the full schematic, design, plans, and source code for the interactive RGB LED keepsake gadget from Eric and Stephie's wedding on Saturday August 15th 2026. These PCBs are attached to a keychain and were distributed to guests as keepsake party favors. The keychain displays a bright grid of LED lights and features simple animations and games.

# Modes

When powered on, the keychain begins in either one of two modes: Animation mode and Game mode. Press and Hold the button for one second to switch between Animation and Game modes.

### Animation Mode

The keychain displays an animation from the selection below. Single-press the button to cycle between the following animations.
* Tunnel
* Swipe
* Rainbow
* American Flag
* Candle

### Game Mode

As of this writing, the keychain only offers one game named *Dodge*. Dodge is a space-themed endless runner arcade survival game. You are piloting a space shuttle, traveling through the solar system. You encouter space debris, and must evade them before they collide into you.

Single-press the button to steer your rocket in the opposite direction to dodge obstacles. Survive as long as you can, even as you accelerate through the debris at progressively faster rates.

# Bill of Materials

* 32 acrylic-diffused RGB LEDs, arranged in an 8x4 matrix.
* ~~A MEMS microphone and op-amp for simple audio sampling (no FFT).~~
  * This idea was included in the design and was manufactured. The idea was to create additional audio-reactive (and interactive) modes like animations for decibel and music analyzers, but development time exceeded my delivery timeline. This will be revisited later in future updates.
* Animations can be cycled and games that can be played using the single tactile push button.
* Controlled by the AVR-based ATtiny1614 manufactured by *Microchip Technology*.
* Powered by a 24mm x 5mm CR2450 coin cell battery.
* On an 80mm x 30mm PCB with a D-hook clasp and snake keychain.
* Placed inside a custom-made sled enclosure with snap-fit sliding lid.

# Design

## 3D Rendering
![Front side of the PCB](./hardware/pcb/images/pcb-3d-render-front.png)
<p align="center"><i>Front side of the PCB</i></p>

![Back side of the PCB](./hardware/pcb/images/pcb-3d-render-back.png)
<p align="center"><i>Back side of the PCB</i></p>

## Electrical Schematic
![Electrical Schematic](./hardware/pcb/images/keepsake-keychain.jpg)

## PCB Layout
![Layer 1 of PCB Design](./hardware/pcb/images/pcb-design-L1.png)
<p align="center"><i>Layer 1 of the PCB (signals/components)</i></p>

![Layer 2 of PCB Design](./hardware/pcb/images/pcb-design-L2.png)
<p align="center"><i>Layer 2 of the PCB (GND)</i><p>

![Layer 3 of PCB Design](./hardware/pcb/images/pcb-design-L3.png)
<p align="center"><i>Layer 3 of the PCB (3V3 copper pour)</i><p>

![Layer 4 of PCB Design](./hardware/pcb/images/pcb-design-L4.png)
<p align="center"><i>Layer 4 of the PCB (Additional signals/components)</i><p>

# Details

### Architecture and Engine

This repository was built using the toolkits provided by PlatformIO. It is based on the Arduino framework, though quite minimally. An RTOS is not used, fairly bare metal in terms of architecture. To keep things as efficient as possible, abstractions that Arduino provides like `digitalWrite()` were replaced with direct register manipulations, especially duirng hot execution paths. Most notably it is used during the LED rendering logic, which renders each row sequentially for 50 microseconds, creating a multiplexed effect on the display, as if all the LEDs were on simutaneously. The main reason that the Arduino framework is still used is because of the timers.

Internally, this repo was built on top of the custom game engine used in the [LumenLab](https://github.com/ericmcdaniel/lumenlab), with a handful of adaptations. This includes the platform-level core services, the engine, and general architecture from the LumenLab. This repo implements multiplexing manually, so libraries like FastLED used in the LumenLab could not be used. The keychain runs the main game loop at 60 Hz. Between each frame, the engine multiplexes each row at a frequency of 20 kHz (50 microseconds). Between each row rendering, three shift registers designated to the red, green, and blue channels take in a serial stream of bits to indicate if the respective color's LED should be on. If it's signal LOW, the LED turns on, and if signal HIGH then off. (this is in reverse because the MOSFETS are active HIGH).

Pulse-width modulation (PWM) is needed to dim the three primary colors, allowing for any arbitrary color can be made via blending. This was implemented using [bit-angle modulation (BAM)](https://www.desertember.com/posts/bit-angle-modulation.html) to determine the duty cycle. That was a headache, almost literally, because given large time values, the PWM's duty cycle would be so spread your eyes would noticably see the flicker. The color depth was reduced to 6-bit. The flicker isn't fully removed, but it's significantly better. Brightness and gamma correction was implemented, but disabled because adjustmenets is needed (again, mostly due to the noticable PWM flicker).


### Audio profiling (not implemented)

A MEMS microphone and amplifier was a part of the keychain's goal and is still a part of the design and schematic. The idea was realistic to implement, but was bound by an ambitious timeline, so I had to pause development that for now. The microphone still remains on the PCB since they were already manufactured (center-right). This gives me the opportunity to simply suspend working on the audio-reactive features rather than cancel entirely.

The idea for this keychain was to include audio reactivity, which would complement the already interactive animations. Running a full spectrum analyzer was not possible given the microcontroller selected, power constraints, and technical limitations like the inability to timely perform computationally heavy Fast-Fourier Transformations (FFT). So to be clear, it is too low-powered/low-budget to record conversation. Instead, the device was going to sample decibel levels in real time and display a sound-reactive bar, like the EQ on a stereo system. Another idea I had for the built-in microphone was to make the devices react to the wedding reception music live in real time. Between songs, I could have my computer play a swift, 20+ kHz logic signal at the before every song. This high-frequency chirp wouldn't be heard by humans, but detected by this keychain. It would then decode the message, and play an animation or color theme dynamically, as if it's listening to the music and dancing along.

These were two ideas that have artifacts on the board, but were not implemented.

# Development

### Software

The keychain is programmable using the UPDI protocol, which is the newer version of AVR's ISP and JTAG programming. The UPDI (PA0, pin 10) is exposed on a THT test pad, along with 3V3 and GND. To program the device, you need a $7 module called the UPDI Friend - USB Serial UPDI Programmer from [Adafruit](https://www.adafruit.com/product/5879) or [Digikey](https://www.digikey.com/en/products/detail/adafruit-industries-llc/5879/22596413). Releases are provided every PR and can be flashed directly. I'll write instructions to directly flash the device later (hopefully), and possibly even dockerize it for simplicity. Until then, the easiest way to update is to install the PlatformIO toolkit, compile this repo locally, and flash using the *PlatformIO: Upload (Release)* build script included.

In addition to the UPDI pin, PB2 (pin 7) and PB3 (pin 6) are mapped to TX and RX respectively. Because they were unused, these pins are exposed as SMD test pads. This allows you to probe TX (PB2) to read the serial logs, if you compiled the debug version.

### Hardware

The PCB design files were made using KiCad 9.0.5. The board layout was optimized for the manufacturing capabilities of [PCBWay](https://www.pcbway.com/). Before you start writing me hate mail, know that I'm aware of the issues, such as the lack of ESD protection and reverse polarity protection. Perhaps a future revision can include these, but I have no such plans.

The enclosure was made using FreeCAD 1.1.0. They also suck, but I tried. The models were also exported as .3mf files, and were optimized for immediate FDM printing, particularly the Bambu Labs A1 Combo. Feel free to adjust as needed for your machine. The model includes a sled enclosure which retains the PCB using four friction fit ribs. A lid is attached by sliding it along the guide rails from left to right. A snap-fit latch locks the lid in place, preventing it from falling off. I printed this using Bambu Lab's PLA Basic, however given the variance between 3D printers, brands, filament, and other conditions, your mileage may vary.

## AI Disclaimer

AI was consulted as a research and discovery analysis tool. I asked it general design, architecture, and best practices questions, especially during the board bring-up stage. I don't have a professional background in electrical engineering (is YouTube University accredited?), so I used it as a an informational resource. 

*Generative* AI, however, was **not** used to author code. Call me a luddite, but this is out of priniciple. Software engineering is an art as it is a science. Cheers to all the other crazies out there!