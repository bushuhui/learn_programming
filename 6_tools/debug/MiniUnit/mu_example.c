// #define MU_NOCOLOR
#include "miniunit.h"

int test_one()
{
  mu_assert(2 + 2 == 4);
  return 0; // 0 means test passed
}

int test_two()
{
  int a = 3, b = 5;
  mu_assert(a == 3);
  mu_assert(b == 5, "b is 5");
  mu_assert(a + b == 7, "should be %d", a + b); // fail
  return 0;
}

int main()
{
  mu_run_test(test_one);
  mu_run_test(test_two);

  mu_test_results();

  return 0;
}
