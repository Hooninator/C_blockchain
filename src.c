/*Credit to: https://myram.xyz/c-blockchain-implementation-1/*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src.h"


int string_hash(void *string) {
    int result = 5381;
    unsigned char *p;
    p = (unsigned char *) string;

    while (*p!='\0') {
        result = (result << 5) + result + *p;
        ++p;
    }

    return result;
}

NODE* add(NODE* node, DATA data) {
    while (node!=NULL) {
        node = node->next;
    }
    node = malloc(sizeof(NODE));
    node->data = data;
    return node;
}

void print_list(NODE* head) {
    printf("Print chain\n");
    printf("===========\n");
    int prev_hash = 0;
    while (head!=NULL) {
        int block_hash = head->data.info.block_hash;
        unsigned char *transaction = head->data.info.transactions;
        printf("Previous hash    %d\n", prev_hash);
        printf("Block hash  %d\n", block_hash);
        printf("Transaction:    %s\n", transaction);
        prev_hash = block_hash;
    }
}

void get_list_transactions(NODE* head, unsigned char *list_trans) {
    int len=0;
    NODE *curr = head;
    while (curr!=NULL) {
        len+=1;
        curr=curr->next;
    }
    list_trans = malloc(sizeof(char)*len+1);
    /*REMEMBER to shove in the null terminator yourself at the end of list_trans*/
    int i=0;
    while (head!=NULL) {
        list_trans[i] = head->data.info.transactions;
        i+=1;
        head = head->next;
    }
    list_trans[i]='\0';
}

NODE *reverse(NODE *head) {
    NODE *curr = head;
    NODE *next = NULL;
    NODE *prev = NULL;
    while(curr!=NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
    return head;
}

party_code get_vote() {
    int r = rand();
    return r%MAX_PARTIES;
}

NODE *genesis_block() {
    NODE *head=NULL;
    DATA genesis_element;
    transaction genesis_transaction = get_vote();
    block_t genesis_block = {0, string_hash(genesis_transaction), genesis_transaction};
    genesis_element.info = genesis_block;
    head = add(head, genesis_element);
    return head;
}

void add_votes(NODE *head, int nvotes) {
    int previous_hash = head->data.info.previous_block_hash;
    int i;
    for (i=0; i<nvotes; i+=1) {
        DATA *el;
        block_t *b;
        transaction t = {get_vote()};

        b->block_hash = string_hash(t);
        b->transactions = t;
        el->info = *b;
        previous_hash = b->block_hash;
        head = add(head, *el);
    }
}

int main() {
    NODE *head = genesis_block();
    add_votes(head, 5);
    print_list(head);
    return 1;
}