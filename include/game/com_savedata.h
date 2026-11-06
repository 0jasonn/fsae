#ifndef WIP_B_COM_SAVEDATA_H
#define WIP_B_COM_SAVEDATA_H

#include "engine/functions.h"

// Not in engine/functions.h yet: writes one save record (original setKnifeSaveData4S(unsigned char, unsigned long,
// unsigned long, unsigned char), 0x020284d4), mangled _Z18setKnifeSaveData4Shmmh
void setKnifeSaveData4S(u8 slot, u32 a, u32 b, u8 flag);

// Shared byte arrays used by com_savedata (also declared in other headers)
extern u8 comWork[];   // communication state block
extern u8 multiSioSelect[];   // index byte at +4 selects the send table entry

// Original com_savedata() (0x020284fc), plain name
void com_savedata(void);

#endif
