#include <vec3.h>

#include <math.h>

double dot_mul(vec3 v1, vec3 v2)
{
    return (v1.m_xyz[0] * v2.m_xyz[0]) + (v1.m_xyz[1] * v2.m_xyz[1]) + (v1.m_xyz[2] * v2.m_xyz[2]);
}

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

double distance(vec3 v1, vec3 v2)
{
    double x = v1.m_xyz[0] - v2.m_xyz[0];
    double y = v1.m_xyz[1] - v2.m_xyz[1];
    double z = v1.m_xyz[2] - v2.m_xyz[2];
    double dis = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    return dis;
}

double angle(vec3 v1, vec3 v2)
{
    double temp = dot_mul(v1, v2);
    double temp1 = pow(v1.m_xyz[0], 2) + pow(v1.m_xyz[1], 2) + pow(v1.m_xyz[2], 2);
    double temp2 = pow(v2.m_xyz[0], 2) + pow(v2.m_xyz[1], 2) + pow(v2.m_xyz[2], 2);
    double cos = temp / (sqrt(temp1) * sqrt(temp2));
#define PI 3.14159265
    double ang = acos(cos) * 180.0 / PI;
#undef PI
}