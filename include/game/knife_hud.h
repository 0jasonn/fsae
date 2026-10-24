#ifndef WIP_E_KNIFE_HUD_H
#define WIP_E_KNIFE_HUD_H

#include "engine/functions.h"
#include "game/knife_message.h"

namespace Knife {
namespace Hud {

// HUD manager (Knife::Hud::HudManager). Only the fields used by the functions matched so far are named.
class HudManager {
public:
    void initialize(void);
    void finalize(void);
    void update(int mode);
    void setActivePlayer(int player);
    void setField70(int player, int value);
    BOOL startCallAnim(int player);
    BOOL isJustStartedCallAnim(int player) const;
    void setStateOne(void);
    void setStateThree(void);
    void setStateNone(void);
    BOOL isGameoverMode(void) const;
    int getPlayerDir(int player) const;
    BOOL getGameOverCharDataType(Knife::Message::Language language) const;

    u8 unk_00[0x04];
    u8 initialized;       // 0x04: set by initialize
    u8 unk_05[0x70 - 0x05];
    int field70[4];       // 0x70: one value per player
    u8 unk_80[0x160 - 0x80];
    int callAnim[4];      // 0x160: call animation state per player
    int state170;         // 0x170: game-over state (0 none, 1 and 3 used by the game-over sequence)
};

}
}

#endif
