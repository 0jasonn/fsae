#ifndef SDK_OS_OS_OWNER_INFO_H
#define SDK_OS_OS_OWNER_INFO_H

// TwlSDK OS owner information (the console's user settings and MAC address in the shared area).
#include "types.h"

// Firmware user settings as the ARM7 leaves them at 0x02fffc80; the DSi extension (0x17c bytes in) follows.
typedef struct OsNvramUserInfo {
    u8 unk_00[2];            // 0x00
    u8 favoriteColor : 4;    // 0x02
    u8 unk_02b4 : 4;
    u8 birthMonth;           // 0x03
    u8 birthDay;             // 0x04
    u8 unk_05;               // 0x05
    u16 nickName[10];        // 0x06
    u8 nickNameLength;       // 0x1a
    u8 unk_1b;               // 0x1b
    u16 comment[26];         // 0x1c
    u8 commentLength;        // 0x50
    u8 unk_51;               // 0x51
    u8 unk_52[0x64 - 0x52];  // 0x52: includes the touch panel calibration points at 0x58 (see TpUserInfo in tp.cpp)
    u16 language : 3;        // 0x64
    u16 unk_64b3 : 13;
    u8 unk_66[0x17c - 0x66]; // 0x66
    const u8 *countryInfo;   // 0x17c: bytes 5 and 6 are the country and the language of OS_GetOwnerInfoEx
} OsNvramUserInfo;

// Owner information as returned by OS_GetOwnerInfo (0x54 bytes) and OS_GetOwnerInfoEx (0x58 bytes).
typedef struct OsOwnerInfo {
    u8 language;             // 0x00
    u8 favoriteColor;        // 0x01
    u8 birthMonth;           // 0x02
    u8 birthDay;             // 0x03
    u16 nickName[11];        // 0x04: zero terminated
    u16 nickNameLength;      // 0x1a
    u16 comment[27];         // 0x1c: zero terminated
    u16 commentLength;       // 0x52
    u8 country;              // 0x54: OS_GetOwnerInfoEx only
    u8 unk_55[3];            // 0x55
} OsOwnerInfo;

#define OS_NVRAM_USER_INFO (*(OsNvramUserInfo *)0x02fffc80)

extern "C" {
void OS_GetOwnerInfo(void *info);   // fills an OsOwnerInfo (callers pass a byte buffer)
void OS_GetOwnerInfoEx(void *info); // fills an OsOwnerInfo including country
void OS_GetMacAddress(u8 *dest);
}

#endif
