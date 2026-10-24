#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/m4a.h"

// KnifeApp::loadAllResource (0x0208db60): loads the three sound and resource files into their globals, the file chosen
// by a byte in data_021348d8, the two Zelda resources and the text file, then starts the sound system.
// The three local tables are copies of rodata tables (paths, destinations and the nine file names).
typedef struct KnifeAppPathTable {
    const char *paths[3];
} KnifeAppPathTable;

typedef struct KnifeAppDestTable {
    void **dests[3];
} KnifeAppDestTable;

typedef struct KnifeAppNameTable {
    const char *names[9];
} KnifeAppNameTable;

extern KnifeAppPathTable data_0211ac2c;
extern KnifeAppDestTable data_0211ac20;
extern KnifeAppNameTable data_0211acf8;
extern u8 data_021348d8[];
extern void *data_02171e18;
extern void *data_02171e10;
extern void *data_02171e0c;

extern "C" void KnifeApp_loadAllResource(void *self);
ARM void KnifeApp_loadAllResource(void *self) {
    u32 size;
    KnifeAppPathTable paths;
    KnifeAppDestTable dests;
    KnifeAppNameTable names;
    u32 i;
    u32 id;

    paths = data_0211ac2c;
    dests = data_0211ac20;
    for (i = 0; i < 3; i++) {
        *dests.dests[i] = loadFile(&size, paths.paths[i], 0x20);
    }
    names = data_0211acf8;
    data_02171e18 = loadFile(&size, names.names[data_021348d8[0]], 0x20);
    id = 0x27e;
    data_02171e10 = KnifeApp_getZeldaResource_08ddcc(self, id);
    data_02171e0c = KnifeApp_getZeldaResource_08ddcc(self, id + 1);
    KnifeApp_loadField20(self);
    {
        void *buffer = loadFile(&size, (const char *)data_0211ad1c, 0x20);
        KnifeApp_TextTokenizer_initWithData(self, buffer, size);
    }
    m4aSoundInit();
}
