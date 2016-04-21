#ifndef _Hash_H
struct ListNode;
struct HashTal;
typedef struct ListNode *Position;
typedef struct HashTal *HashTable;
typedef int ElementType;
HashTable InitializeTable(int size);
int NextPrime(int);
int hash(ElementType, int);
Position Find(ElementType, HashTable);
void Insert(ElementType, ElementType, HashTable);
#endif