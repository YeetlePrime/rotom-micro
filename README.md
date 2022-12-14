## rotom-micro

A small framework for automatic Nintendo Switch games (mainly Pokémon) by emulating a Nintendo Switch Pro Controller.

---
### How To Use

First of, there are some more things needed to get the setup up and running.

#### Microcontroller

Currently this project was only tested on the [Pro Micro](https://www.amazon.de/DUBEUYEW-Atmega32U4-Bootloadered-Development-Mikrocontroller/dp/B0B7KXZN1D/ref=sr_1_1_sspa?__mk_de_DE=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=XSKYONIBCY6Q&keywords=pro+micro&qid=1671047714&sprefix=pro+micro%2Caps%2C218&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1).  
The "Teensy2.0", "Teensy2.0++", "Arduino Leonardo" and "Arduino UNO R3" should work fine too.

#### Compiler

The avr-gcc compiler is needed, in order to generate a .hex file from the source code.  
I use the linux release of avr-gcc on WSL (Windows subsystem for linux). Any other release should work aswell, but may be used a little differently.  
For Linux or WSL you can use:
```
sudo apt-get install gcc-avr binutils-avr avr-libc
```
to install the avr-gcc toolchain.

#### make

You need "make" to use the makefile for compilation.  
For Linux or WSL you can use:
```
sudo apt install make
```
to install it.

#### AVRDUDE or QMK Toolbox

If you run windows, you can use the QMK Toolbox to upload the .hex file to the microcontroller.  
You can find it [here](https://github.com/qmk/qmk_toolbox/releases). Just download "qmk_toolbox.exe".

#### Recommended setup for Windows

- WSL (Ubuntu 20.04)
- Windows Terminal
- avr-gcc (on WSL)
- make (on WSL)
- QMK Toolbox


---
### Compatibility

This software was only tested on the "Pro-Micro". The "Arduino Leonardo", "Arduino UNO R3" and "Teensy 2.0/Teensy 2.0++" should work aswell.
Don't forget to change the MCU type ine the makefile tho.

---
### LICENSE

This project is licensed by the MIT LICENSE.
It uses the LUFA library for USB communication, so the LUFA LICENSE has to be accounted for aswell, when redistributing parts of it.

---
### Inspiration

This project builds on [bertrandom's snowball-thrower project](https://github.com/bertrandom/snowball-thrower).  
So thanks to him for making it publicly available.  
His project is based on [progmem's switch-fightstick project](https://github.com/progmem/Switch-Fightstick).
