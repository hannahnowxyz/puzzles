#ifdef AOC_INCLUDEME
struct line {
	char* cstr_ptr;
	size_t length;
	size_t num_tokens;
};
// assumes there actually is a next token
#define NEXT_TOKEN(p) p = strchr(p, delim) + 1
#endif
