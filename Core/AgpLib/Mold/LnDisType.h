/************************
 ***    LnDisType.h   ***
 ************************/
 
#ifndef         _LN_DIS_H_
#define         _LN_DIS_H_


#include        "Uigp/igp.h"



typedef struct lnDis_type {
	float	u;
	float	gt;		// global t

	float	dt;


} lnDis_type;



typedef struct lnDisA_type {

	int	Ni,	NI;

	float	endDt;	// dt of the last point

	lnDis_type	*d;
} lnDisA_type;



lnDisA_type *	lnDisA_alloc( int ni);


void	lnDisA_realloc( lnDisA_type *ldA, int ni);


void	lnDisA_destroy( lnDisA_type *ldA );


int	lnDisA_set_dt( lnDisA_type *ad, float contourLen );

int	lnDisA_segment_minDt( lnDisA_type *ad, float minDt );

void	lnDis_compute_dis( lnDisA_type *ldA, int i0, int i1,
				  float *maxDt, float *av_u, float *min_u, float *max_u );



#endif 