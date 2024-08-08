#include "unity_internals.h"

void setUp() {};
void tearDown() {};

void test_hash_table(void);
void test_tcp(void);

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_hash_table);
  RUN_TEST(test_tcp);
  return UNITY_END();
}
