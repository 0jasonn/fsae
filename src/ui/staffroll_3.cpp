#include "engine/functions.h"
#include "knife/message/text_tokenizer.h"
#include "knife/message/textrender.h"

extern u8 data_02180da8[];
extern u8 data_02180e24[];

// Restores the previous tokenizer pool and frees the staff-roll pool.
void subTask_staffroll_release(void) {
    s32 zero;
    void *app;
    void *staffRollPool;

    zero = 0;
    if (*(s32 *)(data_02180da8 + 8) == 0) {
        return;
    }

    func_02082c54((void *)zero);
    ((Knife::Message::TextRenderer *)data_02180e24)->finalize();
    staffRollPool = *(void **)((u8 *)KnifeApp_getInstance() + 0x58);
    app = KnifeApp_getInstance();
    ((Knife::Message::TextTokenizer *)((u8 *)app + 0x44))
        ->changeMemoryPool(*(void **)(data_02180da8 + 8), *(u32 *)(data_02180da8 + 4));
    *(s32 *)(data_02180da8 + 8) = zero;
    *(s32 *)(data_02180da8 + 4) = zero;
    func_0208e188(staffRollPool);
}

// subTask_staffroll_releaseEntry (0x020adfe4): entry of the release step, jumps to subTask_staffroll_release
void subTask_staffroll_releaseEntry(void) {
    subTask_staffroll_release();
}
