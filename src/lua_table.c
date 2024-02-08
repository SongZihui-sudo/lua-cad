#include <lua_table.h>

double get_table_field_int_value(lua_State* L, const char* key, int ss_index)
{
    lua_pushstring(L, key);
    lua_gettable(L, ss_index);
    double value = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return value;
}