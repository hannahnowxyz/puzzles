#ifndef PARSLEY_H
#define PARSLEY_H

struct line {
	char* cstr_ptr;
	size_t length;
	size_t num_tokens;
};

#include "parsley.c"

#endif
