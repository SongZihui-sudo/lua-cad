#pragma once

/**
 * @description: 3 维向量
 * @return {*}
 */
typedef struct vec3
{
    double m_xyz[3];
}vec3;

/**
 * @description: 缩放指定的比例
 * @param {vec3} src
 * @param {vec3} to
 * @return {*}
 */
int scale(vec3* src, vec3 to);

/**
 * @description: 平移
 * @param {vec3} cur
 * @param {vec3} to
 * @return {*}
 */
int pan(vec3* cur, vec3 to);

/**
 * @description: 旋转变换
 * @param {vec3*} src
 * @param {vec3} a
 * @param {vec3} v
 * @return {*}
 */
/* reference: https://blog.csdn.net/wishchin/article/details/80926037 */
int rotation(vec3* src, vec3 a, vec3 v);
