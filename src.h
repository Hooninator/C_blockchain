#define NULL ((void *)0)


typedef int hash;
typedef char *transaction;

typedef struct Block_T {
    hash previous_block_hash;
    hash block_hash;
    transaction transactions;
}block_t;

typedef struct {
    block_t info;
} DATA;

typedef struct node {
    DATA data;
    struct node *next;
} NODE;

typedef enum party_code_t {
    GOOD_PARTY, EVIL_PARTY, MEDIOCRE_PARTY, MAX_PARTIES
} party_code;


extern int string_hash(void *string);


extern NODE* add(NODE* node, DATA data);


extern void print_list(NODE* head);


extern NODE * reverse(NODE * node);


extern void get_list_transactions(NODE* head,unsigned char *list_trans);

extern party_code get_vote();