#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include <setjmp.h>
#include <math.h>

jmp_buf jumper;

struct ListNode{
	ElementType key;
	ElementType value;
	Position next;
};

struct HashTal{
	int size;
	Position* TheLists;
};

int NextPrime(int size){
	if(0 == size%2)
		size++;
	return size;
}

int hash(ElementType key, HashTable table){
	int index;
	int size;
	size = table->size;
	index = key%size;

	return index;
}

Position Find(ElementType key, HashTable table){
	Position header, CurrentNode;
	int index;

	key = abs(key);
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

void Insert(ElementType key, ElementType value, HashTable table){
	int index;
	Position TargetNode, NewCell;
	index = hash(key,table);

	if(index > table->size)
		return;

	TargetNode = table->TheLists[index];
	NewCell = malloc(sizeof(struct ListNode));

	if(NULL == NewCell)
		return;

	NewCell->key = key;
	NewCell->value = value;

	NewCell->next = TargetNode->next;
	TargetNode->next = NewCell;
}

HashTable InitializeTable(int size){
	int i;
	HashTable table = malloc(sizeof(struct HashTal));
	
	if(0==setjmp(jumper)){
		if(NULL==table)
			longjmp(jumper,1); 
	}
	else{
		printf("malloc is failed");
	}

	table->size = NextPrime(size);
	table->TheLists = malloc(sizeof(struct ListNode*)*(table->size));

	for(i=0; i<table->size; i++){
		table->TheLists[i] = malloc(sizeof(struct ListNode));

		if(0==setjmp(jumper)){
			if(NULL==table->TheLists[i])
				longjmp(jumper,1); 
		}
		else{
				printf("malloc is failed");
				exit(0);
			}
		table->TheLists[i]->next = NULL;
	}

	return table;
}

void FreeTable(HashTable table){
	int i;

	if(NULL == table)
		return;
	
	for(i=0; i<table->size; i++){
		free(table->TheLists[i]);
	}
	free(table->TheLists);
	free(table);
}
