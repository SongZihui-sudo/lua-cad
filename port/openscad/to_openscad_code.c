/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:22:34
 * @LastEditors: SongZihui-sudo 1751122876@qq.com
 * @LastEditTime: 2024-02-02 16:44:39
 * @FilePath: /lua-cad/port/openscad/to_openscad_code.c
 * @Description:
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */
#include <lauxlib.h>
#include <obj_type.h>
#include <stdlib.h>
#include <string.h>
#include <to_openscad_code.h>

char* LAYOUT_EXPORT_RULE[]
= { "difference()\n{\n%s\n}\n", "union()\n{\n%s\n}\n", "intersection(){\n%s\n}",
    "fill(){\n%s\n}",           "hull(){\n%s\n}",      "minkowski(){\n%s\n}",
    "offset(%s){\n%s\n}" };

void cube_to_code( lua_State* L, struct cube* self ) { d3obj_to_code( L, &self->base ); }

void transform_to_code( lua_State* L, D3OBJECT_BASE* base )
{
    int buffer[20];
    buffer[0] = 0;
    for ( int i = 1; i <= base->m_op_stack[0]; i++ )
    {
        for ( int j = 0; j < buffer[0]; j++ )
        {
            if (buffer[j] == base->m_op_stack[i]) {
                goto continue_;      
            }
        }
        append_transform_code( L, base, base->m_op_stack[i] );
        buffer[buffer[0]++] = base->m_op_stack[i];
continue_:
    continue;
    }
}

void d3obj_to_code( lua_State* L, D3OBJECT_BASE* base )
{
    if ( !base )
    {
        luaL_error( L, "The pointer is empty and an error has occurred!" );
    }
    char temp[CODE_LENGTH] = " ";
    cube* self1;
    cylinder* self2;
    sphere* self3;
    polyhedron* self4;
    switch ( base->m_obj_base.m_type )
    {
        case CUBE:
            self1 = dynast_cast( cube, base );
            sprintf( temp, CUBE_ALL_EXPORT_RULE, CUBE_EXPORT_ARGS( self1 ) );
            break;
        case CYLINDER:
            self2 = dynast_cast( cylinder, base );
            sprintf( temp, CYLINDER_ALL_EXPORT_RULE, CYLINDER_EXPORT_ARGS( self2 ) );
            break;
        case SPHERE:
            self3 = dynast_cast( sphere, base );
            sprintf( temp, SPHERE_ALL_EXPORT_RULE, SPHERE_EXPORT_ARGS( self3 ) );
            break;
        case POLYHEDRON:
            self4 = dynast_cast( polyhedron, base );
            sprintf( temp, POLYHEDRON_ALL_EXPORT_RULE, POLYHEDRON_EXPORT_ARGS( self4 ) );
            break;
        case USER_DEFINE:
            sprintf(temp, "%s", base->m_obj_base.m_code);
            break;
        default:
            luaL_error( L, "Unknown object!" );
    }
    base->m_obj_base.m_code = dynast_cast( char, malloc( sizeof( temp ) ) );
    strcpy( base->m_obj_base.m_code, temp );
    transform_to_code( L, base );
    temp[0] = ' ';
    temp[1] = '\0';
}

void boolean_to_code( lua_State* L, OBJ_TYPE* self )
{
    char temp[CODE_LENGTH];
    temp[0] = ' ';
    memset( temp, 0, 5 );
    if ( !self )
    {
        return;
    }
    layout_to_code( L, ( OBJ_TYPE* )self, temp );
    struct OBJ_BASE* base = dynast_cast( OBJ_BASE, self );
    base->m_code          = dynast_cast( char, malloc( sizeof( temp ) ) );
    sprintf( base->m_code, LAYOUT_EXPORT_RULE[*self - BOOLEAN_BEGIN - 1], temp );
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
    double offset;
    char buffer_offset[32];
    char buffer2[128];
    switch ( *self )
    {
        case OFFSET:
            offset = lua_checkstack( L, 3 );
            sprintf( buffer_offset, SINGLE_ARG_RULE1, "r", offset );
            sprintf( buffer2,
                     LAYOUT_EXPORT_RULE[OFFSET - 1 - BOOLEAN_BEGIN],
                     buffer_offset,
                     "%s" );
            LAYOUT_EXPORT_RULE[OFFSET - 1 - BOOLEAN_BEGIN] = buffer2;
        case MINKOWSKI:
        case HULL:
        case FILL:
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
                    temp2 = dynast_cast( D3OBJECT_BASE, children[i] );
                    d3obj_to_code( L, temp2 );
                    char* buffer = temp2->m_obj_base.m_code;
                    char temp_buffer[CODE_LENGTH];
                    sprintf( temp_buffer, "%s%s", temp, buffer );
                    strcpy( temp, temp_buffer );
                }
            }
            break;
        case POLYHEDRON:
        case SPHERE:
        case CYLINDER:
        case USER_DEFINE:
        case CUBE:
            temp2 = dynast_cast( D3OBJECT_BASE, self );
            d3obj_to_code( L, temp2 );
            sprintf( temp, "%s", temp2->m_obj_base.m_code );
            break;
        default:
            luaL_error( L, "Unknown object type!" );
            return;
    }
}

void cylinder_to_code( lua_State* L, cylinder* self ) { d3obj_to_code( L, &self->base ); }

void sphere_to_code( lua_State* L, sphere* self ) { d3obj_to_code( L, &self->base ); }

void polyhedron_to_code( lua_State* L, polyhedron* self )
{
    d3obj_to_code( L, &self->base );
}
