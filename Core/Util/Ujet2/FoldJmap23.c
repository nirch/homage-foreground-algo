/****************************************************************
*								*
*		Module: FoldJet22_3.c				*
*								*
****************************************************************/
#include	<math.h>
#include		"Uigp/igp.h"
#include        "Ujet2/Jet2Type.h"
#include        "Uvec/Vec2d.h"
#include        "Jet23Type.h"



static void	fold_level_0( jmap23 *F, jmap23 *L0, jmap23 *F0 );

static void	fold_level_1( jmap23 *F,
				jmap23 *R1, jmap23 *L1, jmap23 *F1 );

static void	fold_level_2( jmap23 *F1,
				jmap23 *R2, jmap23 *L2, jmap23 *F2 );

static void	fold_level_3( jmap23 *F2,
				jmap23 *R3, jmap23 *L3, jmap23 *F3 );


void
fold_jmap23( jmap23 *F, jmap23 *R, jmap23 *L, float *a, float *b )
{
jmap23	F0,	F1,	F2,	F3;
jmap23	L0,	L1,	L2,	L3;
jmap23	R1,	R2,	R3;
jmap23	T1,	T2;

	/************************************************************
	*    final normal form is     (L3*L2*L1*L0) * F * (R1*R2*R3)    *
	************************************************************/

	fold_level_0( F, &L0, &F0 );

	fold_level_1( &F0, &R1, &L1, &F1 );

	fold_level_2( &F1, &R2, &L2, &F2 );

	fold_level_3( &F2, &R3, &L3, &F3 );


	substit_jmap23( &L1, &L0, &T1 );
	substit_jmap23( &L2, &T1, &T2 );
	substit_jmap23( &L3, &T2, L );


	substit_jmap23( &R1, &R2, &T1 );
	substit_jmap23( &T1, &R3, R );

	*a = J10(F3.f1);
	*b = J02(F3.f2);
}




static void
fold_level_0( jmap23 *F, jmap23 *L0, jmap23 *F0 )
{
	identity_jmap23( L0 );
	J00( L0->f1 ) = - J00( F->f1 );
	J00( L0->f2 ) = - J00( F->f2 );

	*F0 = *F;
	J00( F0->f1 ) = 0;
	J00( F0->f2 ) = 0;
}



static void
fold_level_1(jmap23 *F, jmap23 *R1, jmap23 *L1, jmap23 *F1 )
{
jmap23   T;
float	A,	B,	C,	D,	t,	tj,	det;

	if ((J10(F->f1) * J10(F->f1) + J01(F->f1) * J01(F->f1)) >
			(J10(F->f2) * J10(F->f2) + J01(F->f2) * J01(F->f2)) ){
		A = J10(F->f1);
		B = J01(F->f1);
	} else {
		A = J10(F->f2);
		B = J01(F->f2);
	}

	t = hypot( A, B );
	A /= t;
	B /= t;


	C = 2*J20(F->f1) *J01(F->f2) - J11(F->f1)*J10(F->f2 ) + 
		J10(F->f1) * J11(F->f2 ) - J01(F->f1)*2*J20(F->f2);

	D = J11(F->f1) *J01(F->f2) - 2*J02(F->f1)*J10(F->f2 ) + 
		J10(F->f1) * 2*J02(F->f2 ) - J01(F->f1)*J11(F->f2);

	tj = hypot( C, D );
	C /= tj;
	D /= tj;

	det = A*D - B*C;
	if( det < 0 ){
		A = -A;
		B = -B;
		det = -det;
	}

	zero_jmap23( R1 );
/*
	J10( R1->f1 ) = -D/det;
	J01( R1->f1 ) = -B/det;
	J10( R1->f2 ) = C/det;
	J01( R1->f2 ) = A/det;
*/
	J10( R1->f1 ) = D/det;
	J01( R1->f1 ) = -B/det;
	J10( R1->f2 ) = -C/det;
	J01( R1->f2 ) = A/det;




	C = A*J10(F->f1) + B * J01(F->f1);
	D = A*J10(F->f2) + B * J01(F->f2);
	t = hypot( C, D );
	C /= t;
	D /= t;

/*
	fprintf( stderr, "det: %.4f   a: %.4f   j: %.4f  %.4f\n",
		det, t, tj, tj * sqrt( 2- det*det)/(2*t )  );
*/


	/* it means linear part of L1 is orthogonal */
	zero_jmap23( L1 );
	J10(L1->f1) = C;
	J01(L1->f1) = D;
	J10(L1->f2) = -D;
	J01(L1->f2) = C;


	substit_jmap23( F, R1, &T );

	substit_jmap23( L1, &T, F1 );
}




static void
fold_level_2(jmap23 *F1, jmap23 *R2, jmap23 *L2, jmap23 *F2 )
{
jmap23   T;
vec2d	v;
float	t,	a,	b;

	v.x = J11(F1->f2);
	v.y = 2*J02(F1->f2);

	t = 1.0 / hypot( v.x, v.y );
	v.x *= t;
	v.y *= t;

	a = 1.0/J10(F1->f1);
	b = -v.x/v.y;

	zero_jmap23( R2 );
	J10( R2->f1 ) = 1;
	J01( R2->f1 ) = 0;
	J20( R2->f1 ) = -J20(F1->f1)*a;
	J11( R2->f1 ) = -J11(F1->f1)*a;
	J02( R2->f1 ) = -J02(F1->f1)*a;
	J01( R2->f2 ) = 1.0;




	identity_jmap23( L2 );
	J20(L2->f2) = -J20(F1->f2)*(a*a);


	substit_jmap23( F1, R2, &T );
	substit_jmap23( L2, &T, F2 );
}





static void
fold_level_3(jmap23 *F2, jmap23 *R3, jmap23 *L3, jmap23 *F3 )
{
jmap23   T;
float	a,	b;


	a = 1.0/J10(F2->f1);
	b = 1.0/J02(F2->f2);

	identity_jmap23( R3 );
	J30( R3->f1 ) = -J30(F2->f1)*a;
	J21( R3->f1 ) = -J21(F2->f1)*a;
	J12( R3->f1 ) = -J12(F2->f1)*a;
	J03( R3->f1 ) = -J03(F2->f1)*a;

	J20(R3->f2) = -J21(F2->f2)*0.5*b;
	J11(R3->f2) = -J12(F2->f2)*0.5*b;
	J02(R3->f2) = -J03(F2->f2)*0.5*b;


	identity_jmap23( L3 );
	J30(L3->f2) = -J30(F2->f2)*(a*a*a);

	substit_jmap23( F2, R3, &T );
	substit_jmap23( L3, &T, F3 );
}




void
fold_jmap23_test( jmap23 *F, jmap23 *R, jmap23 *L, float a, float b )
{
jmap23	F1,	F2;
float	a1,	b1;
	substit_jmap23( F, R, &F1 );
	substit_jmap23( L, &F1, &F2 );

	a1 = J10(F2.f1);
	b1 = J02(F2.f2);
}
