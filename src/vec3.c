#include <vec3.h>

#include <math.h>

int scale( vec3* src, vec3 to )
{
    if ( !src )
    {
        return -1;
    }
    src->m_xyz[0] = src->m_xyz[0] * to.m_xyz[0];
    src->m_xyz[1] = src->m_xyz[1] * to.m_xyz[1];
    src->m_xyz[2] = src->m_xyz[2] * to.m_xyz[2];
    return 1;
}

int pan( vec3* cur, vec3 to )
{
    if ( !cur )
    {
        return -1;
    }
    cur->m_xyz[0] = cur->m_xyz[0] + to.m_xyz[0];
    cur->m_xyz[1] = cur->m_xyz[1] + to.m_xyz[1];
    cur->m_xyz[2] = cur->m_xyz[2] + to.m_xyz[2];
    return 1;
}

/**
 * @description: 相对一个特定的坐标轴的特定方向旋转
 * @param {vec3*} src
 * @param {double} angle
 * @param {vec3} v
 * @return {*}
 */
int rotation_direct( vec3* src, double angle, vec3 v ) 
{
    TODO相对一个特定的坐标轴的特定方向旋转:
    return 1;
}

int rotation( vec3* src, vec3 a, vec3 v ) 
{
    if ( !src )
    {
        return -1;
    }
    // x
    rotation_direct(src, a.m_xyz[0], v);
    // y
    rotation_direct(src, a.m_xyz[1], v);
    // z
    rotation_direct(src, a.m_xyz[2], v);
    return 1;
}
