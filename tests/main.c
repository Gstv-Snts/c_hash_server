#include "unity_internals.h"

void setUp() {};
void tearDown() {};

void test_hash_table(void);
int main() {
  UNITY_BEGIN();
  RUN_TEST(test_hash_table);
  return UNITY_END();
}
