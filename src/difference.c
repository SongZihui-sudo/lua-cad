#include <difference.h>
#include <stdlib.h>
#include <string.h>
#include <to_code.h>

int difference( lua_State* L )
{
    // 创建一个 difference 对象
    unsigned int i_bytes = sizeof( struct difference );
    struct difference* current;
    current         = ( struct difference* )lua_newuserdata( L, i_bytes );
    current->m_type = DIFFERENCE;
    memset( current->m_children, 0, 10 * sizeof( OBJ_TYPE ) );
    current->m_count = 0;
    // 读一个 table
    // 读输入的参数
    const int count = luaL_len( L, 1 );
    for ( int i = 0; i < count; i++ )
    {
        lua_pushnumber( L, i + 1 );
        lua_gettable( L, 1 );
        unsigned short* temp   = lua_touserdata( L, -1 );
        current->m_children[i] = temp;
        lua_pop( L, 1 );
        current->m_count++;
    }
    difference_to_code( L, current );
    return 1;
}