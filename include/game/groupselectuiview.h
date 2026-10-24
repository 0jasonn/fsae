#ifndef WIP_F_GROUPSELECTUIVIEW_H
#define WIP_F_GROUPSELECTUIVIEW_H

// groupSelectUIView: the room list of the multiplayer group select screen. The list has four room slots inside the
// view (0x20 bytes each, from 0x34). Each room has a UIObject in data_0217eb2c (indexed by RoomInfo::uiIndex) that
// slides in and out of the screen with the list.

#include "types.h"
#include "game/baseduiview.h"
#include "game/uiobject.h"

// Text handle of Knife::Message::Text (handle, string and kind)
typedef struct KnifeMsgText {
    u32 handle;
    const u16 *str;
    u32 kind;
} KnifeMsgText;

class groupSelectUIView : public basedUIView {
public:
    // One room slot (0x20 bytes). The first six bytes are the id of the room.
    struct RoomInfo {
        u8 id[6];       // 0x00: id of the room, compared with the arguments of addRoomPane
        u8 uiIndex;     // 0x06: index of the room's UIObject in data_0217eb2c
        u8 paneNo;      // 0x07: text pane of the room (two per room), see getRoomInfoFromTextID
        u8 active;      // 0x08: set when the slot holds a room, cleared by clearRoom
        u8 sortKey;     // 0x09: sort key of the room, largest first in roomSort
        u8 nameIndex;   // 0x0a: picks one of four name strings in getText
        u8 unk_0b;      // 0x0b
        u8 unk_0c;      // 0x0c: set to 1 by addRoomPane
        u8 unk_0d;
        u16 name[7];    // 0x0e: name of the room, 14 bytes
        u32 state;      // 0x1c: getNumOfRoom counts the leading rooms whose state is above 8
    };

    void move_in(void);
    void move_out(void);
    void move_return(void);
    void moveOutRoom(void);
    void moveReturnRoom(void);
    s32 getNumOfRoom(void) const;
    void writeOamBuffer(RoomInfo *room, s32 index);
    void redrawText(RoomInfo *room, s32 index);
    void removeRoomPane(RoomInfo *room);
    void roomSort(void);
    void updateScan(void);
    BOOL wirelessStartAsChild(void);
    void clearRoom(void);
    void stopScan(void);
    BOOL getText(KnifeMsgText *text, u32 textId, s32 language);
    RoomInfo *getRoomInfoFromTextID(u32 textId);
    void noop(void);
    void viewDidDisapper(void);

    u8 unk_30[0x34 - 0x30];
    RoomInfo slots[4];    // 0x34: the room slots, see RoomInfo
    RoomInfo *rooms[5];   // 0xb4: room list, roomCount entries
    u32 roomCount;        // 0xc8
    u8 unk_cc[0x102 - 0xcc];
    u16 moveFrames;       // 0x102: frames of the room move, set by move_out and move_return
    s8 selectedRoom;      // 0x104: index of the room the wireless start works on (wirelessStartAsChild)
    u8 unk_105[0x110 - 0x105];
};

// Group select data (bss). data_0217f6dc is the slide object of the room list (a UIObject, its fields from 0x14 on
// overlap data_0217f6f0, which the move_in stores address directly). data_0217f314 is the list panel object.
extern u8 data_0217f6dc[];
extern u8 data_0217f6f0[];
extern u8 data_0217f314[];
extern UIObject data_0217eb2c[]; // one UIObject per room, stride 0x58
extern u8 data_0217e6f0[];       // shared UI block, the list panel start is at 0xc4c, 0xc54 and 0xc58
extern u8 data_021806f0[];       // message and UI globals, the pointer at 0x554 leads to the text renderer buffer
extern u8 data_021263cc[];       // text table, the pointer at 0x10 is the string of the room not found
extern u8 data_021263dc[];       // four string pointers for the room names

// Layout constants (rodata)
extern const s32 data_020de834;   // -32: y offset of the slide start
extern const s32 data_020de83c;   // 12: frames of move_in and move_out
extern const s32 data_020de840;   // 24: y offset of the list panel start
extern const s32 data_020de844;   // 12: frames of the move of move_out and move_return
extern const s32 data_020de848;   // 20: frames of the room move
extern const s32 data_020de84c[2]; // list panel position (x, y) in pixels
extern const s32 data_020de864[2]; // slide position (x, y) in pixels

extern "C" u32 func_0208fc6c(const void *a);
extern "C" void func_02091464(void *manager);
extern "C" s32 func_02091d38(void *manager);
extern "C" void *Knife_Comm_WirelessManager_getScanResult(void *manager, s32 index);
extern "C" s32 Knife_Comm_WirelessManager_getState(void *manager);
extern "C" void subTaskSendObjChar(void *buf, u32 offset, u32 size);

// Text render target of a pane (Knife::Message render target, only the fields the room drawing reads)
typedef struct TextRenderTarget {
    u8 unk_00[0x24];
    u8 *cellBase;     // 0x24: cell data, the cell of an entry is at cellBase + cellIndex * 8
    u8 unk_28[0x2c - 0x28];
    u32 unk_2c;       // 0x2c: passed to func_020c6550 on the stack
    u8 unk_30[0x38 - 0x30];
    u32 unk_38;       // 0x38: size arguments of func_020c6550
    u32 unk_3c;
    u8 unk_40[0x44 - 0x40];
    u32 cellIndex;    // 0x44: index of the cell of the entry
} TextRenderTarget;

extern "C" void func_020c6550(void *cell, s32 a1, s32 a2, s32 x, s32 y, s32 a5, s32 a6);
extern "C" void *Knife_Message_GetRenderTarget(s32 pane);

// Palette link table (5 entries, rodata)
typedef struct LinkPalTable {
    s8 entry[5];
} LinkPalTable;
extern const LinkPalTable data_020ded44;

#endif
