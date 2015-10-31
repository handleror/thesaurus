#include "thesaurus.h"

VALUE rb_mThesaurus;

void
Init_thesaurus(void)
{
  rb_mThesaurus = rb_define_module("Thesaurus");
}
