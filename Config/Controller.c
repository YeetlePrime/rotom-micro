/*
			 LUFA Library
	 Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
		   www.lufa-lib.org
*/

/*
MIT License
Copyright 2022 YeetlePrime

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS 
OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "Controller.h"

USB_ControllerReport_Input_t InputReport;
int readyToSendInput = 0;

// Configures hardware
void SetupHardware(void)
{
    // Disable watchdog
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    // configure 8-bit timer:            ↓ timer counter
    // rate for 16MHz -> (16000000/256)/256 ~ 244Hz Timer frequency
    //                              ↑ prescaler
    TCCR0B |= (1 << CS02);  // prescaler 256
    TIMSK0 |= (1 << TOIE0); // overflow interrupt

    DDRB |= 1; // RXLED on output mode

    // init controller
    controller_init();

    // init USB stack
    USB_Init();
}

// Fired to indicate that the device is enumerating.
void EVENT_USB_Device_Connect(void)
{
    // We can indicate that we're enumerating here (via status LEDs, sound, etc.).
}

// Fired to indicate that the device is no longer connected to a host.
void EVENT_USB_Device_Disconnect(void)
{
    // We can indicate that our device is not ready (via status LEDs, sound, etc.).
}

// Fired when the host set the current configuration of the USB device after enumeration.
void EVENT_USB_Device_ConfigurationChanged(void)
{
    bool ConfigSuccess = true;

    // We setup the HID report endpoints.
    ConfigSuccess &= Endpoint_ConfigureEndpoint(CONTROLLER_OUT_EPADDR, EP_TYPE_INTERRUPT, CONTROLLER_EPSIZE, 1);
    ConfigSuccess &= Endpoint_ConfigureEndpoint(CONTROLLER_IN_EPADDR, EP_TYPE_INTERRUPT, CONTROLLER_EPSIZE, 1);

    // We can read ConfigSuccess to indicate a success or failure at this point.
}

// Process control requests sent to the device from the USB host.
void EVENT_USB_Device_ControlRequest(void)
{
    // We can handle two control requests: a GetReport and a SetReport.

    // Not used here, it looks like we don't receive control request from the Switch.
}

// set "button" bit to 1
void controller_press_button(uint16_t button)
{
    InputReport.Button |= button;
}

// set "button" bit to 0
void controller_release_button(uint16_t button)
{
    InputReport.Button &= ~button;
}

// transmit the current inputreport for "duration" ticks
void controller_wait(uint16_t duration)
{
    int i = 0;
    while (i < duration)
    {
        if (USB_DeviceState == DEVICE_STATE_Configured)
        {

            // We'll start with the OUT endpoint.
            Endpoint_SelectEndpoint(CONTROLLER_OUT_EPADDR);
            // We'll check to see if we received something on the OUT endpoint.
            if (Endpoint_IsOUTReceived())
            {
                // If we did, and the packet has data, we'll react to it.
                if (Endpoint_IsReadWriteAllowed())
                {
                    // We'll create a place to store our data received from the host.
                    USB_ControllerReport_Output_t OutputReport;
                    // We'll then take in that data, setting it up in our storage.
                    while (Endpoint_Read_Stream_LE(&OutputReport, sizeof(OutputReport), NULL) != ENDPOINT_RWSTREAM_NoError)
                        ;
                    // At this point, we can react to this data.

                    // However, since we're not doing anything with this data, we abandon it.
                }
                // Regardless of whether we reacted to the data, we acknowledge an OUT packet on this endpoint.
                Endpoint_ClearOUT();
            }

            // We'll then move on to the IN endpoint.
            Endpoint_SelectEndpoint(CONTROLLER_IN_EPADDR);
            // We first check to see if the host is ready to accept data.
            if (Endpoint_IsINReady() && readyToSendInput)
            {
                // Once populated, we can output this data to the host. We do this by first writing the data to the control stream.
                while (Endpoint_Write_Stream_LE(&InputReport, sizeof(InputReport), NULL) != ENDPOINT_RWSTREAM_NoError)
                    ;
                // We then send an IN packet on this endpoint.
                Endpoint_ClearIN();
                readyToSendInput = 0;
                i++;
            }
        }
        USB_USBTask();
    }
}

// change dpad state to "dpad"
void controller_set_dpad(uint8_t dpad)
{
    InputReport.DPAD = dpad;
}

// in grip menu: connect controller and go to home screen
void connect_and_return_to_home(void)
{
    controller_wait(STARTUP_WAIT_DELAY);

    controller_press_button(BUTTON_L);
    controller_press_button(BUTTON_R);
    controller_wait(BUTTON_PRESS_DURATION);
    controller_release_button(BUTTON_L);
    controller_release_button(BUTTON_R);
    controller_wait(BUTTON_PRESS_DURATION);
    controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, SWITCH_LEAVE_CONTROLLER_SETUP_DELAY);
    controller_press_and_release_button(BUTTON_HOME, BUTTON_PRESS_DURATION, SWITCH_TO_HOME_DELAY);
}

// press button for "duration" ticks and release it for "release" ticks
void controller_press_and_release_button(uint16_t button, uint16_t duration, uint16_t release)
{
    controller_press_button(button);
    controller_wait(duration);
    controller_release_button(button);
    controller_wait(release);
}

// press dpad for "duration" ticks and release it for "release" ticks
void controller_press_and_release_dpad(uint8_t dpad, uint16_t duration, uint16_t release)
{
    controller_init();

    controller_set_dpad(dpad);
    controller_wait(duration);
    controller_set_dpad(DPAD_NONE);
    controller_wait(release);
}

// reset input report
void controller_init(void)
{
    memset(&InputReport, 0, sizeof(USB_ControllerReport_Input_t));
    InputReport.LX = STICK_CENTER;
    InputReport.LY = STICK_CENTER;
    InputReport.RX = STICK_CENTER;
    InputReport.RY = STICK_CENTER;
    InputReport.DPAD = DPAD_NONE;
}

// counter variable for LED flashing
int counter = 0;
ISR(TIMER0_OVF_vect)
{
    /* Interrupt Action
    (1600000/256)/256 Hz = 244.140625 Hz (frequency)
    1/244.140625 s = 4.096 ms (interval length)
    */

    // ready flag to transmit next input report
    readyToSendInput = 1;

    // blinking status LED (RX)
    // 1 second interval (.5seconds on, .5 seconds off)
    if (++counter > 122)
    {
        PORTB ^= 1;
        counter = 0;
    }
}