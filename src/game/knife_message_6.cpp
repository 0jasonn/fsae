#include "engine/functions.h"
#include "global.h"
#include "game/knife_message.h"

// Functions in this file (original names from the debug build):
//   MessageTextRender::onReadTextSETag (0x020a08f0); onReadSelectTag (0x020a089c) is parked in scratch/agentE/nonmatching

namespace Knife {
namespace Message {

// MessageTextRender::onReadTextSETag(Voice) (0x020a08f0): stores the voice of the speech tag (voices 0 to 3 only)
ARM void MessageTextRender::onReadTextSETag(Voice voice) {
    switch (voice) {
    case VOICE_0:
    case VOICE_1:
    case VOICE_2:
    case VOICE_3:
        sceneInfo->voice = voice;
        break;
    }
}

}
}
