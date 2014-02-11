/************************
 ***    LnAttType.h   ***
 ************************/
 
#ifndef		_LN_ATT_H_
#define		_LN_ATT_H_


#include	"Uigp/igp.h"

#include	"LnSegType.h"


typedef struct lnAtt_type {

	lnSeg_type	ls;


	float	d0;			// min u
	float	d1;			// max u	
	float	av;			// average distance	: average of all u
	float	avAbs;		// average Abs(distance)	: average of all Abs(u)
	float	var;		// vaeiability :	deviation from the average

} lnAtt_type;




lnAtt_type *	lnAtt_alloc();

void lnAtt_destroy( lnAtt_type *at );

void	lnAtt_compute_dis( lnAtt_type *at, lnDisA_type *ldA, int i0, int i1 );

lnAtt_type *	lnAtt_attach( lnSeg_type *ls, vec2d *ctr, link_type *link );


#endif 