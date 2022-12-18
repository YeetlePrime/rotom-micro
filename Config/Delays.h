#ifndef _CONFIG_DELAYS_H_
#define _CONFIG_DELAYS_H_

//GENERAL----------------------------------------
#define TICKS_PER_SECOND 244

#define STARTUP_WAIT_DELAY 30
#define BUTTON_PRESS_DURATION 20

//Switch delays ---------------------------------
#define SWITCH_TO_HOME_DELAY 244
#define SWITCH_LEAVE_CONTROLLER_SETUP_DELAY 122


//PokemonSV delays ---------------------------
#define PokemonSV_STARTUP_DELAY 244

    //general delays
#define PokemonSV_OPEN_MENU_DELAY 122
#define PokemonSV_NAVIGATION_DELAY 20
#define PokemonSV_SPAWN_POPUP_DELAY 61

    // pokemon select delays
#define PokemonSV_SELECT_POKEMON_DELAY 122
#define PokemonSV_PUT_AWAY_HELD_ITEM_DELAY 61
#define PokemonSV_RETURN_TO_RIDE_DELAY 122
#define PokemonSV_READY_TO_TRAVEL_DELAY 300

    // box delays
#define PokemonSV_OPEN_BOX_DELAY 244
#define PokemonSV_CLOSE_BOX_DELAY 244
#define PokemonSV_CHANGE_SELECTION_MODE_DELAY 30
#define PokemonSV_CHANGE_BOX_DELAY 61

    // picnic delays
#define PokemonSV_PICNIC_TABLE_INTERACTION_DELAY 122
#define PokemonSV_OPEN_SANDWICH_MENU_DELAY 732
#define PokemonSV_SELECT_SANDWICH_DELAY 61
#define PokemonSV_START_SANDWICH_MINIGAME_DELAY 900
#define PokemonSV_READY_TO_PLACE_BUN_DELAY 244
#define PokemonSV_PLACE_BUN_DELAY 488
#define PokemonSV_SANDWICH_DISPLAY_ANIMATION_DELAY 2000
#define PokemonSV_SANDWICH_EAT_ANIMATION_DELAY 3600
#define PokemonSV_CLOSE_SANDWICH_MINIGAME_DELAY 244

    // picnic controls
#define PokemonSV_PICNIC_TURN_POSITION_UP 108
#define PokemonSV_PICNIC_TURN_POSITION_DOWN 148
#define PokemonSV_PICNIC_TURN_HOLD_DURATION 10
#define PokemonSV_TURN_AROUND_DELAY 61


    // sandwich minigame controls
#define PokemonSV_SANDWICH_INITIAL_STICK_HOLD_DURATION 20
#define PokemonSV_SANDWICH_STICK_HOLD_DURATION 135
#define PokemonSV_SANDWICH_STICK_POSITION_UP 64
#define PokemonSV_SANDWICH_STICK_POSITION_DOWN 191
#define PokemonSV_SANDWICH_MOVE_HAND_DELAY 122






#endif