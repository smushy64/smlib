/**
 * Description:  Collection Types Implementation
 * Author:       Alicia Amarilla (smushyaa@gmail.com)
 * File Created: February 24, 2023
*/
#include "smcol.h"
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

// NOTE(alicia): helper functions

#if defined(SM_COMPILER_GCC) || defined(SM_COMPILER_CLANG)
    #define vsnprintf __builtin_vsnprintf
#elif defined(SM_COMPILER_MSVC)
    #include <stdio.h>
#endif

typedef enum {
    SLICE_CMP_TYPE_BYTE,
    SLICE_CMP_TYPE_SHORT,
    SLICE_CMP_TYPE_INT,
    SLICE_CMP_TYPE_LONG_LONG
} slice_cmp_type_t;

bool32 slice_cmp( const u8* a, const u8* b, usize size ) {
    slice_cmp_type_t cmp_type = SLICE_CMP_TYPE_BYTE;
    if( size % sizeof(u64) == 0 ) {
        cmp_type = SLICE_CMP_TYPE_LONG_LONG;
    } else if( size % sizeof(u32) == 0 ) {
        cmp_type = SLICE_CMP_TYPE_INT;
    } else if( size % sizeof(u16) == 0 ) {
        cmp_type = SLICE_CMP_TYPE_SHORT;
    }

    switch( cmp_type ) {
        case SLICE_CMP_TYPE_BYTE: {
            for( usize i = 0; i < size; ++i ) {
                if( a[i] != b[i] ) {
                    return FALSE;
                }
            }
        } break;
        case SLICE_CMP_TYPE_SHORT: {
            u16* short_a = (u16*)a;
            u16* short_b = (u16*)b;
            usize short_size = size / sizeof(u16);
            for( usize i = 0; i < short_size; ++i ) {
                if( short_a[i] != short_b[i] ) {
                    return FALSE;
                }
            }
        } break;
        case SLICE_CMP_TYPE_INT: {
            u32* int_a = (u32*)a;
            u32* int_b = (u32*)b;
            usize int_size = size / sizeof(u32);
            for( usize i = 0; i < int_size; ++i ) {
                if( int_a[i] != int_b[i] ) {
                    return FALSE;
                }
            }
        } break;
        case SLICE_CMP_TYPE_LONG_LONG: {
            u64* long_long_a = (u64*)a;
            u64* long_long_b = (u64*)b;
            usize long_long_size = size / sizeof(u64);
            for( usize i = 0; i < long_long_size; ++i ) {
                if( long_long_a[i] != long_long_b[i] ) {
                    return FALSE;
                }
            }
        } break;
    }
    return TRUE;
}

// NOTE(alicia): allocator management

smushy_collections_heap_alloc_fn   SMCOL_ALLOC   = malloc;
smushy_collections_heap_realloc_fn SMCOL_REALLOC = realloc;
smushy_collections_heap_free_fn    SMCOL_FREE    = free;

void smcol_set_allocator(
    smushy_collections_heap_alloc_fn heap_alloc,
    smushy_collections_heap_realloc_fn heap_realloc,
    smushy_collections_heap_free_fn heap_free
) {
    SMCOL_ALLOC   = heap_alloc;
    SMCOL_REALLOC = heap_realloc;
    SMCOL_FREE    = heap_free;
}

// NOTE(alicia): list

bool32 list_create( usize stride, usize capacity, list_t* result ) {
    usize size   = stride * capacity;
    void* buffer = (SMCOL_ALLOC( size ));
    if( (capacity != 0) && !buffer ) {
        return FALSE;
    }

    result->buffer   = buffer;
    result->size     = size;
    result->stride   = stride;
    result->capacity = capacity;
    result->count    = 0;

    return TRUE;
}
bool32 list_from_array( usize stride, usize array_len, void* array, list_t* result ) {
    if( !list_create( stride, array_len, result ) ) {
        return FALSE;
    }

    memcpy( result->buffer, array, array_len * stride );
    result->count = array_len;

    return TRUE;
}
bool32 list_clone( const list_t* src, list_t* dst ) {
    usize size   = src->count * src->stride;
    void* buffer = (SMCOL_ALLOC( size ));
    if( !buffer ) {
        return FALSE;
    }

    memcpy( buffer, src->buffer, size );

    dst->buffer   = buffer;
    dst->size     = size;
    dst->count    = src->count;
    dst->capacity = src->count;
    dst->stride   = src->stride;

    return TRUE;
}
void list_free( list_t* list ) {
    if( list->buffer ) {
        SMCOL_FREE( list->buffer );
    }
    memset( list, 0, sizeof(list_t) );
}
void list_free_lists( usize count, list_t* lists ) {
    for( usize i = 0; i < count; ++i ) {
        list_free( &lists[i] );
    }
}
void list_free_lists_strided( usize offset, usize stride, usize count, void* lists ) {
    for( usize i = 0; i < count; ++i ) {
        usize index = (i * stride) + offset;
        list_free( (list_t*)(&(((u8*)lists)[index])) );
    }
}
bool32 list_realloc( list_t* list, usize new_capacity ) {
    if( !list->buffer ) {
        return list_create( list->stride, new_capacity, list );
    }

    usize new_size = list->stride * new_capacity;
    void* new_buffer = (SMCOL_REALLOC( list->buffer, new_size ));
    if( !new_buffer ) {
        return FALSE;
    }

    list->buffer   = new_buffer;
    list->size     = new_size;
    list->capacity = new_capacity;

    return TRUE;
}
bool32 list_shrink( list_t* list ) {
    if( list->count == list->capacity ) {
        return TRUE;
    }
    return list_realloc( list, list->count );
}
void list_reverse( list_t* list ) {
    usize start = 0;
    usize end   = list->count - 1;
    while( start < end ) {
        uint8_t temp[list->stride];
        memcpy( temp, list_get( list, start ), list->stride );
        list_set( list, start++, list_get( list, end ) );
        list_set( list, end--, temp );
    }
}
bool32 list_push( list_t* list, void* value ) {
    if( list->capacity == 0 || list->count == list->capacity ) {
        return FALSE;
    }

    usize index = list->count++;
    memcpy(
        &(((u8*)list->buffer)[list->stride * index]),
        value,
        list->stride
    );

    return TRUE;
}
bool32 list_push_realloc( list_t* list, void* value ) {
    if( list->capacity == 0 ) {
        if( !list_create( list->stride, 2, list ) ) {
            return FALSE;
        }
    } else if( list->count == list->capacity ) {
        if( !list_realloc( list, list->capacity * 2 ) ) {
            return FALSE;
        }
    }

    list_set( list, list->count++, value );

    return TRUE;
}
void* list_get( list_t* list, usize index ) {
    return &(((u8*)list->buffer)[list->stride * index]);
}
void list_set( list_t* list, usize index, void* value ) {
    memcpy(
        &(((u8*)list->buffer)[list->stride * index]),
        value,
        list->stride
    );
}
void* list_pop( list_t* list ) {
    if( list->count == 0 ) {
        return NULL;
    }
    return (void*)(&(((u8*)list->buffer)[list->stride * --list->count]));
}
bool32 list_contains( const list_t* list, void* item ) {
    bool32 item_found = FALSE;
    for( usize i = 0; i < list->count; ++i ) {
        u8* chunk = &(((u8*)list->buffer)[list->stride * i]);
        if( slice_cmp( chunk, (u8*)item, list->stride ) ) {
            item_found = TRUE;
            break;
        }
    }
    return item_found;
}
bool32 list_index_of( const list_t* list, void* item, usize* result_index ) {
    bool32 item_found = FALSE;
    for( usize i = 0; i < list->count; ++i ) {
        u8* chunk = &(((u8*)list->buffer)[list->stride * i]);
        if( slice_cmp( chunk, (u8*)item, list->stride ) ) {
            item_found = TRUE;
            if( result_index ) {
                *result_index = i;
            }
            break;
        }
    }
    return item_found;
}
bool32 list_is_full( const list_t* list ) {
    return list->count == list->capacity;
}
bool32 list_is_empty( const list_t* list ) {
    return list->count == 0;
}

// NOTE(alicia): string

bool32 string_create( usize capacity, string_t* result ) {
    char* buffer = (char*)(SMCOL_ALLOC( capacity ));
    if( !buffer ) {
        return FALSE;
    }

    buffer[0] = '\0';

    result->buffer   = buffer;
    result->capacity = capacity;
    result->count    = 1;

    return TRUE;
}
bool32 string_fmt( string_t* result, const char* format, ... ) {
    va_list args;
    va_start( args, format );
    
    usize formatted_string_count = vsnprintf( NULL, 0, format, args ) + 1;
    va_end( args );
    
    char* buffer = (char*)(SMCOL_ALLOC( formatted_string_count ));
    if( !buffer ) {
        return FALSE;
    }

    va_start( args, format );
    vsnprintf( buffer, formatted_string_count, format, args );
    va_end( args );

    result->buffer   = buffer;
    result->count    = formatted_string_count;
    result->capacity = result->count;

    return TRUE;
}
bool32 string_from_str( const char* c_str, string_t* result ) {
    usize str_count = strlen( c_str ) + 1;
    if( !string_create( str_count, result ) ) {
        return FALSE;
    }

    result->count = str_count;
    memcpy( result->buffer, c_str, result->count );

    return TRUE;
}
bool32 string_from_str_concat( const char* lhs, const char* rhs, string_t* result ) {
    usize lhs_count = strlen( lhs ) + 1;
    usize rhs_count = strlen( rhs ) + 1;
    usize str_count = lhs_count + rhs_count - 1;
    if( !string_create( str_count, result ) ) {
        return FALSE;
    }
    result->count = str_count;
    memcpy( result->buffer, lhs, lhs_count );
    memcpy( &result->buffer[lhs_count - 1], rhs, rhs_count );
    return TRUE;
}
bool32 string_with_value( usize capacity, char value, string_t* result ) {
    if( !string_create( capacity, result ) ) {
        return FALSE;
    }

    memset( result->buffer, value, result->capacity - 1 );
    result->count = result->capacity;
    result->buffer[result->count - 1] = '\0';

    return TRUE;
}
bool32 string_realloc( string_t* string, usize new_capacity ) {
    char* new_buffer = (char*)(SMCOL_REALLOC( string->buffer, new_capacity ));
    if( !new_buffer ) {
        return FALSE;
    }

    string->capacity = new_capacity;
    string->buffer   = new_buffer;

    return TRUE;
}
void string_free( string_t* string ) {
    if( string->buffer ) {
        SMCOL_FREE( string->buffer );
    }
    memset( string, 0, sizeof( string_t ) );
}
bool32 string_cmp( const string_t* a, const string_t* b ) {
    return strcmp( a->buffer, b->buffer ) == 0;
}
bool32 string_cmp_str( const string_t* a, const char* b ) {
    return strcmp( a->buffer, b ) == 0;
}
bool32 string_concat( const string_t* lhs, const string_t* rhs, string_t* dst ) {
    bool32 lhs_is_dst = lhs == dst;
    usize new_count = lhs->count + rhs->count - 1;
    if( dst->capacity < new_count ) {
        if( !string_realloc( dst, new_count ) ) {
            return FALSE;
        }
    }

    if( lhs_is_dst ) {
        memcpy( &(lhs->buffer[lhs->count - 1]), rhs->buffer, rhs->count );
        dst->count = new_count;
    } else {
        memcpy( dst->buffer, lhs->buffer, lhs->count );
        memcpy( &dst->buffer[lhs->count - 1], rhs->buffer, rhs->count );

        dst->count = new_count;
    }

    if( dst->capacity < dst->count ) {
        dst->capacity = dst->count;
    }

    return TRUE;
}
bool32 string_concat_str( const string_t* lhs, const char* rhs, string_t* dst ) {
    bool32 lhs_is_dst = lhs == dst;
    usize rhs_count = strlen( rhs ) + 1;
    usize new_count = lhs->count + rhs_count - 1;
    if( dst->capacity < new_count ) {
        if( !string_realloc( dst, new_count ) ) {
            return FALSE;
        }
    }

    if( !lhs_is_dst ) {
        memcpy( dst->buffer, lhs->buffer, lhs->count );
    }
    memcpy( &(dst->buffer[lhs->count - 1]), rhs, rhs_count );
    dst->count = new_count;
    if( dst->capacity < dst->count ) {
        dst->capacity = dst->count;
    }
    return TRUE;
}
bool32 string_concat_str_rev( const char* lhs, const string_t* rhs, string_t* dst ) {
    bool32 rhs_is_dst = rhs == dst;
    usize lhs_count = strlen( lhs ) + 1;
    usize new_count = lhs_count + rhs->count - 1;
    if( rhs_is_dst ) {
        char* temp_buffer = (char*)(SMCOL_ALLOC( new_count ));
        if( !temp_buffer ) {
            return FALSE;
        }
        memcpy( temp_buffer, lhs, lhs_count );
        memcpy( &(temp_buffer[lhs_count - 1]), rhs->buffer, rhs->count );

        SMCOL_FREE( dst->buffer );
        dst->buffer   = temp_buffer;
        dst->count    = new_count;
        dst->capacity = new_count;

        return TRUE;
    } else {
        if( dst->capacity < new_count ) {
            if( !string_realloc( dst, new_count ) ) {
                return FALSE;
            }
        }

        memcpy( dst->buffer, lhs, lhs_count );
        memcpy( &(dst->buffer[lhs_count - 1]), rhs->buffer, rhs->count );
        dst->count = new_count;

        if( dst->capacity < dst->count ) {
            dst->capacity = dst->count;
        }

        return TRUE;
    }
}
bool32 string_contains( const string_t* string, const string_t* substring ) {
    if( string->count < substring->count ) {
        return FALSE;
    }

    for( usize i = 0; i < string->count; ++i ) {
        if( string->count - i < substring->count ) {
            break;
        }
        if( string->buffer[i] == substring->buffer[0] ) {
            if( slice_cmp( (u8*)&(string->buffer[i]), (u8*)substring->buffer, substring->count - 1 ) ) {
                return TRUE;
            }
        }
    }

    return FALSE;
}
bool32 string_contains_str( const string_t* string, const char* substring ) {
    usize count = strlen( substring ) + 1;
    string_t temp = {
        (char*)substring,
        count, count
    };
    return string_contains( string, &temp );
}
bool32 string_index_of( const string_t* string, const string_t* substring, usize* index ) {
    if( string->count < substring->count ) {
        return FALSE;
    }

    for( usize i = 0; i < string->count; ++i ) {
        if( string->count - i < substring->count ) {
            break;
        }
        if( string->buffer[i] == substring->buffer[0] ) {
            if( slice_cmp( (u8*)&(string->buffer[i]), (u8*)substring->buffer, substring->count - 1 ) ) {
                if( index ) {
                    *index = i;
                }
                return TRUE;
            }
        }
    }

    return FALSE;
}
bool32 string_index_of_str( const string_t* string, const char* substring, usize* index ) {
    usize count = strlen( substring ) + 1;
    string_t temp = {
        (char*)substring,
        count, count
    };
    return string_index_of( string, &temp, index );
}
usize string_length( const string_t* string ) {
    return string->count - 1;
}
