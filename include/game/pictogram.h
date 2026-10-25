#ifndef WIP_E_PICTOGRAM_H
#define WIP_E_PICTOGRAM_H

#include "engine/functions.h"
#include "game/subtask.h"

namespace Knife {
namespace Message {

// Pictogram id (values not known yet; the character info table has 41 entries)
typedef enum PictogramID { PICTOGRAM_ID_UNKNOWN } PictogramID;

// One entry of the character info table (12 bytes)
typedef struct PictCharEntry {
    u32 charNo;     // 0x00: character number, low 10 bits go to OAM attr2
    u8 colorMode;   // 0x04: nonzero selects 256 colours (OAM attr0 bit 13)
    u8 unk_05[3];
    u32 palette;    // 0x08: palette number, bits 12 to 15 of OAM attr2
} PictCharEntry;

// Character info table of the pictogram renderer (copied by setCharInfo): 41 entries, the first at +0x0c
typedef struct PictCharInfo {
    PictCharEntry entries[41];
} PictCharInfo;

// Pictogram renderer (Knife::Message::PictogramRenderer). Only the fields the functions matched so far use are named.
class PictogramRenderer {
public:
    void assignOam(GXOamAttr *oam, s32 count);
    void setCharInfo(const PictCharInfo *info);
    void clearAllPictogram(void);
    void clearPictogram(s32 index);
    s32 renderPictogram(PictogramID id, s32 x, s32 y, s32 priority);
    s32 findEmptyIndex(void) const;

    u8 unk_00[0x04];
    GXOamAttr *oam;        // 0x04: OAM buffer, one entry per pictogram
    s32 count;             // 0x08: number of pictograms (at most 0x80)
    PictCharInfo charInfo; // 0x0c
    u32 usedBits[4];       // 0x1f8: one bit per pictogram, set while the pictogram is in use
};

}
}

#endif
