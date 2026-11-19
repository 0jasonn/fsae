#ifndef WIP_B_COM_SAVEDATA_H
#define WIP_B_COM_SAVEDATA_H

#include "engine/functions.h"

// Not in engine/functions.h yet: writes one save record (original setKnifeSaveData4S(unsigned char, unsigned long,
// unsigned long, unsigned char), 0x020284d4), mangled _Z18setKnifeSaveData4Shmmh
void setKnifeSaveData4S(u8 slot, u32 a, u32 b, u8 flag);

// Data used by com_savedata: comWork, and multiSioSelect (its index selects the send table entry)
#include "engine/com_work.h"
#include "knife/comm/multisio.h"

// Original com_savedata() (0x020284fc), plain name
extern "C" void com_savedata(void);

#endif
