#ifndef FILE_H
#define FILE_H

#include "global.h"

#define DEBUG
//#define BORLANDC
#if defined( BORLANDC )
    #define DIRECTORY "..\\..\\code\\database\\"
#elif defined( DEBUG )
    #define DIRECTORY "C:\\Users\\eyx\\Desktop\\debug\\database\\"
#else 
    #define DIRECTORY "C:\\code\\database\\"
#endif

#define FILE_LEN (sizeof(DIRECTORY)+CODE_LEN+sizeof(".weektxt")+5)


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

FILE* open_file( const char* code , enum line_type type, const char* mode );
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