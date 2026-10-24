#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"

// Forwards to the sound volume setter.
ARM void Menu_SetMasterVolume(s32 volume) {
    SND_SetMasterVolume(volume);
}
