#include "global.h"
#include "types.h"
#include "sdk/os/os_owner_info.h"
#include "sdk/mi/mi_memory.h"

void OS_GetOwnerInfo(void *info) {
    OsNvramUserInfo *src = &OS_NVRAM_USER_INFO;
    OsOwnerInfo *dest = (OsOwnerInfo *)info;

    dest->language = src->language;
    dest->favoriteColor = src->favoriteColor;
    dest->birthMonth = src->birthMonth;
    dest->birthDay = src->birthDay;
    dest->nickNameLength = src->nickNameLength;
    dest->commentLength = src->commentLength;
    MIi_CpuCopy16(src->nickName, dest->nickName, 0x14);
    MIi_CpuCopy16(src->comment, dest->comment, 0x34);
    dest->nickName[10] = 0;
    dest->comment[26] = 0;
}

void OS_GetOwnerInfoEx(void *info) {
    OsNvramUserInfo *src = &OS_NVRAM_USER_INFO;
    OsOwnerInfo *dest = (OsOwnerInfo *)info;
    const u8 *countryInfo;

    dest->favoriteColor = src->favoriteColor;
    dest->birthMonth = src->birthMonth;
    dest->birthDay = src->birthDay;
    dest->nickNameLength = src->nickNameLength;
    dest->commentLength = src->commentLength;
    MIi_CpuCopy16(src->nickName, dest->nickName, 0x14);
    MIi_CpuCopy16(src->comment, dest->comment, 0x34);
    dest->nickName[10] = 0;
    dest->comment[26] = 0;
    countryInfo = src->countryInfo;
    dest->country = countryInfo[5];
    dest->language = countryInfo[6];
}
