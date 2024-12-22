#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <stdbool.h>

#if !defined( LUA_PROGNAME )
#define LUA_PROGNAME "lua"
#endif
static const char* progname = LUA_PROGNAME;

bool loadLuaFile( lua_State* luaEnv, const char* fileName )
{
    int result = luaL_loadfile( luaEnv, fileName );
    result = lua_pcall( luaEnv, 0, 0, 0 );
    return result;
}

static void l_message( const char* pname, const char* msg )
{
    if ( pname )
        lua_writestringerror( "%s: ", pname );
    lua_writestringerror( "%s\n", msg );
}

static int report( lua_State* L, int status )
{
    if ( status != LUA_OK )
    {
        const char* msg = lua_tostring( L, -1 );
        l_message( progname, msg );
        lua_pop( L, 1 ); /* remove message */
    }
    return status;
}

int main( int argc, char** argv )
{
    char buff[256];
    lua_State* L = luaL_newstate( );
    luaL_openlibs( L );

    int status = loadLuaFile( L, argv[1] );
    report( L, status );

    lua_close( L );
    return 0;
}