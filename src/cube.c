#include <cube.h>
#include <stdlib.h>
#include <string.h>
#include <to_code.h>
#include <vec3.h>

// 初始化一个立方体
int cube_init( lua_State* L )
{
    // 读输入的参数
    const int count       = 3;
    vec3* temp_vec = dynast_cast( vec3, malloc( sizeof( vec3 ) ) );
    for ( int i = 0; i < count; i++ )
    {
        lua_pushnumber( L, i + 1 );
        lua_gettable( L, 1 );
        double temp_num    = lua_tonumber( L, -1 );
        temp_vec->m_xyz[i] = temp_num;
        lua_pop( L, 1 );
    }
    bool is_center = lua_toboolean( L, 2 );
    // 创建一个立方体对象
    unsigned int i_bytes = sizeof( cube );
    cube* current;
    current                         = dynast_cast( cube, lua_newuserdata( L, i_bytes ) );
    current->base.m_obj_base.m_type = CUBE;
    current->m_w_l_h                = temp_vec;
    current->base.m_center          = is_center;
    current->base.m_offset          = dynast_cast(vec3, malloc( sizeof( vec3 ) ));
    for ( int i = 0; i < count; i++ )
    {
        current->base.m_offset->m_xyz[i] = 0.0f;
    }
    cube_to_code( L, current );
    return 1;
}

// 读立方体的高
int cube_height( lua_State* L )
{
    cube* current = dynast_cast(cube, lua_touserdata( L, 1 ));
    lua_pushnumber( L, current->m_w_l_h->m_xyz[2] );
    return 1;
}

// 读立方体的宽
int cube_width( lua_State* L )
{
    cube* current = dynast_cast(cube, lua_touserdata( L, 1 ));
    lua_pushnumber( L, current->m_w_l_h->m_xyz[0] );
    return 1;
}

// 读立方体的长
int cube_length( lua_State* L )
{
    cube* current = dynast_cast(cube, lua_touserdata( L, 1 ));
    lua_pushnumber( L, current->m_w_l_h->m_xyz[1] );
    return 1;
}

// 立方体的锚点
// 就是立方体的八个顶点，加六个平面的中心
/*
    前面右上 case 1:
    前面左上 case 2:
    前面右下 case 3:
    前面左上 case 4:
    后面右上 case 5:
    后面左上 case 6:
    后面右下 case 7:
    后面左下 case 8:
    顶 case 9:
    底 case 10:
    左 case 11:
    右 case 12:
    前 case 13:
    后 case 14:
*/
int cube_anchor( lua_State* L )
{
    cube* current = dynast_cast(cube, lua_touserdata( L, 1 ));
    unsigned short index = luaL_checkinteger( L, 2 );
    vec3 point    = calculate_vertices( current, index );
    // 返回一个 table
    lua_newtable( L );
    lua_pushstring( L, "x" );
    lua_pushnumber( L, point.m_xyz[0] );
    lua_settable( L, -3 );
    lua_pushstring( L, "y" );
    lua_pushnumber( L, point.m_xyz[1] );
    lua_settable( L, -3 );
    lua_pushstring( L, "z" );
    lua_pushnumber( L, point.m_xyz[2] );
    lua_settable( L, -3 );
    return 1;
}

int cube_postion( lua_State* L )
{
    cube* current = dynast_cast(cube, lua_touserdata( L, 1 ));
    // 读输入的参数
    const int count       = 3;
    vec3* temp_vec = dynast_cast(vec3, malloc( sizeof( vec3 ) ));
    for ( int i = 0; i < count; i++ )
    {
        lua_pushnumber( L, i + 1 );
        lua_gettable( L, 2 );
        double temp_num                  = lua_tonumber( L, -1 );
        current->base.m_offset->m_xyz[i] = temp_num;
        lua_pop( L, 1 );
    }
    // 设置当前的输出代码
    cube_to_code( L, current );
    return 1;
}

static const luaL_Reg cubelib[] = { { "new", cube_init },
                                    { "height", cube_height },
                                    { "width", cube_width },
                                    { "length", cube_length },
                                    { "anchor", cube_anchor },
                                    { "postion", cube_postion },
                                    { NULL, NULL } };

LUAMOD_API int luaopen_cube( lua_State* L )
{
    luaL_newlib( L, cubelib );
    return 1;
}

vec3 calculate_vertices( cube* self, unsigned short index )
{
    vec3 result;
    vec3* sides = self->m_w_l_h;
    if ( self->base.m_center )
    {
        switch ( index )
        {
            // 前面右上
            case 1:
                result.m_xyz[0] = sides->m_xyz[0] / 2 + self->base.m_offset->m_xyz[0]; // x
                result.m_xyz[1] = sides->m_xyz[1] / 2 + self->base.m_offset->m_xyz[1]; // y
                result.m_xyz[2] = sides->m_xyz[2] / 2 + self->base.m_offset->m_xyz[2]; // z
                break;
            // 前面左上
            case 2:
                result.m_xyz[0] = sides->m_xyz[0] / 2 + self->base.m_offset->m_xyz[0]; // x
                result.m_xyz[1] = -sides->m_xyz[1] / 2 + self->base.m_offset->m_xyz[1]; // y -
                result.m_xyz[2] = sides->m_xyz[2] / 2 + self->base.m_offset->m_xyz[2]; // z
                break;
            // 前面右下
            case 3:
                result.m_xyz[0] = sides->m_xyz[0] / 2 + self->base.m_offset->m_xyz[0]; // x
                result.m_xyz[1] = sides->m_xyz[1] / 2 + self->base.m_offset->m_xyz[1]; // y
                result.m_xyz[2] = -sides->m_xyz[2] / 2 + self->base.m_offset->m_xyz[2]; // z -
                break;
            // 前面左上
            case 4:
                result.m_xyz[0] = sides->m_xyz[0] / 2 + self->base.m_offset->m_xyz[0]; // x
                result.m_xyz[1] = -sides->m_xyz[1] / 2 + self->base.m_offset->m_xyz[1]; // y -
                result.m_xyz[2] = -sides->m_xyz[2] / 2 + self->base.m_offset->m_xyz[2]; // z -
                break;
            // 后面右上
            case 5:
                result.m_xyz[0] = -sides->m_xyz[0] / 2 + self->base.m_offset->m_xyz[0]; // x -
                result.m_xyz[1] = sides->m_xyz[1] / 2 + self->base.m_offset->m_xyz[1]; // y
                result.m_xyz[2] = sides->m_xyz[2] / 2 + self->base.m_offset->m_xyz[2]; // z
                break;
            // 后面左上
            case 6:
                result.m_xyz[0] = -sides->m_xyz[0] / 2 + self->base.m_offset->m_xyz[0]; // x -
                result.m_xyz[1] = -sides->m_xyz[1] / 2 + self->base.m_offset->m_xyz[1]; // y -
                result.m_xyz[2] = sides->m_xyz[2] / 2 + self->base.m_offset->m_xyz[2]; // z
                break;
            // 后面右下
            case 7:
                result.m_xyz[0] = -sides->m_xyz[0] / 2 + self->base.m_offset->m_xyz[0]; // x -
                result.m_xyz[1] = sides->m_xyz[1] / 2 + self->base.m_offset->m_xyz[1]; // y
                result.m_xyz[2] = -sides->m_xyz[2] / 2 + self->base.m_offset->m_xyz[2]; // z -
                break;
            // 后面左下
            case 8:
                result.m_xyz[0] = -sides->m_xyz[0] / 2 + self->base.m_offset->m_xyz[0]; // x -
                result.m_xyz[1] = -sides->m_xyz[1] / 2 + self->base.m_offset->m_xyz[1]; // y -
                result.m_xyz[2] = -sides->m_xyz[2] / 2 + self->base.m_offset->m_xyz[2]; // z -
                break;
            // 顶
            case 9:
                result.m_xyz[0] = self->base.m_offset->m_xyz[0];                       // x
                result.m_xyz[1] = self->base.m_offset->m_xyz[1];                       // y
                result.m_xyz[2] = self->base.m_offset->m_xyz[2] + sides->m_xyz[2] / 2; // z
                break;
            // 底
            case 10:
                result.m_xyz[0] = self->base.m_offset->m_xyz[0];
                result.m_xyz[1] = self->base.m_offset->m_xyz[1];
                result.m_xyz[2] = self->base.m_offset->m_xyz[2] - sides->m_xyz[2] / 2;
                break;
            // 左
            case 11:
                result.m_xyz[0] = self->base.m_offset->m_xyz[0];                       // x
                result.m_xyz[1] = self->base.m_offset->m_xyz[1] - sides->m_xyz[1] / 2; // y
                result.m_xyz[2] = self->base.m_offset->m_xyz[2];                       // z
                break;
            // 右
            case 12:
                result.m_xyz[0] = self->base.m_offset->m_xyz[0];                       // x
                result.m_xyz[1] = self->base.m_offset->m_xyz[1] + sides->m_xyz[1] / 2; // y
                result.m_xyz[2] = self->base.m_offset->m_xyz[2];                       // z
                break;
            // 前
            case 13:
                result.m_xyz[0] = self->base.m_offset->m_xyz[0] + sides->m_xyz[0] / 2; // x
                result.m_xyz[1] = self->base.m_offset->m_xyz[1];                       // y
                result.m_xyz[2] = self->base.m_offset->m_xyz[2];                       // z
                break;
            // 后
            case 14:
                result.m_xyz[0] = self->base.m_offset->m_xyz[0] - sides->m_xyz[0] / 2; // x
                result.m_xyz[1] = self->base.m_offset->m_xyz[1];                       // y
                result.m_xyz[2] = self->base.m_offset->m_xyz[2];                       // z
                break;
        }
    }
    else
    {
        switch ( index )
        {
            // 前面右上
            case 1:
                result.m_xyz[0] = sides->m_xyz[0] + self->base.m_offset->m_xyz[0]; // x
                result.m_xyz[1] = sides->m_xyz[1] + self->base.m_offset->m_xyz[1]; // y
                result.m_xyz[2] = sides->m_xyz[2] + self->base.m_offset->m_xyz[2]; // z
                break;
            // 前面左上
            case 2:
                result.m_xyz[0] = sides->m_xyz[0] + self->base.m_offset->m_xyz[0]; // x
                result.m_xyz[1] = self->base.m_offset->m_xyz[1];                   // y
                result.m_xyz[2] = sides->m_xyz[2] + self->base.m_offset->m_xyz[2]; // z
                break;
            // 前面右下
            case 3:
                result.m_xyz[0] = sides->m_xyz[0] + self->base.m_offset->m_xyz[0]; // x
                result.m_xyz[1] = sides->m_xyz[1] + self->base.m_offset->m_xyz[1]; // y
                result.m_xyz[2] = self->base.m_offset->m_xyz[2];                   // z
                break;
            // 前面左上
            case 4:
                result.m_xyz[0] = sides->m_xyz[0] + self->base.m_offset->m_xyz[0]; // x
                result.m_xyz[1] = self->base.m_offset->m_xyz[1];                   // y
                result.m_xyz[2] = self->base.m_offset->m_xyz[2];                   // z
                break;
            // 后面右上
            case 5:
                result.m_xyz[0] = self->base.m_offset->m_xyz[0];                   // x
                result.m_xyz[1] = sides->m_xyz[1] + self->base.m_offset->m_xyz[1]; // y
                result.m_xyz[2] = sides->m_xyz[2] + self->base.m_offset->m_xyz[2]; // z
                break;
            // 后面左上
            case 6:
                result.m_xyz[0] = self->base.m_offset->m_xyz[0];                   // x
                result.m_xyz[1] = self->base.m_offset->m_xyz[1];                   // y
                result.m_xyz[2] = sides->m_xyz[2] + self->base.m_offset->m_xyz[2]; // z
                break;
            // 后面右下
            case 7:
                result.m_xyz[0] = self->base.m_offset->m_xyz[0];                   // x
                result.m_xyz[1] = sides->m_xyz[1] + self->base.m_offset->m_xyz[1]; // y
                result.m_xyz[2] = self->base.m_offset->m_xyz[2];                   // z
                break;
            // 后面左下
            case 8:
                result.m_xyz[0] = self->base.m_offset->m_xyz[0]; // x
                result.m_xyz[1] = self->base.m_offset->m_xyz[1]; // y
                result.m_xyz[2] = self->base.m_offset->m_xyz[2]; // z
                break;
            // 顶
            case 9:
                result.m_xyz[0] = sides->m_xyz[0] / 2 + self->base.m_offset->m_xyz[0]; // x
                result.m_xyz[1] = sides->m_xyz[1] / 2 + self->base.m_offset->m_xyz[1]; // y
                result.m_xyz[2] = sides->m_xyz[2] + self->base.m_offset->m_xyz[1];     // z
                break;
            // 底
            case 10:
                result.m_xyz[0] = sides->m_xyz[0] / 2 + self->base.m_offset->m_xyz[0]; // x
                result.m_xyz[1] = sides->m_xyz[1] / 2 + self->base.m_offset->m_xyz[1]; // y
                result.m_xyz[2] = self->base.m_offset->m_xyz[1];                       // z
                break;
            // 左
            case 11:
                result.m_xyz[0] = sides->m_xyz[0] / 2 + self->base.m_offset->m_xyz[0]; // x
                result.m_xyz[1] = self->base.m_offset->m_xyz[1];                       // y
                result.m_xyz[2] = sides->m_xyz[2] / 2 + self->base.m_offset->m_xyz[1]; // z
                break;
            // 右
            case 12:
                result.m_xyz[0] = sides->m_xyz[0] / 2 + self->base.m_offset->m_xyz[0]; // x
                result.m_xyz[1] = sides->m_xyz[1] + self->base.m_offset->m_xyz[1];     // y
                result.m_xyz[2] = sides->m_xyz[2] / 2 + self->base.m_offset->m_xyz[1]; // z
                break;
            // 前
            case 13:
                result.m_xyz[0] = sides->m_xyz[0] + self->base.m_offset->m_xyz[0];     // x
                result.m_xyz[1] = sides->m_xyz[1] / 2 + self->base.m_offset->m_xyz[1]; // y
                result.m_xyz[2] = sides->m_xyz[2] / 2 + self->base.m_offset->m_xyz[1]; // z
                break;
            // 后
            case 14:
                result.m_xyz[0] = self->base.m_offset->m_xyz[0];                       // x
                result.m_xyz[1] = sides->m_xyz[1] / 2 + self->base.m_offset->m_xyz[1]; // y
                result.m_xyz[2] = sides->m_xyz[2] / 2 + self->base.m_offset->m_xyz[1]; // z
                break;
        }
    }
    return result;
}
