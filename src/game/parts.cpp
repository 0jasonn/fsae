#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/frame_load.h"

// parts_set(frame, flags) (0x0204db38): places the parts of a frame. Each part is chosen by parts_select, registered
// in the info tables and passed to PartsSet with the position bytes of the frame; the event and treasure lists of the
// part's area (index + 1) are loaded too. The part cursor (game state byte 0x4b) is restored at the end.
void parts_set(FRAME_INFO_ *frame, u32 flags) {
    u8 i;
    u8 cursor;
    PartRecord *part;

    cursor = gameState.unk_49[2];
    if (gameState.unk_8c == 0) {
        for (i = 0; i < 0x20; i++) {
            data_0216f8b4[i] = data_0216f834[i];
        }
    }
    for (i = 0; i < frame->unk_02[0]; i++) {
        part = parts_select(frame, flags);
        if (i == 0 && gameState.unk_8c == 0) {
            cursor = gameState.unk_49[2];
        }
        data_0216f820[1] = part->partId;
        data_02134968[i + 1] = part->infoRows;
        PartsSet(part->partId, frame->unk_02[2 + i * 2], frame->unk_02[3 + i * 2]);
        if (GetInfoAdrs(i + 1, 0) != 0) {
            MultiEventSet((u16 *)GetInfoAdrs(i + 1, 0), frame->unk_02[2 + i * 2], frame->unk_02[3 + i * 2], i + 1);
        }
        if (GetInfoAdrs(i + 1, 1) != 0) {
            MultiEventSet((u16 *)GetInfoAdrs(i + 1, 1), frame->unk_02[2 + i * 2], frame->unk_02[3 + i * 2], i + 1);
        }
        if (GetInfoAdrs(i + 1, 3) != 0) {
            takara_set((u8 *)GetInfoAdrs(i + 1, 3), frame, i + 1);
        }
    }
    gameState.unk_49[2] = cursor;
}
