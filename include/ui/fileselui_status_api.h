#ifndef UI_FILESELUI_STATUS_API_H
#define UI_FILESELUI_STATUS_API_H

// Functions defined in src/game/fileselui_status_e*.cpp.

#include "engine/entity.h"

extern "C" {
s32 fileSelUIView_checkSaveStatus(void *self);
}

#endif
