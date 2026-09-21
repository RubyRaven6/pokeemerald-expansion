#include "story_jump_setup_funcs.h"

#include "random.h"
#include "new_game.h"
#include "script_pokemon_util.h"
#include "rtc.h"
#include "clock.h"
#include "sound.h"
#include "load_save.h"
#include "main.h"
#include "script.h"
#include "story_jump_menu.h"
#include "main_menu.h"
#include "play_time.h"
#include "event_data.h"
#include "constants/flags.h"
#include "constants/maps.h"
#include "constants/vars.h"

void StoryJumpSetup_Dummy(void){}

void StoryJumpSetup_GotStarterPokemon(void)
{
    RtcInitLocalTimeOffset(0, 0);
    InitTimeBasedEvents();
	FlagSet(FLAG_SET_WALL_CLOCK);
	FlagSet(FLAG_HIDE_LITTLEROOT_TOWN_PLAYERS_HOUSE_VIGOROTH_1);
	FlagSet(FLAG_HIDE_LITTLEROOT_TOWN_PLAYERS_HOUSE_VIGOROTH_2);
	FlagSet(FLAG_MET_RIVAL_MOM);
	VarSet(VAR_LITTLEROOT_INTRO_STATE, 7);
	FlagSet(FLAG_SYS_TV_HOME);
	VarSet(VAR_LITTLEROOT_TOWN_STATE, 2);
	FlagSet(FLAG_SYS_POKEMON_GET);
	FlagSet(FLAG_RESCUED_BIRCH);
    FlagSet(FLAG_HIDE_ROUTE_101_ZIGZAGOON);
	FlagSet(FLAG_HIDE_ROUTE_101_BIRCH_ZIGZAGOON_BATTLE);
	FlagClear(FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH);
	FlagSet(FLAG_HIDE_ROUTE_101_BIRCH_STARTERS_BAG);
	VarSet(VAR_BIRCH_LAB_STATE, 2);
	VarSet(VAR_ROUTE101_STATE, 3);
	FlagClear(FLAG_HIDE_MAP_NAME_POPUP);
    FlagSet(FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_TRUCK);
    FlagSet(FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_TRUCK);
	VarSet(VAR_LITTLEROOT_RIVAL_STATE, 3);
    FlagSet(FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_POKE_BALL);
    FlagSet(FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_POKE_BALL);

    if (gSaveBlock2Ptr->playerGender == MALE)
    {
        FlagSet(FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_MOM);
        FlagSet(FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_MOM);
        FlagSet(FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_SIBLING);
        VarSet(VAR_LITTLEROOT_HOUSES_STATE_MAY, 2);
        FlagSet(FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_MAY);
        FlagSet(FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM);
    }
    else
    {
        FlagSet(FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_MOM);
        FlagSet(FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_MOM);
        FlagSet(FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_SIBLING);
        VarSet(VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 2);
        FlagSet(FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_BRENDAN);
        FlagSet(FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM);
    }
}

void StoryJumpSetup_FinishedTalkingToBirch(void)
{
	VarSet(VAR_BIRCH_LAB_STATE, 3);
}

// define your story jump setup funcs here
