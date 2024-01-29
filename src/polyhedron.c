#include <polyhedron.h>
#include <to_code.h>

#include <stdlib.h>
#include <string.h>

char POLYHEDRON_ARG1[200];
char POLYHEDRON_ARG2[200];

static int polyhedron_init( lua_State* L )
{
    // 读 points 表
    vec3 points[64];
    memset( POLYHEDRON_ARG1, ' ', 1 );
    const int points_count = luaL_len( L, 1 );
    for ( int i = 0; i < points_count; i++ )
    {
        char buffer[100];
        lua_pushnumber( L, i + 1 );
        lua_gettable( L, 1 );
        vec3 temp;
        const int counter = luaL_len( L, -1 );
        for ( int j = 0; j < counter; j++ )
        {
            lua_pushnumber( L, j + 1 );
            lua_gettable( L, -2 );
            temp.m_xyz[j] = lua_tonumber( L, -1 );
            lua_pop( L, 1 );
        }
        points[i] = temp;
        sprintf( buffer, POINT_RULE, temp.m_xyz[0], temp.m_xyz[1], temp.m_xyz[2] );
        strcat( POLYHEDRON_ARG1, buffer );
        POLYHEDRON_ARG1[strlen( POLYHEDRON_ARG1 )] = ',';
        lua_pop( L, 1 );
    }
    POLYHEDRON_ARG1[strlen( POLYHEDRON_ARG1 ) - 1] = '\0';
    // 读 faces 表
    int* faces[64];
    const int faces_count = luaL_len( L, 2 );
    int counter;
    for ( int i = 0; i < faces_count; i++ )
    {
        char buffer[100];
        buffer[0] = '[';
        lua_pushnumber( L, i + 1 );
        lua_gettable( L, 2 );
        counter  = luaL_len( L, -1 );
        faces[i] = ( double* )malloc( sizeof( double ) );
        for ( int j = 0; j < counter; j++ )
        {
            char buffer2[100];buffer2[0] = '\0';
            lua_pushnumber( L, j + 1 );
            lua_gettable( L, -2 );
            faces[i][j] = lua_tointeger( L, -1 );
            sprintf(buffer2, "%s%d,", buffer, faces[i][j]);
            strcpy(buffer, buffer2);
            lua_pop( L, 1 );
        }
        buffer[strlen(buffer) - 1] = ']';
        strcat( POLYHEDRON_ARG2, buffer );
        POLYHEDRON_ARG2[strlen( POLYHEDRON_ARG2 )] = ',';
        memset(buffer, 0, strlen(buffer));
        lua_pop( L, 1 );
    }
    POLYHEDRON_ARG2[strlen( POLYHEDRON_ARG2 ) - 1] = '\0';
    // 创建多变体对象
    unsigned int i_bytes = sizeof( polyhedron );
    polyhedron* current;
    current = dynast_cast( polyhedron, lua_newuserdata( L, i_bytes ) );
    current->base.m_center = lua_toboolean(L, 2);
    current->base.m_obj_base.m_type = POLYHEDRON;
    memcpy( current->m_points, points, sizeof( vec3 ) * points_count );
    memcpy( current->m_faces, faces, sizeof( double ) * counter * faces_count );
    current->m_points_count = points_count;
    current->m_face_countl  = faces_count;
    current->base.m_offset  = dynast_cast( vec3, malloc( sizeof( vec3 ) ) );
    // free
    for ( int i = 0; i < faces_count; i++ )
    {
        free( faces[i] );
    }
    // to-code
    polyhedron_to_code( L, current );
    return 1;
}

static const luaL_Reg polyhedronlib[] = { { "new", polyhedron_init }, { NULL, NULL } };

LUAMOD_API int luaopen_polyhedron( lua_State* L )
{
    luaL_newlib( L, polyhedronlib );
    return 1;
}
