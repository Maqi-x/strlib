#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct StringView {
    const char* data;
    size_t len;
} StringView;

#define SV_NULL ((StringView) { .data = NULL, .len = 0 })
#define SV(STRING_LITERAL) ((StringView) { .data = (STRING_LITERAL), .len = sizeof(STRING_LITERAL) - 1 })

#define SV_FMT "%.*s"
#define SV_FARG(SV) \
    ((int)((SV).data ? (SV).len : 5)), \
    ((SV).data ? (SV).data : "(nil)")

static inline unsigned long sv_print(StringView sv, FILE* out) {
    return fwrite(sv.data, 1, sv.len, out);
}

static inline StringView sv_from_cstr(const char* cstr) {
    return (StringView) { .data = cstr, .len = strlen(cstr) };
}

static inline StringView sv_from_data_and_len(const char* data, size_t len) {
    return (StringView) { .data = data, .len = len };
}

static inline bool sv_is_null(StringView sv) {
    return sv.data == NULL;
}

static inline bool sv_eql(StringView lhs, StringView rhs) {
    if (lhs.len != rhs.len) return false;
    if (lhs.data == rhs.data) return true;
    return memcmp(lhs.data, rhs.data, lhs.len) == 0;
}

static inline char sv_map_tolower(char c) {
    return (char)tolower((unsigned char)c);
}
static inline char sv_map_toupper(char c) {
    return (char)toupper((unsigned char)c);
}

static inline bool sv_eql_by(StringView lhs, StringView rhs, char (*map)(char)) {
    if (lhs.len != rhs.len) return false;
    if (lhs.data == rhs.data) return true;

    for (size_t i = 0; i < lhs.len; ++i) {
        if (map(lhs.data[i]) != map(rhs.data[i])) {
            return false;
        }
    }
    return true;
}

static inline bool sv_eql_icase(StringView lhs, StringView rhs) {
    return sv_eql_by(lhs, rhs, sv_map_tolower);
}

static inline bool sv_starts_with(StringView sv, StringView prefix) {
    if (prefix.len > sv.len) return false;
    return memcmp(sv.data, prefix.data, prefix.len) == 0;
}

static inline bool sv_ends_with(StringView sv, StringView suffix) {
    if (suffix.len > sv.len) return false;
    if (suffix.len == sv.len) return memcmp(sv.data, suffix.data, sv.len) == 0;

    return memcmp(sv.data + (sv.len - suffix.len), suffix.data, suffix.len) == 0;
}

static inline StringView sv_trim_prefix(StringView sv, StringView prefix) {
    if (!sv_starts_with(sv, prefix)) return sv;
    return (StringView) { .data = sv.data + prefix.len, .len = sv.len - prefix.len };
}

static inline StringView sv_trim_suffix(StringView sv, StringView suffix) {
    if (!sv_ends_with(sv, suffix)) return sv;
    return (StringView) { .data = sv.data, .len = sv.len - suffix.len };
}

static inline StringView sv_trim(StringView sv, int (*pred)(int)) {
    while (sv.len != 0 && pred((unsigned char)sv.data[0])) sv.data++, sv.len--;
    while (sv.len != 0 && pred((unsigned char)sv.data[sv.len - 1])) sv.len--;
    return sv;
}

static inline StringView sv_trim_prefix_or_null(StringView sv, StringView prefix) {
    if (!sv_starts_with(sv, prefix)) return SV_NULL;
    return (StringView) { .data = sv.data + prefix.len, .len = sv.len - prefix.len };
}

static inline StringView sv_trim_suffix_or_null(StringView sv, StringView suffix) {
    if (!sv_ends_with(sv, suffix)) return SV_NULL;
    return (StringView) { .data = sv.data, .len = suffix.len };
}

static inline StringView sv_slice(StringView sv, size_t start, size_t end) {
    if (sv.data == NULL || start > end || end > sv.len) {
        return SV_NULL;
    }

    return (StringView) { .data = sv.data + start, .len = end - start };
}

static inline StringView sv_window(StringView sv, size_t start, size_t len) {
    if (start >= sv.len) return SV_NULL;
    if (start + len > sv.len) len = sv.len - start;

    return (StringView) { .data = sv.data + start, .len = len };
}

