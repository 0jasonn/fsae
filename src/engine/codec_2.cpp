#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/codec.h"

// Dispatches one byte store through the codec record (data_020df74c[2]).
ARM s32 Codec_StoreChar(u8 *target, s32 value) {
    return data_020df74c[2]->store(target, value);
}
