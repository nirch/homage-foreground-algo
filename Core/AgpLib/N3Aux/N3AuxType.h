/***********************
 ***   N3AuxType.h   ***
 ***********************/

#ifndef		_N3_AUX_TYPE_
#define		_N3_AUX_TYPE_

#include	"GpType/GpType.h"
#include	"Uheap/HeapType.h"

//struct heap_type;

typedef struct in_ntype {	//36 byte
	u_char	type;
	u_char	direct;

	u_char	use;

	// source
	s_char	bno;
	struct jnt_type *jnt;


	//target 
	float	t;
	link_type	*link;
	int	side;
	float	gt;
	struct n3Line_type *nl;


	struct jnt_type *pj;
	struct link_type	*dLink[2];	// for N3AuxLoad:  dLink[F_BEGIN] and dLink[F_END];


	struct in_ntype	*next;
}	in_ntype;




typedef struct n3Line_type {	// 28 byte

	link_type	*link;

	in_ntype	*in[2];

	jnt_type	*jnt;
	int	bno;

	jnt_type	*njnt;
	int	nbno;


//	u_char	flag[2];	// for N3AuxLoad
	struct link_type	*bLink[2];	// for N3AuxLoad: bLink[F_RIGHT] and bLink[F_END];

} n3Line_type;




#define		N3_AUX_VER0		0	// == 0x0007
#define		N3_AUX_VER1		1	// == 0x0007


typedef struct n3Aux_type {	// 24

	int	veriosn;

	int	nLn,	NLn;
	n3Line_type	*ln;


	int	nIn,	NIn;
	in_ntype	*in;


	width_type	*width;
//	heap_type *heap;

}	n3Aux_type;



n3Aux_type *	n3Aux_alloc( int version, int n3_no, int in_no );

void	n3Aux_destroy( n3Aux_type *ra );

void	n3Aux_add_line( n3Aux_type *na, jnt_type *jnt, int bno );


#define	ALLOC_IN_NTYPE( n3aux )	( &n3aux->in[n3aux->nIn++] );

#endif
