#include "engine/functions.h"
#include "global.h"
#include "types.h"

extern "C" u32 data_02129d78[];

extern "C" void func_0201aa78(u32 arg0, u32 data, s32 arg2) {
    u32 rawMode = data & 0x3f00000;
    u32 rawIndex = data & 0xf0000;
    rawMode >>= 20;
    rawIndex >>= 16;
    u16 mode = (u16)rawMode;
    u16 index = (u16)rawIndex;
    u16 payload = (u16)data;

    switch (mode) {
    case 1: {
        u32 *state = data_02129d78;
        u64 accumulated = *(u64 *)(state + 1);
        accumulated |= (u64)payload << (index * 16);
        *(u64 *)(state + 1) = accumulated;
        u32 bitmap = state[3] | (1 << index);
        state[3] = bitmap;
        if (bitmap != 0xf) {
            return;
        }
        if (state[4] != 0) {
            ((void (*)(u64, void *))state[4])(*(u64 *)(state + 1), (void *)state[5]);
            state[4] = 0;
        }
        data_02129d78[0] = 0;
        return;
    }
    case 2: {
        u32 *state = data_02129d78;
        u64 callbackValue;
        // The ROM writes only this halfword, then forwards the full 64-bit stack slot.
        *(u16 *)&callbackValue = payload;
        void (*callback)(u64, void *) = (void (*)(u64, void *))state[4];
        if (callback != 0) {
            callback(callbackValue, (void *)state[5]);
            state[4] = 0;
        }
        data_02129d78[0] = 0;
        return;
    }
    default:
        OS_Terminate();
    }
}
