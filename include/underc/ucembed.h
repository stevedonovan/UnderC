#ifndef UNDERC_UCEMBED_H
#define UNDERC_UCEMBED_H

#ifdef _WIN32
# define UC_EMBED_CALL __stdcall
#else
# define UC_EMBED_CALL
#endif

// The definition lives in dll_entry.cpp, which is compiled WITHIN_UC.  Keeping
// the declaration's dll linkage in step with that definition stops MSVC from
// rejecting the two as inconsistent (C2375).
#if defined(_WIN32) && defined(WITHIN_UC)
# define UC_EMBED_API __declspec(dllexport)
#elif defined(_WIN32) && defined(UC_EMBED_SHARED)
# define UC_EMBED_API __declspec(dllimport)
#else
# define UC_EMBED_API
#endif

typedef enum uc_variable_type {
  UC_TYPE_BOOL, UC_TYPE_CHAR, UC_TYPE_UNSIGNED_CHAR,
  UC_TYPE_SHORT, UC_TYPE_UNSIGNED_SHORT,
  UC_TYPE_INT, UC_TYPE_UNSIGNED_INT,
  UC_TYPE_LONG, UC_TYPE_UNSIGNED_LONG,
  UC_TYPE_FLOAT, UC_TYPE_DOUBLE
} uc_variable_type;

typedef enum uc_status {
  UC_STATUS_OK = 0,
  UC_STATUS_INVALID_ARGUMENT,
  UC_STATUS_ALREADY_EXISTS,
  UC_STATUS_NOT_INITIALIZED,
  UC_STATUS_UNSUPPORTED_TYPE
} uc_status;

#ifdef __cplusplus
extern "C" {
#endif

UC_EMBED_API uc_status UC_EMBED_CALL uc_bind_variable(const char *name,
                                         uc_variable_type type,
                                         void *address);

#ifdef __cplusplus
}
#endif

#endif
