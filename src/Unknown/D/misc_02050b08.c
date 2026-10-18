#include "Unknown/D/Misc_D.h"
#include "global.h"

ARM void func_02050b08(void) {
    func_0208455c();
    data_02104a24[data_0212c500]();
    func_02050ef0();
}

ARM s32 func_02050b34(void) {
    EntityNode *head;
    EntityNode *n;
    for (head = data_0212c6b0; head < data_0212c6f0; head++) {
        n = head->next;
        if (n != head) {
            do {
                if (((Entity *)n)->unk_08 == 6 && ((Entity *)n)->unk_09 == 0x28 && ((Entity *)n)->type == 5) {
                    return 0;
                }
                n = n->next;
            } while (n != head);
        }
    }
    return 1;
}

ARM void func_02050b98(void) {
    EntityNode *head;
    EntityNode *n;
    for (head = data_0212c6b0; head < data_0212c6f0; head++) {
        n = head->next;
        if (n != head) {
            do {
                if (((Entity *)n)->unk_08 == 6 && ((Entity *)n)->unk_09 == 0x28 && ((Entity *)n)->type == 0) {
                    ((Entity *)n)->subtimer = 1;
                    break;
                }
                n = n->next;
            } while (n != head);
        }
    }
    {
        EntityNode *h2;
        EntityNode *m;
        EntityNode *p;
        for (h2 = data_0212c6b0; h2 < data_0212c6f0; h2++) {
            m = h2->next;
            if (m != h2) {
                do {
                    if (((Entity *)m)->unk_08 == 6 && ((Entity *)m)->unk_09 == 0x28 && ((Entity *)m)->type == 5) {
                        p = m->prev;
                        DeleteEntity((Entity *)m);
                        m = p;
                    }
                    m = m->next;
                } while (m != h2);
            }
        }
    }
}
