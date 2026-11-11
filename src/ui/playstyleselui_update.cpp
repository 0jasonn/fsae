#include "engine/functions.h"
#include "knife/message/playstyle_update.h"
#define CTRL ((FileSelUIViewCtrl *)data_0217e6f0)

extern u8 data_021806f0[];

// playStyleSelUIView::update() (0x020ab190): state machine of the play style select screen (unk_5e is the state):
// 0/1 slide in, 2 choose (single player / wireless), 3 pop the view, 4 wait for the wireless link and push the second
// view, 5 wait for the exchange request and start the save data exchange, 6 wait for its end, 7 countdown
void playStyleSelUIView_update(PlayStyleSelUIView *self) {
    PlayStyleOamRows oamRows = data_020de780;
    void *wirelessManager = func_020909c8();
    s32 wirelessState = Knife_Comm_WirelessManager_getState(wirelessManager);
    s32 i;
    s32 oldChoice;
    s32 slot;
    s32 sel;
    volatile u32 *dispcnt;

    switch (self->unk_5e) {
    case 0:
        playStyleSelUIView_clearScreen(self);
        playStyleSelUIView_move_in(self);
        self->unk_5e = 2;
        break;
    case 1:
        playStyleSelUIView_move_in_return(self);
        self->unk_5e = 2;
        break;
    case 2:
        dispcnt = (volatile u32 *)0x04001000;
        *dispcnt = (*dispcnt & ~0x1f00) | 0x1900;
        if (UIObject_getDurationRatio(&data_0217f1b4) == 0x1000) {
            oldChoice = (s8)self->unk_5d;
            switch (data_0212c510) {
            case 0x80:
                self->unk_5d = oldChoice + 1;
                break;
            case 0x40:
                self->unk_5d = oldChoice - 1;
                break;
            case 2:
                self->unk_5e = 3;
                playStyleSelUIView_move_out_return(self);
                SoundReq(0x44);
                break;
            case 1:
                if (oldChoice == 0) {
                    if (wirelessState == 0) {
                        Knife_Comm_WirelessManager_turnOn(wirelessManager, 0);
                        self->unk_5e = 4;
                        sel = (s8)self->unk_5d;
                        sel = (s8)self->unk_5d;
                    slot = self->entryCount;
                        self->entryCount = slot + 1;
                        self->entries[slot] = sel;
                        playStyleSelUIView_move_out(self);
                        SoundReq(0x3e);
                    }
                } else if (oldChoice == 1) {
                    self->unk_5e = 5;
                    MachiukeStart();
                    sel = (s8)self->unk_5d;
                    slot = self->entryCount;
                    self->entryCount = slot + 1;
                    self->entries[slot] = sel;
                    playStyleSelUIView_move_out(self);
                    SoundReq(0x3e);
                }
                break;
            }
            if (func_02019968() != 0) {
                clamp_s8((signed char &)self->unk_5d, 0, 1);
            } else {
                clamp_s8((signed char &)self->unk_5d, 1, 1);
            }
            if (oldChoice != (s8)self->unk_5d) {
                SoundReq(0x3d);
            }
            CTRL->uiObjects[3].durationFP = 0;
            CTRL->uiObjects[3].pos.x = data_020de88c[(s8)self->unk_5d].x << 12;
            CTRL->uiObjects[3].pos.y = data_020de88c[(s8)self->unk_5d].y << 12;
            fileSelUIViewCtrl_addOamEntry_0ad964(CTRL, 3);
        }
        break;
    case 3:
        if (UIObject_getDurationRatio(&data_0217f1b4) == 0x1000) {
            basedUIView_pop_view((basedUIView *)data_0217e6f0);
        }
        break;
    case 4:
        if (UIObject_getDurationRatio(&data_0217f1b4) == 0x1000 && wirelessState == 2) {
            basedUIView_push_view((basedUIView *)data_0217e6f0, self->secondView);
        }
        break;
    case 5:
        if (func_020280e0() & 0x40) {
            gameState.playerCount = CountBits(func_020280e0() & 0xf);
            exchange_savedata();
            self->unk_5e = 6;
        }
        break;
    case 6:
        if (is_exchange_savedata_end()) {
            func_0202809c();
            self->unk_5c = 1;
            self->unk_5e = 7;
        }
        break;
    case 7:
        if (--self->unk_5c == 0) {
            data_021806f0[0x53e] = 0x84;
        }
        break;
    }
    for (i = 0; i < 2; i++) {
        if ((s8)self->unk_5d == i) {
            fileSelUIViewCtrl_addOamEntry_0ad964(CTRL, oamRows.index[i][0]);
        } else {
            fileSelUIViewCtrl_addOamEntry_0ad964(CTRL, oamRows.index[i][1]);
        }
    }
    fileSelUIViewCtrl_addOamEntry_0ad964(CTRL, 0x17);
}
