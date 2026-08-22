#ifndef GUARD_CUTSCENE_H
#define GUARD_CUTSCENE_H

#define CUTSCENE_FLAG_TRACKING FALSE

struct CutscenesSkips
{
    const u8 *scriptCutsceneSkipPtr;
#if CUTSCENE_FLAG_TRACKING == TRUE
    u16 flag;
#endif
};

void EndSkippableCutscene(void);

#endif // GUARD_CUTSCENE_H