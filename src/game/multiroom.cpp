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

    data_0212c648.offsetX = 0;
    data_0212c648.offsetY = 0;
    target = data_0212c648.target;
    targetX = target->x.HALF.HI;
    targetY = target->y.HALF.HI;
    data_0212c648.unk_14 = 0;
    data_0212c648.unk_12 = 0xe;
    target->layer = 0xe;
    data_0212c648.limitX = 0x3f0;
    data_0212c648.limitY = 0x3f0;
    data_0212c648.originX = 0;
    data_0212c648.originY = 0;
    data_0212c648.startX = targetX;
    data_0212c648.startY = targetY;
    if (targetX < 0x80) {
        data_0212c648.scrollX = 0;
    } else if (data_0212c648.limitX - 0x80 < targetX) {
        data_0212c648.scrollX = data_0212c648.limitX - 0x100;
    } else {
        data_0212c648.scrollX = targetX - 0x80;
    }
    if (targetY < 0x60) {
        data_0212c648.scrollY = 0;
    } else if (data_0212c648.limitY - 0x60 < targetY) {
        data_0212c648.scrollY = data_0212c648.limitY - 0xc0;
    } else {
        data_0212c648.scrollY = targetY - 0x60;
    }

    func_02029a50(triangleTable, 0x800);
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

    (*(u16 **)data_02163fa4)[1] = data_0212c648.offsetX + data_0212c648.scrollX - data_0212c648.originX;
    (*(u16 **)data_02158fa0)[1] = (*(u16 **)data_02163fa4)[1];
    (*(u16 **)data_02163fa4)[2] = data_0212c648.offsetY + data_0212c648.scrollY - data_0212c648.originY;
    (*(u16 **)data_02158fa0)[2] = (*(u16 **)data_02163fa4)[2];
}
