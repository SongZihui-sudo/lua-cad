/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-02-08 21:20:28
 * @LastEditors: SongZihui-sudo 1751122876@qq.com
 * @LastEditTime: 2024-02-10 15:25:17
 * @FilePath: /lua-cad/port/gmsh/to_gmsh.cpp
 * @Description:
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#include <gmsh.h>
#include <to_gmsh.h>

#include <string>
#include <vector>

void gmsh_save( lua_State* L )
{
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
    double nx        = luaL_checkinteger( L, 4 );
    double ny        = luaL_checkinteger( L, 5 );
    double nz        = luaL_checkinteger( L, 6 );
    int index
    = gmsh::model::geo::addCircleArc( start_point, center_point, end_point, -1, nx, ny, nz );
    lua_pushinteger( L, index );
    return 1;
}

static LUA_CAD_API gmsh_add_ellipsearc( lua_State* L )
{
    int start_point  = get_table_field_number_value( L, "index", 1 );
    int center_point = get_table_field_number_value( L, "index", 2 );
    int major_point  = get_table_field_number_value( L, "index", 3 );
    int end_point    = get_table_field_number_value( L, "index", 4 );
    double nx        = luaL_checkinteger( L, 5 );
    double ny        = luaL_checkinteger( L, 6 );
    double nz        = luaL_checkinteger( L, 7 );
    int index
    = gmsh::model::geo::addEllipseArc( start_point, center_point, major_point, end_point, -1, nx, ny, nz );
    lua_pushinteger( L, index );
    return 1;
}

static LUA_CAD_API gmsh_add_curve( lua_State* L, GMSH_CURVE type )
{
    double buffer[64] = { 0 };
    int length        = get_table_field_number_array( L, "points", 1, buffer );
    std::vector< int > points, curves = { };
    for ( int i = 0; i < length; i++ )
    {
        points.push_back( buffer[i] );
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
            index = gmsh::model::occ::addSpline( points, -1, tangents );
            break;
        case GMSH_BSPLINE:
            // need - fix
            index = gmsh::model::occ::addBSpline( points );
            break;
        case GMSH_BEZIER:
            index = gmsh::model::occ::addBezier( points );
            break;
        case GMSH_PLANESURFACE:
            index = gmsh::model::occ::addPlaneSurface( points );
            break;
        case GMSH_SURFACELOOP:
            temp  = get_table_field_boolean_value( L, "sewing", 1 );
            index = gmsh::model::occ::addSurfaceLoop( points, -1, temp );
            break;
        case GMSH_VOLUME:
            index = gmsh::model::occ::addVolume( points );
            break;
        case GMSH_CURVELOOP:
            index = gmsh::model::occ::addCurveLoop( points );
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
    int anisotropic       = get_table_field_boolean_value( L, "anisotropic", 1 );
    double tol2d          = get_table_field_number_value( L, "tol2d", 1 );
    double tol3d          = get_table_field_number_value( L, "tol3d", 1 );
    double tolAng         = get_table_field_number_value( L, "tolAng", 1 );
    double tolCurv        = get_table_field_number_value( L, "tolCurv", 1 );
    int maxDegree         = get_table_field_number_value( L, "maxDegree", 1 );
    int maxSegments       = get_table_field_number_value( L, "maxSegments ", 1 );
    double buffer1[64]    = { 0 };
    int length1           = get_table_field_number_array( L, "points", 1, buffer1 );
    std::vector< int > points;
    for ( int i = 0; i < length1; i++ )
    {
        points.push_back( buffer1[i] );
    }
    int index = gmsh::model::occ::addSurfaceFilling(
    wire, -1, points, degree, numPointsOnCurves, numIter, anisotropic, tol2d, tol3d, tolAng, tolCurv, maxDegree, maxSegments );
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
                                    { NULL, NULL } };

LUAMOD_API int luaopen_gmsh( lua_State* L )
{
    luaL_newlib( L, gmshlib );
    return 1;
}