#include "engine/sndpcm.h"

// SndPcmPlayer_Start (0x020bf540): sets up a hardware PCM channel (format 0 = PCM8, 1 = PCM16, 2 = ADPCM; the loop
// start and length are counted in words), starts its timer and records the playing state and the command tag.
s32 SndPcmPlayer_Start(SndPcmPlayer *self, s32 format, const void *data, s32 repeat, s32 loopStart, s32 length,
                       s32 rate, s32 volume, s32 divisor, s32 pan) {
    s32 start;
    s32 words;
    u64 timer;

    switch (format) {
    case 2:
        start = loopStart >> 3;
        words = (length >> 3) - start;
        break;
    case 0:
        start = loopStart >> 2;
        words = (length >> 2) - start;
        break;
    case 1:
        start = loopStart >> 1;
        words = (length >> 1) - start;
        break;
    }
    timer = 0x7fd87f8000ULL / rate / divisor;
    if (timer < 0x10) {
        timer = 0x10;
    } else if (timer > 0xffff) {
        timer = 0xffff;
    }
    SND_SetupChannelPcm(self->channel, format, data, repeat ? 1 : 2, start, words, volume, 0, (s32)timer, pan);
    SND_StartTimer(1 << self->channel, 0, 0, 0);
    self->playing = 1;
    self->unk_0c = 0;
    self->tag = SND_GetCurrentCommandTag();
    self->rate = rate;
    return 1;
}
