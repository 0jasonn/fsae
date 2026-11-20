#ifndef KNIFE_SUBTASK_SUBTASK_DATA_H
#define KNIFE_SUBTASK_SUBTASK_DATA_H

#include "engine/entity.h"

struct NNSG2dOamManagerInstance;
s32 _get_subtask_data(s32 index);
s32 _get_subtask_data_size(s32 index);
void InitOamManager(NNSG2dOamManagerInstance *manager);

#endif
