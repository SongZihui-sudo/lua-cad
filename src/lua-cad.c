#include <lua-cad.h>
#include <lua.h>
#include <obj_type.h>
#include <stdlib.h>

// 返回代码
int code( lua_State* L )
{
    OBJ_BASE* obj = dynast_cast( OBJ_BASE, lua_touserdata( L, 1 ) );
    const char* code     = obj->m_code;
    lua_pushstring( L, code );
    return 1;
}

// 导出
int lua_cad_export( lua_State* L )
{
    const char* path     = luaL_checkstring( L, 1 );
    OBJ_BASE* obj = dynast_cast( OBJ_BASE, lua_touserdata( L, 2 ) );
    if (!obj) 
    {
        luaL_error(L, "object is null!");
        return -1;
    }
    const char* code     = obj->m_code;
    // 写入文件
    FILE* fptr;
    fptr = fopen( path, "w" );
    if ( fptr == NULL )
    {
        luaL_error( L, "File write failed!" );
        exit( 1 );
    }
    fprintf( fptr, "%s", code );
    fclose( fptr );
    return 1;
}

int include_code(lua_State* L)
{
    
}

int import_module(lua_State* L)
{

}
