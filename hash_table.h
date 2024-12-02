
#include <string.h>
#include <math.h>
#include <stdbool.h>

int compare_ints(const void *a, const void *b)
{
    int value_a = *(int *)a;
    int value_b = *(int *)b;
    return value_a - value_b;
}

const unsigned int ALPHA = 2654435769; // 2^32 (-1 + sqrt(5)) / 2
int hash(int value, int hash_table_size)
{
    // Knuth multiplicative hash 
    unsigned int unsigned_value = (unsigned int)value;
    return (value*ALPHA)>>(32-hash_table_size);
}

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

struct hash_table *hash_table_create(int min_capacity)
{
    struct hash_table *dict = malloc(sizeof(struct hash_table));
    if(!dict)
    {
        return NULL;
    }

    dict->key_size = (int)floor(log2(min_capacity))+1;
    dict->size = (int)pow(2,dict->key_size);

    dict->entries = (struct hash_table_entry **)calloc(dict->size, sizeof(struct hash_table_entry *));
    if(!dict->entries)
    {
        free(dict);
        return NULL;
    }
    
    return dict;
}

void hash_table_delete(struct hash_table* dict)
{
    for(int i=0;i<dict->size;i++)
    {
        struct hash_table_entry * next_entry = dict->entries[i];
        while(next_entry != NULL)
        {
            struct hash_table_entry *temp = next_entry;
            next_entry = next_entry->next;
            free(temp);
        }
    }
    free(dict->entries);
    free(dict);
}

struct hash_table_entry *hash_table_lookup(struct hash_table *dict, int key)
{
    int index = hash(key, dict->key_size);
    struct hash_table_entry *next_value = dict->entries[index];
    int depth = 0;
    while (next_value != NULL)
    {
        if (next_value->key == key)
        {
            return next_value;
        }
        next_value = next_value->next;
        depth++;
    }
    return NULL;
}

void hash_table_insert(struct hash_table *dict, int key, int value)
{
    struct hash_table_entry *existing_entry = hash_table_lookup(dict, key);
    if (existing_entry)
    {
        existing_entry->value = value;
    }
    else
    {
        int index = hash(key, dict->key_size) % dict->size;
        existing_entry = dict->entries[index];
        struct hash_table_entry *new_entry = malloc(sizeof(struct hash_table_entry));
        new_entry->key = key;
        new_entry->value = value;
        new_entry->next = existing_entry;
        dict->entries[index] = new_entry;
    }
}

bool hash_table_contains(struct hash_table *dict, int key)
{
    return hash_table_lookup(dict, key) != NULL;
}

