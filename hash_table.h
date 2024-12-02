#include <stdbool.h>

int hash(int value, int hash_table_size);
struct hash_table_entry
{
    struct hash_table_entry *next;
    int key;
    int value;
};

struct hash_table
{
    struct hash_table_entry **entries;
    int size;
    int key_size;
};

struct hash_table *hash_table_create(int min_capacity);

void hash_table_delete(struct hash_table* dict);

struct hash_table_entry *hash_table_lookup(struct hash_table *dict, int key);

void hash_table_insert(struct hash_table *dict, int key, int value);

bool hash_table_contains(struct hash_table *dict, int key);