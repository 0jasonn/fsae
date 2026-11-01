#ifndef GAME_TEXTREADER_H
#define GAME_TEXTREADER_H

#include "engine/entity.h"

// Text reader state (Knife::Message::TextReader). Only the fields the functions matched so far use are named.
typedef struct KnifeTextReader {
    void *vtbl;         // 0x00
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;          // 0x06: set while a read is in progress, cancel asks for an end
    u8 unk_07;          // 0x07: set by cancel
    u8 unk_08;
    u8 unk_09[3];
    u32 unk_0c;
    u8 *paramPtr;       // 0x10: next parameter bytes
    s32 paramPos;       // 0x14: bytes of the parameters read so far
} KnifeTextReader;

#endif
