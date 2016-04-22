#ifndef _Hash_H

struct ListNode;
struct HashTal;
typedef struct ListNode *Position;
typedef struct HashTal *HashTable;
typedef unsigned int ElementType;
HashTable InitializeTable(unsigned int);
unsigned int NextPrime(unsigned int);
unsigned int hash(ElementType key, struct HashTal const *);
void Insert(ElementType, ElementType, struct HashTal const *);
Position Find(ElementType, struct HashTal const *);
void FreeTable(HashTable);

#endif