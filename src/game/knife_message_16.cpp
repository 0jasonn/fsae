#include "engine/functions.h"
#include "global.h"

// Functions in this file (invented name, the debug build has none):
//   KnifeInfoGetter::noop (0x020a16c0): an empty function after KnifeInfoGetter::getVariable

// KnifeInfoGetter::noop() (0x020a16c0): does nothing
extern "C" void Knife_Message_KnifeInfoGetter_noop(void *a);
ARM void Knife_Message_KnifeInfoGetter_noop(void *a) {
}
