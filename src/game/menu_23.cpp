#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"
#include "game/menu_wip.h"

// Functions in this file (provisional names, role not confirmed):
//   Menu_CreateEntryDefault (Menu_CreateEntryDefault), Menu_CreateEntryEx (Menu_CreateEntryEx)

extern "C" void Menu_CreateEntryEx(void *out, void *checker, void *a, void *b, void *c, u16 d);

// Menu_CreateEntryDefault (0x020befd0): Menu_CreateEntryEx with a zero sixth argument.
extern "C" void Menu_CreateEntryDefault(void *out, void *checker, void *a, void *b, void *c);
ARM void Menu_CreateEntryDefault(void *out, void *checker, void *a, void *b, void *c) {
    Menu_CreateEntryEx(out, checker, a, b, c, 0);
}

// Menu_CreateEntryEx (0x020beff4): looks up the object for id 0x40628 in the checker (func_020c2c34), makes it with
// func_020bc588 when the lookup found something, then creates the entry with func_020bc84c and stores it in *out.
extern "C" void Menu_CreateEntryEx(void *out, void *checker, void *a, void *b, void *c, u16 d);
ARM void Menu_CreateEntryEx(void *out, void *checker, void *a, void *b, void *c, u16 d) {
    s32 result;

    result = func_020c2c34((MenuChecker *)checker, 0x40628);
    if (result != 0) {
        result = func_020bc588(result);
    }
    func_020bc84c(result, checker, a, b, c, d);
    *(s32 *)out = result;
}
