#include <stdio.h>
#include <stdlib.h>
#include "hashTable.h"
#include "hashTable.c"

#include <string.h>

int main()
{
    struct HashTable *ht = create();
    struct Binding *val;

    add(ht, "john2", 17);
    add(ht, "john", 15);
    add(ht, "john3", 16);
    add(ht, "john4", 19);

    // removeItem(ht, "john3");

    for (int i = 0; i < BUCKET_COUNT; i++)
    {
        struct Binding *bd = table->buckets[i];
        while (bd != NULL)
        {
            printf("\t %i  --- key %s value %d\n", i, bd->key, bd->value);
            bd = bd->next;
        }
    }
    if ((val = find(table, "john")) == NULL)
    {
        printf("\t NULL\n");
    }
    else
    {
        val = find(table, "john");
        printf("\t key ---  %s value %d\n", val->key, val->value);
    }
    // delete_table(ht);
}