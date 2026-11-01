#ifndef WIP_D_KMSGREADER_D_H
#define WIP_D_KMSGREADER_D_H

#include "types.h"

// Declarations of message reader functions that the D units call but that no unit defines yet. Each name is the plain
// symbols.txt name, so they are extern "C" (see the linkage rule in scratch/agent_brief.md).
extern "C" {
// Knife::Message::KMsgFileReader::initialize(void const*, unsigned long) (0x0208e20c, parked)
BOOL Knife_Message_KMsgFileReader_initialize(void *self, const void *data, u32 size);
}

#endif
