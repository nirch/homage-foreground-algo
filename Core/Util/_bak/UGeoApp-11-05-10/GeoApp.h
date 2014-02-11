/***
***    author:		Yoram Elichai   yorame@gmail.com
***    Copyright (C) 2000 - All Rights Reserved
***/
#ifndef		_GEO_APP_
#define		_GEO_APP_

#ifdef __cplusplus
extern "C" {
#endif

#include	"Uvec/Vec2d.h"


//#define		MAX_POINT_NUMBER    4096
#define		MAX_POINT_NUMBER    16384


#define		GEOM_DIVISION		1



typedef struct gapp_type {
	int	type;
	int	no;		/* Segments number in polyline */
	int	ino;

	int	N;

	vec2d	*v;

	vec2d	*tang;
	
	int   *flag;

	float   *a;

}	gapp_type;



typedef struct {
	float	dwight;		/* wight of dev 1 */

	float	err;		/* max  L2  distance */

	float	Max_dev;	/* max distance */
	float	Min_dev;	/* distance */

	int	Min_pnumber;
	float	min_len;
	float	max_len;
}	gapp_prm;



	// GappTool.h
gapp_type *	gapp_alloc( int no );

gapp_type *	gapp_realloc( gapp_type *gapp, int no );

void	gapp_destroy( gapp_type *gapp );

void	gapp_inverse( gapp_type *gapp );

	// GeoApp.c
int	geo_approximate( gapp_type *gapp, gapp_prm *gprm );

void	geo_approximate_modify( gapp_type *gapp, int dlen, float Dang,
					gapp_prm *gprm );

int	gapp_next( gapp_type *gapp, int from, int div_type );



	// GeoApp1.c
float	geo_approximate_l2( vec2d *p0, vec2d *p1,
			vec2d *v, vec2d *tang, int no,
			gapp_prm *gprm,
			float *a, float *len,
			vec2d *p2, int *i2, float *a2 );



	// GeoAppLine.c
int	geo_approximate_line( vec2d v[], int no, float max_err, vec2d *p0, vec2d *p1 );


	// GeoApp2.c
float	geo_approximate2( vec2d *p0, vec2d *p1, vec2d *v, vec2d *tang, int no, gapp_prm *gprm, float *a );



	// GappDump.c
void	gapp_dump( gapp_type *gapp,  char *prefix, int index, char *suffix );


#ifdef _DUMP
#define  GAPP_DUMP( gapp, prefix, index, suffix )	gapp_dump( gapp, prefix, index, suffix )
#else
#define  GAPP_DUMP( gapp, prefix, index, suffix )
#endif


#ifdef __cplusplus
}
#endif
#endif
