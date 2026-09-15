#ifdef __UNDERC__
#define EXPORT
#else
#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif
#endif

