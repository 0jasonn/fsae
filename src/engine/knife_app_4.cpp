#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/m4a.h"

// KnifeApp::TextTokenizer_initWithData (0x0208dc84): takes the message data and its size, frees a previous buffer and
// initializes the three text tokenizers (at +0x1bc, +0x44 and +0x180) with the data and a pool each. The pools (0x400,
// 0x1000 and 0x400 bytes) are allocated the first time.
extern "C" void KnifeApp_TextTokenizer_initWithData(void *self, void *data, u32 size);
ARM void KnifeApp_TextTokenizer_initWithData(void *self, void *data, u32 size) {
    u8 *app;

    app = (u8 *)self;
    if (*(void **)(app + 0x30) != NULL) {
        Knife_Message_TextTokenizer_finalize(app + 0x44);
        func_0208e188(*(void **)(app + 0x30));
        *(u32 *)(app + 0x40) = size;
        *(void **)(app + 0x30) = data;
        Knife_Message_TextTokenizer_initialize(app + 0x1bc, *(void **)(app + 0x30), *(u32 *)(app + 0x40), *(void **)(app + 0x34), 0x400);
        Knife_Message_TextTokenizer_initialize(app + 0x44, *(void **)(app + 0x30), *(u32 *)(app + 0x40), *(void **)(app + 0x38), 0x1000);
        Knife_Message_TextTokenizer_initialize(app + 0x180, *(void **)(app + 0x30), *(u32 *)(app + 0x40), *(void **)(app + 0x3c), 0x400);
    } else {
        *(void **)(app + 0x30) = data;
        *(u32 *)(app + 0x40) = size;
        *(void **)(app + 0x34) = func_0208e148(0x400);
        Knife_Message_TextTokenizer_initialize(app + 0x1bc, *(void **)(app + 0x30), *(u32 *)(app + 0x40), *(void **)(app + 0x34), 0x400);
        *(void **)(app + 0x38) = func_0208e148(0x1000);
        Knife_Message_TextTokenizer_initialize(app + 0x44, *(void **)(app + 0x30), *(u32 *)(app + 0x40), *(void **)(app + 0x38), 0x1000);
        *(void **)(app + 0x3c) = func_0208e148(0x400);
        Knife_Message_TextTokenizer_initialize(app + 0x180, *(void **)(app + 0x30), *(u32 *)(app + 0x40), *(void **)(app + 0x3c), 0x400);
    }
}

extern const char *data_0211abfc;
extern u8 *data_02171e08;
extern u8 *data_02171e18;

// KnifeApp_loadField20 (0x0208dd8c): loads the file named by data_0211abfc into the object at +0x20 (when it could be read)
extern "C" void KnifeApp_loadField20(void *self);
ARM void KnifeApp_loadField20(void *self) {
    u32 size;
    void *buffer;

    buffer = loadFile(&size, data_0211abfc, 0x20);
    if (buffer == NULL) {
        return;
    }
    TextBox_SetDefaultHandler((u8 *)self + 0x20, buffer);
}

// KnifeApp::getZeldaResource (0x0208ddcc): the data of a resource, without its size
ARM u8 *KnifeApp_getZeldaResource_08ddcc(void *a, s32 id) {
    s32 size;

    return (u8 *)KnifeApp_getZeldaResource_08dde0(a, &size, id);
}
