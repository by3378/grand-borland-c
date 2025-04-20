#include "global.h"

FILE* open_file( const char* code , enum line_type type, const char* mode )
{

    char* extension = NULL;
    switch( type )
    {
        case DAY:
        {
            extension = ".d";
            break;
        }
        case WEEK:
        {
            extension = ".w";
            break;
        }
        case KDAY:
        {
            extension = ".kd";
            break;
        }
        case KWEEK:
        {
            extension = ".kw";
            break;
        }
        case MA:
        {
            extension = ".ma";
            break;
        }
        case EXPMA:
        {
            extension = ".exp";
            break;
        }
        case XUECHI:
        {
            extension = ".xue";
            break;
        }
        case KDJ:
        {
            extension = ".kdj";
            break;
        }
        case MACD:
        {
            extension = ".mcd";
            break;
        }
        case PRED:
        {
            extension = ".ar";
            break;
        }
        case STOCK:
        {
            extension = ".stc";
            break;
        }
        case GENE:
        {
            extension = ".ge";
            break;
        }
        case CHOICE:
        {
            extension = ".cho";
            break;
        }
        default:
        {
            fprintf(stderr, "Error: Invalid type\n");
            exit(EXIT_FAILURE);
        }
    }

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
    