#ifndef DATCALC_H
#define DATCALC_H

#include "datPersona.h"

u8 Character_GetLevel_Impl(CharacterHeader* characterHeader);
void Character_AddBattleFlags_Impl(CharacterHeader* characterHeader, u32 flags);
u32 Character_GetBattleFlagsNoDown_Impl(CharacterHeader* characerHeader);
u32 Character_GetBattleFlags(CharacterHeader* characterHeader);
void Character_RemoveBattleFlags_Impl(CharacterHeader* characterHeader, u32 flags);
u8 Character_HasBattleFlags(CharacterHeader* characterHeader, u32 flags);
u8 Character_IsCharacterDead(CharacterHeader* characterHeader, s32 param_2);
void FUN_0030c440();

#endif