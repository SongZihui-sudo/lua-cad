#pragma once

#include <stdbool.h>

#include <vec3.h>

#define OBJ_TYPE unsigned short

/*
 * TYPE
*/
enum TYPES
{
    OBJECT_BEGIN = 0,
    USER_DEFINE,
    CUBE,
    OBJECT_END,
    BOOLEAN_BEGIN,
    DIFFERENCE,
    UNION,
    INTERSECTION,
    BOOLEAN_END
};

#define CODE_LENGTH 3000

#define dynast_cast( DEST, base) ( DEST* )( base )

/*
 *  OBJECY BASE
 */
typedef struct OBJ_BASE
{
    OBJ_TYPE m_type;
    char* m_code;
}OBJ_BASE;

/*
 *  boolean base struct
 */
typedef struct BOOLEAN_BASE 
{
    OBJ_BASE m_obj_base;
    OBJ_TYPE* m_children[10];
    unsigned int m_count;
}BOOLEAN_BASE;

/*
 *  3D OBJECT base
 */
typedef struct D3OBJECT_BASE
{
    OBJ_BASE m_obj_base;
    bool m_center;
    vec3* m_offset;
}D3OBJECT_BASE;
