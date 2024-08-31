#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_HASHMAP_SIZE 16
#define MIN_FULLFILMENT_PERSENTAGE 20
#define MAX_FULLFILMENT_PERSENTAGE 80

typedef struct Hashmap_item {
  char *key;
  char *value;
  struct Hashmap_item *next;
} Hashmap_item;

typedef struct {
  Hashmap_item **arr;
  unsigned int fullfiled_slots;
  unsigned int size;
} Hashmap;

Hashmap *init_hashmap() {
  Hashmap *hashmap = malloc(sizeof(Hashmap));
  if (hashmap == NULL) {
    exit(1);
  }

  hashmap->arr = malloc(sizeof(Hashmap_item) * MIN_HASHMAP_SIZE);
  if (hashmap->arr == NULL) {
    free(hashmap);
    exit(1);
  }
  hashmap->fullfiled_slots = 0;
  hashmap->size = MIN_HASHMAP_SIZE;

  for (int i = 0; i < MIN_HASHMAP_SIZE; ++i) {
    hashmap->arr[i] = NULL;
  }

  return hashmap;
}

unsigned int sdbm_hash_me_dady(char *str, unsigned int length,
                               unsigned int hmap_size) {
  unsigned int hash = 0;
  unsigned int i = 0;

  for (i = 0; i < length; str++, i++) {
    hash = (*str) + (hash << 6) + (hash << 16) - hash;
  }

  return hash % hmap_size;
}

Hashmap_item *create_h_item(char *key, char *value) {
  Hashmap_item *h_item = malloc(sizeof(Hashmap_item));
  if (h_item == NULL) {
    exit(1);
  }
  h_item->key = key;
  h_item->value = value;
  h_item->next = NULL;

  return h_item;
}

void resize(Hashmap *hmap, unsigned int new_size) {
  Hashmap_item **new_arr = malloc(sizeof(Hashmap_item) * new_size);
  if (new_arr == NULL) {
    exit(1);
  }

  for (int i = 0; i < hmap->size; ++i) {
    if (hmap->arr[i] != NULL) {
      unsigned int new_hash = sdbm_hash_me_dady(
          hmap->arr[i]->key,
          strnlen(hmap->arr[i]->key, sizeof hmap->arr[i]->key), new_size);

	  new_arr[new_hash] = hmap->arr[i];
    }
  }
}

void resize_or_skip(Hashmap *hmap) {
  if ((hmap->fullfiled_slots / hmap->size) * 100 == MIN_FULLFILMENT_PERSENTAGE) {
    resize(hmap, hmap->size * 2);
  }

  if ((hmap->fullfiled_slots / hmap->size) * 100 == MAX_FULLFILMENT_PERSENTAGE) {
    resize(hmap, hmap->size / 2);
  }
}

void insert(Hashmap *hmap, char *key, char *value) {
  Hashmap_item *new_h_item = create_h_item(key, value);
  unsigned int hash = sdbm_hash_me_dady(key, strnlen(key, sizeof key), MIN_HASHMAP_SIZE);

  if (hmap->arr[hash] == NULL) {
    hmap->arr[hash] = new_h_item;
    hmap->fullfiled_slots++;
    return;
  }

  // move through linked list until the key is found
  Hashmap_item *prev = hmap->arr[hash];
  while (prev != NULL) {
    if (strcmp(prev->key, new_h_item->key) == 0) {
      prev->value = new_h_item->value;
      return;
    }
    prev = prev->next;
  }

  // or add a new entry
  prev->next = new_h_item;
}

Hashmap_item *get(Hashmap *hmap, char *key) {
  unsigned int hash =
      sdbm_hash_me_dady(key, strnlen(key, sizeof key), MIN_HASHMAP_SIZE);

  if (hmap->arr[hash] == NULL) {
    return NULL;
  }

  Hashmap_item *prev = hmap->arr[hash];
  while (prev != NULL) {
    if (strcmp(prev->key, key) == 0) {
      return prev;
    }
    prev = prev->next;
  }

  return NULL;
}

void delete(Hashmap *hmap, char *key) {
  unsigned int hash = sdbm_hash_me_dady(key, strnlen(key, sizeof key), MIN_HASHMAP_SIZE);

  if (hmap->arr[hash] == NULL) {
    return;
  }

  if (hmap->arr[hash]->next == NULL) {
    hmap->arr[hash] = NULL;
    hmap->fullfiled_slots--;
    free(hmap->arr);
  }

  Hashmap_item *current_item = hmap->arr[hash];
  Hashmap_item *prev_item = NULL;
  while (current_item != NULL) {
    if (strcmp(current_item->key, key) == 0) {
      break;
    }
    prev_item = current_item;
    current_item = current_item->next;
  }

  if (current_item != NULL && prev_item != NULL) {
    prev_item->next = current_item->next;
    current_item = NULL;
    free(current_item);
  }

  if (current_item != NULL) {
    hmap->arr[hash] = NULL;
    current_item = NULL;
    free(current_item);
  }
}

int main() {
  Hashmap *hashmap = init_hashmap();
  insert(hashmap, "deez", "nuts");
  delete (hashmap, "deez");
}
