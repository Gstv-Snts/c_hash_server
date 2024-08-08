#include "hash_table.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initialize_hash_table(struct hash_table* ht, int size) {
  ht->size = size;
  ht->length = 0;
  ht->table = malloc(sizeof(struct hash_table_list) * size);
  for (int i = 0; i < size; i++) {
    struct hash_table_list* htl = malloc(sizeof(struct hash_table_list));
    htl->length = 0;
    htl->head = NULL;
    *(ht->table + i) = htl;
  }
};

void free_hash_table(struct hash_table* ht) {
  for (int i = 0; i < ht->size; i++) {
    free_hash_table_list(*(ht->table + i));
  }
  free(ht->table);
}

void free_hash_table_list(struct hash_table_list* htl) {
  if (htl->length > 0) {
    struct hash_table_node* curr = htl->head;
    for (int i = 0; i < htl->length; i++) {
      struct hash_table_node* tmp = curr;
      int* v = tmp->value;
      curr = curr->next;
      free(tmp);
    }
  }
  free(htl);
}

void rezise_hash_table(struct hash_table* ht) {
  int old_size = ht->size;
  int new_size = ht->size + (ht->size / 2);
  struct hash_table_list** old_table = ht->table;
  initialize_hash_table(ht, new_size);
  ht->size = new_size;

  for (int i = 0; i < old_size; i++) {
    struct hash_table_list* curr_table = old_table[i];
    struct hash_table_node* dq = NULL;
    while (curr_table->length > 0) {
      if (curr_table->length == 1) {
        dq = curr_table->head;
        curr_table->head = NULL;
        curr_table->length--;
      } else {
        dq = curr_table->head;
        curr_table->head = dq->next;
        curr_table->length--;
      }
      insert_on_hash_table(ht, dq->key, dq->value);
      free(dq);
    }
  }
  for (int i = 0; i < old_size; i++) {
    free(*(old_table + i));
  }
  free(old_table);
};

int djb2(char* key, int size) {
  unsigned long hash = 5381;
  int c;
  while ((c = *key++)) {
    hash = ((hash << 5) + hash) + c;
  }
  return hash % size;
}

int* get_from_hash_table(struct hash_table* ht, char* key) {
  struct hash_table_list* htl = *(ht->table + djb2(key, ht->size));
  struct hash_table_node* curr = htl->head;
  for (int i = 0; i < htl->length; i++) {
    if (curr->key == key) {
      return curr->value;
    }
    curr = curr->next;
  }
  return NULL;
}

void insert_on_hash_table(struct hash_table* ht, char* key, int* value) {
  int i = djb2(key, ht->size);
  struct hash_table_node* new_node = malloc(sizeof(struct hash_table_node));
  struct hash_table_list* curr_table = *(ht->table + i);
  new_node->key = key;
  new_node->value = value;
  new_node->next = NULL;
  if (curr_table->length == 0) {
    curr_table->head = new_node;
  } else {
    new_node->next = curr_table->head;
    curr_table->head = new_node;
  }
  curr_table->length++;
  ht->length++;
  if (ht->length == ht->size * 2) {
    rezise_hash_table(ht);
  }
}

int* delete_on_hash_table(struct hash_table* ht, char* key) {
  struct hash_table_list* htl = *(ht->table + djb2(key, ht->size));

  if (htl->length > 0) {
    struct hash_table_node* curr = (struct hash_table_node*)htl->head;
    if (curr->key == key) {
      int* r = curr->value;
      htl->length--;
      ht->length--;
      if (htl->length == 0) {
        htl->head = NULL;
      } else {
        htl->head = curr->next;
      }
      free(curr);
      return r;
    }

    while (curr != NULL) {
      if (curr->next != NULL) {
        if (curr->next->key == key) {
          struct hash_table_node* tmp = curr->next;
          if (tmp->next != NULL) {
            curr->next = tmp->next;
          }
          int* r = tmp->value;
          htl->length--;
          ht->length--;
          free(tmp);
          return r;
        }
      }
    }
  }

  return NULL;
}

int* update_on_hash_table(struct hash_table* ht, char* key, int* new_value) {
  struct hash_table_list* htl = *(ht->table + djb2(key, ht->size));
  struct hash_table_node* curr = htl->head;
  for (int i = 0; i < htl->length; i++) {
    if (curr->key == key) {
      int* curr_value = curr->value;
      curr->value = new_value;
      return curr_value;
    }
    curr = curr->next;
  }
  return NULL;
}
