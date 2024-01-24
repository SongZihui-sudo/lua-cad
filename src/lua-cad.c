#include <lua-cad.h>
#include <lua.h>
#include <obj_type.h>
#include <stdlib.h>

// 返回代码
int code( lua_State* L )
{
    OBJ_TYPE* type   = ( OBJ_TYPE* )lua_touserdata( L, 1 );
    const char* code = ( char* )( type + sizeof( OBJ_TYPE ) - 1 );
    lua_pushstring( L, code );
    return 1;
}

// 导出
int lua_cad_export( lua_State* L )
{
    const char* path = luaL_checkstring( L, 1 );
    OBJ_TYPE* type   = ( OBJ_TYPE* )lua_touserdata( L, 2 );
    const char* code = ( char* )( type + sizeof( OBJ_TYPE ) - 1 );
    // 写入文件
    FILE* fptr;
    fptr = fopen( path, "w" );
    if ( fptr == NULL )
    {
        luaL_error(L, "File write failed!");
        exit( 1 );
    }
    fprintf( fptr, "%s", code );
    fclose( fptr );
    return 1;
}