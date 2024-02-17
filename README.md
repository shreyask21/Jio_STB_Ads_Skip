# Jio Set Top Box Ad Skipper with Raspberry Pi Pico

This project enables you to skip ads that appear when the Jio Set Top Box boots up using a RP2040 microcontroller. By interfacing the Raspberry Pi Pico with the Jio Set Top Box, you can automate the process of skipping ads, providing a less annoying viewing experience.

## How it Works

The Raspberry Pi Pico emulates the USB Human Interface Device (HID) typically used by keyboards/mice etc. When the Jio Set Top Box boots up, it powers on the RP2040 and it sends HID keycodes to Jio STB. The HID Alt+Escape keycode is used to skip the ads, allowing the viewer to proceed directly to the home screen.

## Features

- Automatically skips boot time ads on Jio Set Top Box
- Cheap and cheerful
- Easy to deploy and modify

## Hardware Requirements

- Raspberry Pi Pico (or any other RP2040 based dev board)
- Micro USB cable

## Basic Usage

1. [Download the UF2 file from releases](https://github.com/shreyask21/Jio_STB_Ads_Skip/releases/latest) to your PC
2. Press and hold the boot button on the Raspberry Pi Pico and connect it with a micro USB cable to your PC.
3. Drag and drop the downloaded UF2 file onto the USB mass storage device.
4. Connect the RP2040 and the USB cable to backside USB ports of the Jio STB.

## Contributions

Contributions to this project are welcome! Feel free to submit bug reports, feature requests, or pull requests through GitHub.

## License

This project is licensed under the [MIT License](https://raw.githubusercontent.com/shreyask21/Jio_STB_Ads_Skip/main/LICENSE)
