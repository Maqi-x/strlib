#include <stdbool.h>
#include <ctype.h>

typedef char SlMapFn(char);
static inline char sl_to_lower(char c) { return (char)tolower((unsigned char)c); }
static inline char sl_to_upper(char c) { return (char)toupper((unsigned char)c); }

typedef bool SlPredFn(char);
static inline bool sl_is_alpha(char c)  { return isalpha((unsigned char)c);  }
static inline bool sl_is_alnum(char c)  { return isalnum((unsigned char)c);  }
static inline bool sl_is_blank(char c)  { return isblank((unsigned char)c);  }
static inline bool sl_is_cntrl(char c)  { return iscntrl((unsigned char)c);  }
static inline bool sl_is_digit(char c)  { return isdigit((unsigned char)c);  }
static inline bool sl_is_graph(char c)  { return isgraph((unsigned char)c);  }
static inline bool sl_is_lower(char c)  { return islower((unsigned char)c);  }
static inline bool sl_is_print(char c)  { return isprint((unsigned char)c);  }
static inline bool sl_is_punct(char c)  { return ispunct((unsigned char)c);  }
static inline bool sl_is_space(char c)  { return isspace((unsigned char)c);  }
static inline bool sl_is_upper(char c)  { return isupper((unsigned char)c);  }
static inline bool sl_is_xdigit(char c) { return isxdigit((unsigned char)c); }
