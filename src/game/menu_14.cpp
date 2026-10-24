#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"

// Runs the menu main sequence for the menu held by the wrapper.
ARM void Menu_RunFromWrapper(MenuWrapper *w) {
    func_020bce14(w->ptr);
}
