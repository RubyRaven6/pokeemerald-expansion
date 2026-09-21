
#define STORY_POINT_MAP(map) .mapGroup = MAP_GROUP(map), .mapNum = MAP_NUM(map)

const u8* const gStoryActTitles[NUM_STORY_ACTS] = 
{
    [STORY_ACT_EXAMPLE_1] = COMPOUND_STRING("Example Act 1"),
    [STORY_ACT_EXAMPLE_2] = COMPOUND_STRING("Example Act 2"),
    [STORY_ACT_EXAMPLE_3] = COMPOUND_STRING("Example Act 3"),
};

const u16 gDefaultStoryJumpParty[PARTY_SIZE] =
{
    SPECIES_BULBASAUR,
    SPECIES_CHARMANDER,
    SPECIES_SQUIRTLE,
    SPECIES_WURMPLE,
    SPECIES_WURMPLE,
    SPECIES_WURMPLE,
};

const struct StoryPoint gStoryPoints[NUM_STORY_POINTS] =
{
    [STORY_POINT_EXAMPLE_1] = {
        .title = COMPOUND_STRING("Beginning of Game"),
        .act = STORY_ACT_EXAMPLE_1,
        .dependencies = {STORY_POINT_NONE},
        .setupFunc = StoryJumpSetup_Dummy,
        .minLevel = 0,
        STORY_POINT_MAP(MAP_INSIDE_OF_TRUCK),
        .warpId = WARP_ID_NONE,
        .x = -1,
        .y = -1,
    },
    [STORY_POINT_EXAMPLE_2] = {
        .title = COMPOUND_STRING("Got Starter Pokemon"),
        .act = STORY_ACT_EXAMPLE_1,
        .dependencies = {STORY_POINT_NONE},
        .setupFunc = StoryJumpSetup_GotStarterPokemon,
        .minLevel = 5,
        STORY_POINT_MAP(MAP_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB),
        .warpId = WARP_ID_NONE,
        .x = 6,
        .y = 5,
    },
    [STORY_POINT_EXAMPLE_3] = {
        .title = COMPOUND_STRING("After Talking to Birch"),
        .act = STORY_ACT_EXAMPLE_1,
        .dependencies = {STORY_POINT_NONE},
        .setupFunc = StoryJumpSetup_FinishedTalkingToBirch,
        .minLevel = 5,
        STORY_POINT_MAP(MAP_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB),
        .warpId = WARP_ID_NONE,
        .x = 6,
        .y = 5,
    },
    [STORY_POINT_EXAMPLE_4] = {
        .title = COMPOUND_STRING("Example Story Point 4"),
        .act = STORY_ACT_EXAMPLE_2,
        .dependencies = {STORY_POINT_NONE},
        .setupFunc = StoryJumpSetup_Dummy,
        .minLevel = 5,
        STORY_POINT_MAP(MAP_LITTLEROOT_TOWN),
        .warpId = WARP_ID_NONE,
        .x = 0,
        .y = 0,
    },
    [STORY_POINT_EXAMPLE_5] = {
        .title = COMPOUND_STRING("Example Story Point 5"),
        .act = STORY_ACT_EXAMPLE_3,
        .dependencies = {STORY_POINT_NONE},
        .setupFunc = StoryJumpSetup_Dummy,
        .minLevel = 5,
        STORY_POINT_MAP(MAP_LITTLEROOT_TOWN),
        .warpId = WARP_ID_NONE,
        .x = 0,
        .y = 0,
    },
    [STORY_POINT_EXAMPLE_6] = {
        .title = COMPOUND_STRING("Example Story Point 6"),
        .act = STORY_ACT_EXAMPLE_3,
        .dependencies = {STORY_POINT_NONE},
        .setupFunc = StoryJumpSetup_Dummy,
        .minLevel = 5,
        STORY_POINT_MAP(MAP_LITTLEROOT_TOWN),
        .warpId = WARP_ID_NONE,
        .x = 0,
        .y = 0,
    },
};
