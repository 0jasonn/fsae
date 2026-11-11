#ifndef WIP_E_STAFFROLL_E_H
#define WIP_E_STAFFROLL_E_H

#include "engine/functions.h"
#include "knife/message/text_tokenizer.h"

// Minimal views of Knife::Message::RenderTarget and TextRenderer: only the members the staff roll setup calls.
namespace Knife {
namespace Message {
class RenderTarget;
class TextRenderer {
public:
    BOOL initialize(u32 poolSize);
    s32 renderText(const RenderTarget *target, const u16 *str);
    u8 unk_00[0x98];
    s32 unk_98;
    s32 unk_9c;
};
}
}

// Fields of the staff roll state (data_02180da8) the setup writes
typedef struct StaffRollState {
    /* 00 */ u8 started;
    /* 01 */ u8 finale;
    /* 02 */ u8 unk_02[2];
    /* 04 */ s32 appField5c;
    /* 08 */ s32 appField58;
    /* 0c */ s32 pending;
    /* 10 */ s32 tokenIndex;
    /* 14 */ s32 ready;
} StaffRollState;

extern StaffRollState data_02180da8;
extern u8 data_02180e24[];
extern u8 data_02180fe0[];
extern u8 data_0217d23c[];
extern const u16 data_021250c8[];
extern const u16 data_021250d0[];
extern s32 OamRing_dmaNo;

extern "C" {
void GXS_SetGraphicsMode(u32 mode);
void Vram_SetBankGroupA(u32 a);
void Vram_SetBankGroupB(u32 a);
void *func_0208e148(u32 size);
void DC_FlushRange(const void *base, u32 size);
void MI_WaitDma(s32 channel);
s32 KnifeApp_getCurrentLanguage(void *app);
void Knife_Message_setPendingPtr(u32 a);
void Knife_Message_RenderTarget_initialize_forBG(Knife::Message::RenderTarget *target, s32 a, s32 b, s32 c, s32 d, s32 e,
                                                 s32 f, s32 g, s32 h, s32 i, const u16 *text);
void subtask_resourceCtrlCallback(void);
void subTask_staffroll_init(void);
void subTaskSetBG0Offset_reset(void);
void subTaskSetBG1Offset_reset(void);
void subTaskSetBG2Offset_reset(void);
void subTaskSetBG3Offset_reset(void);
}
void subTask_setupBuffer(u32 mode);

#endif
