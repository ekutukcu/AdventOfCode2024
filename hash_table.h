#include <stdbool.h>

int hash(int value, int hash_table_size);
typedef struct hash_table_entry
{
    struct hash_table_entry *next;
    int key;
    void* value;
} hash_table_entry;

typedef struct hash_table
{
    struct hash_table_entry **entries;
    int capacity;
    int key_size;
    int size;
} hash_table;

hash_table *hash_table_create(int min_capacity);

void hash_table_delete(hash_table* dict);

hash_table_entry *hash_table_lookup( hash_table *dict, int key);

void hash_table_insert(hash_table *dict, int key, void* value);

bool hash_table_contains(hash_table *dict, int key);