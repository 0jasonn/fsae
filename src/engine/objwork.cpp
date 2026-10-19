#include "engine/functions.h"
#include "engine/misc_d.h"
#include "engine/objwork.h"
#include "global.h"
#include "types.h"

// Data used by the entity pool and its lists (declared here, not in a shared header yet)
extern u8 data_0212f890[];
extern u8 data_02134290[];
extern u8 data_02134890[];
extern u8 data_021348d4;
extern u8 data_0212c4f4;
extern u8 data_0212c4cc;
extern const u8 data_020d7c60[];
extern const u8 data_020d7dc8[];
extern u8 data_02134dd0[];
extern u16 data_0213493c[];
extern EntityNode *data_0212c52c;
extern EntityNode data_0212c6b8[];
extern EntityFunc data_02103c50[];
void func_02084460(void);

// Entities are 0x80 bytes apart in the pool
#define ENTITY_POOL_STRIDE 0x80

// Clears the whole entity pool (0x5000 bytes)
ARM void ObjWorkPoolClear(void) {
    OSi_CpuClear32(0, data_0212f890, 0x5000);
}

// Resets every list head to point at itself and clears the three list counters
ARM void ObjMoveInit(void) {
    EntityNode *end;
    EntityNode *node;

    node = data_0212c6b0;
    end = data_0212c6f0;
    if (node < end) {
        do {
            node->next = node;
            node->prev = node;
            node++;
        } while (node < end);
    }
    data_0212c4f4 = 0;
    data_021348d4 = 0;
    data_0212c4cc = 0;
}

// Runs the per-kind update function of every entity in every list. data_0212c52c follows the walk so that an entity
// removed by its own update does not break the loop.
ARM void ObjMove(void) {
    EntityNode *node;
    EntityNode *end;
    EntityNode *list;

    data_0213493c[0] = data_0213493c[1] = data_0213493c[2] = data_0213493c[3] = 0xffff;
    list = data_0212c6b0;
    end = data_0212c6f0;
    while (list < end) {
        node = list->next;
        data_0212c52c = node;
        if (node != list) {
            do {
                data_02103c50[((Entity *)node)->unk_08]((Entity *)node);
                if (node == data_0212c52c) {
                    func_02084460();
                }
                node = data_0212c52c->next;
                data_0212c52c = node;
            } while (node != list);
        }
        if (list == data_0212c6b8) {
            AfterPlayer();
        }
        list++;
    }
    DeletePutWork();
}

// First free entity in the main pool (its link word is 0), or NULL
ARM Entity *GetObjWork(void) {
    u8 *p;
    u8 *end;

    p = data_0212f890;
    end = data_02134290;
    if (p < end) {
        do {
            if (*(u32 *)p == 0) {
                return (Entity *)p;
            }
            p += ENTITY_POOL_STRIDE;
        } while (p < end);
    }
    return 0;
}

// Next free entity after start, searching up to data_02134890
ARM Entity *GetObjWork2(Entity *start) {
    u8 *p;
    u8 *end;

    p = (u8 *)start + ENTITY_POOL_STRIDE;
    if (p >= data_02134290) {
        return 0;
    }
    end = data_02134890;
    if (p < end) {
        do {
            if (*(u32 *)p == 0) {
                return (Entity *)p;
            }
            p += ENTITY_POOL_STRIDE;
        } while (p < end);
    }
    return 0;
}

// First free entity of the special pool (data_02134290..data_02134890)
ARM Entity *GetObjWorkSp(void) {
    u8 *p;
    u8 *end;

    p = data_02134290;
    end = data_02134890;
    if (p < end) {
        do {
            if (*(u32 *)p == 0) {
                return (Entity *)p;
            }
            p += ENTITY_POOL_STRIDE;
        } while (p < end);
    }
    return 0;
}

// Takes a free entity for an enemy with the given id and registers it in list 4
ARM Entity *GetEnemyWork(u16 id) {
    Entity *e;

    e = GetObjWork();
    if (e == 0) {
        return 0;
    }
    e->unk_08 = 3;
    e->unk_09 = (u8)id;
    RegistObjWork(4, e);
    return e;
}

// Takes a free entity for a shot with the given id and registers it in list 5
ARM Entity *GetTamaWork(u16 id) {
    Entity *e;

    e = GetObjWork();
    if (e == 0) {
        return 0;
    }
    e->unk_08 = 4;
    e->unk_09 = (u8)id;
    RegistObjWork(5, e);
    return e;
}

// Takes a free entity for a shot with the given id and registers it in list 3
ARM Entity *GetTamaWork2(u16 id) {
    Entity *e;

    e = GetObjWork();
    if (e == 0) {
        return 0;
    }
    e->unk_08 = 4;
    e->unk_09 = (u8)id;
    RegistObjWork(3, e);
    return e;
}

// Allocates a child of parent (same kind and list), copies its type and position data and registers it
ARM Entity *GetChildWork(Entity *parent, u8 type, u8 type2) {
    Entity *child;
    u8 kind;

    child = GetObjWork();
    if (child != 0) {
        kind = parent->unk_08;
        child->unk_08 = kind;
        child->unk_09 = parent->unk_09;
        child->type = type;
        child->type2 = type2;
        child->unk_50 = parent->unk_50;
        child->unk_52 = parent->unk_52;
        RegistObjWork(data_020d7c60[kind], child);
    }
    return child;
}
