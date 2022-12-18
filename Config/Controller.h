/*
			 LUFA Library
	 Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
		   www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#ifndef _CONFIG_CONTROLLER_H_
#define _CONFIG_CONTROLLER_H_

/* Includes: */
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>

#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Drivers/Board/Joystick.h>
#include <LUFA/Drivers/Board/LEDs.h>
#include <LUFA/Drivers/Board/Buttons.h>
#include <LUFA/Platform/Platform.h>

#include "Descriptors.h"
#include "Delays.h"
#include "Config.h"

// Type Defines
// Enumeration for buttons.
typedef enum
{
	BUTTON_Y = 0x01,
	BUTTON_B = 0x02,
	BUTTON_A = 0x04,
	BUTTON_X = 0x08,
	BUTTON_L = 0x10,
	BUTTON_R = 0x20,
	BUTTON_ZL = 0x40,
	BUTTON_ZR = 0x80,
	BUTTON_MINUS = 0x100,
	BUTTON_PLUS = 0x200,
	BUTTON_LCLICK = 0x400,
	BUTTON_RCLICK = 0x800,
	BUTTON_HOME = 0x1000,
	BUTTON_CAPTURE = 0x2000,
} Buttons_t;

#define DPAD_UP 0x00
#define DPAD_UP_RIGHT 0x01
#define DPAD_RIGHT 0x02
#define DPAD_DOWN_RIGHT 0x03
#define DPAD_DOWN 0x04
#define DPAD_DOWN_LEFT 0x05
#define DPAD_LEFT 0x06
#define DPAD_UP_LEFT 0x07
#define DPAD_NONE 0x08

#define STICK_MIN 0
#define STICK_CENTER 128
#define STICK_MAX 255

// Joystick HID report structure. We have an input and an output.
typedef struct
{
	uint16_t Button; // 16 buttons; see JoystickButtons_t for bit mapping
	uint8_t DPAD;	 // HAT switch; one nibble w/ unused nibble
	uint8_t LX;		 // Left  Stick X
	uint8_t LY;		 // Left  Stick Y
	uint8_t RX;		 // Right Stick X
	uint8_t RY;		 // Right Stick Y
	uint8_t VendorSpec;
} USB_ControllerReport_Input_t;

// The output is structured as a mirror of the input.
// This is based on initial observations of the Pokken Controller.
typedef struct
{
	uint16_t Button; // 16 buttons; see JoystickButtons_t for bit mapping
	uint8_t DPAD;	 // HAT switch; one nibble w/ unused nibble
	uint8_t LX;		 // Left  Stick X
	uint8_t LY;		 // Left  Stick Y
	uint8_t RX;		 // Right Stick X
	uint8_t RY;		 // Right Stick Y
} USB_ControllerReport_Output_t;

// Function Prototypes
// Setup all necessary hardware, including USB initialization.
void SetupHardware(void);

// USB device event handlers.
void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_Disconnect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_ControlRequest(void);

void controller_press_button(uint16_t button);
void controller_release_button(uint16_t button);
void controller_wait(uint16_t duration);

void controller_set_dpad(uint8_t dpad);

void controller_set_stick_position_l(uint8_t x, uint8_t y);
void controller_set_stick_position_r(uint8_t x, uint8_t y);

void connect_and_return_to_home(void);

void controller_press_and_release_button(uint16_t button, uint16_t duration, uint16_t release);
void controller_press_and_release_dpad(uint8_t dpad, uint16_t duration, uint16_t release);
void controller_move_and_release_stick_l(uint8_t x, uint8_t y, uint16_t duration, uint16_t release);
void controller_move_and_release_stick_r(uint8_t x, uint8_t y, uint16_t duration, uint16_t release);

void controller_init(void);



#endif
