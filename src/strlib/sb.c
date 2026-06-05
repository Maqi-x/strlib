#include <strlib/sb.h>

#include <stdlib.h>
#include <string.h>

#define EL_STRBUF_DEFAULT_CAP 16

static size_t _sb_next_cap(size_t current_cap, size_t required_min_cap) {
    size_t new_cap = current_cap == 0 ? EL_STRBUF_DEFAULT_CAP : current_cap * 2;
    if (new_cap < required_min_cap) {
        new_cap = required_min_cap;
    }
    return new_cap;
} 

bool sb_init(StringBuf* sb) {
    return sb_init_with_cap(sb, EL_STRBUF_DEFAULT_CAP);
}

bool sb_init_with_cap(StringBuf* sb, size_t init_cap) {
    sb->data = malloc(init_cap);
    if (sb->data == NULL) return false;
    sb->len = 0;
    sb->cap = init_cap;
    return true;
}

bool sb_init_from(StringBuf* sb, StringView sv) {
    sb->data = malloc(sv.len);
    if (sb->data == NULL) return false;

    memcpy(sb->data, sv.data, sv.len);
    sb->len = sv.len;
    sb->cap = sv.len;
    return true;
}

bool sb_init_from_cstr(StringBuf* sb, const char* cstr) {
    return sb_init_from(sb, sv_from_cstr(cstr));
}

void sb_destroy(StringBuf* sb) {
    free(sb->data);
    sb->data = NULL;
    sb->len = 0;
    sb->cap = 0;
}

bool sb_copy(const StringBuf* src, StringBuf* dst) {
    if (src->len == 0) {
        dst->data = NULL;
        dst->len = 0;
        dst->cap = 0;
        return true;
    }
    dst->data = malloc(src->len);
    if (dst->data == NULL) {
        dst->len = 0;
        dst->cap = 0;
        return false;
    }
    memcpy(dst->data, src->data, src->len);
    dst->len = src->len;
    dst->cap = src->len;
    return true;
}

void sb_move(StringBuf* src, StringBuf* dst) {
    *dst = *src;
    src->data = NULL;
    src->len = 0;
    src->cap = 0;
}

bool sb_resize(StringBuf* sb, size_t new_len) {
    if (new_len > sb->cap) {
        if (!sb_reserve_exact(sb, new_len)) {
            return false;
        }
    }
    sb->len = new_len;
    return true;
}

bool sb_reserve(StringBuf* sb, size_t min_cap) {
    if (min_cap <= sb->cap) {
        return true;
    }

    size_t new_cap = _sb_next_cap(sb->cap, min_cap);
    char* new_data = realloc(sb->data, new_cap);
    if (new_data == NULL) return false;

    sb->data = new_data;
    sb->cap = new_cap;
    return true;
}

bool sb_reserve_exact(StringBuf* sb, size_t new_cap) {
    if (new_cap <= sb->cap) {
        return true;
    }
    
    char* new_data = realloc(sb->data, new_cap);
    if (new_data == NULL) return false;

    sb->data = new_data;
    sb->cap = new_cap;
    return true;
}

void sb_clear(StringBuf* sb) {
    sb->len = 0;
}

bool sb_append(StringBuf* sb, StringView sv) {
    if (sv.len == 0) return true;
    if (!sb_reserve(sb, sb->len + sv.len)) {
        return false;
    }

    if (!memcpy(sb->data + sb->len, sv.data, sv.len)) {
        return false;
    }
    sb->len += sv.len;
    return true;
}

bool sb_append_char(StringBuf* sb, char c) {
    if (!sb_reserve(sb, sb->len + 1)) {
        return false;
    }
    sb->data[sb->len] = c;
    sb->len += 1;
    return true;
}

