#include <lauxlib.h>
#include <obj_type.h>
#include <stdlib.h>
#include <string.h>
#include <to_code.h>

char* LAYOUT_EXPORT_RULE[]
= { "difference()\n{\n%s\n}\n", "union()\n{\n%s\n}\n", "intersection(){\n%s\n}" };

void cube_to_code( lua_State* L, struct cube* self )
{
    const char* rule = CUBE_EXPORT_RULE;
    char center[10];
    if ( self->m_center )
    {
        strcpy( center, "true" );
    }
    else
    {
        strcpy( center, "false" );
    }
    if ( !self->m_offset || !self->m_w_l_h )
    {
        luaL_error( L, "The pointer is empty and an error has occurred!" );
    }
    sprintf( self->m_code, rule, CUBE_EXPORT_ARGS );
}

void difference_to_code( lua_State* L, struct difference* self )
{
    char* temp = ( char* )malloc( sizeof( char ) * LAYOUT_CODE_LENGTH );
    memset( temp, ' ', 5 );
    const char* rule = LAYOUT_EXPORT_RULE[DIFFERENCE - LAYOUT_BEGIN - 1];
    layout_to_code( L, (OBJ_TYPE*)self, temp );
    sprintf( self->m_code, rule, temp );
}

void union_to_code( lua_State* L, struct Union* self )
{
    char* temp = ( char* )malloc( sizeof( char ) * LAYOUT_CODE_LENGTH );
    memset( temp, ' ', 5 );
    const char* rule = LAYOUT_EXPORT_RULE[UNION - LAYOUT_BEGIN - 1];
    layout_to_code( L, (OBJ_TYPE*)self, temp );
    sprintf( self->m_code, rule, temp );
}

void intersection_to_code( lua_State* L, struct intersection* self )
{
    char* temp = ( char* )malloc( sizeof( char ) * LAYOUT_CODE_LENGTH );
    memset( temp, ' ', 5 );
    const char* rule = LAYOUT_EXPORT_RULE[INTERSECTION - LAYOUT_BEGIN - 1];
    layout_to_code( L, (OBJ_TYPE*)self, temp );
    sprintf( self->m_code, rule, temp );
}

void layout_to_code( lua_State* L, OBJ_TYPE* self, char* temp )
{
    if ( !self )
    {
        return;
    }
    OBJ_TYPE** children;
    struct cube* temp2;
    unsigned int* count;
    switch ( *self )
    {
        case INTERSECTION:
        case UNION:
        case DIFFERENCE:
            children = ( OBJ_TYPE** )( self - 1 + sizeof( OBJ_TYPE )
                                       + sizeof( char[LAYOUT_CODE_LENGTH / 2 + 3] ) );
            count    = ( unsigned int* )( children + sizeof( children ) + 2 );
            for ( int i = 0; i < *count; i++ )
            {
                if ( *children[i] > LAYOUT_BEGIN && *children[i] < LAYOUT_END )
                {
                    layout_to_code( L, children[i], temp );
                    char* temp_buffer = ( char* )malloc( sizeof( char ) * LAYOUT_CODE_LENGTH );
                    sprintf( temp_buffer, LAYOUT_EXPORT_RULE[*children[i] - 1 - LAYOUT_BEGIN], temp );
                    strcpy( temp, temp_buffer );
                    free( temp_buffer );
                }
                else
                {
                    temp2             = ( struct cube* )children[i];
                    char* buffer      = ( char* )( children[i] + sizeof( OBJ_TYPE ) - 1 );
                    char* temp_buffer = ( char* )malloc( sizeof( char ) * LAYOUT_CODE_LENGTH );
                    sprintf( temp_buffer, "%s%s", temp, buffer );
                    strcpy( temp, temp_buffer );
                    free( temp_buffer );
                }
            }
            break;
        case CUBE:
            temp2 = ( struct cube* )self;
            sprintf( temp, "%s", temp2->m_code );
            break;
        default:
            luaL_error( L, "Unknown object type!" );
            return;
    }
}