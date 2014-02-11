/***
***    author:		Yoram Elichai   yorame@gmail.com
***    Copyright (C) 2000 - All Rights Reserved
***/
/******************
 ***  PtLine.h  ***
 ******************/
#ifndef _PT_LINE_
#define _PT_LINE_



#include "Ucamera/Pt2dType.h"



typedef struct pln_type {

	int	i[2];
	int	nP;		// point number;

	vec2f_type	ctr;
	ln_type *link;

	float	len;

} pln_type;





typedef struct plnA_type {
	int	NA;

	int	nA;
	pln_type	*a;

} plnA_type;





void	pln_destroy( pln_type *pl );

int		pln_set( pln_type *pl, vec2f_type *ctr, ln_type *l );


void	pln_inverse( pln_type *pl );

int		pln_create( pln_type *pl, pt2dA_type *apt );

void	pln_trim( pln_type *pl, int direct, float gt );

void	pln_append( pln_type *pl, vec2f_type *ctr, ln_type *link );

void	pln_gt2p( pln_type *pl, float gt, vec2f_type *p );

int		pln_write( pln_type *pl, char *file );



plnA_type *		plnA_alloc( int n );

void	plnA_destroy( plnA_type *am );

int		plnA_decrease( plnA_type *al );

int		plnA_select( plnA_type *am, vec2f_type *v, float dis );




#endif