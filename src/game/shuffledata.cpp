#include "engine/functions.h"
#include "game/triangle.h"
#include "global.h"

// shuffledata (0x0204e0f8): shuffles a list of ids. The list is first riffled with itself (first half interleaved with
// the second half) into triangleTable. That copy is cut into four runs (two read forwards, two backwards) which are
// written back one entry per run in a rotation chosen by Random(), until the first run is used up.
// dst, the riffle's write pointer, is reused as the second run's (backward) read pointer: with a separate variable the
// table base and that pointer swap registers (sl/r8).
void shuffledata(u16 *list, u16 count) {
    u16 *firstPart;
    u16 *secondPart;
    u16 *dst;
    u16 *runForward0;
    u16 *runForward2;
    u16 *runBackward3;
    u16 firstCount;
    u16 secondCount;
    u16 run2;
    u16 run3;
    u16 run1;
    u16 run0;
    u16 rest;
    u16 odd;

    if (count == 0) {
        return;
    }
    secondCount = count >> 1;
    odd = count & 1;
    firstCount = secondCount;
    if (odd != 0) {
        firstCount = secondCount + 1;
    }
    firstPart = list;
    secondPart = list + firstCount;
    dst = (u16 *)triangleTable;
    do {
        *dst++ = *firstPart++;
        firstCount--;
        if (secondCount != 0) {
            secondCount--;
            *dst++ = *secondPart++;
        }
    } while (firstCount != 0);
    run0 = run1 = run2 = run3 = count >> 2;
    rest = count & 3;
    if (rest != 0) {
        run0 = run0 + 1;
        if (rest > 1) {
            run1 = run0;
            if (rest > 2) {
                run2 = run0;
            }
        }
    }
    runForward0 = (u16 *)triangleTable;
    dst = runForward0 + run0 + run1 - 1; // start of run 1 (read backwards)
    runForward2 = dst + 1;
    runBackward3 = runForward0 + count - 1;
    switch (Random() & 3) {
    case 0:
        do {
            *list++ = *runForward0++;
            run0--;
            if (run1 != 0) {
                *list++ = *dst--;
                run1--;
            }
            if (run2 != 0) {
                *list++ = *runForward2++;
                run2--;
            }
            if (run3 != 0) {
                *list++ = *runBackward3--;
                run3--;
            }
        } while (run0 != 0);
        break;
    case 1:
        do {
            if (run3 != 0) {
                *list++ = *runBackward3--;
                run3--;
            }
            if (run2 != 0) {
                *list++ = *runForward2++;
                run2--;
            }
            if (run1 != 0) {
                *list++ = *dst--;
                run1--;
            }
            *list++ = *runForward0++;
            run0--;
        } while (run0 != 0);
        break;
    case 2:
        do {
            if (run2 != 0) {
                *list++ = *runForward2++;
                run2--;
            }
            *list++ = *runForward0++;
            run0--;
            if (run3 != 0) {
                *list++ = *runBackward3--;
                run3--;
            }
            if (run1 != 0) {
                *list++ = *dst--;
                run1--;
            }
        } while (run0 != 0);
        break;
    case 3:
        do {
            if (run1 != 0) {
                *list++ = *dst--;
                run1--;
            }
            if (run3 != 0) {
                *list++ = *runBackward3--;
                run3--;
            }
            *list++ = *runForward0++;
            run0--;
            if (run2 != 0) {
                *list++ = *runForward2++;
                run2--;
            }
        } while (run0 != 0);
        break;
    }
}
