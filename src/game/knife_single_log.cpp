#include "engine/functions.h"
#include "global.h"
#include "game/knife_single_log.h"

// Knife::Single::SinglePlay::SinglePlayLog, 0x0209fa4 to 0x0209a02c. The constructor stays a plain extern "C" function.

namespace Knife {
namespace Single {
namespace SinglePlay {

// SinglePlayLog::SinglePlayLog() (0x0209fa4)
extern "C" SinglePlayLog *Knife_Single_SinglePlay_SinglePlayLog_SinglePlayLog(SinglePlayLog *self);
ARM SinglePlayLog *Knife_Single_SinglePlay_SinglePlayLog_SinglePlayLog(SinglePlayLog *self) {
    self->Initialize();
    return self;
}

// SinglePlayLog::Initialize() (0x0209fb8)
ARM void SinglePlayLog::Initialize(void) {
    kind = 0;
    *(u32 *)&pos2 = 0;
    *(u32 *)&pos1 = 0;
    c = 0;
    e = 0;
    d = 0;
}

// SinglePlayLog::SetPos(POS const&, POS const&, unsigned short, long, long, long) (0x0209fd8)
ARM void SinglePlayLog::SetPos(const POS &a, const POS &b, u16 kind_, s32 c_, s32 d_, s32 e_) {
    *(u32 *)&pos1 = *(const u32 *)&a;
    *(u32 *)&pos2 = *(const u32 *)&b;
    kind = kind_;
    c = c_;
    d = d_;
    e = e_;
}

// SinglePlayLog::CheckEqualPos(POS const&, POS const&) const (0x0a008): nonzero unless both positions match
ARM int SinglePlayLog::CheckEqualPos(const POS &a, const POS &b) const {
    return !(*(const u32 *)&pos1 == *(const u32 *)&a && *(const u32 *)&pos2 == *(const u32 *)&b);
}

// SinglePlayLogList::SinglePlayLogList() (0x0a02c): constructs the entries, then Initialize.
extern "C" SinglePlayLogList *Knife_Single_SinglePlay_SinglePlayLogList_SinglePlayLogList(SinglePlayLogList *self);
ARM SinglePlayLogList *Knife_Single_SinglePlay_SinglePlayLogList_SinglePlayLogList(SinglePlayLogList *self) {
    SinglePlayLog *end = self->log + 128;
    SinglePlayLog *entry = self->log;

    do {
        Knife_Single_SinglePlay_SinglePlayLog_SinglePlayLog(entry);
        entry++;
    } while (entry < end);
    self->Initialize();
    return self;
}

// SinglePlayLogList::Initialize() (0x0a060)
ARM void SinglePlayLogList::Initialize(void) {
    oldest = 0;
    current = 0;
    unk_02[1] = 0;
    unk_02[0] = 0;
    distance = 0;
    sumB = 0;
    sumA = 0;
}

}
}
}
