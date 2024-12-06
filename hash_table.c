#include <string.h>
#include <math.h>
#include "hash_table.h"
#include <stdlib.h>
const unsigned int ALPHA = 2654435769; // 2^32 (-1 + sqrt(5)) / 2
int hash(int value, int hash_table_size)
{
    // Knuth multiplicative hash 
    unsigned int unsigned_value = (unsigned int)value;
    return (value*ALPHA)>>(32-hash_table_size);
}

hash_table *hash_table_create(int min_capacity)
{
    hash_table *dict = malloc(sizeof(hash_table));
    if(!dict)
    {
        return NULL;
    }

    dict->key_size = (int)floor(log2(min_capacity))+1;
    dict->capacity = (int)pow(2,dict->key_size);
    dict->size = 0;

    dict->entries = (hash_table_entry **)calloc(dict->capacity, sizeof(hash_table_entry *));
    if(!dict->entries)
    {
        free(dict);
        return NULL;
    }

    return dict;
}

void hash_table_delete(hash_table* dict)
{
    for(int i=0;i<dict->capacity;i++)
    {
        hash_table_entry * next_entry = dict->entries[i];
        while(next_entry != NULL)
        {
            hash_table_entry *temp = next_entry;
            next_entry = next_entry->next;
            free(temp);
        }
    }
    free(dict->entries);
    free(dict);
}

hash_table_entry *hash_table_lookup(hash_table *dict, int key)
{
    int index = hash(key, dict->key_size);
    hash_table_entry *next_value = dict->entries[index];
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

void hash_table_insert(hash_table *dict, int key, void* value)
{
    hash_table_entry *existing_entry = hash_table_lookup(dict, key);
    if (existing_entry!=NULL)
    {
        existing_entry->value = value;
    }
    else
    {
        int index = hash(key, dict->key_size) % dict->capacity;
        existing_entry = dict->entries[index];
        hash_table_entry *new_entry = (hash_table_entry *)malloc(sizeof(hash_table_entry));
        new_entry->key = key;
        new_entry->value = value;
        new_entry->next = existing_entry;
        dict->entries[index] = new_entry;
        dict->size++;
    }
}

bool hash_table_contains(hash_table *dict, int key)
{
    return hash_table_lookup(dict, key) != NULL;
}

