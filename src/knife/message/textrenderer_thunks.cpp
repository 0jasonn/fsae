#include "engine/functions.h"
#include "global.h"

// This-adjusting thunks of TextRenderer for its secondary base (ITokenAnalyzer, at this+4): each one subtracts 4 from this
// and jumps to the real tag handler. The compiler generates them for the virtual overrides; they are written as
// instructions because the vtable that would own them cannot be reproduced.
extern "C" void func_020a614c(void);
extern "C" void func_020a6140(void);
extern "C" void func_020a6134(void);
extern "C" void Knife_Message_TextRenderer_onReadColorTag(void);
extern "C" void func_020a6110(void);
extern "C" void Knife_Message_TextRenderer_onReadRightTag(void);
extern "C" void Knife_Message_TextRenderer_onReadCenterTag(void);
extern "C" void Knife_Message_TextRenderer_onReadBlankTag(void);
extern "C" void Knife_Message_TextRenderer_onReadButtonTag(void);
extern "C" void Knife_Message_TextRenderer_onReadPictTag(void);
extern "C" void func_020a5fc8(void);
extern "C" void func_020a5fbc(void);
extern "C" void func_020a5fb0(void);
extern "C" void func_020a5fa4(void);
extern "C" void func_020a5f98(void);
extern "C" void func_020a5f8c(void);
extern "C" void Knife_Message_TextRenderer_onReadNewLine(void);
extern "C" void Knife_Message_TextRenderer_onReadPlainText(void);

extern "C" asm void ITokenAnalyzer_thunk_020a614c(void) {
    ldr ip, =-0x4
    add r0, r0, ip
    b func_020a614c
}

extern "C" asm void ITokenAnalyzer_thunk_020a6140(void) {
    ldr ip, =-0x4
    add r0, r0, ip
    b func_020a6140
}

extern "C" asm void ITokenAnalyzer_thunk_020a6134(void) {
    ldr ip, =-0x4
    add r0, r0, ip
    b func_020a6134
}

extern "C" asm void ITokenAnalyzer_thunk_onReadColorTag(void) {
    ldr ip, =-0x4
    add r0, r0, ip
    b Knife_Message_TextRenderer_onReadColorTag
}

extern "C" asm void ITokenAnalyzer_thunk_020a6110(void) {
    ldr ip, =-0x4
    add r0, r0, ip
    b func_020a6110
}

extern "C" asm void ITokenAnalyzer_thunk_onReadRightTag(void) {
    ldr ip, =-0x4
    add r0, r0, ip
    b Knife_Message_TextRenderer_onReadRightTag
}

extern "C" asm void ITokenAnalyzer_thunk_onReadCenterTag(void) {
    ldr ip, =-0x4
    add r0, r0, ip
    b Knife_Message_TextRenderer_onReadCenterTag
}

extern "C" asm void ITokenAnalyzer_thunk_onReadBlankTag(void) {
    ldr ip, =-0x4
    add r0, r0, ip
    b Knife_Message_TextRenderer_onReadBlankTag
}

extern "C" asm void ITokenAnalyzer_thunk_onReadButtonTag(void) {
    ldr ip, =-0x4
    add r0, r0, ip
    b Knife_Message_TextRenderer_onReadButtonTag
}

extern "C" asm void ITokenAnalyzer_thunk_onReadPictTag(void) {
    ldr ip, =-0x4
    add r0, r0, ip
    b Knife_Message_TextRenderer_onReadPictTag
}

extern "C" asm void ITokenAnalyzer_thunk_020a5fc8(void) {
    ldr ip, =-0x4
    add r0, r0, ip
    b func_020a5fc8
}

extern "C" asm void ITokenAnalyzer_thunk_020a5fbc(void) {
    ldr ip, =-0x4
    add r0, r0, ip
    b func_020a5fbc
}

extern "C" asm void ITokenAnalyzer_thunk_020a5fb0(void) {
    ldr ip, =-0x4
    add r0, r0, ip
    b func_020a5fb0
}

extern "C" asm void ITokenAnalyzer_thunk_020a5fa4(void) {
    ldr ip, =-0x4
    add r0, r0, ip
    b func_020a5fa4
}

extern "C" asm void ITokenAnalyzer_thunk_020a5f98(void) {
    ldr ip, =-0x4
    add r0, r0, ip
    b func_020a5f98
}

extern "C" asm void ITokenAnalyzer_thunk_020a5f8c(void) {
    ldr ip, =-0x4
    add r0, r0, ip
    b func_020a5f8c
}

extern "C" asm void ITokenAnalyzer_thunk_onReadNewLine(void) {
    ldr ip, =-0x4
    add r0, r0, ip
    b Knife_Message_TextRenderer_onReadNewLine
}

extern "C" asm void ITokenAnalyzer_thunk_onReadPlainText(void) {
    ldr ip, =-0x4
    add r0, r0, ip
    b Knife_Message_TextRenderer_onReadPlainText
}
