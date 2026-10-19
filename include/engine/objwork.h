#ifndef WIP_C_OBJWORK_H
#define WIP_C_OBJWORK_H

#include "engine/entity.h"

// Entity pool helpers (0x0204bbb8..0x0204c250). Declared here until the reviewer moves them into engine/functions.h.
extern "C" {
void ObjMove(void);
Entity *GetObjWorkSp(void);
void DeletePutWork(void);
Entity *SearchWork(s32 id, s32 list);
Entity *SearchWorkNext(Entity *start, s32 list);
}
void ObjMoveInit(void);
void ObjWorkPoolClear(void);
Entity *GetObjWork2(Entity *e);
Entity *GetChildWork(Entity *parent, u8 type, u8 type2);
void RotateObjWork(u8 list);

#endif
