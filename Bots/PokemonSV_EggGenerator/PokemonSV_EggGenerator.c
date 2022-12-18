#include "../../Config/Controller.h"

#define DELAY1 122 // picnic popup delay
#define DELAY2 732 // open sandwich menu delay

#define DELAY3 40 // select sandwich delay

#define DELAY4 900 // selected all ingredients

#define FINISHED_SANDWICH_DELAY 2000
#define SANDWICH_EAT_ANIMATION_DELAY 3600

#define STICK_INGREDIENT_HOLD 135

void make_sandwich(void)
{
    controller_init();
    // turn to table
    controller_move_and_release_stick_l(STICK_CENTER, STICK_CENTER - 20, 10, PokemonSV_NAVIGATION_DELAY);

    // open sandwich menu
    controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, DELAY1);
    controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, DELAY2);
    // navigate to "Great Peanut Butter Sandwich"
    controller_press_and_release_dpad(DPAD_DOWN, BUTTON_PRESS_DURATION, PokemonSV_NAVIGATION_DELAY);
    // select sandwich
    controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, DELAY3);
    // select pick
    controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, DELAY4);

    // place banana
    controller_move_and_release_stick_l(STICK_CENTER, 64, 20, 0);
    for (int i = 0; i < 3; i++)
    {
        controller_move_and_release_stick_l(STICK_CENTER, 64, STICK_INGREDIENT_HOLD, 50);
        controller_press_button(BUTTON_A);
        controller_move_and_release_stick_l(STICK_CENTER, STICK_MAX - 64, STICK_INGREDIENT_HOLD, 50);
        controller_release_button(BUTTON_A);
        controller_wait(50);
    }
    controller_init();
    controller_wait(244);
    // place bun 
    controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, 488);
    // place pick
    controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, FINISHED_SANDWICH_DELAY);
    // finished sandwich animation, press a
    controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, SANDWICH_EAT_ANIMATION_DELAY);
    // finished eat animation, press a
    controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, 244);
    //turn to basket again
    controller_move_and_release_stick_l(STICK_CENTER, STICK_CENTER + 20, 10, PokemonSV_NAVIGATION_DELAY);
}

int main(void)
{
    SetupHardware();
    TIMSK1 |= (1 << TOIE1); // setup 16-bit timer to overflow interrupt mode
    TCCR1B |= (1 << CS10);
    DDRD |= (1 << 5); // set port PIN D5 to output
    sei();
    connect_and_return_to_home();
    controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, PokemonSV_STARTUP_DELAY);

    while (1)
    {
        make_sandwich();
    }
}

int timer1counter = 0;
ISR(TIMER1_OVF_vect)
{
    if (++timer1counter > 122)
    {
        //PORTD ^= (1 << 5);
        timer1counter = 0;
    }
}