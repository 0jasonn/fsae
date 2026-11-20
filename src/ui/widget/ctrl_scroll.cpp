#include "engine/functions.h"
#include "ui/ctrl_scroll.h"

// Ctrl_updateScroll(self) (0x020bacb8, provisional name): per-frame animation of a list Ctrl. Panel A slides in or out
// (y moves by 0x20 towards 0x96 while opening is clear, towards 0 while it is set), panel B follows it mirrored, the side
// pane eases towards sideTargetX (by at most 0x20 a frame) and drags the list pane with it, the vertical offset eases
// towards its target, and the cursor/side pane get the selected flag when the list slider has settled. Finally the four
// countdown lists tick.
void Ctrl_updateScroll(CtrlScrollObj *self) {
    CtrlPos16 posOpen;
    CtrlPos16 posClose;
    CtrlPos16 posB;
    CtrlPos16 posSide;
    CtrlPos16 posList;
    CtrlPanel *panelA = (CtrlPanel *)self->panelA;
    CtrlPanel *panelB = (CtrlPanel *)self->panelB;
    s16 mainCoord;
    s16 auxCoord;
    s32 dir;
    s16 step;
    s32 diff;
    s32 flag;

    auxCoord = panelA->x;
    mainCoord = panelA->y;
    if (self->opening) {
        if (mainCoord > 0) {
            diff = mainCoord - 0x20;
            if (diff < 0) {
                diff = 0;
            }
            mainCoord = (s16)diff;
            posOpen.x = auxCoord;
            posOpen.y = mainCoord;
            panelA->setPos(&posOpen);
        }
    } else if (mainCoord < 0x96) {
        mainCoord = (s16)(mainCoord + 0x20);
        if (mainCoord > 0x96) {
            mainCoord = 0x96;
        }
        posClose.x = auxCoord;
        posClose.y = mainCoord;
        panelA->setPos(&posClose);
    }
    posB.x = panelB->x;
    posB.y = 0xec - mainCoord;
    panelB->setPos(&posB);

    mainCoord = self->sidePane->x;
    s16 sideY = self->sidePane->y;
    if (mainCoord != self->sideTargetX) {
        dir = mainCoord > self->sideTargetX;
        diff = self->sideTargetX - mainCoord;
        if (diff < 0) {
            diff = -diff;
        }
        step = diff;
        if (step > 0x20) {
            step = 0x20;
        }
        if (dir) {
            step = -step;
        }
        mainCoord += step;
        posSide.y = sideY;
        posSide.x = mainCoord;
        self->sidePane->setPos(&posSide);
        diff = mainCoord - 0x89;
        posList.y = self->listPane->y;
        if (diff > 0) {
            diff = 0;
        }
        posList.x = diff;
        self->listPane->setPos(&posList);
        if (mainCoord == self->sideTargetX) {
            Ctrl_setStateValue(self);
        }
    }
    if (self->offsetTarget != self->offsetCurrent) {
        dir = self->offsetCurrent > self->offsetTarget;
        diff = self->offsetTarget - self->offsetCurrent;
        if (diff < 0) {
            diff = -diff;
        }
        step = diff;
        if (step > 0x20) {
            step = 0x20;
        }
        if (dir) {
            step = -step;
        }
        self->offsetCurrent += step;
    }
    if (func_020b9df0(self->listPane, Ctrl_getItemEntry, self->itemList) && self->selected) {
        flag = 1;
        if (self->listPane->rangeCurrent != self->listPane->rangeTarget) {
            flag = 0;
        }
        self->cursor->setSelected(flag);
        self->sidePane->setSelected(flag);
    }
    RectObjList_countDown(self->timer68);
    RectObjList_countDown(self->timer6c);
    RectObjList_countDown(self->timer70);
    RectObjList_countDown(self->timer74);
}
