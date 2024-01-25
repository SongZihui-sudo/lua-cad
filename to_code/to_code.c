#include <lauxlib.h>
#include <obj_type.h>
#include <stdlib.h>
#include <string.h>
#include <to_code.h>

char* LAYOUT_EXPORT_RULE[]
= { "difference()\n{\n%s\n}\n", "union()\n{\n%s\n}\n", "intersection(){\n%s\n}" };

void cube_to_code( lua_State* L, struct cube* self )
{
    char temp[CODE_LENGTH] = " ";
    const char* rule       = CUBE_EXPORT_RULE;
    char center[10];
    if ( self->base.m_center )
    {
        strcpy( center, "true" );
    }
    else
    {
        strcpy( center, "false" );
    }
    if ( !self->base.m_offset || !self->m_w_l_h )
    {
        luaL_error( L, "The pointer is empty and an error has occurred!" );
    }
    sprintf( temp, rule, CUBE_EXPORT_ARGS );
    self->base.m_obj_base.m_code = ( char* )malloc( sizeof( temp ) );
    strcpy( self->base.m_obj_base.m_code, temp );
    temp[0] = ' ';
    temp[1] = '\0';
}

void boolean_to_code( lua_State* L, OBJ_TYPE* self )
{
    char temp[CODE_LENGTH];
    temp[0] = ' ';
    memset( temp, ' ', 1 );
    if ( !self )
    {
        return;
    }
    const char* rule = LAYOUT_EXPORT_RULE[*self - BOOLEAN_BEGIN - 1];
    layout_to_code( L, ( OBJ_TYPE* )self, temp );
    struct OBJ_BASE* base = dynast_cast( OBJ_BASE, self );
    base->m_code          = dynast_cast( char, malloc( sizeof( temp ) ) );
    sprintf( base->m_code, rule, temp );
    temp[0] = ' ';
    temp[1] = '\0';
}

void layout_to_code( lua_State* L, OBJ_TYPE* self, char* temp )
{
    if ( !self )
    {
        return;
    }
    OBJ_TYPE** children;
    struct BOOLEAN_BASE* temp1;
    struct D3OBJECT_BASE* temp2;
    unsigned int count;
    switch ( *self )
    {
        case INTERSECTION:
        case UNION:
        case DIFFERENCE:
            temp1    = dynast_cast( BOOLEAN_BASE, self );
            children = temp1->m_children;
            count    = temp1->m_count;
            for ( int i = 0; i < count; i++ )
            {
                if ( *children[i] > BOOLEAN_BEGIN && *children[i] < BOOLEAN_END )
                {
                    layout_to_code( L, children[i], temp );
                    char temp_buffer[CODE_LENGTH];
                    sprintf( temp_buffer, LAYOUT_EXPORT_RULE[*children[i] - 1 - BOOLEAN_BEGIN], temp );
                    strcpy( temp, temp_buffer );
                }
                else
                {
                    temp2        = dynast_cast( D3OBJECT_BASE, children[i] );
                    char* buffer = temp2->m_obj_base.m_code;
                    char temp_buffer[CODE_LENGTH];
                    sprintf( temp_buffer, "%s%s", temp, buffer );
                    strcpy( temp, temp_buffer );
                }
            }
            break;
        case CUBE:
            temp2 = dynast_cast( D3OBJECT_BASE, self );
            sprintf( temp, "%s", temp2->m_obj_base.m_code );
            break;
        default:
            luaL_error( L, "Unknown object type!" );
            return;
    }
}
