#ifndef __UTILS_DEBUG_H__
#define __UTILS_DEBUG_H__


////////////////////////////////////////////////////////////////////////////////
/// ASSERT macro
////////////////////////////////////////////////////////////////////////////////
#ifdef RTK_DEBUG

    #define ASSERT(f) \
        do { \
            if (!f ) { \
                fprintf(stderr, "ERROR (FILE: %s, LINE: %d, FUNC: %s)\n", \
                    __FILE__, __LINE__, __FUNCTION__); \
                exit(1); \
            } \
        } while (0); \


    #define ASSERT2(f, s) \
        do { \
            if (!f ) { \
                fprintf(stderr, "ERROR: %s (FILE: %s, LINE: %d, FUNC: %s)\n", \
                    s, __FILE__, __LINE__, __FUNCTION__); \
                exit(1); \
            } \
        } while (0); \

#else
    #define ASSERT(f)
    #define ASSERT2(f, s)
#endif


////////////////////////////////////////////////////////////////////////////////
/// debug stack trace functions
////////////////////////////////////////////////////////////////////////////////

int dbg_stacktrace_setup(void);



#endif // end of __UTILS_DEBUG_H__

