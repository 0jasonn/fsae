#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/message/kmsgreader.h"

// Knife::Message::KMsgFileReader::finalize, 0x0208e294

namespace Knife {
namespace Message {

// KMsgFileReader::finalize (0x0208e294): clears the data pointer, the body pointer and the size
void KMsgFileReader::finalize(void) {
    data = NULL;
    body = NULL;
    size = 0;
}

}
}
