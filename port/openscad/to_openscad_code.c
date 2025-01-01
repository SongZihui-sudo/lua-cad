/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:22:34
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-02-07 13:44:12
 * @FilePath: /lua-cad/port/openscad/to_openscad_code.c
 * @Description:
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */
#include "lua.h"
#include <lauxlib.h>
#include <obj_type.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <to_openscad_code.h>
#include <transform.h>

char* CYLINDER_ARGS_ARRAY[7] = {"r", "d", "r1", "r2","d1", "d2", " "};

char* LAYOUT_EXPORT_RULE[]
= { "difference()\n{\n%s\n}\n", "union()\n{\n%s\n}\n", "intersection(){\n%s\n}",
    "fill(){\n%s\n}",           "hull(){\n%s\n}",      "minkowski(){\n%s\n}",
    "offset(%s){\n%s\n}" };

void transform_to_openscad_code( lua_State* L, D3OBJECT_BASE* base )
{
    int* buffer = dynast_cast(int, malloc( sizeof( int ) * 20 ));
    memset(buffer, 0, 20);
    for ( int i = 1; i <= base->m_op_stack[0]; i++ )
    {
        for ( int j = 0; j <= buffer[0]; j++ )
        {
            if ( buffer[j] == base->m_op_stack[i] )
            {
                goto continue_;
            }
        }
        append_transform_openscad_code( L, base, base->m_op_stack[i] );
        buffer[++buffer[0]] = base->m_op_stack[i];
    continue_:
        continue;
    }
    free(buffer);
}

void obj_to_openscad_code( lua_State* L, D3OBJECT_BASE* base )
{
    if ( !base )
    {
        luaL_error( L, "The pointer is empty and an error has occurred!" );
    }
    char* temp = dynast_cast( char, malloc( sizeof( char ) * CODE_LENGTH ) );
    cube* self1;
    cylinder* self2;
    sphere* self3;
    polyhedron* self4;
    square* self5;
    circle* self6;
    polygon* self7;
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
            sprintf( temp, "%s", base->m_obj_base.m_code );
            break;
        case SQUARE:
            self5 = dynast_cast( square, base );
            sprintf( temp, SQUARE_ALL_EXPORT_RULE, SQUARE_EXPORT_ARGS( self5 ) );
            break;
        case CIRCLE:
            self6 = dynast_cast( circle, base );
            sprintf( temp, CIRCLE_ALL_EXPORT_RULE, CIRCLE_EXPORT_ARGS( self6 ) );
            break;
        case POLYGON:
            self7 = dynast_cast( polygon, base );
            sprintf( temp, POLYGON_ALL_EXPORT_RULE, POLYGON_EXPORT_ARGS( self7 ) );
            break;
        default:
            luaL_error( L, "Unknown object!" );
    }
    base->m_obj_base.m_code = dynast_cast( char, malloc(  CODE_LENGTH * sizeof(char) ) );
    strcpy( base->m_obj_base.m_code, temp );
    transform_to_openscad_code( L, base );
    free(temp);
}

void boolean_to_openscad_code( lua_State* L, OBJ_TYPE* self )
{
    char* temp = dynast_cast( char, malloc( sizeof( char ) * CODE_LENGTH ) );
    memset( temp, 0, 5 );
    if ( !self )
    {
        return;
    } 
    layout_to_code( L, ( OBJ_TYPE* )self, temp );
    struct OBJ_BASE* base = dynast_cast( OBJ_BASE, self );
    base->m_code          = dynast_cast( char, malloc( CODE_LENGTH * sizeof(char) ) );
    sprintf( base->m_code, LAYOUT_EXPORT_RULE[*self - BOOLEAN_BEGIN - 1], temp );
    free(temp);
}

void layout_to_code( lua_State* L, OBJ_TYPE* self, char* temp )
{
    if ( !self )
    {
        return;
    }
    OBJ_TYPE** children;
    BOOLEAN_BASE* temp1;
    D3OBJECT_BASE* temp2;
    unsigned int count;
    char* buffer_offset;
    char* buffer2 = dynast_cast(char, malloc( sizeof(char) * 128 ));
    switch ( *self )
    {
        case OFFSET:
            LAYOUT_EXPORT_RULE[OFFSET - 1 - BOOLEAN_BEGIN] = "offset(%s){\n%s\n}";
            buffer_offset = dynast_cast(char, malloc(32));
            sprintf( buffer_offset, SINGLE_ARG_RULE1, "r", OFFSET_ARG );
            sprintf( buffer2, LAYOUT_EXPORT_RULE[OFFSET - 1 - BOOLEAN_BEGIN], buffer_offset, "%s" );
            LAYOUT_EXPORT_RULE[OFFSET - 1 - BOOLEAN_BEGIN] = dynast_cast(char, dynast_cast(char, malloc( sizeof(char) * strlen(buffer2) )));
            strcpy(LAYOUT_EXPORT_RULE[OFFSET - 1 - BOOLEAN_BEGIN], buffer2);
            free(buffer_offset);
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
                if ( is_boolean( *children[i] ) )
                {
                    layout_to_code( L, children[i], temp );
                    char* temp_buffer = dynast_cast(char, malloc( sizeof(char) * CODE_LENGTH ));
                    sprintf( temp_buffer, LAYOUT_EXPORT_RULE[*children[i] - 1 - BOOLEAN_BEGIN], temp );
                    strcpy( temp, temp_buffer );
                    free(temp_buffer);
                }
                else if ( *children[i] == USER_DEFINE )
                {
                    temp2        = dynast_cast( D3OBJECT_BASE, children[i] );
                    char* buffer = temp2->m_obj_base.m_code;
                    char* temp_buffer = dynast_cast(char, malloc( sizeof(char) * CODE_LENGTH ));
                    sprintf( temp_buffer, "%s%s", temp, buffer );
                    strcpy( temp, temp_buffer );
                    free(temp_buffer);
                }
                else
                {
                    temp2 = dynast_cast( D3OBJECT_BASE, children[i] );
                    obj_to_openscad_code( L, temp2 );
                    char* buffer = temp2->m_obj_base.m_code;
                    char* temp_buffer = dynast_cast(char, malloc( sizeof(char) * CODE_LENGTH ));
                    sprintf( temp_buffer, "%s%s", temp, buffer );
                    strcpy( temp, temp_buffer );
                    free(temp_buffer);
                }
            }
            break;
        case USER_DEFINE:
            temp2 = dynast_cast( D3OBJECT_BASE, self );
            sprintf( temp, "%s", temp2->m_obj_base.m_code );
            break;
        case POLYHEDRON:
        case SPHERE:
        case CYLINDER:
        case CUBE:
            temp2 = dynast_cast( D3OBJECT_BASE, self );
            obj_to_openscad_code( L, temp2 );
            sprintf( temp, "%s", temp2->m_obj_base.m_code );
            break;
        default:
            luaL_error( L, "Unknown object type!" );
            return;
    }
    free(buffer2);
}