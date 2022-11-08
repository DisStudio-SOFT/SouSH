#include <stdio.h>
#include <stdlib.h>

void *cmalloc(unsigned long size){
    void *out = malloc(size);
    if(!out){
        fprintf(stderr, "Memory error");
        exit(EXIT_FAILURE);
    }
    return out; 
}
void *crealloc(void *ptr, unsigned long size){
    void *out = realloc(ptr, size);
    if(!out){
        fprintf(stderr, "Memory error");
        exit(EXIT_FAILURE);
    }
    return out; 
}