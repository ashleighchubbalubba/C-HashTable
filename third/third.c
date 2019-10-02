#include "linkedlist.h"
#include<stdio.h> 
#include<stdlib.h> 
#define _GNU_SOURCE

int main(int argc, char *argv[]) {
    FILE* fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    //what we will be printing later
    int collision = 0;
    int success = 0;
    node_t* hashtable[10000]; 

    //checks if the file doesn't exist or it is blank
    fp = fopen(argv[1], "r");
    if(fp == NULL){
         printf("error");
         return 0;
    }
    if (NULL != fp){
        fseek(fp, 0, SEEK_END);
        int size = ftell(fp);
        if(size == 0){ 
            printf("0\n");
            exit(EXIT_FAILURE);
        }
    }
    
    fp = fopen(argv[1], "r");
    while ((read = getline(&line, &len, fp)) != -1) {
        //get letter. i==insert, s==search
        int size = sizeof(line)/sizeof(line[0]);
        int operation;
        if (line[0] == 'i')
            operation = 1;
        else if (line[0] == 's')
            operation = 0;
        else 
            operation = 2;
        char number[size];
        
        //get value
        arrayCopy(line, number, 2, size);
        int num = atoi(number);

        //establish key
        int key;
        key = num%10000;
        if(key<0) 
            key = key+10000;
        
        //inserting
        if(operation == 1) {
            //if key is empty
            if (hashtable[key] == NULL){
                node_t* startNode = NULL;
                hashtable[key] = push(num,startNode);
            } 
            //if key is not empty
            else {
                node_t* tempHead = hashtable[key];
                hashtable[key] = push(num,tempHead);
                collision++;
            }
        }
        else if(operation == 0) {
            //searching
            if(hashtable[key] == NULL){
                //do nothing
            }
            else{
                node_t *searchHead = hashtable[key];
                if(getNode(num, searchHead) != NULL)
                    success++;
            }
        } 
        else {
            //do nothing
        }
    }

    printf("%d\n",collision);
    printf("%d", success);

    free(line);
    exit(EXIT_SUCCESS);
    return 0;
}

