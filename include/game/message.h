#ifndef WIP_A_MESSAGE_A_H
#define WIP_A_MESSAGE_A_H

#include "engine/functions.h"
#include "ui/message.h"

// Original names (C++ linkage); not in engine/functions.h yet.
int tlpMove(void);
int msgMove(void);

// The move functions in msgMoveTable take the message system they work on (knife_commDispMove and friends).
typedef void (*MsgMoveFunc)(KNIFE_MSGSYS *msg);

#endif
