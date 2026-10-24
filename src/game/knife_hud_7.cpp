#include "engine/functions.h"
#include "global.h"
#include "game/knife_hud.h"
#include "game/knife_hud_layout.h"

// Functions in this file (original names from the debug build, or invented where marked):
//   Knife::Interp<VecFx32>::Interp (0x0209dfc4), empty dtor of the Interp array (0x0209dfe0, name invented),
//   StatusUpMarker::StatusUpMarker (0x0209dfe4), empty dtor of the marker array (0x0209e000, name invented),
//   HudManager::HudManager (0x0209df50, name invented), HudManager::~HudManager (0x0209e004 and 0x0209e054)

extern "C" void Knife_Interp_VecFx32__Interp(KnifeHudInterp *self);
extern "C" void Knife_Interp_VecFx32_emptyDtor(void *self);
extern "C" void Knife_Hud_HudManager_StatusUpMarker_StatusUpMarker(KnifeHudStatusUpMarker *self);
extern "C" void Knife_Hud_HudManager_StatusUpMarker_emptyDtor(void *self);
extern "C" Knife::Hud::HudManager *Knife_Hud_HudManager_ctor(Knife::Hud::HudManager *self);
extern "C" Knife::Hud::HudManager *Knife_Hud_HudManager_dtor_HudManager_09e004(Knife::Hud::HudManager *self);
extern "C" Knife::Hud::HudManager *Knife_Hud_HudManager_dtor_HudManager_09e054(Knife::Hud::HudManager *self);

// HudManager::HudManager() (0x0209df50, name invented): vtable, the two arrays of interpolations and markers, then finalize
ARM Knife::Hud::HudManager *Knife_Hud_HudManager_ctor(Knife::Hud::HudManager *self) {
    KnifeHudVars *v = (KnifeHudVars *)self;

    v->vtbl = data_0211c6e8;
    func_0200c7b8(&v->interp, 2, sizeof(KnifeHudInterp), (void *)Knife_Interp_VecFx32__Interp, (void *)Knife_Interp_VecFx32_emptyDtor);
    func_0200c7b8(&v->statusUp, 4, sizeof(KnifeHudStatusUpMarker), (void *)Knife_Hud_HudManager_StatusUpMarker_StatusUpMarker, (void *)Knife_Hud_HudManager_StatusUpMarker_emptyDtor);
    self->finalize();
    return self;
}

// Knife::Interp<VecFx32>::Interp() (0x0209dfc4): vtable, no time and no function
ARM void Knife_Interp_VecFx32__Interp(KnifeHudInterp *self) {
    self->vtbl = data_0211c6f8;
    self->t = 0;
    self->fn = NULL;
}

// Empty destructor of an Interp array element (0x0209dfe0)
ARM void Knife_Interp_VecFx32_emptyDtor(void *self) {
}

// StatusUpMarker::StatusUpMarker() (0x0209dfe4): its interpolation (vtable, no time, no function)
ARM void Knife_Hud_HudManager_StatusUpMarker_StatusUpMarker(KnifeHudStatusUpMarker *self) {
    self->interp.vtbl = data_0211c6f8;
    self->interp.t = 0;
    self->interp.fn = NULL;
}

// Empty destructor of a status-up marker array element (0x0209e000)
ARM void Knife_Hud_HudManager_StatusUpMarker_emptyDtor(void *self) {
}

// HudManager::~HudManager() (0x0209e004): finalize, then the two arrays are destroyed
ARM Knife::Hud::HudManager *Knife_Hud_HudManager_dtor_HudManager_09e004(Knife::Hud::HudManager *self) {
    KnifeHudVars *v = (KnifeHudVars *)self;

    v->vtbl = data_0211c6e8;
    self->finalize();
    func_0200c868(&v->statusUp, 4, sizeof(KnifeHudStatusUpMarker), (void *)Knife_Hud_HudManager_StatusUpMarker_emptyDtor);
    func_0200c868(&v->interp, 2, sizeof(KnifeHudInterp), (void *)Knife_Interp_VecFx32_emptyDtor);
    return self;
}

// HudManager::~HudManager() (0x0209e054): the deleting destructor, the same as 0x0209e004 and then operator delete
ARM Knife::Hud::HudManager *Knife_Hud_HudManager_dtor_HudManager_09e054(Knife::Hud::HudManager *self) {
    KnifeHudVars *v = (KnifeHudVars *)self;

    v->vtbl = data_0211c6e8;
    self->finalize();
    func_0200c868(&v->statusUp, 4, sizeof(KnifeHudStatusUpMarker), (void *)Knife_Hud_HudManager_StatusUpMarker_emptyDtor);
    func_0200c868(&v->interp, 2, sizeof(KnifeHudInterp), (void *)Knife_Interp_VecFx32_emptyDtor);
    operator delete(self);
    return self;
}
