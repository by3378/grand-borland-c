#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "stock.h"

#define DIRECTORY "C:\\code\\database\\"
#define FILE_LEN (sizeof(DIRECTORY)+CODE_LEN+sizeof(".expma")+5)


#define SAFE_READ( ptr, size, num, file) \
    if (fread(ptr, size, num, file) != num) \
    { \
        if (feof(file)) \
        { \
            fprintf(stderr, "Unexpected end of file.\n"); \
        } \
        else if (ferror(file)) \
        { \
            perror("Read error"); \
        } \
        exit(EXIT_FAILURE); \
    }

#define SAFE_WRITE( ptr, size, num, file) \
    if (fwrite( ptr, size, num, file) != num) \
    { \
        perror("Write error"); \
        exit(EXIT_FAILURE); \
    }

#define SAFE_SCANF( file, info ) \
    do{ \
        int result = fscanf(file, " %u %f %f %f %f", &(info).date, &(info).open, &(info).high, &(info).low, &(info).close); \
        if (result != 5)\
        { \
            if( feof(file) )\
            { \
                fprintf(stderr, "Unexpected end of file while reading.\n"); \
            } \
            else if( ferror(file) )\
            { \
                perror("Read error"); \
            } \
            else\
            { \
                fprintf(stderr, "Failed to read all 5 values.\n"); \
            } \
            exit(EXIT_FAILURE); \
        } \
    }while (0)


FILE* open_file( const char* code , const char* extension, const char* mode );
void close_file( FILE* fp , const char* code, const char* extension );

void* safe_malloc( size_t size ); 
void* safe_calloc( int num, size_t size ); 

/* variable arguments 
#define SAFE_FSCANF( file, format, ...) \
    do{ \
        int result = fscanf(file, format, __VA_ARGS__); \
        if (result == EOF) \
        { \
            if (feof(file)) \
            { \
                fprintf(stderr, "Unexpected end of file while reading.\n"); \
            } \
            else if (ferror(file)) \
            { \
                    perror("Read error"); \
            } \
            exit(EXIT_FAILURE); \
        } \
    } while (0)*/

#endif