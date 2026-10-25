#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/node.h"

extern "C" void Node_Write(NodeSrc *self, u32 offset, u32 extra);

// Node_Write(self, offset, extra) (0x0200c358): fills the record at base + offset from the source block. The first byte of
// the text selects the form: '*' makes +0xc point at +0x10 and stores the word at the value pointer plus extra there;
// otherwise +0xc is the value plus extra.
ARM void Node_Write(NodeSrc *self, u32 offset, u32 extra) {
    NodeRec *node;

    node = (NodeRec *)(self->base + offset);
    node->w0 = self->value;
    node->text = self->text;
    node->w8 = self->extra;
    if (self->text[0] != 0x2a) {
        node->wC = self->value + extra;
        return;
    }
    node->wC = (u32)&node->w10;
    node->w10 = *(u32 *)self->value + extra;
}
