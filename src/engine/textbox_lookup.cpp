#include "engine/functions.h"
#include "global.h"

// TextBox_LookupEntry (provisional name, TextBox_LookupEntry): maps value through the range entry. The kind halfword at +4
// selects the rule: 0 base at +0xc plus value - low (low at +0), 1 a halfword table at +0xc indexed by value - low, 2 a
// binary search of the count at +0xc (records of two halfwords, key then value, from +0xe); 0xffff for other kinds or
// when no key matches.
extern "C" u32 TextBox_LookupEntry(u8 *entry, u32 value);
ARM u32 TextBox_LookupEntry(u8 *entry, u32 value) {
    u32 result;
    u8 *first;
    u8 *last;
    u8 *mid;
    s32 index;
    u16 kind;

    result = 0xffff;
    kind = *(u16 *)(entry + 4);
    switch (kind) {
    case 0:
        result = (u16)(*(u16 *)(entry + 0xc) + (value - *(u16 *)entry));
        break;
    case 1:
        result = *(u16 *)(entry + 0xc + (value - *(u16 *)entry) * 2);
        break;
    case 2:
        first = entry + 0xe;
        last = first + (*(u16 *)(entry + 0xc) - 1) * 4;
        if (first <= last) {
            do {
                index = (last - first) / 4 / 2;
                mid = first + index * 4;
                if (*(u16 *)mid < value) {
                    first = mid + 4;
                } else if (value < *(u16 *)mid) {
                    last = mid - 4;
                } else {
                    result = *(u16 *)(mid + 2);
                    break;
                }
            } while (first <= last);
        }
        break;
    }
    return result;
}
