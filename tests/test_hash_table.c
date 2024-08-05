#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"
#include "unity.h"

void setUpHashTable(void) {};
void tearDownHashTable(void) {};

void test_hash_table(void) {
  setUpHashTable();
  struct hash_table *hash_table = malloc(sizeof(struct hash_table));
  initialize_hash_table(hash_table, 2);

  TEST_ASSERT_EQUAL(hash_table->length, 0);
  TEST_ASSERT_EQUAL(hash_table->size, 2);

  TEST_ASSERT_EQUAL(NULL, get_from_hash_table(hash_table, "test"));
  TEST_ASSERT_EQUAL(NULL, delete_on_hash_table(hash_table, "test"));
  TEST_ASSERT_EQUAL(NULL, update_on_hash_table(hash_table, "a", (int *)"avocado"));

  int index = djb2("a", hash_table->size);
  TEST_ASSERT_EQUAL(0, index);

  insert_on_hash_table(hash_table, "a", (int *)"test1");
  TEST_ASSERT_EQUAL("test1", hash_table->table[index]->head->value);

  insert_on_hash_table(hash_table, "ad", (int *)"test10");
  TEST_ASSERT_EQUAL("test10", hash_table->table[index]->head->value);
  TEST_ASSERT_EQUAL("test1", hash_table->table[index]->head->next->value);

  insert_on_hash_table(hash_table, "a", (int *)"test3");
  TEST_ASSERT_EQUAL("test3", hash_table->table[index]->head->value);
  TEST_ASSERT_EQUAL("test10", hash_table->table[index]->head->next->value);

  TEST_ASSERT_EQUAL("test10", get_from_hash_table(hash_table, "ad"));

  TEST_ASSERT_EQUAL("test10", update_on_hash_table(hash_table, "ad", (int *)"test2"));

  TEST_ASSERT_EQUAL("test2", delete_on_hash_table(hash_table, "ad"));

  TEST_ASSERT_EQUAL("test3", delete_on_hash_table(hash_table, "a"));

  TEST_ASSERT_EQUAL("test1", delete_on_hash_table(hash_table, "a"));

  TEST_ASSERT_EQUAL(0, hash_table->table[index]->length);
  TEST_ASSERT_EQUAL(0, hash_table->length);

  insert_on_hash_table(hash_table, "b", (int *)"test1");
  insert_on_hash_table(hash_table, "b", (int *)"test2");
  insert_on_hash_table(hash_table, "b", (int *)"test3");
  insert_on_hash_table(hash_table, "b", (int *)"test4");
  insert_on_hash_table(hash_table, "b", (int *)"test5");
  TEST_ASSERT_EQUAL("test5", delete_on_hash_table(hash_table, "b"));
  TEST_ASSERT_EQUAL("test1", delete_on_hash_table(hash_table, "b"));
  TEST_ASSERT_EQUAL("test2", delete_on_hash_table(hash_table, "b"));
  TEST_ASSERT_EQUAL("test3", delete_on_hash_table(hash_table, "b"));
  TEST_ASSERT_EQUAL("test4", delete_on_hash_table(hash_table, "b"));
  insert_on_hash_table(hash_table, "b", (int *)"test1");
  insert_on_hash_table(hash_table, "b", (int *)"test2");
  insert_on_hash_table(hash_table, "b", (int *)"test3");
  insert_on_hash_table(hash_table, "b", (int *)"test4");
  insert_on_hash_table(hash_table, "b", (int *)"test5");

  free_hash_table(hash_table);
  free(hash_table);
  tearDownHashTable();
}
