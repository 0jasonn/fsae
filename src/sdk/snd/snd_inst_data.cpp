#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/snd/snd_bank.h"

// SND_GetFirstInstDataPos() (0x0201bc28): position before the first instrument of a bank.
SndInstDataPosition SND_GetFirstInstDataPos(void) {
    SndInstDataPosition position;

    position.instrumentIndex = 0;
    position.subIndex = 0;
    return position;
}
