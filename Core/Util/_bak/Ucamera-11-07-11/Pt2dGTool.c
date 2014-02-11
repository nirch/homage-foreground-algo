/***********************
 ***	Pt2dTool.c   ***
 ***********************/
#include	<math.h>
#include	"Uigp/igp.h"
#include	"Umath/Matrix2Type.h"
#include	"Ubox/Box2d.h"
#include	"Pt2dType.h"


pt2dG_type *

pt2dG_alloc( box2f_type *b, float d )
{
pt2dG_type	*gpt;
int	i;

	gpt = (pt2dG_type *)malloc( sizeof( pt2dG_type) );

	gpt->d = d;
	gpt->inv_d = 1.0 /d;

	gpt->box = *b;


	gpt->Ni = ( gpt->box.y1 - gpt->box.y0) * gpt->inv_d;
	if( gpt->Ni * gpt->d <  gpt->box.y1 - gpt->box.y0 )
		gpt->Ni++;

	gpt->Nj = ( gpt->box.x1 - gpt->box.x0) * gpt->inv_d;
	if( gpt->Nj * gpt->d <  gpt->box.x1 - gpt->box.x0 )
		gpt->Nj++;


	gpt->p = ( pt2d_type **)malloc( gpt->Ni * gpt->Nj*sizeof(pt2d_type *) );

	for( i = 0 ; i < gpt->Ni*gpt->Nj ; i++ )
		gpt->p[i] = 0;

	return( gpt );
}




void
pt2dG_destroy( pt2dG_type *gpt )
{
	free( gpt->p );

	free( gpt );
}


#define	GPT_PT( gpt, i, j )	( (gpt)->p + i * (gpt)->Nj + j))
#define GPT_I( gpt, p )		( ( (p).y - (gpt)->box.y0 )*(gpt)->inv_d )
#define GPT_J( gpt, p )		( ( (p).x - (gpt)->box.x0 )*(gpt)->inv_d )


pt2dG_type *
pt2dG_create( pt2dA_type *apt, float d )
{
pt2dG_type *gpt;
int	i,	i0,	j0,	k;

	pt2dA_box( apt );

	gpt = pt2dG_alloc( &apt->box, d );


	for( i = 0 ; i < apt->nP ; i++ ){
		pt2d_type *pt = &apt->p[i];

		i0 = GPT_I( gpt, pt->p );
		j0 = GPT_J( gpt, pt->p );

		k = i0 * gpt->Nj + j0;

		pt->np = gpt->p[k];
		gpt->p[k] = pt;

	}

	return( gpt );

}