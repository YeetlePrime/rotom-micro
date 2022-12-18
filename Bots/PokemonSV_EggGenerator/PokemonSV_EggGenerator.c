#include "../../Framework/Controller.h"
#include "Config.h"

uint16_t five_minute_timer = 0;
uint8_t thirty_minute_timer = 0;
int shouldCollectEggs = 0;
int shouldMakeSandwich = 0;

void make_sandwich(void)
{
    shouldMakeSandwich = 0;
    controller_init();
    // turn to table
    controller_move_and_release_stick_l(STICK_CENTER, PokemonSV_PICNIC_TURN_POSITION_UP, PokemonSV_PICNIC_TURN_HOLD_DURATION, PokemonSV_TURN_AROUND_DELAY);

    // open sandwich menu
    controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, PokemonSV_PICNIC_TABLE_INTERACTION_DELAY);
    controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, PokemonSV_OPEN_SANDWICH_MENU_DELAY);
    // navigate to "Great Peanut Butter Sandwich"
    for (int i = 0; i < EGG_POWER_SANDWICH_DOWN; i++)
    {
        controller_press_and_release_dpad(DPAD_DOWN, BUTTON_PRESS_DURATION, PokemonSV_NAVIGATION_DELAY);
    }
    if (EGG_POWER_SANDWICH_LOCATION == RIGHT) controller_press_and_release_dpad(DPAD_RIGHT, BUTTON_PRESS_DURATION, PokemonSV_NAVIGATION_DELAY);
    // select sandwich
    controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, PokemonSV_SELECT_SANDWICH_DELAY);
    // select pick
    controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, PokemonSV_START_SANDWICH_MINIGAME_DELAY);

    // place banana
    controller_move_and_release_stick_l(STICK_CENTER, PokemonSV_SANDWICH_STICK_POSITION_UP, PokemonSV_SANDWICH_INITIAL_STICK_HOLD_DURATION, 0);
    for (int i = 0; i < 3; i++)
    {
        controller_move_and_release_stick_l(STICK_CENTER, PokemonSV_SANDWICH_STICK_POSITION_UP, PokemonSV_SANDWICH_STICK_HOLD_DURATION, PokemonSV_SANDWICH_MOVE_HAND_DELAY);
        controller_press_button(BUTTON_A);
        controller_move_and_release_stick_l(STICK_CENTER, PokemonSV_SANDWICH_STICK_POSITION_DOWN, PokemonSV_SANDWICH_STICK_HOLD_DURATION, PokemonSV_SANDWICH_MOVE_HAND_DELAY);
        controller_release_button(BUTTON_A);
        controller_wait(PokemonSV_SANDWICH_MOVE_HAND_DELAY);
    }
    controller_init();
    controller_wait(PokemonSV_READY_TO_PLACE_BUN_DELAY);
    // place bun
    controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, PokemonSV_PLACE_BUN_DELAY);
    // place pick
    controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, PokemonSV_SANDWICH_DISPLAY_ANIMATION_DELAY);
    // finished sandwich animation, press a
    controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, PokemonSV_SANDWICH_EAT_ANIMATION_DELAY);
    // finished eat animation, press a
    controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, PokemonSV_CLOSE_SANDWICH_MINIGAME_DELAY);
    // turn to basket
    controller_move_and_release_stick_l(STICK_CENTER, PokemonSV_PICNIC_TURN_POSITION_DOWN, PokemonSV_PICNIC_TURN_HOLD_DURATION, PokemonSV_TURN_AROUND_DELAY);
}

void collect_eggs(void)
{
    shouldCollectEggs = 0;
    controller_init();
    // interact with basket
    controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, BUTTON_PRESS_DURATION);
    for (uint16_t i = 0; i < 3660; i++)
    {
        controller_press_and_release_button(BUTTON_B, 1, 1);
    }
}

int main(void)
{
    SetupHardware();
    TIMSK1 |= (1 << TOIE1);              // setup 16-bit timer to overflow interrupt mode
    TCCR1B |= (1 << CS12) | (1 << CS10); // pre-scalar to 1024
    sei();
    connect_and_return_to_home();
    controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, PokemonSV_STARTUP_DELAY);
    make_sandwich();
    TCNT1H = 0x00; // reset timer
    TCNT1L = 0x00; //

    while (1)
    {
        if (shouldCollectEggs)
        {
            collect_eggs();
        }
        else if (shouldMakeSandwich)
        {
            make_sandwich();
        }
        else
        {
            controller_wait(1);
        }
    }
}

ISR(TIMER1_OVF_vect)
{
    // TIMER interrupt:
    // 16,000,000Hz/((2^16)*1024) = 0.2384185791Hz
    // 4.194304s between each interrupt
    if (five_minute_timer < 71)
    {
        five_minute_timer++;
    }
    else
    {
        five_minute_timer = 0;
        thirty_minute_timer++;
        shouldCollectEggs = 1;
    }
    if (thirty_minute_timer >= 6)
    {
        thirty_minute_timer = 0;
        shouldMakeSandwich = 1;
    }
}