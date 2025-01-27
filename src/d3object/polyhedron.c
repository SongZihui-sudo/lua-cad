#include <polyhedron.h>
#include <to_openscad_code.h>

#include <stdlib.h>
#include <string.h>

char POLYHEDRON_ARG1[200];
char POLYHEDRON_ARG2[200];

int polyhedron_init( lua_State* L )
{
    // read points table
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
        sprintf( buffer, POINT3_RULE, temp.m_xyz[0], temp.m_xyz[1], temp.m_xyz[2] );
        strcat( POLYHEDRON_ARG1, buffer );
        POLYHEDRON_ARG1[strlen( POLYHEDRON_ARG1 )] = ',';
        lua_pop( L, 1 );
    }
    POLYHEDRON_ARG1[strlen( POLYHEDRON_ARG1 ) - 1] = '\0';
    // read faces table
    int* faces[64];
    const int faces_count = luaL_len( L, 2 );
    int counter;
    int total_counter_faces = 0;
    for ( int i = 0; i < faces_count; i++ )
    {
        char buffer[100];
        buffer[0] = '[';
        buffer[1] = ' ';
        buffer[2] = '\0';
        lua_pushnumber( L, i + 1 );
        lua_gettable( L, 2 );
        counter  = luaL_len( L, -1 );
        faces[i] = dynast_cast( int, malloc( sizeof( int ) * counter ) );
        total_counter_faces += counter;
        for ( int j = 0; j < counter; j++ )
        {
            char buffer2[100];
            buffer2[0] = '\0';
            lua_pushnumber( L, j + 1 );
            lua_gettable( L, -2 );
            faces[i][j] = lua_tointeger( L, -1 );
            sprintf( buffer2, "%s%d,", buffer, faces[i][j] );
            strcpy( buffer, buffer2 );
            lua_pop( L, 1 );
        }
        buffer[strlen( buffer ) - 1] = ']';
        strcat( POLYHEDRON_ARG2, buffer );
        POLYHEDRON_ARG2[strlen( POLYHEDRON_ARG2 )] = ',';
        memset( buffer, 0, strlen( buffer ) );
        lua_pop( L, 1 );
    }
    POLYHEDRON_ARG2[strlen( POLYHEDRON_ARG2 ) - 1] = '\0';
    // create polyhedron
    unsigned int i_bytes = sizeof( polyhedron );
    polyhedron* current;
    current                = dynast_cast( polyhedron, lua_newuserdata( L, i_bytes ) );
    D3OBJECT_BASE_INIT(&current->base);
    current->m_convexity = lua_tonumber(L, 3);
    current->base.m_obj_base.m_type = POLYHEDRON;
    memcpy( current->m_points, points, sizeof( vec3 ) * points_count );
    memcpy( current->m_faces, faces, sizeof( int ) * total_counter_faces );
    current->m_points_count = points_count;
    current->m_face_count   = faces_count;
    current->m_face_count   = counter;
    return 1;
}

vec3 calculate_vertices_polyhedron( lua_State* L, polyhedron* self, unsigned short index )
{
    vec3 result;
    vec3_init(&result, 0);
    vec3 sides;
    pan( &result, self->base.m_offset );
    // calculate the center of the face
    double max_x = 0, max_y = 0, max_z = 0, min_x = 0x3f3f3f3f,
           min_y = 0x3f3f3f3f, min_z = 0x3f3f3f3f;
    for ( int i = 0; i < self->m_face_count; i++ )
    {
#define xx( xyz, cmp, op )                                                                 \
    if ( self->m_points[self->m_faces[index][i]].m_xyz[xyz] op cmp )                                     \
    {                                                                                      \
        cmp = self->m_points[self->m_faces[index][i]].m_xyz[xyz];                                        \
    }
        xx( 0, max_x, > )
        xx(1, max_y, >)
        xx(2, max_z, >)
        xx(0, min_x, <)
        xx(1, min_y, <)
        xx(2, min_z, <)
#undef xx
    }
    result.m_xyz[0] = (max_x + min_x) / 2;
    result.m_xyz[1] = (max_y + min_y) / 2;
    result.m_xyz[2] = (max_z + min_z) / 2;
    rotation( &result, self->base.m_rotate_a, self->base.m_rotate_v );
    return result;
}
