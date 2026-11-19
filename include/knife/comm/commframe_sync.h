#ifndef KNIFE_COMM_COMMFRAME_SYNC_H
#define KNIFE_COMM_COMMFRAME_SYNC_H

#include "engine/functions.h"

#include "engine/com_work.h"
extern u8 data_0212c4d4;   // nonzero while the communication frame sync is still pending

int CommFrameSync(void);

#endif
