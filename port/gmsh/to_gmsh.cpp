/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-02-08 21:20:28
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-02-11 01:14:15
 * @FilePath: /lua-cad/port/gmsh/to_gmsh.cpp
 * @Description:
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */
extern "C"
{
#include <circle.h>
#include <square.h>
}
#include <gmsh.h>
#include <to_gmsh.h>

#include <iostream>
#include <string>
#include <vector>

static void square_to_gmsh( square* obj )
{
    if ( !obj->base.m_center )
    {
        gmsh::model::occ::addRectangle( obj->base.m_offset.m_xyz[0],
                                        obj->base.m_offset.m_xyz[1],
                                        obj->base.m_offset.m_xyz[2],
                                        obj->w_l.m_xy[0],
                                        obj->w_l.m_xy[1] );
    }
    else
    {
        gmsh::model::occ::addRectangle( obj->base.m_offset.m_xyz[0] - ( obj->w_l.m_xy[0] / 2 ),
                                        obj->base.m_offset.m_xyz[1] - ( obj->w_l.m_xy[1] / 2 ),
                                        obj->base.m_offset.m_xyz[2],
                                        obj->w_l.m_xy[0],
                                        obj->w_l.m_xy[1] );
    }
}

static void circle_to_gmsh( circle* obj )
{
    if ( obj->m_r_d == 'd' )
    {
        obj->m_value = obj->m_value / 2;
    }
    gmsh::model::occ::addCircle( obj->base.m_offset.m_xyz[0],
                                 obj->base.m_offset.m_xyz[1],
                                 obj->base.m_offset.m_xyz[2],
                                 obj->m_value );
}

void object_to_gmsh( lua_State* L )
{
    OBJ_BASE* current = dynast_cast( OBJ_BASE, lua_touserdata( L, 2 ) );
    if ( !current )
    {
        luaL_error( L, "object is null!" );
    }
    if ( is_d2object( current->m_type ) )
    {
        d2object_to_gmsh( dynast_cast( D2OBJECT_BASE, current ) );
    }
    else if ( is_d3object( current->m_type ) )
    {
        d3object_to_gmsh( dynast_cast( D3OBJECT_BASE, current ) );
    }
    else
    {
        luaL_error( L, "Unsupported types!" );
    }
}

void d3object_to_gmsh( D3OBJECT_BASE* obj )
{
    switch ( obj->m_obj_base.m_type )
    {
        case CUBE:
            break;
        case CYLINDER:
            break;
        case SPHERE:
            break;
        case POLYHEDRON:
            break;
        default:
            break;
    }
}

void d2object_to_gmsh( D2OBJECT_BASE* obj )
{
    switch ( obj->m_obj_base.m_type )
    {
        case SQUARE:
            square_to_gmsh( dynast_cast( square, obj ) );
            break;
        case CIRCLE:
            circle_to_gmsh( dynast_cast( circle, obj ) );
            break;
        case POLYGON:
            std::cout << "For polygons, please use 'addPlaneSurface'!" << std::endl;
            break;
        default:
            break;
    }
}

void gmsh_save( lua_State* L )
{
    if ( lua_istable( L, 2 ) )
    {
        lua_getfield( L, 2, "add" );
        lua_pushvalue( L, 2 );
        int iRet = lua_pcall( L, 1, 0, 0 );
        if ( iRet )
        {
            const char* pErrorMsg = lua_tostring( L, -1 );
            luaL_error( L, pErrorMsg );
        }
    }
    else if ( lua_isuserdata( L, 2 ) )
    {
        object_to_gmsh( L );
    }
    else
    {
        luaL_error( L, "Unsupported types!" );
    }
    gmsh::model::occ::synchronize( );
    const char* filename = luaL_checkstring( L, 1 );
    gmsh::write( filename );
}

static LUA_CAD_API gmsh_init( lua_State* L )
{
    gmsh::initialize( );
    return 1;
}

static LUA_CAD_API gmsh_finalize( lua_State* L )
{
    gmsh::finalize( );
    return 1;
}

static LUA_CAD_API gmsh_generate( lua_State* L )
{
    int num = luaL_checkinteger( L, 1 );
    gmsh::model::mesh::generate( num );
    return 1;
}

static LUA_CAD_API gmsh_add_line( lua_State* L )
{
    int start_point = get_table_field_number_value( L, "index", 1 );
    int end_point   = get_table_field_number_value( L, "index", 2 );
    int index       = gmsh::model::occ::addLine( start_point, end_point );
    lua_pushinteger( L, index );
    return 1;
}

static LUA_CAD_API gmsh_add_point( lua_State* L )
{
    double x  = get_table_field_number_value( L, "x", 1 );
    double y  = get_table_field_number_value( L, "y", 1 );
    double z  = get_table_field_number_value( L, "z", 1 );
    double lc = get_table_field_number_value( L, "lc", 1 );
    int index = gmsh::model::occ::addPoint( x, y, z, lc );
    lua_pushinteger( L, index );
    return 1;
}

static LUA_CAD_API gmsh_add( lua_State* L )
{
    const char* name = lua_tostring( L, 1 );
    gmsh::model::add( name );
    return 1;
}

static LUA_CAD_API gmsh_synchronize( lua_State* L )
{
    gmsh::model::occ::synchronize( );
    return 1;
}

static LUA_CAD_API gmsh_add_circlearc( lua_State* L )
{
    int start_point  = get_table_field_number_value( L, "index", 1 );
    int center_point = get_table_field_number_value( L, "index", 2 );
    int end_point    = get_table_field_number_value( L, "index", 3 );
    bool center      = lua_toboolean( L, 7 );
    int index = gmsh::model::occ::addCircleArc( start_point, center_point, end_point, -1, center );
    lua_pushinteger( L, index );
    return 1;
}

static LUA_CAD_API gmsh_add_ellipsearc( lua_State* L )
{
    int start_point  = get_table_field_number_value( L, "index", 1 );
    int center_point = get_table_field_number_value( L, "index", 2 );
    int major_point  = get_table_field_number_value( L, "index", 3 );
    int end_point    = get_table_field_number_value( L, "index", 4 );
    int index = gmsh::model::occ::addEllipseArc( start_point, center_point, major_point, end_point );
    lua_pushinteger( L, index );
    return 1;
}

static LUA_CAD_API gmsh_add_curve( lua_State* L, GMSH_CURVE type )
{
    double buffer[64] = { 0 };
    int length        = get_table_field_number_array( L, "indexs", 1, buffer );
    std::vector< int > indexs, curves = { };
    for ( int i = 0; i < length; i++ )
    {
        indexs.push_back( buffer[i] );
    }
    int index;
    bool temp;
    std::vector< double > tangents;
    switch ( type )
    {
        case GMSH_SPLINE:
            memset( buffer, 0, 64 );
            length = get_table_field_number_array( L, "tangents", 1, buffer );
            for ( int i = 0; i < length; i++ )
            {
                tangents.push_back( buffer[i] );
            }
            index = gmsh::model::occ::addSpline( indexs, -1, tangents );
            break;
        case GMSH_BSPLINE:
            // need - fix
            index = gmsh::model::occ::addBSpline( indexs );
            break;
        case GMSH_BEZIER:
            index = gmsh::model::occ::addBezier( indexs );
            break;
        case GMSH_PLANESURFACE:
            index = gmsh::model::occ::addPlaneSurface( indexs );
            break;
        case GMSH_SURFACELOOP:
            temp  = get_table_field_boolean_value( L, "sewing", 1 );
            index = gmsh::model::occ::addSurfaceLoop( indexs, -1, temp );
            break;
        case GMSH_VOLUME:
            index = gmsh::model::occ::addVolume( indexs );
            break;
        case GMSH_CURVELOOP:
            index = gmsh::model::occ::addCurveLoop( indexs );
            break;
        default:
            break;
    }
    lua_pushinteger( L, index );
    return 1;
}

static LUA_CAD_API gmsh_add_spline( lua_State* L )
{
    gmsh_add_curve( L, GMSH_SPLINE );
    return 1;
}

static LUA_CAD_API gmsh_add_bspline( lua_State* L )
{
    gmsh_add_curve( L, GMSH_BSPLINE );
    return 1;
}

static LUA_CAD_API gmsh_add_bezier( lua_State* L )
{
    gmsh_add_curve( L, GMSH_BEZIER );
    return 1;
}

static LUA_CAD_API gmsh_add_plane_surface( lua_State* L )
{
    gmsh_add_curve( L, GMSH_PLANESURFACE );
    return 1;
}

static LUA_CAD_API gmsh_add_surface_loop( lua_State* L )
{
    gmsh_add_curve( L, GMSH_SURFACELOOP );
    return 1;
}

static LUA_CAD_API gmsh_add_volume( lua_State* L )
{
    gmsh_add_curve( L, GMSH_VOLUME );
    return 1;
}

static LUA_CAD_API gmsh_add_add_curve_loop( lua_State* L )
{
    gmsh_add_curve( L, GMSH_CURVELOOP );
    return 1;
}

static LUA_CAD_API gmsh_add_surface_filling( lua_State* L )
{
    int wire              = get_table_field_number_value( L, "wire", 1 );
    int degree            = get_table_field_number_value( L, "degree", 1 );
    int numPointsOnCurves = get_table_field_number_value( L, "numPointsOnCurves", 1 );
    int numIter           = get_table_field_number_value( L, "numIter", 1 );
    bool anisotropic      = get_table_field_boolean_value( L, "anisotropic", 1 );
    double tol2d          = get_table_field_number_value( L, "tol2d", 1 );
    double tol3d          = get_table_field_number_value( L, "tol3d", 1 );
    double tolAng         = get_table_field_number_value( L, "tolAng", 1 );
    double tolCurv        = get_table_field_number_value( L, "tolCurv", 1 );
    int maxDegree         = get_table_field_number_value( L, "maxDegree", 1 );
    int maxSegments       = get_table_field_number_value( L, "maxSegments ", 1 );
    double buffer1[64]    = { 0 };
    int length1           = get_table_field_number_array( L, "indexs", 1, buffer1 );
    std::vector< int > indexs;
    for ( int i = 0; i < length1; i++ )
    {
        indexs.push_back( buffer1[i] );
    }
    int index = gmsh::model::occ::addSurfaceFilling(
    wire, -1, indexs, degree, numPointsOnCurves, numIter, anisotropic, tol2d, tol3d, tolAng, tolCurv, maxDegree, maxSegments );
    lua_pushinteger( L, index );
    return 1;
}

static LUA_CAD_API gmsh_add_wire( lua_State* L )
{
    bool checkClosed  = get_table_field_boolean_value( L, "check_closed", 1 );
    double buffer[64] = { 0 };
    int length        = get_table_field_number_array( L, "curves", 1, buffer );
    std::vector< int > curives;
    for ( int i = 0; i < length; i++ )
    {
        curives.push_back( buffer[i] );
    }
    int index = gmsh::model::occ::addWire( curives, checkClosed );
    lua_pushinteger( L, index );
    return 1;
}

// extrude, revolve，twist，extrudeBoundaryLayer，translate，rotate，dilate，mirror，addPhysicalGroup,occ/addRectangle，occ/addSphere,occ/addBox,occ/addCylinder,
// occ/addCone, occ/addWedge, occ/addTorus, intersect,cut,fragment
static const luaL_Reg gmshlib[] = { { "addPoint", gmsh_add_point },
                                    { "init", gmsh_init },
                                    { "add", gmsh_add },
                                    { "finalize", gmsh_finalize },
                                    { "generate", gmsh_generate },
                                    { "addLine", gmsh_add_line },
                                    { "syn", gmsh_synchronize },
                                    { "addCircleArc", gmsh_add_circlearc },
                                    { "addEllipseArc", gmsh_add_ellipsearc },
                                    { "addSpline", gmsh_add_spline },
                                    { "addBSpline", gmsh_add_bspline },
                                    { "addBezier", gmsh_add_bezier },
                                    { "addCurveLoop", gmsh_add_add_curve_loop },
                                    { "addPlaneSurface", gmsh_add_plane_surface },
                                    { "addSurfaceFilling", gmsh_add_surface_filling },
                                    { "addSurfaceLoop", gmsh_add_surface_loop },
                                    { "addVolume", gmsh_add_volume },
                                    { "addWire", gmsh_add_wire },
                                    { NULL, NULL } };

LUAMOD_API int luaopen_gmsh( lua_State* L )
{
    luaL_newlib( L, gmshlib );
    return 1;
}
