#ifndef SDK_OS_CP_CONTEXT_H
#define SDK_OS_CP_CONTEXT_H

// TwlSDK CP: saves and restores the divider and square-root unit registers (hand-written assembly).
#include "types.h"

extern "C" {
void CP_SaveContext(void *context);
void CPi_RestoreContext(void *context);
}

#endif
