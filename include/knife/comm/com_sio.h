#ifndef WIP_B_COM_SIO_H
#define WIP_B_COM_SIO_H

// Multiplayer serial (MultiSio) calls used by the communication code. Original signatures from the debug build.
#include "engine/functions.h"
#include "knife/comm/multisio.h" // MultiSioStart, MultiSioStop, MultiSioSendDataSet

#include "knife/comm/comm.h"   // CommStatusSync
void MultiSioInit(void);                 // original MultiSioInit()


#endif
