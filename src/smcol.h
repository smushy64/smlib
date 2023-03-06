/**
 * Description:  Collection Types
 * Author:       Alicia Amarilla (smushyaa@gmail.com)
 * File Created: February 24, 2023
 * Includes:     "smalias.h" required
*/
#if !defined( SMUSHY_COLLECTIONS )
#define SMUSHY_COLLECTIONS

#include "smdef.h"

// allocator management -------------------------------------------------------

typedef void* (*smushy_collections_heap_alloc_fn)( usize size );
typedef void* (*smushy_collections_heap_realloc_fn)( void* buffer, usize new_size );
typedef void  (*smushy_collections_heap_free_fn)( void* buffer );

/// change allocator functions
void smcol_set_allocator(
    smushy_collections_heap_alloc_fn heap_alloc,
    smushy_collections_heap_realloc_fn heap_realloc,
    smushy_collections_heap_free_fn heap_free
);

// collection types -----------------------------------------------------------

/// dynamic heap allocated array
typedef struct {
    /// list buffer
    void* buffer;
    /// byte size of buffer
    usize size;
    /// size of each item in buffer
    usize stride;
    /// number of items in list
    usize count;
    /// number of items list can hold
    usize capacity;
} list_t;

/// create a list
/// @param stride size of each item in list
/// @param capacity number of items that list can hold
/// @param out_result list
/// @return [bool32] true if successful
bool32 list_create( usize stride, usize capacity, list_t* out_result );
/// create a list from array
/// @param stride size of each item in list
/// @param array_len number of items in array
/// @param array pointer to array
/// @param out_result list
/// @return [bool32] true if successful
bool32 list_from_array( usize stride, usize array_len, void* array, list_t* out_result );
/// clone a list
/// @param src source list
/// @param dst destination list, must be uninitialized
/// @return [bool32] true if successful
bool32 list_clone( const list_t* src, list_t* dst );
/// free a list
void list_free( list_t* list );
/// free multiple lists
/// @param count number of lists
/// @param lists lists
void list_free_lists( usize count, list_t* lists );
/// free multiple lists, strided
/// @param offset offset of the first list in lists pointer
/// @param stride bytes between lists in lists pointer
/// @param count number of lists in pointer
/// @param lists lists
void list_free_lists_strided( usize offset, usize stride, usize count, void* lists );
/// reallocate list
/// @param list list to reallocate
/// @param new_capacity capacity to reallocate
/// @return [bool32] true if reallocation successful
bool32 list_realloc( list_t* list, usize new_capacity );
/// shrink list capacity to count
/// @param list list to shrink
/// @return [bool32] true if reallocation successful
bool32 list_shrink( list_t* list );
/// reverse order of items in list
/// @param list list to reverse
void list_reverse( list_t* list );
/// push item onto end of list
/// @param list list to push to
/// @param value value to push
/// @return [bool32] true if value can be pushed, false if list is full
bool32 list_push( list_t* list, void* value );
/// push item onto end of list, reallocating list if necessary
/// @param list list to push to
/// @param value value to push
/// @return [bool32] true if no reallocation necessary or if it is, if reallocation was successful
bool32 list_push_realloc( list_t* list, void* value );
/// get item from list
/// @param list list to get item from
/// @param index index of item
/// @return [void*] pointer to item
void* list_get( list_t* list, usize index );
/// set item in list
/// @param list list to modify
/// @param index index of item to modify
/// @param value value to set item to
void list_set( list_t* list, usize index, void* value );
/// remove last item from list
/// @param list list to modify
/// @return [void*] pointer to item removed, null if list is empty
void* list_pop( list_t* list );
/// check if list contains item. compares input item bytes with item bytes in list
/// @param list list to check
/// @param item item to look for
/// @return [bool32] true if list contains item
bool32 list_contains( const list_t* list, void* item );
/// get index of item in list. compares input item bytes with item bytes in list
/// @param list list to check
/// @param item item to look for
/// @param out_index pointer to index of item if found, can be null
/// @return [bool32] true if item was found
bool32 list_index_of( const list_t* list, void* item, usize* out_index );
/// check if list is full (list count == list capacity)
bool32 list_is_full( const list_t* list );
/// check if list is empty (list count == 0)
bool32 list_is_empty( const list_t* list );

/// dynamic heap allocated string
typedef struct {
    /// pointer to string buffer
    char* buffer;
    /// number of characters buffer can hold, including null-terminator
    usize capacity;
    /// number of characters in string, including null-terminator
    usize count;
} string_t;

// TODO(alicia): write documentation

bool32 string_create( usize capacity, string_t* result );
bool32 string_from_str_concat( const char* lhs, const char* rhs, string_t* result );
bool32 string_from_str( const char* c_str, string_t* result );
bool32 string_fmt( string_t* result, const char* format, ... );
bool32 string_with_value( usize capacity, char value, string_t* result );
bool32 string_realloc( string_t* string, usize new_capacity );
void string_free( string_t* string );
bool32 string_cmp( const string_t* a, const string_t* b );
bool32 string_cmp_str( const string_t* a, const char* b );
bool32 string_concat( const string_t* lhs, const string_t* rhs, string_t* dst );
bool32 string_concat_str( const string_t* lhs, const char* rhs, string_t* dst );
bool32 string_concat_str_rev( const char* lhs, const string_t* rhs, string_t* dst );
bool32 string_contains( const string_t* string, const string_t* substring );
bool32 string_contains_str( const string_t* string, const char* substring );
bool32 string_index_of( const string_t* string, const string_t* substring, usize* index );
bool32 string_index_of_str( const string_t* string, const char* substring, usize* index );
usize string_length( const string_t* string );

// macros ---------------------------------------------------------------------

#if defined(__cplusplus)

#define SMCOL_DEFINE_OPTIONAL( type ) \
struct type##_opt {\
    type value;\
    bool32 has_value;\
    type##_opt() : has_value(false) {}\
    type##_opt( type value ) : value(value), has_value(true) {}\
    type##_opt( type value, bool32 has_value ) : value(value), has_value(has_value) {}\
}

#else // if cpp

#define SMCOL_DEFINE_OPTIONAL( type ) \
typedef struct {\
    type value;\
    bool32 has_value;\
} type##_opt

#endif // elif c

/// define specialized functions for list type for given type
/// functions follow list_*_type convention
#define SMCOL_LIST_SPECIALIZE( type ) \
inline bool32 list_create_##type( usize capacity, list_t* result ) {\
    return list_create( sizeof(type), capacity, result );\
}\
inline bool32 list_from_array_##type( usize array_len, type* array, list_t* result ) {\
    return list_from_array( sizeof(type), array_len, (void*)array, result );\
}\
inline type list_get_##type( list_t* list, usize index ) {\
    return ((type*)list->buffer)[index];\
}\
inline void list_set_##type( list_t* list, usize index, type value ) {\
    ((type*)list->buffer)[index] = value;\
}\
inline bool32 list_push_##type( list_t* list, type value ) {\
    if( list->capacity == 0 || list->count == list->capacity ) {\
        return FALSE;\
    }\
    ((type*)list->buffer)[list->count++] = value;\
    return TRUE;\
}\
inline bool32 list_push_realloc_##type( list_t* list, type value ) {\
    if( list->capacity == 0 ) {\
        if( !list_create( list->stride, 2, list ) ) {\
            return FALSE;\
        }\
    } else if( list->count == list->capacity ) {\
        if( !list_realloc( list, list->capacity * 2 ) ) {\
            return FALSE;\
        }\
    }\
    ((type*)list->buffer)[list->count++] = value;\
    return TRUE;\
}\
inline type list_pop_##type( list_t* list ) {\
    return ((type*)list->buffer)[--list->count];\
}\
inline bool32 list_contains_##type( list_t* list, type item ) {\
    bool32 item_found = FALSE;\
    for( usize i = 0; i < list->count; ++i ) {\
        if( list_get_##type( list, i ) == item ) {\
            item_found = TRUE;\
            break;\
        }\
    }\
    return item_found;\
}\
inline bool32 list_index_of_##type( list_t* list, type item, usize* result_index ) {\
    bool32 item_found = FALSE;\
    for( usize i = 0; i < list->count; ++i ) {\
        if( list_get_##type( list, i ) == item ) {\
            item_found = TRUE;\
            if( result_index ) {\
                *result_index = i;\
            }\
            break;\
        }\
    }\
    return item_found;\
}\

#endif // header guard
