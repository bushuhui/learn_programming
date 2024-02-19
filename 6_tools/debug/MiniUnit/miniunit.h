// The MIT License (MIT)
// Copyright (c) 2018 Bo Zhuang <sdzhuangbo@hotmail.com>

/**
 * A small unit test framework for C/C++.
 * 
 * Features:
 *   - `mu_assert(expr)` assertion fail if `expr` false
 *   - `mu_assert(expr, message)` assertion with message
 *   - `mu_assert(expr, message, args...)` assertion with message and args
 *   - `mu_run_test(test)` to run a test function in form `int f()`
 *                         return 0 if passed
 *   - `mu_test_results()` to display the test results
 *   - `#define MU_NOCOLOR` if ANSI escape code not supported
 * 
 * For example,
 * <code>
 * #include "miniunit.h"
 * 
 * int test_one() {
 *   mu_assert(2 + 2 == 4);
 *   return 0; // 0 means test passed
 * }
 * 
 * int test_two() {
 *   int a = 3, b = 5;
 *   mu_assert(a == 3);
 *   mu_assert(b == 5, "b is 5");
 *   mu_assert(a + b == 7, "should be %d", a + b); // fail
 *   return 0;
 * }
 * 
 * int main()
 * {
 *   mu_run_test(test_one);
 *   mu_run_test(test_two);
 * 
 *   mu_test_results();
 * 
 *   return 0;
 * }
 * </code>
 */

#ifndef MINI_UNIT_H
#define MINI_UNIT_H

#include <stdio.h>

/* Count of args */
#define VA_NARG(args...) VA_NARG_(0, ##args, VA_RSEQ_N())
#define VA_NARG_(args...) VA_ARG_N(args)
#define VA_ARG_N(_0, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, N, ...) N
#define VA_RSEQ_N() 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

/* The first arg */
#define VA_FIRST(args...) VA_FIRST_(args)
#define VA_FIRST_(F, ...) F

/* The first arg in string */
#define VA_FIRST_STR(args...) VA_FIRST_STR_(args)
#define VA_FIRST_STR_(F, ...) #F

/* The rest args */
#define VA_REST(args...) VA_REST_(args)
#define VA_REST_(F, args...) args

/* Define MU_NOCOLOR if not linux */
#ifndef __linux__
#ifndef MU_NOCOLOR
#define MU_NOCOLOR
#endif
#endif /* not linux */

/* ANSI escape code */
#ifdef MU_NOCOLOR

#define NULSTR ""

#define RST NULSTR
#define BOLD NULSTR
#define UNDL NULSTR

/* foreground */
#define FBLK NULSTR
#define FRED NULSTR
#define FGRN NULSTR
#define FYEL NULSTR
#define FBLU NULSTR
#define FMAG NULSTR
#define FCYN NULSTR
#define FWHT NULSTR

#else /* MU_NOCOLOR */

#define RST "\x1B[0m"
#define BOLD "\x1B[1m"
#define UNDL "\x1B[4m"

/* foreground */
#define FBLK "\x1B[30m"
#define FRED "\x1B[31m"
#define FGRN "\x1B[32m"
#define FYEL "\x1B[33m"
#define FBLU "\x1B[34m"
#define FMAG "\x1B[35m"
#define FCYN "\x1B[36m"
#define FWHT "\x1B[37m"

#endif /* MU_NOCOLOR */

#define ENDL RST "\n"
#define BORED BOLD FRED
#define BOGRN BOLD FGRN
#define BOYEL BOLD FYEL
#define BOWHT BOLD FWHT

#ifdef __linux__
#define FAIL "✘"
#define PASS "✔"
#else /* for others */
#define FAIL "FAIL"
#define PASS "PASS"
#endif /* __linux__ */

#define mu_assert(test...)                                  \
    do                                                      \
    {                                                       \
        if (!(VA_FIRST(test)))                              \
        {                                                   \
            printf(BORED FAIL ENDL                          \
                   "|\\_[" BORED "FAIL" RST                 \
                   "] at " BOWHT "./%s:%d" RST              \
                   " for '" BOYEL "%s" RST "' ",            \
                   __FILE__, __LINE__, VA_FIRST_STR(test)); \
            if (VA_NARG(test) == 1)                         \
                printf(BORED FAIL);                         \
            else                                            \
                printf(BORED FAIL " " FMAG VA_REST(test));  \
            printf(ENDL);                                   \
            return 1;                                       \
        }                                                   \
    } while (0)

static int n_test; /* number of tests */
static int n_pass; /* number of tests passed */
static int n_fail; /* number of tests failed */

#define mu_run_test(test)                                 \
    do                                                    \
    {                                                     \
        ++n_test;                                         \
        printf("|- " BOWHT "%s" FBLK " ./%s:%d ... " RST, \
               #test, __FILE__, __LINE__);                \
        if (!test())                                      \
        {                                                 \
            ++n_pass;                                     \
            printf(BOGRN PASS ENDL);                      \
        }                                                 \
        else                                              \
            ++n_fail;                                     \
    } while (0)

void mu_test_results()
{
    printf("\\_________________________________\n");
    printf(BOGRN "%d " PASS RST " and ", n_pass);
    printf(n_fail ? BORED "%d " FAIL : BOLD FBLK "%d " FAIL, n_fail);
    printf(RST " in " BOWHT "%d" RST " TEST(S)" ENDL, n_test);
    if (n_pass == n_test)
        printf(BOGRN "==== ALL TESTS PASSED ====" ENDL);
    else
        printf(BORED "#### %d TEST(S) FAILED ####" ENDL, n_fail);
}

#endif /* MINI_UNIT_H */
