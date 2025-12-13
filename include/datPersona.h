#ifndef DATPERSONA_H
#define DATPERSONA_H

#include "g_data.h"

u8 Persona_GetPersonaLevel(PersonaData* persona);
u32 Persona_GetPersonaNextExp(PersonaData* persona);
PersonaData* Persona_GetPersonaByCharacterId(u16 characterId);
PersonaData* Persona_GetHeroPersona(u16 heroPersonaIdx);

#endif