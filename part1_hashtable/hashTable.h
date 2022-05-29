#ifndef hashTable
#define hashTable
#define BUCKET_COUNT 1024

#ifndef __cplusplus
typedef unsigned char bool;
static const bool False = 0;
static const bool True = 1;
#endif
typedef struct Binding
{
    char *key;
    int value;
    struct Binding *next;
} Binding;

typedef struct HashTable
{
    struct Binding *buckets[BUCKET_COUNT];
} HashTable;

struct HashTable *create();

unsigned int hash(const char *key);

bool add(struct HashTable *table, const char *key, int value);

struct Binding *find(struct HashTable *table, const char *key);

bool remove(struct HashTable *table, const char *key);

void delete_table(struct HashTable *table);
#endif