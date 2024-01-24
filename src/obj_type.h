#pragma once

#define OBJ_TYPE unsigned short

#define OBJECT_BEGIN 0
#define CUBE 1
#define OBJECT_END 2
#define LAYOUT_BEGIN 3
#define DIFFERENCE 4
#define UNION 5
#define INTERSECTION 6
#define LAYOUT_END 7

#define OBJECT_CODE_LENGTH 100
#define LAYOUT_CODE_LENGTH 2048

#define dynast_cast( DEST, base, pointer ) struct DEST* pointer = ( struct DEST* )( base )