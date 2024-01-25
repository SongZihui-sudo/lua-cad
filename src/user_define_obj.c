#include <user_define_obj.h>

static const luaL_Reg userdefineobjlib[]
= { { NULL, NULL } };

LUAMOD_API int luaopen_user_define_obj( lua_State* L )
{
    luaL_newlib( L, userdefineobjlib );
    return 1;
}
