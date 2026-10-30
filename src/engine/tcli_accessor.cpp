#include "engine/functions.h"
#include "global.h"
#include "types.h"

// tcli_accessor: function TCLi_InitAccessor (0x020b69e4), keeps its symbol name.

// TCLi_InitAccessor(self, a, b, c, d) (0x020b69e4): stores the four words a, b, c and d at +0, +4, +8 and +0xc
extern "C" void TCLi_InitAccessor(void *self, u32 a, u32 b, u32 c, u32 d);
ARM void TCLi_InitAccessor(void *self, u32 a, u32 b, u32 c, u32 d) {
    u32 *words = (u32 *)self;
    words[0] = a;
    words[1] = b;
    words[2] = c;
    words[3] = d;
}
