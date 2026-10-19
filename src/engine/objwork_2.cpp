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

// Frees every entity whose index is listed in data_02134dd0 (count in data_021348d4)
ARM void DeletePutWork(void) {
    u8 *table;
    u8 count;

    table = data_02134dd0;
    count = data_021348d4;
    data_021348d4 = count - 1;
    if (count != 0) {
        do {
            OSi_CpuClear32(0, data_0212f890 + (*table << 7), 0x80);
            table++;
            count = data_021348d4;
            data_021348d4 = count - 1;
        } while (count != 0);
    }
    data_021348d4 = 0;
}

// Appends e to the end of a list and counts it in the matching counter
ARM void RegistObjWork(int list, Entity *e) {
    EntityNode *head;

    head = &data_0212c6b0[list];
    ((EntityNode *)e)->next = head;
    ((EntityNode *)e)->prev = head->prev;
    head->prev->next = (EntityNode *)e;
    head->prev = (EntityNode *)e;
    if (e->hitbox == 0) {
        e->hitbox = data_020d7dc8;
    }
    e->unk_5e.b0 = 2;
    if ((u8 *)e < data_02134290) {
        data_0212c4f4++;
    } else {
        data_0212c4cc++;
    }
}

// Moves the first entity of a list to its end (no-op for lists with at most one entry)
ARM void RotateObjWork(u8 list) {
    EntityNode *head;
    EntityNode *node;

    head = &data_0212c6b0[list];
    node = head->next;
    if (node == head->prev) {
        return;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
    if ((u8 *)node < data_02134290) {
        data_0212c4f4--;
    } else {
        data_0212c4cc--;
    }
    RegistObjWork(list, (Entity *)node);
}

// First entity of list with the given id, or NULL
ARM Entity *SearchWork(s32 id, s32 list) {
    EntityNode *head;
    EntityNode *node;

    head = &data_0212c6b0[list];
    node = head->next;
    while (node != head) {
        if (((Entity *)node)->unk_09 == id) {
            return (Entity *)node;
        }
        node = node->next;
    }
    return 0;
}

// Next entity after start in list with the same id as start, or NULL
ARM Entity *SearchWorkNext(Entity *start, s32 list) {
    EntityNode *head;
    EntityNode *node;
    u8 id;

    head = &data_0212c6b0[list];
    node = ((EntityNode *)start)->next;
    if (node != head) {
        id = start->unk_09;
        do {
            if (((Entity *)node)->unk_09 == id) {
                return (Entity *)node;
            }
            node = node->next;
        } while (node != head);
    }
    return 0;
}
