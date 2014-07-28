/**********************
 ***   GradNjet.c   ***
 **********************/

#include	<math.h>

#include	"Uigp/igp.h"
#include "Uvec/Vec2d.h"
#include "UJet2/Jet23Type.h"

#include "ImageType/ImageType.h"

#include "ImageApp/ImageApp.h"


#include "GradCenter.h"




//#define GRAD_EPS          (0.5)
//#define GRAD_IS_ZERO( x ) ( (x) < GRAD_EPS && (x) > -GRAD_EPS )




//static float	Gc_d1,	Gc_curvature;
static float Gc_df = 15.0;
static float Gc_d = 1.25;

#ifdef _AA_
static GP_prm params[] = {
  {"Gc-N-d", (char *)&Gc_d, PRM_FLOAT,"%.2f","1.25"},
  {"Gc-N-d1", (char *)&Gc_d1, PRM_FLOAT,"%.3f","0.70"},

  {"Gc-N-df", (char *)&Gc_df, PRM_FLOAT,"%.2f","15.0"},
  {"Gc-N-c", (char *)&Gc_curvature, PRM_FLOAT,"%.2f","0.45"},
};
#endif


static int	grad_center_jet3( jet3_type *f, vec2f_type *p, vec2f_type *n, float *w );


int
grad_center( image_type *im, int i0, int j0, vec2f_type *p, vec2f_type *n, float *w )

{
jet3_type      f;
int	ret;

	image1_app5_jet3(  im, i0, j0, &f );
			

	ret = grad_center_jet3( &f, p, n, w );

	VEC2D_SWAP( *p );
	VEC2D_SWAP( *n );
	p->x = p->x + j0 + 0.5;
	p->y = p->y + i0 + 0.5;

	return( ret );
}








static int
grad_center_jet3( jet3_type *f, vec2f_type *p, vec2f_type *n, float *w )
{
float  q0, q1, q2, a10, a01, desc, sq_desc;
float	a;
float	c0,	c1,	c2,	c3;

	n->x = J10(*f);
	n->y = J01(*f);

	float t = n->x * n->x + n->y*n->y;
	if( t < Gc_df*Gc_df )
		return( -1 );



	float df = hypot( n->x, n->y );
	n->x /= df;
	n->y /= df;



	a10 = n->x;
	a01 = n->y;

	/* NEW 9-8-95 */
	//a = -n->y;
	//b =  n->x;
	//tmp = 2 * a * b * ( J20(*f) - J02(*f) ) + J11(*f) * (b * b - a * a);
	//if( tmp < 0 )	tmp  = -tmp;
	//if( tmp >  2*df * Gc_curvature ){
	//	return( -1 );

	/* end NEW */



	// coefficients of single variable polynom of degree 3 
	c0 = J00(*f);
	q0 = c1 = J10(*f)*a10 + J01(*f)*a01;
	q1 = c2 = a10*( J20(*f)*a10 + J11(*f)*a01 ) + J02(*f)*a01*a01;
	q2 = c3 = a10*( a10*( J30(*f)*a10 + J21(*f)*a01 ) +
				J12(*f)*a01*a01 ) + J03(*f)*a01*a01*a01;
  
	desc = q1*q1 - 3*q0*q2;
 


	if ( desc < 0 || ABS(desc) < 0.5 )
		return( -1 );



	if ( ABS(q2) < 0.5   || q2 > 0 )  // root with same sign
		return( -1 );




	sq_desc = (float)sqrt( desc );

	float rw = (-q1 - sq_desc) / (3*q2);
	float lw = (-q1 + sq_desc) / (3*q2);





	if( n->x*n->x >= n->y*n->y )
		a = ABS(n->x);
	else    a = ABS(n->y);

	if( a* ABS(rw) > Gc_d ){
		return( -1 );
		// njet->rval  = c0 + njet->rw* (c1 + njet->rw*( c2 + njet->rw*c3 ) );
	}
	


	if( a* ABS(lw) > Gc_d ){
		return( -1 );
		//njet->lval  = c0 + njet->lw* (c1 + njet->lw*( c2 + njet->lw*c3 ) );
	}



	t = 0.5*(rw + lw );

	p->x = t*n->x;
	p->y = t*n->y;

	*w = 0.5*(rw - lw );

	return( 1 );
}    
