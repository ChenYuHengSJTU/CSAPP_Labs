// #define REF
#ifndef REF
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "cachelab.h"

#define Group(a) ((a >> b) & groupmask)
#define Valid(a) (((uint32_t)a) >> (s + b))

int s, b, E;
int hit, miss, eviction;
int groupmask, validmask;

struct Node{
    struct Node* next;
    unsigned addr;
};

struct Node** Mem;
int* Num;

// pop the node d
void Pop(struct Node* prev, struct Node* d){
    struct Node* tmp = prev;
    while(tmp->next != d){
        // printf("Pop\n");
        assert(tmp->next != NULL);
        tmp = tmp->next;
    }
    tmp->next = tmp->next->next;
    // free(d);
}

// push i into Mem[prev]
void Push(struct Node* prev, struct Node* i){
    struct Node* tmp = prev->next;
    i->next = tmp;
    prev->next = i;
}

void Access(char op, uint32_t addr, uint32_t sz){
    int group = Group(addr);
    int valid = Valid(addr);

    struct Node* tmp = Mem[group];
    int found = 0;
    

    while(tmp->next != NULL){
        // printf("Access\n");
        tmp = tmp->next;
        if(Valid(tmp->addr) == valid){
            if(op == 'M')
                hit += 2;
            else
                hit++;
            found = 1;
            Pop(Mem[group],tmp);
            Push(Mem[group], tmp);   
            break;     
        }
    }
    
    if(!found){
        if(op == 'M'){
            miss++;
            hit++;
        }
        else 
            miss++;
        int num = 0;
        struct Node* t = Mem[group];
        while(t->next != NULL){
            t=t->next;
            num++;
        }

        if(num == E){
            Pop(Mem[group], t);
            eviction++;
        }
        t = (struct Node*)malloc(sizeof(struct Node));
        t->addr = addr;
        Push(Mem[group], t);
    }
}

void ProcessInput(const char* filename){
    FILE* fp = fopen(filename, "r");

    if(fp == NULL)
        perror("open file error");
    
    char buf[32];

    char op;
    uint32_t addr, sz;

    while(fgets(buf, 32, fp)){
        if(buf[0] == ' '){
            op = buf[1];
        }        
        else op = buf[0];

        sscanf(buf + 2, "%x,%d", &addr, &sz);

        // printf("op:%c\taddr:%x\tsz:%d\n", op, addr, sz);
        if(op != 'I')
            Access(op, addr, sz);
        memset(buf, 0, 32);
        // printf("hit: %d\tmiss: %devict: %d\n", hit, miss, eviction);
    }
}

void Init(){
    Mem = (struct Node**)malloc((1 << s) * sizeof(struct Node*));

    int S = (1 << s);

    for(int i = 0;i < S;++i)
        Mem[i] = (struct Node*)malloc(sizeof(struct Node));

    // for(int i = 0;i < s;++i){
    //     groupmask <<= 1;
    //     groupmask |= 1;
    // }

    unsigned mask = 0xffffffff;

    groupmask = mask >> (32 - s);
    // validmask = mask >> (s + b);

    Num = (int*)malloc(sizeof(int) * S);
    memset(Num, 0, sizeof(int) * S);

    // printf("Init over\n");
}   

int main(int argc, char* argv[])
{
    printf("%s\n", argv[argc - 1]);
    char opt;
    // char filename[32];
    while((opt = getopt(argc, argv, "s:E:b:t:")) != -1){
        switch(opt){
            case 's':
                s = atoi(optarg);
                printf("s:%d\n", s);
                break;
            case 'E':
                E = atoi(optarg);
                printf("E:%d\n", E);
                break;
            case 'b':
                b = atoi(optarg);
                printf("b:%d\n", b);
                break;
            case 't':
                // memcpy(filename, optarg, strlen(optarg));
                break;
        }
    }
    Init();
    ProcessInput(argv[argc - 1]);
    printSummary(hit, miss, eviction);
    return 0;
}
#endif

#ifdef REF
#define _GNU_SOURCE
#include "cachelab.h"
#include "stdlib.h"
#include <stdio.h>
#include "getopt.h"
#include <string.h>
#define addrLen 8

static int S;
static int E;
static int B;
static int hits = 0;
static int misses = 0;
static int evictions = 0;
static int totalSet;

typedef struct _Node{
    unsigned tag;
    struct _Node* next;
    struct _Node* prev;
}Node;

typedef struct _LRU{
    Node* head;
    Node* tail;
    int* size;
}LRU;

static LRU* lru;

void initializeLRU(int i){
    lru[i].head = malloc(sizeof(Node));
    lru[i].tail = malloc(sizeof(Node));

    lru[i].head->next = lru[i].tail;
    lru[i].tail->prev = lru[i].head;
    (lru[i].size)     = (int* )malloc(sizeof(int));
    *(lru[i].size)      = 0;
}

/**
 *
 * @param lru the lru we manupilate
 * @param pos the node position to be deleted usually 0 or 1
 *              0 means the first one
 *              1 means the last one
 */
void deleteElement(unsigned set, Node* nodeToDel, LRU* curLru){
    nodeToDel->next->prev = nodeToDel->prev;
    nodeToDel->prev->next = nodeToDel->next;
    *(curLru->size) = *(curLru->size) - 1;
}

void evict(unsigned set, LRU* curLru){
    deleteElement(set, curLru->tail->prev, curLru);
}

void addFirst(unsigned set, Node* node, LRU* curLru){
    node->next = curLru->head->next;
    node->prev = curLru->head;

    curLru->head->next->prev = node;
    curLru->head->next       = node;

    *(curLru->size) = *(curLru->size) + 1;
}

void parseOption(int argc, char** argv, char** fileName){
    int option;
    while( (option = getopt(argc, argv, "s:E:b:t:")) != -1){
        switch (option) {
            case 's':
                S = atoi(optarg);
            case 'E':
                E = atoi(optarg);
            case 'b':
                B = atoi(optarg);
            case 't':
                strcpy(*fileName, optarg);
        }
    }


    totalSet = 1 << S;
}
void update(unsigned address){
    unsigned mask = 0xFFFFFFFF;
    unsigned maskSet = mask >> (32 - S);
    unsigned targetSet = ((maskSet) & (address >> B));
    unsigned targetTag = address >> (S + B);

    LRU curLru = lru[targetSet];
    
    // to find if we have one
    Node* cur = curLru.head->next;
    int found = 0;
    while(cur != curLru.tail){
        if(cur->tag == targetTag){
            found = 1;
	    break;
        }

        cur = cur->next;
    }

    
    if(found){
        hits++;
        deleteElement(targetSet, cur, &curLru);
        addFirst(targetSet, cur, &curLru);
	// printf("hit!, the set number %d \n", targetSet);
    }else{

        Node* newNode = malloc(sizeof(Node));
        newNode->tag = targetTag;
        if(*(curLru.size) == E){ // full, need to evict
            deleteElement(targetSet, curLru.tail->prev, &curLru);
            addFirst(targetSet, newNode, &curLru);

            evictions++;
            misses++;
	    // printf("evic + miss set -> %d\n", targetSet);
        }else{
            misses++;
            addFirst(targetSet, newNode, &curLru);
            // printf("only miss %d\n", targetSet);
        }    
    }
}



void cacheSimulateWhole(char* fileName){
    // step1: new lru with s sets
    lru = malloc(totalSet * sizeof(*lru));
    for(int i = 0; i < totalSet; i++)
        initializeLRU(i);

    FILE* file = fopen(fileName, "r");
    char op;
    unsigned address;
    int size;
    // L 10, 1
    while(fscanf(file, " %c %x,%d", &op, &address, &size) > 0){
        printf("%c, %x %d\n", op, address, size);
	switch (op) {
            case 'L':
                update(address);
                break;
            case 'M':
                update(address);
            case 'S':
                update(address);
                break;
        }
        printf("hit: %d\tmiss: %d\tevict: %d\n", hits, misses, evictions);
    }
}

int main(int argc, char** argv)
{
    char* fileName = malloc(100 * sizeof(char));

    // step1: parse option
    parseOption(argc, argv, &fileName);

    // step2: read all of the lines and analyze it
    cacheSimulateWhole(fileName);

    printSummary(hits, misses, evictions);
    return 0;
}
#endif