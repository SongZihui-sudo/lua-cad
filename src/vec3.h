#pragma once

/**
 * @description: 3 维向量
 * @return {*}
 */
typedef struct vec3
{
    double m_xyz[3];
} vec3;

static void vec3_init( vec3* obj, int c )
{
    if ( !obj )
    {
        return;
    }
    obj->m_xyz[0] = c;
    obj->m_xyz[1] = c;
    obj->m_xyz[2] = c;
}

/**
 * @description: 缩放指定的比例
 * @param {vec3} src
 * @param {vec3} to
 * @return {*}
 */
int scale( vec3* src, vec3 to );

/**
 * @description: 平移
 * @param {vec3} cur
 * @param {vec3} to
 * @return {*}
 */
int pan( vec3* cur, vec3 to );

/**
 * @description: 旋转变换
 * @param {vec3*} src
 * @param {vec3} a
 * @param {vec3} v
 * @return {*}
 */
/* reference: https://blog.csdn.net/wishchin/article/details/80926037 */
int rotation( vec3* src, vec3 a, vec3 v );

/**
 * @description: 计算两个三维坐标点距离
 * @param {vec3} v1
 * @param {vec3} v2
 * @return {*}
 */
double distance(vec3 v1, vec3 v2);

/**
 * @description: 计算两个三维向量间的夹角
 * @param {vec3} v1
 * @param {vec3} v2
 * @return {*}
 */
double angle(vec3 v1, vec3 v2);

/**
 * @description: 两个三维向量点乘
 * @param {vec3} v1
 * @param {vec3} v2
 * @return {*}
 */
double dot_mul(vec3 v1, vec3 v2);