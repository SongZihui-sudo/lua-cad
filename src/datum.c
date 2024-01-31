#include <datum.h>

int relative_position(lua_State* L)
{
    TODO点相对位置计算:
    return 1;
}

int distance_to_datum(lua_State* L)
{
    TODO点相对距离的测量:
    return 1;
}

int angle_to_datum(lua_State* L)
{
    TODO向量与基准面间角度的测量:
    return 1;
}

static const luaL_Reg datumlib[]
= { {"relative", relative_position}, {"distance", distance_to_datum}, {"angle", angle_to_datum}, { NULL, NULL } };

LUAMOD_API int luaopen_datum( lua_State* L )
{
    luaL_newlib( L, datumlib );
    return 1;
}
