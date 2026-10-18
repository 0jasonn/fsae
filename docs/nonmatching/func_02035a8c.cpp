// Enemy at 0x020347dc (Vars_020347dc). Only difference: where `mov r1, #5` (animation argument of the
// last func_020859e0 call on unk_70) is scheduled.

ARM extern "C" void func_02035a8c(Entity *e) {
    e->unk_1c.b20 = func_0208455c() % data_0212c7c8.unk_0 + 7;
    e->unk_1c.b16 = e->unk_1c.b20;
    if (V(e)->unk_70 != NULL) {
        void *a = func_0208da4c();
        if (V(e)->unk_6e != 0 && func_0208de54(a) != 0) {
            V(e)->unk_70->unk_1c.b20 = func_0208455c() % data_0212c7c8.unk_0 + 7;
        } else {
            V(e)->unk_70->unk_1c.b20 = e->unk_1c.b16;
        }
        V(e)->unk_70->unk_1c.b16 = V(e)->unk_70->unk_1c.b20;
        V(e)->unk_70->unk_1c.b0 = 1;
        func_020859e0(V(e)->unk_70, 5);
    }
    func_020859e0(e, 4);
    func_02085f80(0xa2);
}

