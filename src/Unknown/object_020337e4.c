#include "Unknown/Object_02033708.h"
#include "global.h"

void func_020347a8(Entity *e);
void func_0203464c(Entity *e, Entity *other, u16 a);
void func_02034730(Entity *e, Entity *other);
void func_0205031c(Entity *e, Entity *other);
extern const u8 data_020d0eb8[];
extern const u8 data_020d0ebe[];
extern const s8 data_020d0ebc[];
extern u16 data_0212c584[];
void func_020852f8(Entity *e, s32 dist, u8 speed);

ARM void func_020337e4(Entity *e) {
    if (!(VE(e->unk_54)->unk_7d & data_020cf9b8[VL(V(e)->unk_7c)->unk_7e])) {
        return;
    }
    func_0204fd40(e);
    if (--e->unk_17 == 0) {
        e->unk_14 = 3;
        e->unk_0c = 0x20;
        V(e)->unk_70 = e->unk_30.HALF.HI;
        V(e)->unk_73 = 0;
        V(e)->unk_72 = 0;
    }
    if (data_021348b8[V(e)->unk_75] != 0) {
        data_021348b8[V(e)->unk_75] = 0;
    }
}

ARM void func_0203386c(Entity *e) {
    func_02050840(e);
    if (e->unk_15 == 5) {
        Entity *player = data_0212ceb0[e->unk_0b].unk_28;
        if (V(e)->unk_74 == 0) {
            player->unk_30.HALF.HI = e->unk_30.HALF.HI + data_020d0f0a[player->unk_2a];
            player->unk_34.HALF.HI = e->unk_34.HALF.HI + data_020d0f0a[player->unk_2a + 1];
            V(e)->unk_74 = 1;
            e->unk_18 = 2;
        }
        if (V(e)->unk_75 * 2 + 1 == player->unk_2a >> 1 && player->unk_29 != 0) {
            func_02033e10(e);
            if (V(e)->unk_74 == 1) {
                V(e)->unk_74 = 2;
                func_020859e0(e->unk_54, 0x1c);
                func_02085f80(0xa4);
            }
        }
    } else {
        if (func_0208de54(func_0208da4c()) != 0 || data_021348b8[V(e)->unk_75] == 0) {
            e->unk_14 = 3;
            V(e)->unk_74 = 0;
        } else {
            data_021348b8[V(e)->unk_75]--;
            VL(V(e)->unk_7c)->unk_6e |= V(e)->unk_76;
            if (e->unk_54->unk_14 != 6 || (VL(V(e)->unk_7c)->unk_6e & 0xc0) == 0xc0) {
                e->unk_14 = 4;
                e->unk_17 = 0x3c;
                e->unk_30.HALF.HI += data_020d0f0a[V(e)->unk_75];
                func_02085f80(0x12);
                Entity *fx = func_02076858(0xf, 3, 0x20);
                if (fx != NULL) {
                    func_02050390(e, fx, data_020d0ec0[V(e)->unk_75] << 16, 0);
                }
                Entity *item = func_02076858(0, data_020d0f02[func_0208455c() & 7], 1);
                if (item != NULL) {
                    item->unk_2b = (((V(e)->unk_75 ^ 1) << 4) + 8) | 0x80;
                    func_02050390(e, item, data_020d0ec0[V(e)->unk_75] << 16, 0);
                }
                if (data_021348b8[V(e)->unk_75] != 0) {
                    data_021348b8[V(e)->unk_75] = 0;
                }
            }
        }
        V(e)->unk_74 = 0;
    }
    func_02085d78(e);
}

ARM void func_02033aa8(Entity *e) {
    func_02089524(e);
    if (V(e)->unk_72 != 0) {
        e->unk_2b = (V(e)->unk_75 << 4) + 8;
        func_0204fd40(e);
        func_020340a8(e);
    }
    func_02085d78(e);
}

ARM void func_02033aec(Entity *e) {
    if (--e->unk_17 == 0) {
        e->unk_14 = 5;
        e->unk_1c.b0 = 0;
        return;
    }
    e->unk_1c.b0 ^= 1;
}

ARM void func_02033b38(Entity *e) {
    if (VL(V(e)->unk_7c)->unk_7c != 0x10) {
        return;
    }
    e->unk_14 = 1;
    e->unk_17 = 0x20;
    e->unk_0c = 0x80;
    e->unk_1c.b0 = 1;
    e->unk_2b = ((V(e)->unk_75 ^ 1) << 4) + 8;
    e->unk_30.HALF.HI = e->unk_54->unk_30.HALF.HI + data_020d0eba[V(e)->unk_75];
}

ARM void func_02033ba8(Entity *e) {
    if (e->unk_54->unk_45 != 0) {
        if (e->unk_14 == 0) {
            e->unk_14 = 1;
            e->unk_1c.b0 = 1;
            e->unk_5e.b0 = 1;
            func_020859e0(e, 0x13);
        }
        if (e->unk_0b >> 4) {
            func_0203464c(e, e->unk_58, VL(e->unk_54)->unk_7c);
            return;
        }
        u8 step = e->unk_0b & 0xf;
        Entity *parent = e->unk_54;
        e->unk_30.HALF.HI = parent->unk_58->unk_30.HALF.HI + (parent->unk_30.HALF.HI - parent->unk_58->unk_30.HALF.HI) * step / 4;
        e->unk_34.HALF.HI = parent->unk_58->unk_34.HALF.HI + (parent->unk_34.HALF.HI - parent->unk_58->unk_34.HALF.HI) * step / 4;
    } else {
        func_020347a8(e);
        func_0204be88(e);
    }
}

ARM void func_02033c84(Entity *e) {
    if (e->unk_14 == 0) {
        e->unk_14 = 1;
        e->unk_5e.b0 = 1;
        return;
    }
    BOOL alive = FALSE;
    if (e->unk_0b != 0) {
        if (VC(e)->unk_70 != NULL) {
            func_02034730(e, VC(e)->unk_70);
            alive = TRUE;
        }
        if (VC(e)->unk_74 != NULL) {
            func_02034730(e, VC(e)->unk_74);
            alive = TRUE;
        }
        if (VC(e)->unk_78 != NULL) {
            func_02034730(e, VC(e)->unk_78);
            alive = TRUE;
        }
    } else {
        if (VC(e)->unk_70 != NULL) {
            func_02050390(VC(e)->unk_70->unk_54, VC(VC(e)->unk_70->unk_54)->unk_70, 0, 1);
            alive = TRUE;
        }
        if (VC(e)->unk_74 != NULL) {
            func_02050390(VC(e)->unk_74->unk_54, VC(VC(e)->unk_74->unk_54)->unk_70, 0, 1);
            alive = TRUE;
        }
        if (VC(e)->unk_78 != NULL) {
            func_02050390(VC(e)->unk_78->unk_54, VC(VC(e)->unk_78->unk_54)->unk_70, 0, 1);
            alive = TRUE;
        }
    }
    if (!alive) {
        func_0204be88(e);
    }
}

ARM void func_02033d8c(Entity *e) {
    if (e->unk_14 == 0) {
        e->unk_14 = 1;
        e->unk_1c.b0 = 1;
        e->unk_5e.b0 = 1;
        func_020859e0(e, 0x13);
    }
    if (--e->unk_17 != 0) {
        return;
    }
    Entity *fx = func_02076858(0xf, 1, 0);
    if (fx != NULL) {
        func_0205031c(e, fx);
    }
    func_0204be88(e);
}


ARM void func_02033e10(Entity *e) {
    Entity *player = data_0212ceb0[e->unk_0b].unk_28;
    u8 speed = data_020d0eb8[V(e)->unk_75];
    if (V(e)->unk_72 < 0x30) {
        s16 px = player->unk_30.HALF.HI;
        s16 py = player->unk_34.HALF.HI;
        func_020852f8(player, 0x40, speed);
        if (px == player->unk_30.HALF.HI && py == player->unk_34.HALF.HI) {
            return;
        }
        s16 dist;
        if (V(e)->unk_75 != 0) {
            dist = player->unk_30.HALF.HI - px;
        } else {
            dist = px - player->unk_30.HALF.HI;
        }
        func_020852f8(e, dist << 8, speed);
        func_020340a8(e);
        if (V(e)->unk_72 >= 0x30) {
            V(e)->unk_77 = 0;
            if (data_021348b8[V(e)->unk_75] != 0) {
                data_021348b8[V(e)->unk_75] = 0;
            }
            data_021348b4 = 1;
            return;
        }
        if (--e->unk_18 == 0) {
            e->unk_18 = 8;
            func_02085f80(0x8b);
        }
        return;
    }
    if (data_020d0ebe[V(e)->unk_75] & data_0212c584[e->unk_0b]) {
        if (V(e)->unk_77 < 0xf) {
            V(e)->unk_77++;
            if (data_021348b8[V(e)->unk_75] != 0) {
                data_021348b8[V(e)->unk_75] = 0;
            }
            return;
        }
        VL(V(e)->unk_7c)->unk_6e |= V(e)->unk_76;
        if (e->unk_54->unk_14 == 6 && (VL(V(e)->unk_7c)->unk_6e & 0xc0) != 0xc0) {
            data_021348b8[V(e)->unk_75] = 0x4b0;
            return;
        }
        e->unk_14 = 4;
        e->unk_17 = 0x3c;
        e->unk_30.HALF.HI += data_020d0ebc[V(e)->unk_75];
        func_02085f80(0x12);
        Entity *fx = func_02076858(0xf, 3, 0x20);
        if (fx != NULL) {
            func_02050390(e, fx, data_020d0ec0[V(e)->unk_75] << 16, 0);
        }
        Entity *item = func_02076858(0, data_020d0f02[func_0208455c() & 7], 1);
        if (item != NULL) {
            item->unk_2b = (((V(e)->unk_75 ^ 1) << 4) + 8) | 0x80;
            func_02050390(e, item, data_020d0ec0[V(e)->unk_75] << 16, 0);
        }
        return;
    }
    if (func_0208de54(func_0208da4c()) == 0) {
        V(e)->unk_77 = 0;
        return;
    }
    if (data_021348b8[V(e)->unk_75] != 0) {
        data_021348b8[V(e)->unk_75]--;
    } else {
        V(e)->unk_77 = 0;
    }
}
