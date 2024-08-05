#ifndef HASH_TABLE_H
#define HASH_TABLE_H

struct hash_table {
  int length;
  int size;
  struct hash_table_list **table;
};

struct hash_table_node {
  int *value;
  char *key;
  struct hash_table_node *next;
};

struct hash_table_list {
  struct hash_table_node *head;
  int length;
};

void initialize_hash_table(struct hash_table *ht, int size);

void free_hash_table(struct hash_table *ht);

void free_hash_table_list(struct hash_table_list *htl);

void rezise_hash_table(struct hash_table *ht);

int djb2(char *key, int);

int *get_from_hash_table(struct hash_table *table, char *key);

void insert_on_hash_table(struct hash_table *table, char *key, int *value);

int *delete_on_hash_table(struct hash_table *table, char *key);

int *update_on_hash_table(struct hash_table *table, char *key, int *new_value);

#endif  // !HASH_TABLE_H
