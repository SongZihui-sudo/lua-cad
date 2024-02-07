/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-02-07 18:18:01
 * @LastEditors: SongZihui-sudo 1751122876@qq.com
 * @LastEditTime: 2024-02-07 22:00:57
 * @FilePath: /lua-cad/port/dealii/dealii.cpp
 * @Description:
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#include <cube.h>
#include <dealii.h>
#include <obj_type.h>

#include <cmath>
#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/grid_out.h>
#include <deal.II/grid/tria.h>
#include <fstream>
#include <iostream>
#include <string.h>

using namespace dealii;

static int render_cube( cube* obj )
{
    /* 测试一下 */
    Triangulation< 2 > triangulation;
    GridGenerator::hyper_cube( triangulation );
    triangulation.refine_global( 4 );
    std::ofstream out( "grid-1.svg" );
    GridOut grid_out;
    grid_out.write_svg( triangulation, out );
    std::cout << "Grid written to grid-1.svg" << std::endl;
    return 1;
}

static int render_boolean_tree( BOOLEAN_BASE* obj ) {}

static int render_d3object( D3OBJECT_BASE* obj )
{
    int flag = 0;
    switch ( obj->m_obj_base.m_type )
    {
        case CUBE:
            flag = render_cube( dynast_cast( cube, obj ) );
            break;
        case SPHERE:
            break;
        case CYLINDER:
            break;
        case POLYHEDRON:
            break;
        default:
            return -1;
    }
    return flag;
}

static int render_d2object( D2OBJECT_BASE* obj ) {}

int dealii_render( OBJ_BASE* obj_base )
{
    int flag = 0;
    if ( is_boolean( obj_base->m_type ) )
    {
        flag = render_boolean_tree( dynast_cast( BOOLEAN_BASE, obj_base ) );
    }
    else if ( is_d3object( obj_base->m_type ) )
    {
        flag = render_d3object( dynast_cast( D3OBJECT_BASE, obj_base ) );
    }
    else if ( is_d2object( obj_base->m_type ) )
    {
        flag = render_d2object( dynast_cast( D2OBJECT_BASE, obj_base ) );
    }
    else
    {
        return -1;
    }
    return flag;
}