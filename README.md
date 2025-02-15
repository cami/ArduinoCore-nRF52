# Arduino Core for CAMI sIoTamago on nRF52 Boards

This repository contains the Arduino BSP for nRF52840 series.
[![Build Status](https://github.com/adafruit/Adafruit_nRF52_Arduino/workflows/Build/badge.svg)](https://github.com/adafruit/Adafruit_nRF52_Arduino/actions)

This repository contains the Arduino BSP for Adafruit Bluefruit nRF52 series:

- [Adafruit CLUE nRF52840](https://www.adafruit.com/product/4500)
- [Adafruit Circuit Playground Bluefruit](https://www.adafruit.com/product/4333)
- [Adafruit Feather nRF52832](https://www.adafruit.com/product/3406)
- [Adafruit Feather nRF52840 Express](https://www.adafruit.com/product/4062)
- [Adafruit Feather nRF52840 Sense](https://www.adafruit.com/product/4516)
- [Adafruit ItsyBitsy nRF52840 Express](https://www.adafruit.com/product/4481)
- Adafruit Metro nRF52840 Express

Following boards are also included but are not officially supported:

- [Nordic nRF52840DK PCA10056](https://www.nordicsemi.com/Software-and-Tools/Development-Kits/nRF52840-DK)
- [Particle Xenon](https://store.particle.io/products/xenon)

## BSP Installation

There are two methods that you can use to install this BSP.

### Recommended: via Arduino Board Manager

 1. [Download and install the Arduino IDE](https://www.arduino.cc/en/Main/Software) (At least v1.6.12)
 2. Start the Arduino IDE
 3. Go into Preferences
 
 <img src="./docs/preferences.png" alt="preferences" title="preferences">
 
 4. Add `https://raw.githubusercontent.com/cami/cami.github.io/master/package_nectis_index.json` as an `Additional Board Manager URL`
 5. Restart the Arduino IDE
 6. Open the Boards Manager from the Tools -> Board menu and install `Nectis nRF52 by CAMI&Co.`

 <img src="./docs/additional_board_manager.png" alt="additional_board_manager" title="additional_board_manager">
 
 7. Once the BSP is installed, select `CAMI qibanca nectis series on nRF52840` from the Tools -> Board menu, which will update your system config to use the right compiler and settings for the nRF52.

### Optional (Core Development): via git

 1. Install BSP via Board Manager as above to install `compiler & tools`.
 2. Delete the core folder `nrf52` installed by Board Manager in Adruino15, depending on your OS. It could be
  * macOS  : `~/Library/Arduino15/packages/cami_arduino/hardware/nrf52`
  * Linux  : `~/.arduino15/packages/cami_arduino/hardware/nrf52`
  * Windows: `%APPDATA%\Local\Arduino15\packages\cami_arduino\hardware\nrf52`
 3. `cd <SKETCHBOOK>`, where `<SKETCHBOOK>` is your Arduino Sketch folder:
  * macOS  : `~/Documents/Arduino`
  * Linux  : `~/Arduino`
  * Windows: `Documents/Arduino`
 4. Create a folder named `hardware/cami`, if it does not exist, and change directories to it
 5. Clone this repo: `git clone --recursive git@github.com:cami/ArduinoCore-nRF52.git`
 6. Restart the Arduino IDE
 7. Once the BSP is installed, select `CAMI qibanca nectis series on nRF52840` from the Tools -> Board menu, which will update your system config to use the right compiler and settings for the nRF52.

### Adafruit's nrfutil tools

[adafruit-nrfutil](https://github.com/adafruit/Adafruit_nRF52_nrfutil) (derived from Nordic pc-nrfutil) is needed to upload sketch via serial port.

- For Windows and macOS, pre-built executable binaries are included in the BSP at `tools/adafruit-nrfutil/`. It should work out of the box.
- Linux user need to run follow command to install it from PyPi

```
$ pip3 install adafruit-nrfutil --user
```

### Drivers

- [SiLabs CP2104 driver](http://www.silabs.com/products/mcu/pages/usbtouartbridgevcpdrivers.aspx) is required for USB to Serial when using with Feather nRF52832

## Bootloader Support

### Upgrade existing Bootloader

Bluefruit's Bootloader is self-upgradable, you could upgrade to the latest Bootloader + Softdevice using the serial port within Arduino IDE.

- Select `Tools > Board > CAMI qibanca nectis series on nRF52840`
- Select `Tools > Programmer > STABLE J-Link for qibanca nectis on nRF52`
- Select `Tools > Burn Bootloader`
- **WAIT** until the process complete ~30 seconds

**Note: close the Serial Monitor before you click "Burn Bootloader". Afterwards, you shouldn't close the Arduino IDE, unplug the Feather, launch Serial Monitor etc ... to abort the process. There is a high chance it will brick your device! Do this with care and caution.**

### Burning new Bootloader

To burn the bootloader from within the Arduino IDE, you will need the following tools installed
on your system and available in the system path:

- Segger [JLink Software and Documentation Pack](https://www.segger.com/downloads/jlink)
- Nordic [nRF5x Command Line Tools](https://www.nordicsemi.com/Software-and-Tools/Development-Tools/nRF-Command-Line-Tools)

Check to make sure you can run `nrfjprog` from your terminal/command prompt

**macOS Note** At present, you will need to create a symlink in `/usr/local/bin` to the
`nrfjprog` tool wherever you have added it. You can run the following command, for example:

```
$ ln -s $HOME/prog/nordic/nrfjprog/nrfjprog /usr/local/bin/nrfjprog
```

Once the tools above have been installed and added to your system path, from the Arduino IDE:

- Select `Tools > Board > CAMI qibanca nectis series on nRF52840`
- Select `Tools > Programmer > J-Link for qibanca nectis series on nRF52`
- Select `Tools > Burn Bootloader` with the board and J-Link connected

If you wish to modify bootloader to your own need, check out its repo here [Adafruit_nRF52_Bootloader](https://github.com/adafruit/Adafruit_nRF52_Bootloader)

#### Manually Burning the Bootloader via nrfjprog

The bootloader hex file can be found at `bin/bootloader` run the command as follows:

```
$ nrfjprog --eraseall
$ nrfjprog --chiperase --program nectis_nrf52840_bootloader-6.2.0_s140_6.1.1.hex -f NRF52 -r
```

## Credits

This core is based on [ArduinoCore-nRF52](https://github.com/cami/ArduinoCore-nRF52/tree/7c9438c3149020b8887848a8d03d551302e86904) by Adafruit.
This core is based on [Arduino-nRF5](https://github.com/sandeepmistry/arduino-nRF5) by Sandeep Mistry,
which in turn is based on the [Arduino SAMD Core](https://github.com/arduino/ArduinoCore-samd).

The following libraries are used:

- adafruit-nrfutil is based on Nordic Semiconductor ASA's [pc-nrfutil](https://github.com/NordicSemiconductor/pc-nrfutil)
- [freeRTOS](https://www.freertos.org/) as operating system
- [tinyusb](https://github.com/hathach/tinyusb) as usb stack
- [nrfx](https://github.com/NordicSemiconductor/nrfx) for peripherals driver
- [littlefs](https://github.com/ARMmbed/littlefs) for internal file system
