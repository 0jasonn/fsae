#ifndef ACTOR_OBJECT_OBJECT_HANDLERS_H
#define ACTOR_OBJECT_OBJECT_HANDLERS_H

// Object handlers and the data they read (all C++ linkage: original names have OBJ_WORK_* signatures).
#include "engine/functions.h"

void set1f_move(Entity *e);          // 0x0205a050
void connect_btn(Entity *e);         // 0x0205a480
void set2a_init(Entity *e);          // 0x0205a508
void Set2d(Entity *e);               // 0x0205a80c
void set2f_init(Entity *e);          // 0x0205af04
void open_move(Entity *e);           // 0x0205c158
void set25_init(Entity *e);          // 0x020665dc
void set25_end(Entity *e);           // 0x0206672c
void oplogo_kentama(Entity *e);      // 0x0206884c
void set43_gensoku(Entity *e);       // 0x0206cb1c
void tama0a_type1_init(Entity *e);   // 0x0207ccfc
void tama06_rlarge(Entity *e);       // 0x0207f0cc

// Callees that functions.h does not declare yet
void rewlever(Entity *e);            // 0x0205b024, set2f_2.cpp
void AshimotoCheck(Entity *e);
void recell1(Entity *e);             // 0x02067040, parked
void breakSmokeSet(Entity *e);       // 0x02067770, parked (C++ linkage: symbol _Z13breakSmokeSetP9OBJ_WORK_)

// Data
extern const u8 data_020d8a54[];                 // hitbox of the lever
extern const u8 data_020dca70[];                 // hitbox of the tama0a type 1 ball
extern const u8 *const set25_hitboxTable[];      // hitbox per entity type (declared const: the load is hoisted)
extern u32 em12_typeMasks[];
extern const u32 flagBits[];

#endif
