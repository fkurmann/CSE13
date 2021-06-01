#ifndef __LINKEDLISTUNTRACKED_H__
#define __LINKEDLISTUNTRACKED_H__

#include "node.h"

#include <stdbool.h>
#include <stdint.h>

extern uint64_t seeks; // Number of seeks performed.
extern uint64_t links; // Number of links traversed.

typedef struct LinkedListUntracked LinkedListUntracked;

LinkedListUntracked *llu_create(bool mtf);

void llu_delete(LinkedListUntracked **llu);

uint32_t llu_length(LinkedListUntracked *llu);

Node *llu_lookup(LinkedListUntracked *llu, char *oldspeak);

void llu_insert(LinkedListUntracked *llu, char *oldspeak, char *newspeak);

void llu_print(LinkedListUntracked *llu);

#endif
