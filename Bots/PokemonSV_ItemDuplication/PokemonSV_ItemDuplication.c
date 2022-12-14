#include "../../Config/Controller.h"

// Main entry point.
int main(void)
{
    // We'll start by performing hardware and peripheral setup.
    SetupHardware();

    sei();

    // Once that's done, we'll enter an infinite loop.

    connect_and_return_to_home();

    // start pokemonsv
    controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, PokemonSV_STARTUP_DELAY);
    while (1)
    {
        // select koraidon/miraidon (in slot 2)
        controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, PokemonSV_SELECT_POKEMON_DELAY);
        // navigate to "return to ride form"
        controller_press_and_release_dpad(DPAD_UP, BUTTON_PRESS_DURATION, PokemonSV_NAVIGATION_DELAY);
        controller_press_and_release_dpad(DPAD_UP, BUTTON_PRESS_DURATION, PokemonSV_NAVIGATION_DELAY);
        // select "return to ride form"
        controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, PokemonSV_RETURN_TO_RIDE_DELAY);
        // press a to spawn "yes/no" popup
        controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, PokemonSV_SPAWN_POPUP_DELAY);
        // press "yes"
        controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, PokemonSV_READY_TO_TRAVEL_DELAY);
        // close "Returned to ride form" popup
        controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, PokemonSV_NAVIGATION_DELAY);
        // navigate to "box"
        controller_press_and_release_dpad(DPAD_RIGHT, BUTTON_PRESS_DURATION, PokemonSV_NAVIGATION_DELAY);
        controller_press_and_release_dpad(DPAD_DOWN, BUTTON_PRESS_DURATION, PokemonSV_NAVIGATION_DELAY);
        controller_press_and_release_dpad(DPAD_DOWN, BUTTON_PRESS_DURATION, PokemonSV_NAVIGATION_DELAY);
        // open box
        controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, PokemonSV_OPEN_BOX_DELAY);
        // change mode to "battle-team"
        controller_press_and_release_button(BUTTON_X, BUTTON_PRESS_DURATION, PokemonSV_CHANGE_SELECTION_MODE_DELAY);
        controller_press_and_release_button(BUTTON_X, BUTTON_PRESS_DURATION, PokemonSV_CHANGE_SELECTION_MODE_DELAY);
        // change box
        controller_press_and_release_button(BUTTON_L, BUTTON_PRESS_DURATION, PokemonSV_CHANGE_BOX_DELAY);
        // select koraidon/miraidon in box
        controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, PokemonSV_SELECT_POKEMON_DELAY);
        // navigate to "put away held item"
        controller_press_and_release_dpad(DPAD_DOWN, BUTTON_PRESS_DURATION, PokemonSV_NAVIGATION_DELAY);
        controller_press_and_release_dpad(DPAD_DOWN, BUTTON_PRESS_DURATION, PokemonSV_NAVIGATION_DELAY);
        controller_press_and_release_dpad(DPAD_DOWN, BUTTON_PRESS_DURATION, PokemonSV_NAVIGATION_DELAY);
        // press "put away held item"
        controller_press_and_release_button(BUTTON_A, BUTTON_PRESS_DURATION, PokemonSV_PUT_AWAY_HELD_ITEM_DELAY);
        // leave box menu
        controller_press_and_release_button(BUTTON_B, BUTTON_PRESS_DURATION, PokemonSV_CLOSE_BOX_DELAY);
        // navigate to koraidon/miraidon in team
        controller_press_and_release_dpad(DPAD_LEFT, BUTTON_PRESS_DURATION, PokemonSV_NAVIGATION_DELAY);
    }
}