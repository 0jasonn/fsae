#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/objcolor.h"

// Functions in this file (module objcolor, original names from the debug build): PutObjColor (PutObjColor(unsigned char))

extern u8 set58_bodyState[];
extern u8 data_02134ae8[];

// PutObjColor (0x02027fe8): releases one reference to each record holding the colour id a.
void PutObjColor(u8 a) {
    OC_CTRL_ *rec;

    rec = (OC_CTRL_ *)set58_bodyState;
    do {
        if (rec->id == a) {
            if (rec->refCount != 0) {
                rec->refCount -= 1;
            }
        }
        rec++;
    } while ((u8 *)rec < data_02134ae8);
}
