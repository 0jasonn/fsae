#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/m4a.h"
#include "engine/knife_sound_4.h"

// m4a sound driver front end: m4aSoundInit and pauseWavePlayer (0x0208cda4 to 0x0208d004). m4aSoundMain (0x0208d004)
// is parked in scratch/agentD/nonmatching.

// m4aSoundInit (0x0208cda4): clears the sound globals and the wave tables, opens the two data files, sets up the
// sound heap and the archive, loads the first sound group and starts the wave table.
extern "C" void m4aSoundInit(void);
ARM void m4aSoundInit(void) {
    Knife::File::Entity *entity;
    Knife::File::Entity *entity2;
    void *heapMemory;
    u32 field54;
    u32 field58;
    u16 *list;
    u32 count;
    u32 i;

    ((M4aSoundTable *)&data_02176238)->waveId = 0;
    ((M4aSoundTable *)&data_02176238)->delay = 0;
    ((M4aSoundTable *)&data_02176238)->flags = 0;
    MIi_CpuClearFast(0, data_021762b8, 0x80);
    MIi_CpuClearFast(0, data_02176278, 0x40);

    entity = Knife::File::System::alloc(data_0211abd4);
    Knife_File_Entity_sync(entity);
    {
        DatalinkReader reader;
        field54 = Knife_File_Entity_getField54(entity);
        field58 = Knife_File_Entity_getField58(entity);
        if (reader.initialize((void *)field54, field58)) {
            ((M4aSoundTable *)&data_02176238)->bitmap = (u8 *)reader.getDataBuffer(1);
            ((M4aSoundTable *)&data_02176238)->table2 = reader.getDataBuffer(2);
            ((M4aSoundTable *)&data_02176238)->records = reader.getDataBuffer(3);
            list = (u16 *)reader.getDataBuffer(0);
            count = reader.getDataSize(0) >> 1;
            for (i = 0; i < count; i++) {
                func_020bf800(i, list[i]);
            }
            reader.finalize();
        } else {
            ((M4aSoundTable *)&data_02176238)->bitmap = NULL;
            ((M4aSoundTable *)&data_02176238)->table2 = NULL;
            ((M4aSoundTable *)&data_02176238)->records = NULL;
        }
        Knife::File::System::release(entity);
    }

    entity2 = Knife::File::System::alloc(data_0211abe8);
    Knife_File_Entity_sync(entity2);
    Knife_Sound_System_initialize();
    heapMemory = func_0208e148(0x8000);
    ((M4aSoundTable *)&data_02176238)->heapMemory = heapMemory;
    Knife_Sound_Heap_initialize(data_02176240, heapMemory, 0x8000);
    field54 = Knife_File_Entity_getField54(entity2);
    Knife_Sound_MemoryArchive_initialize(data_02176338, (void *)field54);
    func_0208bdf8(data_02176244, data_02176338, 0, 0);
    Knife_Sound_DataManager_loadGroup(data_02176244, 0, data_02176240);
    func_0208bd24(data_02176239, data_02176240);
    Knife::File::System::release(entity2);
    Knife::File::System::allocGroup(0);
}

// pauseWavePlayer (0x0208cf88): pauses or resumes each playing wave handle and records the flag in the slot table
extern "C" void pauseWavePlayer(s32 pause);
ARM void pauseWavePlayer(s32 pause) {
    s32 i;

    for (i = 0; i < 2; i++) {
        Knife::Sound::WaveHandle *handle = (Knife::Sound::WaveHandle *)Knife_Sound_System_getWaveHandle(i);
        if (handle->isValid()) {
            Knife_Sound_Handle_pause(handle, pause);
            data_021762b8[i + (*(s32 *)((u8 *)handle + 0x4) - 0x1ea) * 2].registered = pause;
        }
    }
}
