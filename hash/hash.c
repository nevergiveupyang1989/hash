#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

struct ListNode{
	ElementType key;
	ElementType value;
	Position next;
};

struct HashTal{
	unsigned int size;
	Position* TheLists;
};

unsigned int NextPrime(unsigned int size){
	unsigned int i;
	int flag=0;

	if(0 == size%2)
		size++;
	else{
		for(;;size+=2){
			for(i=3; i*i<=size; i+=2){
				if(0==size%i){
					break;
				}
				else{
					flag=1;
				}
			}
			if(flag)
				break;
		}
		return size;
	}
	return size;
}

unsigned int hash(ElementType key, struct HashTal const *table){
	unsigned int index;
	unsigned int size;
	size = table->size;
	index = key%size;

	return index;
}

Position Find(ElementType key, struct HashTal const *table){
	Position header, CurrentNode;
	unsigned int index;

	index = hash(key, table);
	header = table->TheLists[index];
	CurrentNode = header;

	CurrentNode=CurrentNode->next;
	while(CurrentNode){
		if(CurrentNode->key == key)
			break;
		CurrentNode=CurrentNode->next;
	}

	return CurrentNode;
}

void Insert(ElementType key, ElementType value, struct HashTal const *table){
	unsigned int index;
	Position TargetNode, NewCell;
	index = hash(key,table);

	if(index > table->size)
		exit(0);

	TargetNode = table->TheLists[index];
	NewCell = malloc(sizeof(struct ListNode));

	if(NULL == NewCell)
		exit(0);

	NewCell->key = key;
	NewCell->value = value;

	NewCell->next = TargetNode->next;
	TargetNode->next = NewCell;
}

HashTable InitializeTable(unsigned int size){
	unsigned int i;
	HashTable table = malloc(sizeof(struct HashTal));
	
	if(NULL==table){
		printf("malloc failed");
		exit(0);
	}

	table->size = NextPrime(size);
	table->TheLists = malloc(sizeof(struct ListNode*)*(table->size));

	for(i=0; i<table->size; i++){
		table->TheLists[i] = malloc(sizeof(struct ListNode));

		if(NULL==table->TheLists[i]){
			printf("malloc failed");
			exit(0);
		}
	
		table->TheLists[i]->next = NULL;
	}

	return table;
}

void FreeTable(HashTable table){
	unsigned int i;

	if(NULL == table)
		return;
	
	for(i=0; i<table->size; i++){
		free(table->TheLists[i]);
	}
	free(table->TheLists);
	free(table);
}
