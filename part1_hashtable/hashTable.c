// Name - kidus sintayehu
// id  - ugr/8503/12
// section - 3

#include <stdio.h>
#include <stdlib.h>
#include "hashTable.h"
#include <string.h>
struct HashTable *table = NULL;
/**
 * It creates a new hash table and returns a pointer to it
 *
 * @return A pointer to a HashTable struct.
 */

struct HashTable *create()
{
    table = (struct HashTable *)malloc(sizeof(struct HashTable));
    if (table == NULL)
        return NULL;
    int i;
    for (i = 0; i < BUCKET_COUNT; i++)
        table->buckets[i] = NULL;
    return table;
};

/**
 * It adds up the ASCII values of the characters in the string, and then returns the remainder of that
 * sum divided by the number of buckets
 *
 * @param key The key to hash.
 *
 * @return The hash function is returning the index of the bucket in which the key should be stored.
 */
unsigned int hash(const char *key)
{
    unsigned long i = 0;
    for (int j = 0; key[j]; j++)
        i += key[j];
    return i % BUCKET_COUNT;
};
/**
 * It creates a new binding with the given key and value, and returns a pointer to it
 *
 * @param key The key to be stored in the binding.
 * @param value The value to be stored in the binding.
 *
 * @return A pointer to a Binding struct.
 */

struct Binding *createBinding(const char *key, int value)
{
    struct Binding *bd = (struct Binding *)malloc(sizeof(struct Binding));

    bd->key = key;
    bd->value = value;

    bd->next = NULL;
    return bd;
}
/**
 * If the bucket is empty, create a new binding and add it to the bucket. Otherwise, iterate through
 * the bucket until you find the key or the end of the bucket, and then add the binding to the end of
 * the bucket
 *
 * @param table The hash table to add the key/value pair to.
 * @param key The key to be added to the hash table.
 * @param value the value to be added to the hash table
 *
 * @return A pointer to the binding with the given key.
 */

bool add(struct HashTable *table, const char *key, int value)
{
    struct Binding *bd;
    int index = hash(key);

    struct Binding *currentItem = table->buckets[index];
    if (currentItem == NULL)
    {
        bd = createBinding(key, value);
        table->buckets[index] = bd;
        return True;
    }
    while (currentItem->next != NULL)
    {
        if (currentItem->key == key)
        {
            currentItem->value = value;
            return False;
        }
        currentItem = currentItem->next;
    }
    bd = createBinding(key, value);
    currentItem->next = bd;
}

/**
 * We start at the head of the linked list at the index of the hash table that corresponds to the key
 * we're looking for. We then iterate through the linked list until we find the key we're looking for,
 * or we reach the end of the linked list
 *
 * @param table The hash table to search in.
 * @param key the key to search for
 *
 * @return A pointer to a binding.
 */

struct Binding *find(struct HashTable *table, const char *key)
{
    int index = hash(key);
    struct Binding *bd = table->buckets[index];

    while (bd != NULL)
    {

        if (strcmp(bd->key, key) == 0)
        {
            return bd;
        }
        else if (bd->next == NULL)
        {
            return NULL;
        }
        bd = bd->next;
    }
    return NULL;
};
/**
 * It removes a binding from the list of bindings
 *
 * @param bd The binding to remove.
 */

void removeBinding(Binding *bd)
{
    if (bd->next != NULL)
    {
        removeBinding(bd->next);
        free(bd->next);
    }
    free(bd->key);
}
/**
 * If the key is found, remove it from the linked list and return true
 *
 * @param table The hash table to remove the key from.
 * @param key The key to remove from the hash table.
 *
 * @return A boolean value.
 */

bool remove(HashTable *table, const char *key)
{
    int index = hash(key);

    struct Binding *bd = table->buckets[index];

    while (bd != NULL)
    {
        if (bd->next != NULL && bd->key == key)
        {
            free(bd);
            table->buckets[index] = bd->next;
            return True;
        }
        else if (bd->next == NULL && bd->key == key)
        {
            free(bd);
            table->buckets[index] = NULL;
            return True;
        }
        else if (bd->next != NULL && bd->next->key == key)
        {
            struct Binding *bd_next = bd->next;
            bd->next = bd->next->next;
            free(bd_next);
            return True;
        }

        bd = bd->next;
    }
    return False;
};
/**
 * For each bucket, free each binding, then free the table.
 *
 * @param table The table to delete.
 */

void delete_table(struct HashTable *table)
{
    for (int i = 0; i < BUCKET_COUNT; i++)
    {
        struct Binding *bd = table->buckets[i];
        while (bd != NULL)
        {
            struct Binding *next_bd = bd->next;
            free(bd);
            bd = next_bd;
        }
    }
    free(table);
}
