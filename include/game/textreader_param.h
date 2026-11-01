#ifndef WIP_E_TEXTREADER_PARAM_H
#define WIP_E_TEXTREADER_PARAM_H

// TextReader::readParam_Str(Text*) (0x020a2a2c): reads one text parameter of a tag (src/wip/E/textreader_param.cpp).

#include "engine/functions.h"
#include "engine/text_tokenizer.h"
#include "engine/texttags.h"
#include "game/textreader.h"

extern "C" {
void Knife_Message_TextReader_readParam_Str(void *self, void *out);
}

#endif
