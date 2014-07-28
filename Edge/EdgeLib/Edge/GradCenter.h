/**********************
 ***  pHunchType.h  ***
 **********************/


#ifndef _GRAD_CENTER_H_
#define _GRAD_CENTER_H_

#include "Uigp/igp.h"
#include "Uvec/Vec2d.h"
#include "ImageType/ImageType.h"



int		grad_center( image_type *im, int i0, int j0, vec2f_type *p, vec2f_type *n, float *w );


#endif