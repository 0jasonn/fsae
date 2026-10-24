#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Tail call to Stub_0200b128 (dsd name Forward_0200b10c).
void Stub_0200b128(void);

ARM void Forward_0200b10c(void) {
    Stub_0200b128();
}

// Empty functions (dsd names Stub_0200b118, Stub_0200b11c, Stub_0200b128) and one that returns 0 (Stub_0200b120).
ARM void Stub_0200b118(void) {
}

ARM void Stub_0200b11c(void) {
}

ARM int Stub_0200b120(void) {
    return 0;
}

ARM void Stub_0200b128(void) {
}
