#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/fatfs/fatfs.h"

// Tail call to FATFSi_SendToPXI.
void Fatfs_SendToPxi(FatfsRequest *request) {
    FATFSi_SendToPXI(request);
}
