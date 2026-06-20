#include "string_slice.h"

StringSlice ss(const char* cstr){
    return (StringSlice){
        .data = cstr,
        .len = strlen(cstr),
    };
}

void chop_left(StringSlice* ss, size_t n){
    if(ss->len < n) n = ss->len;
    ss->data += n;
    ss->len -= n;
}

void chop_right(StringSlice* ss, size_t n){
    if(ss->len < n) n = ss->len;
    ss->len -= n;
}


void trim(StringSlice* ss){
    while(ss->len > 0 && isspace(ss->data[0]))
        chop_left(ss, 1);
    while(ss->len > 0 && isspace(ss->data[ss->len-1]))
        chop_right(ss, 1);
    return;
}

void trim_from(StringSlice* ss, bool from_right){
    if(!from_right){
        while(ss->len > 0 && isspace(ss->data[0]))
            chop_left(ss, 1);
        return;
    }

    while(ss->len > 0 && isspace(ss->data[ss->len-1]))
        chop_right(ss, 1);
    return;
}

StringSlice split_by(StringSlice* ss, char delimiter){
    size_t i = 0;
    while(ss->data[i] != delimiter && i < ss->len){
        i++;
    }

    if(i >= ss->len){
        StringSlice result = *ss;
        chop_left(ss, ss->len);
        return result;
    }

    StringSlice result = {
        .data = ss->data,
        .len = i,
    };
    chop_left(ss, i+1);
    return result;
}

StringSlice split_by_type(StringSlice* ss, int (*is_of_type)(int c)){
    size_t i = 0;
    while(!is_of_type(ss->data[i]) && i < ss->len){
        i++;
    }

    if(i >= ss->len){
        StringSlice result = *ss;
        chop_left(ss, ss->len);
        return result;
    }

    StringSlice result = {
        .data = ss->data,
        .len = i,
    };
    chop_left(ss, i+1);
    return result;
}

bool ss_equals(StringSlice a, StringSlice b){
    if (a.len != b.len) return false;

    for(size_t i = 0; i < a.len; ++i){
        if(a.data[i] != b.data[i])
            return false;
    }
    return true;
}

bool ss_equals_voidptrs(const void* a, const void* b){
    StringSlice* slice_a = (StringSlice*)a;
    StringSlice* slice_b = (StringSlice*)b;
    return ss_equals(*slice_a, *slice_b);
}
