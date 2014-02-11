#ifndef __LINK_LAYER_H__
#define __LINK_LAYER_H__

#include "GpType/LinkType.h"
#include "Uvec/Vec2d.h"

enum direction_type {left = 0, right};

typedef enum direction_type direction_type;


void link_get_point_inside(vec2d *gCtr, link_type *link, vec2d *inside);

void link_get_point_at_direction(vec2d *gCtr, link_type *link, direction_type direction, vec2d *point);

direction_type link_get_inside_direction(vec2d *gCtr, link_type *contour);
#endif
