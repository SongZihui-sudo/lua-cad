#include <to_code.h>
#include <transform.h>

int transform_postion( lua_State* L )
{
    D3OBJECT_BASE* current = dynast_cast( D3OBJECT_BASE, lua_touserdata( L, 1 ) );
    if ( !current )
    {
        luaL_error(L, "Object is null!");
    }
    // 读输入的参数
    const int count = 3;
    for ( int i = 0; i < count; i++ )
    {
        lua_pushnumber( L, i + 1 );
        lua_gettable( L, 2 );
        double temp_num             = lua_tonumber( L, -1 );
        current->m_offset->m_xyz[i] = temp_num;
        lua_pop( L, 1 );
    }
    // 设置当前的输出代码
    d3obj_to_code( L, current );
    return 1;
}

static const luaL_Reg transformlib[] = { { "postion", transform_postion }, { NULL, NULL } };

LUAMOD_API int luaopen_transform( lua_State* L )
{
    luaL_newlib( L, transformlib );
    return 1;
}
