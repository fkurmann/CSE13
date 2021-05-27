#include "ht.h"
#include "ll.h"
#include "speck.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variables if needed


struct HashTable{
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
};
HashTable *ht_create(uint32_t  size , bool  mtf) {
    HashTable *ht = (HashTable  *)  malloc(sizeof(HashTable));
    if (ht) {
        //  Leviathan
	ht->salt[0] = 0x9846e4f157fe8840;
  	ht->salt[1] = 0xc5f318d7e055afb8;
    printf("%u \n", size);
	ht->size = size;
    printf("%u \n", ht->size);
	ht->mtf = mtf;
	ht->lists = (LinkedList  **)  calloc(size , sizeof(LinkedList  *));
	if (!ht->lists) {
            printf("Aborting \n");
	    free(ht);
	    ht = NULL;
	}
    }
    return  ht;
}

void ht_delete(HashTable **ht) {
    if (*ht && (*ht)->lists) {
        // Delete all of the linked lists in the hash table
	for (uint32_t i = 0; i < (*ht)->size; i++) {
	    if ((*ht)->lists[i] != NULL) {
	        ll_delete(&(*ht)->lists[i]);
	    }
	}
	free((*ht)->lists);;
	free(*ht);
	*ht = NULL;
    }
    return;
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}
/*
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    return;
}*/

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    // Create a variable which is the hashed version of oldspeak, adjusted for the size of the hashtable
    uint32_t hash_value = 0; 
    hash_value = hash(ht->salt, oldspeak);
    hash_value = hash_value % ht->size;

    // If this index of the hash table does not have a linked list yet, make one
    if (ht->lists[hash_value] == NULL) {
        ht->lists[hash_value] = ll_create(ht->mtf);
    }

    // Insert the node into the linked list at hash table index "hash"
    ll_insert(ht->lists[hash_value], oldspeak, newspeak);
    return;
}

uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
	if (ht->lists[i] != NULL) {
	    count++;
	}
    }
    return count;
}

void ht_print(HashTable *ht) {
    return;
}
