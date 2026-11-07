#ifndef WIP_E_RECORD_INIT_E_H
#define WIP_E_RECORD_INIT_E_H

#include "engine/functions.h"
#include "engine/record_init_api.h"

// Two bytes per size class: [log2 of the height][log2 of the width] (rodata data_020df144)
typedef struct RecordShapeEntry {
    u8 shape;
    u8 size;
} RecordShapeEntry;

typedef struct RecordShapeTable {
    RecordShapeEntry entry[4][4];
} RecordShapeTable;

// The low half of the record's flag word that Record_InitShape builds from the table
typedef struct RecordShapeBits {
    u32 shape : 8;
    u32 size : 8;
    u32 rest : 16;
} RecordShapeBits;

extern const RecordShapeTable data_020df144;
extern u8 data_020df138[];

extern "C" {
void Record_InitShape(u8 *self, u32 a, u32 width, u32 height, u32 d);
}

#endif
