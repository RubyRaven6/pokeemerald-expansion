#ifndef GUARD_DATA_GUARD_CUTSCENE_H
#define GUARD_DATA_GUARD_CUTSCENE_H

#include "global.h"
#include "gba/gba.h"
#include "constants/cutscene.h"
#include "constants/flags.h"
#include "main.h"

extern const u8 LittlerootTown_ProfessorBirchsLab_SkipBirchCutscene[];

const struct CutscenesSkips sCutsceneSkipScripts[] =
{
    [CUTSCENE_BIRCH] =
    {
        .scriptCutsceneSkipPtr = LittlerootTown_ProfessorBirchsLab_SkipBirchCutscene,
        // .flag = FLAG_SEEN_CUTSCENE_EXAMPLE,      // Do not include the flag if CUTSCENE_FLAG_TRACKING is set to FALSE
    },
};

#endif // GUARD_DATA_GUARD_CUTSCENE_H