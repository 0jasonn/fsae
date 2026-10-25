#include "engine/functions.h"
#include "global.h"

// getarea (0x0206cb84): searches the area table from e->areaTable in one direction chosen by e->type (records
// 0x40 bytes or 1 byte apart), stores the distance as (distance >> 2) - 8 or (distance << 4) - 8, and keeps its high
// nibble as areaResult.

typedef struct Vars_Getarea {
    /* 00 */ u8 unk_00[0x6c];
    /* 6c */ u8 unk_6c[7];
    /* 73 */ u8 areaResult;     // result of getarea: high nibble of the offset
    /* 74 */ u8 *areaTable;     // record table; records are 0x40 or 1 byte apart
    /* 78 */ u8 unk_78[4];
    /* 7c */ u16 scaledOffset;  // (distance << 4) - 8, used by cases 1 and 3
    /* 7e */ u16 shiftedOffset; // (distance >> 2) - 8, used by cases 0 and 2
} Vars_Getarea;

extern "C" void getarea(Entity *e);

ARM void getarea(Entity *e) {
    u8 *p;
    u8 *base;

    base = VARS(Vars_Getarea, e)->areaTable;
    p = base;
    switch (e->type) {
    case 0:
        do {
            p += 0x40;
        } while (*p != 0xff && (u8)(*p - 1) >= 0x1f);
        VARS(Vars_Getarea, e)->shiftedOffset = (((u32)p - (u32)base) >> 2) - 8;
        VARS(Vars_Getarea, e)->areaResult = VARS(Vars_Getarea, e)->shiftedOffset >> 4;
        return;
    case 1:
        do {
            p -= 1;
        } while (*p != 0xff && (u8)(*p - 1) >= 0x1f);
        VARS(Vars_Getarea, e)->scaledOffset = (((u32)base - (u32)p) << 4) - 8;
        VARS(Vars_Getarea, e)->areaResult = VARS(Vars_Getarea, e)->scaledOffset >> 4;
        return;
    case 2:
        do {
            p -= 0x40;
        } while (*p != 0xff && (u8)(*p - 1) >= 0x1f);
        VARS(Vars_Getarea, e)->shiftedOffset = (((u32)base - (u32)p) >> 2) - 8;
        VARS(Vars_Getarea, e)->areaResult = VARS(Vars_Getarea, e)->shiftedOffset >> 4;
        return;
    case 3:
        do {
            p += 1;
        } while (*p != 0xff && (u8)(*p - 1) >= 0x1f);
        VARS(Vars_Getarea, e)->scaledOffset = (((u32)p - (u32)base) << 4) - 8;
        VARS(Vars_Getarea, e)->areaResult = VARS(Vars_Getarea, e)->scaledOffset >> 4;
        return;
    }
}
