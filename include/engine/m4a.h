#ifndef WIP_D_M4A_H
#define WIP_D_M4A_H

#include "types.h"
#include "engine/knife_file_2.h"
#include "engine/knife_sound.h"

// The sound globals at data_02176238 (also the file table of knife_file_2.h): flags, a frame counter, the wave id of
// the song being started, the DatalinkReader tables and the heap memory.
typedef struct M4aSoundTable {
    /* 00 */ u8 flags;        // bit 0: a pause is pending
    /* 01 */ u8 unk_01;
    /* 02 */ u8 delay;        // frames until the pending wave id is handled
    /* 03 */ u8 unk_03;
    /* 04 */ u16 waveId;
    /* 06 */ u8 unk_06[0x0a];
    /* 10 */ void *heapMemory;
    /* 14 */ u8 *bitmap;      // one bit per song number, set while the number is loaded
    /* 18 */ void *table2;
    /* 1c */ void *records;   // Knife::File::FileRecord table (the FileTable records)
} M4aSoundTable;

// One record of the FileTable records array (0x30 bytes); only the word at 0x10 is used by the m4a song code
typedef struct M4aRecord {
    /* 00 */ u8 unk_00[0x10];
    /* 10 */ u16 field10;
    /* 12 */ u8 unk_12[0x1e];
} M4aRecord;

// The DatalinkReader (0x10 bytes): three pointers and a flag, all zeroed by the constructor and finalize
class DatalinkReader {
public:
    DatalinkReader(void);
    ~DatalinkReader(void);
    BOOL initialize(const void *data, u32 size);
    void finalize(void);
    void *getDataBuffer(s32 index) const;
    u32 getDataSize(s32 index) const;

    void *buffer;      // 0x00
    void *table;       // 0x04
    void *tableEnd;    // 0x08
    u8 unk_0c;         // 0x0c
};

extern "C" {
// Calls from the m4a code into other units (dsd names where the function has none yet)
void Knife_File_Entity_sync(Knife::File::Entity *self);
u32 Knife_File_Entity_getField58(Knife::File::Entity *self);
BOOL Knife_Sound_Heap_initialize(void *heap, void *memory, u32 size);
BOOL Knife_Sound_MemoryArchive_initialize(void *archive, void *data);
void Knife_Sound_DataManager_loadGroup(void *manager, s32 group, void *heap);
void *func_0208e148(u32 size);
void Knife_Sound_System_update(void);
void Knife_Sound_System_initialize(void);
void Knife_Sound_System_fwd_08c630(void);
void Knife_Sound_Handle_stop(void *handle, s32 a, s32 b);
void Knife_Sound_Handle_volume(void *handle, s32 a, s32 b);
void Knife_Sound_SequenceHandle_fwdPlayer_08c4a0(void *handle, s32 value);
s32 Knife_Sound_SequenceHandle_getPlayerNumber(void *handle);
KnifeSoundWaveHandle *Knife_Sound_System_getWaveHandle(s32 index);
void *Knife_Sound_System_findHandle(u32 id);
void knifeSoundSetWordReturnOne(void *manager, void *archive, s32 a, s32 b);
void *knifeSoundForwardHandle(void *self, void *heap);
void *Knife_Sound_ArchivePlayer_startSequenceArchive(void *self, s32 a, s32 b, s32 c, s32 d, s32 e);
void SndTable_SetWord4(s32 index, u16 value);
s32 Menu_GetSlotWord(s32 a);
void func_020bf8fc(s32 a, s32 b);
BOOL m4aLoadingCheck(s32 group);
u32 m4aSongNumStart(u16 songNum);
u32 m4aSongNumIsPlaying(u16 songNum);
u32 m4aSongNumContinue(u32 songNum, u32 arg);
u32 func_0208d260(u32 songNum);
u32 knifeSoundGetFlag0e(void *handle);
u16 MPlayGetVolume(u16 songNum);
void m4aSongNumSetParam(u16 songNum, u16 unused, s32 param);
void m4aMPlayAllStop(void);
void m4aEnterManual(void);
void Knife_Sound_System_pause(s32 pause);
void SndTable_SetByte8(s32 a, s32 b);
void SndMaster_SetPan(s32 a);
s32 GzFile_open(void *file, const char *path);
u32 GzFile_getLength(void *file);
u32 GzFile_read(void *file, void *dst, u32 size);
void GzFile_close(void *file);
void m4aReleaseWaveData(s32 index, s32 which);
extern char data_0211abd4[]; // name of the file the sound init opens first
extern char data_0211abe8[]; // name of the file the sound init opens second
extern u8 data_02176239[];   // the sound object placed one byte past data_02176238
extern u8 data_02176240[];   // the Knife::Sound::Heap
extern char data_0211ad1c[];
void KnifeApp_loadField20(void *self);
void KnifeApp_TextTokenizer_initWithData(void *self, void *data, u32 size);
void m4aSoundInit(void);
void Knife_Message_TextTokenizer_finalize(void *self);
extern char data_0211af7c[];
void func_020c4ec0(void *obj, void *buffer);
void Knife_Message_TextTokenizer_initialize(void *self, const void *data, u32 size, void *pool, u32 poolSize);
void *loadFile(u32 *size, const char *path, s32 align);
u8 *KnifeApp_getZeldaResource_08ddcc(void *a, s32 id);
extern u8 data_02176244[];   // the Knife::Sound::DataManager
extern u8 data_02176338[];   // the Knife::Sound::MemoryArchive
}

// Calls and data of the KnifeApp singleton code
extern "C" {
void Knife_Comm_WirelessIcon_WirelessIcon(void *self);
void Knife_Hud_HudManager_ctor(void *self);
void Knife_Message_TextTokenizer_ctor_08e3b4(void *self);
void Chain_Push(void *obj, void *dtor, void *handle);
extern u32 data_021763dc;
extern u8 data_021763ec[];
extern u8 data_021763f0[];
extern u8 data_021763e0[];
extern u8 data_02176430[];
extern char data_0211ed30[];
extern char data_0211ed90[];
}

// C++ (mangled) functions called by the m4a code
void Menu_SetMasterVolume(long volume);

#endif
