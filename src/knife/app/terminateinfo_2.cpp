#include "engine/functions.h"
#include "engine/data_0212c564.h"
#include "global.h"
#include "engine/blend_request.h"
#include "types.h"
#include "knife/app/knife_hud.h"

#include "engine/vblank_request.h"
extern u16 data_0212c510;  // bit 0 requests the white-out
#include "engine/effect_state.h"

void terminateInfo_move(void) {
    u8 *app;
    EffectState *block;
    u16 timer;

    app = (u8 *)KnifeApp_getInstance();
    switch (data_0212c4dc) {
    case 0:
        if (blendRequest.blendEnabled != 0) {
            return;
        }
        block = &effectState;
        timer = block->timer;
        if (timer != 0) {
            timer = timer - 1;
            block->timer = timer;
            if (block->timer == 0) {
                ((Knife::Hud::HudManager *)(app + 0x1f8))->setStateThree();
            }
        } else {
            ((Knife::Hud::HudManager *)(app + 0x1f8))->update(data_0212c4c8);
            if ((data_0212c510 & 1) != 0) {
                SoundReq(0x3e);
                FadeSet(3, 8);
                eff_white_out_init(0x888);
                data_0212c4dc++;
                block->timer = 4;
            }
        }
        break;
    case 1:
        if (blendRequest.blendEnabled != 0) {
            return;
        }
        timer = effectState.timer;
        if (timer != 0) {
            timer = timer - 1;
            effectState.timer = timer;
            if (effectState.timer == 0) {
                Task_Chain(7);
                subTask_game_start_reload();
                func_020827a8(3);
                data_0212c4dc = 1;
            }
        }
        break;
    }
    data_0212c564();
    func_020830ec();
}
