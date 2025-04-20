#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stock.h"
#include "calculate.h"
#include "global.h"
#include "file.h"
#include "draw.h"


FILE* open_file( const char* code , const char* extension, const char* mode )
{

    /* Create file name */
    char filename[FILE_LEN];
    strcpy( filename, DIRECTORY);
    strcat( filename, code);
    strcat( filename, extension);

    FILE* fp = fopen( filename, mode);
    if( fp == NULL )
    {
        fprintf(stderr, "Error: Cannot open file %s.%s\n", code, extension);
        exit(EXIT_FAILURE);
    }
    return fp;

}

void close_file( FILE* fp , const char* code, const char* extension )
{
    if( fclose(fp) != 0 )
    {
        fprintf(stderr, "Error: Cannot close file %s.%s\n", code, extension);
        exit(EXIT_FAILURE);
    }

}


void* safe_malloc( size_t size ) 
{
    void* ptr = malloc(size);
    if( ptr == NULL ) 
    {
        perror("Memory allocation with malloc failed");
        exit(EXIT_FAILURE);
    }
    return ptr;
}
    

void* safe_calloc( int num, size_t size ) 
{
    void* ptr = calloc(num, size);
    if( ptr == NULL ) 
    {
        perror("Memory allocation with calloc failed");
        exit(EXIT_FAILURE);
    }
    return ptr;
}
    