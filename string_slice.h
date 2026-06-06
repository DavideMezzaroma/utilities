#ifndef STRING_SLICE_H_
#define STRING_SLICE_H_
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define SLICE_FMT "%.*s"
#define SLICE_ARG(s) (int)(s).len, (s).data

typedef struct {
    const char *data;
    size_t len;
} StringSlice;

StringSlice ss(const char* cstr);

void chop_right(StringSlice* ss, size_t n);

void chop_left(StringSlice* ss, size_t n);

void trim(StringSlice* ss);

void trim_from(StringSlice* ss, bool from_right);

StringSlice split_by(StringSlice* ss, char delimiter);

StringSlice split_by_type(StringSlice* ss, int (*is_of_type)(int c));

bool ss_equals(StringSlice a, StringSlice b);

#endif // STRING_SLICE_H_
