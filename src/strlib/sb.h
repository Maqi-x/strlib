#pragma once

#include <strlib/sv.h>

typedef struct StringBuf {
    char* data;
    size_t len;
    size_t cap;
} StringBuf;

bool sb_init(StringBuf* sb);
bool sb_init_with_cap(StringBuf* sb, size_t init_cap);
bool sb_init_from(StringBuf* sb, StringView sv);
bool sb_init_from_cstr(StringBuf* sb, const char* cstr);
void sb_free(StringBuf* sb);

bool sb_copy(const StringBuf* src, StringBuf* dst);
void sb_move(StringBuf* src, StringBuf* dst);

static inline StringView sb_view(const StringBuf* sb) {
    return sv_from_data_and_len(sb->data, sb->len);
}

bool sb_resize(StringBuf* sb, size_t new_len);
bool sb_reserve(StringBuf* sb, size_t min_cap);
bool sb_reserve_exact(StringBuf* sb, size_t new_cap);

void sb_clear(StringBuf* sb);

bool sb_append(StringBuf* sb, StringView sv);
static inline bool sb_append_cstr(StringBuf* sb, const char* cstr) {
    return sb_append(sb, sv_from_cstr(cstr));
}
static inline bool sb_append_buf(StringBuf* sb, const StringBuf* other) {
    return sb_append(sb, sb_view(other));
}

bool sb_append_char(StringBuf* sb, char c);

static inline bool sb_eql_to(const StringBuf* lhs, StringView rhs) {
    return sv_eql(sb_view(lhs), rhs);
}
static inline bool sb_eql_to_cstr(const StringBuf* lhs, const char* rhs) {
    return sb_eql_to(lhs, sv_from_cstr(rhs));
}
static inline bool sb_eql_to_sb(const StringBuf* lhs, const StringBuf* rhs) {
    return sb_eql_to(lhs, sb_view(rhs));
}

static inline bool sb_starts_with(const StringBuf* sb, StringView prefix) {
    return sv_starts_with(sb_view(sb), prefix);
}
static inline bool sb_ends_with(const StringBuf* sb, StringView suffix) {
    return sv_ends_with(sb_view(sb), suffix);
}

