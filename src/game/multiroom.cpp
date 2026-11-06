#include "actor/object/multiroom.h"

// Multiplayer room setup: places the scroll window around the followed entity, loads the room map and builds the
// inverse cell index tables of the two layers. 0x02056f4c MultiRoomInit

void MultiRoomInit(u16 room) {
    Entity *target;
    s16 targetX;
    s16 targetY;
    u16 *layerCells;
    u16 *layerCells2;
    s16 i;
    u16 cellIndex;

    mapState.offsetX = 0;
    mapState.offsetY = 0;
    target = mapState.target;
    targetX = target->x.HALF.HI;
    targetY = target->y.HALF.HI;
    mapState.unk_14 = 0;
    mapState.unk_12 = 0xe;
    target->layer = 0xe;
    mapState.limitX = 0x3f0;
    mapState.limitY = 0x3f0;
    mapState.originX = 0;
    mapState.originY = 0;
    mapState.startX = targetX;
    mapState.startY = targetY;
    if (targetX < 0x80) {
        mapState.scrollX = 0;
    } else if (mapState.limitX - 0x80 < targetX) {
        mapState.scrollX = mapState.limitX - 0x100;
    } else {
        mapState.scrollX = targetX - 0x80;
    }
    if (targetY < 0x60) {
        mapState.scrollY = 0;
    } else if (mapState.limitY - 0x60 < targetY) {
        mapState.scrollY = mapState.limitY - 0xc0;
    } else {
        mapState.scrollY = targetY - 0x60;
    }

    MemClearFast(triangleTable, 0x800);
    layerCells = data_0215dfa4;
    MIi_CpuClear16(0xffff, layerCells, 0x1000);
    layerCells2 = data_02168fa8;
    layerCells[0] = 0;
    MIi_CpuClear16(0xffff, layerCells2, 0x1000);
    layerCells2[0] = 0;
    MapLoad(data_020d7110[room], 1);
    DataLoad(0x1e);
    bg2StSet();
    if (data_020d714c[room] != 0) {
        BgAnmInit(data_020d714c[room]);
    }

    for (i = 0; i < 0x800; i++) {
        cellIndex = *layerCells;
        if (cellIndex < 0x800) {
            *(u16 *)(data_02158fa0 + cellIndex * 2 + 0x6004) = i;
        }
        layerCells++;
    }
    for (i = 0; i < 0x800; i++) {
        cellIndex = *layerCells2;
        if (cellIndex < 0x800) {
            *(u16 *)(data_02163fa4 + cellIndex * 2 + 0x6004) = i;
        }
        layerCells2++;
    }

    (*(u16 **)data_02163fa4)[1] = mapState.offsetX + mapState.scrollX - mapState.originX;
    (*(u16 **)data_02158fa0)[1] = (*(u16 **)data_02163fa4)[1];
    (*(u16 **)data_02163fa4)[2] = mapState.offsetY + mapState.scrollY - mapState.originY;
    (*(u16 **)data_02158fa0)[2] = (*(u16 **)data_02163fa4)[2];
}
