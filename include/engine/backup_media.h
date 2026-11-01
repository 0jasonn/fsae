#ifndef WIP_C_BACKUP_MEDIA_H
#define WIP_C_BACKUP_MEDIA_H

// Save media (backup) functions used by src/wip/C/backup_media.cpp. The shared declarations (getEepInfo,
// readFromSaveBuffer, Knife_mediaWrite, the data_02171d10 global) come from game/rankingsave.h and game/backup.h.
#include "engine/functions.h"
#include "game/rankingsave.h"
#include "game/backup.h"

// data_02171d10 viewed as the save load state (game/backup.h). +00 holds the last result code.
#define SAVE_LOAD_STATE (*(SaveLoadState *)&data_02171d10)
#define SAVE_LOAD_RESULT (*(s32 *)&data_02171d10)

extern const u32 data_020d852c[];   // data table passed to Knife_mediaVerify (0x020d852c)

// C++ functions defined in other units (mangled names in symbols.txt)
u32 Knife_loadSaveFile(u32 slot);
s32 Knife_fatRead(u16 slot, _SAVEHEADER *header);
s32 isAccordData(_SAVEHEADER *header, const u32 *data, s32 size);
s32 FSResultToKnifeFsResult(s32 result);
s32 Knife_InitialSaveFileALL(void);
s32 Knife_mediaVerify(u16 slot, const u32 *data, s32 size);

#endif
