#include <boolean.h>
#include <difference.h>
#include <union.h>
#include <intersection.h>

static const luaL_Reg booleanlib[]
= { { "difference", difference }, { "union", Union }, { "intersection", intersection }, { NULL, NULL } };

LUAMOD_API int luaopen_boolean( lua_State* L )
{
    luaL_newlib( L, booleanlib );
    return 1;
}