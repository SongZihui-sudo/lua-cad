#include <lua_table.h>

double get_table_field_number_value( lua_State* L, const char* key, int ss_index )
{
    lua_pushstring( L, key );
    lua_gettable( L, ss_index );
    double value = luaL_checknumber( L, -1 );
    lua_pop( L, 1 );
    return value;
}

bool get_table_field_boolean_value( lua_State* L, const char* key, int ss_index )
{
    lua_pushstring( L, key );
    lua_gettable( L, ss_index );
    double value = lua_toboolean( L, -1 );
    lua_pop( L, 1 );
    return value;
}

const char* get_table_field_string_value( lua_State* L, const char* key, int ss_index )
{
    lua_pushstring( L, key );
    lua_gettable( L, ss_index );
    const char* value = luaL_checkstring( L, -1 );
    lua_pop( L, 1 );
    return value;
}

int get_table_field_number_array( lua_State* L, const char* key, int ss_index, double* buffer )
{
    lua_pushstring( L, key );
    lua_gettable( L, ss_index );
    const int count = luaL_len( L, -1 );
    for ( int i = 0; i < count; i++ )
    {
        lua_pushinteger( L, i + 1 );
        lua_gettable( L, 3 );
        buffer[i] = luaL_checknumber( L, -1 );
        lua_pop( L, 1 );
    }
    lua_pop( L, 1 );
    return count;
}

int get_table_field_string_array( lua_State* L, const char* key, int ss_index, const char** buffer )
{
    lua_pushstring( L, key );
    lua_gettable( L, ss_index );
    const int count = luaL_len( L, -1 );
    for ( int i = 0; i < count; i++ )
    {
        lua_pushinteger( L, i + 1 );
        lua_gettable( L, 3 );
        buffer[i] = luaL_checkstring( L, -1 );
        lua_pop( L, 1 );
    }
    lua_pop( L, 1 );
    return count;
}