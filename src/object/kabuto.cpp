#include "engine/functions.h"
#include "global.h"

// Sword module, continued: kabutoEvent (0x0207bc48).

// Spawns an effect (kind 0) at each of the 3 x 3 points that are 16 pixels apart around the object's position
extern "C" void func_0208a240(Entity *e, u32 kind, u16 x, u16 y); // 0x0208a240, thumb, no original name

// kabutoEvent (0x0207bc48)
extern "C" void kabutoEvent(Entity *e);
ARM void kabutoEvent(Entity *e) {
    u8 row;
    u8 col;
    s8 dy;
    s8 dx;

    dy = -16;
    for (row = 0; row < 3; row++) {
        dx = -16;
        for (col = 0; col < 3; col++) {
            func_0208a240(e, 0, (u16)(e->x.HALF.HI + dx), (u16)(e->y.HALF.HI + dy));
            dx += 16;
        }
        dy += 16;
    }
}
