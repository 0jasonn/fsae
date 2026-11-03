#include "actor/object/ranking5.h"
#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"

// Ranking screen, exit phase machine: 0 starts the message and the fade, 1 waits for the fade, 2 resets the display.
// 0x02055d28 ranking_exit

void ranking_exit(void) {
    u8 msgScreen[0x38];
    u8 *screen;
    u16 msgLines;
    s32 saveResult;

    switch (data_0212c4dc) {
    case 0:
        CgLoad(0x15);
        SetCgColor(0, 0);
        *(u8 **)((u8 *)rankingStepTable + 0x64) = (u8 *)KnifeApp_getInstance() + 0x44;
        screen = msgScreen;
        MIi_CpuCopy32(data_02115298, screen, 0x38);
        saveResult = Save4Swords(localPlayerIndex);
        if (saveResult == 0) {
            msgScreen[0x12] = 0x23;
            msgLines = knife_MakeMsgScreen(0x7ee, screen);
        } else if ((u32)(saveResult - 3) <= 1) {
            Task_Chain(0xb);
        } else {
            msgScreen[0x12] = 3;
            msgLines = knife_MakeMsgScreen(0x7dc, screen);
        }
        SoundReq(0x79);
        data_0212c75c.unk_0a = 0;
        data_0212c75c.unk_0c = -(0xc0 - (msgLines + 2) * 8) / 2;
        data_0212c75c.unk_08 = *(u16 *)(data_020ce4d0 + 0x24);
        data_0212c75c.displayFlags |= 0x100;
        FadeSet(0, 8);
        data_021349c0.timer = 0x78;
        data_0212c4dc++;
        break;
    case 1:
        if (data_0212c5ac != 0) {
            return;
        }
        data_021349c0.timer--;
        if (data_021349c0.timer != 0) {
            return;
        }
        FadeSet(3, 8);
        data_0212c4dc++;
        break;
    case 2:
        if (data_0212c5ac != 0) {
            return;
        }
        DispReset();
        *(u16 *)0x05000000 = 0x6739;
        data_021355a0 = 0x6739;
        Task_Chain(5);
        break;
    }
}

// 0x02055f18 CalcRanking
// Builds the ranking table from the scores, sorts it by score, gives equal scores the same rank and sorts it back
// into player order. 0x02055f18 CalcRanking
void CalcRanking(void) {
    s8 i;
    s8 j;
    u16 rank;
    u8 keyPlayer;
    u8 keyRank;
    u16 keyScore;
    RankingEntry *rk;

    ranking_noop();
    rk = data_02171d00; // local pointer: keeps the table address loads after the call
    for (i = 0; i < data_0212c7c8.playerCount; i++) {
        rk[i].playerIndex = i;
        rk[i].rank = 0;
        if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
            rk[i].score = data_0212c7c8.playerCounters[i];
        } else {
            rk[i].score = data_0212c7c8.score;
        }
    }

    for (i = 1; i < data_0212c7c8.playerCount; i++) {
        keyPlayer = rk[i].playerIndex;
        keyRank = rk[i].rank;
        keyScore = rk[i].score;
        j = i - 1;
        while (j >= 0 && rk[j].score < keyScore) {
            rk[j + 1].playerIndex = rk[j].playerIndex;
            rk[j + 1].rank = rk[j].rank;
            rk[j + 1].score = rk[j].score;
            j--;
        }
        rk[j + 1].playerIndex = keyPlayer;
        rk[j + 1].rank = keyRank;
        rk[j + 1].score = keyScore;
    }

    rank = 1;
    for (i = 1; i < data_0212c7c8.playerCount; i++, rank++) {
        if (rk[i].score == rk[i - 1].score) {
            rk[i].rank = rk[i - 1].rank;
        } else {
            rk[i].rank = rank;
        }
    }

    for (i = 1; i < data_0212c7c8.playerCount; i++) {
        keyPlayer = rk[i].playerIndex;
        keyRank = rk[i].rank;
        keyScore = rk[i].score;
        j = i - 1;
        while (j >= 0 && ((u8 *)rk)[j * 4] > keyPlayer /* same load as rk[j].playerIndex; written this way so it is not reused by the body */) {
            rk[j + 1].playerIndex = rk[j].playerIndex;
            rk[j + 1].rank = rk[j].rank;
            rk[j + 1].score = rk[j].score;
            j--;
        }
        rk[j + 1].playerIndex = keyPlayer;
        rk[j + 1].rank = keyRank;
        rk[j + 1].score = keyScore;
    }
}

// Ranking table accessors. Address -> name:
//   0x0205610c ranking_getKey (provisional, reads the sort key byte of entry 'index' of data_02171d00)
//   0x0205611c ranking_noop (provisional, empty function)

u8 ranking_getKey(u8 index) {
    return data_02171d01[index * 4];
}

void ranking_noop(void) {
}
