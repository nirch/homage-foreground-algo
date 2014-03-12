/***
***    author:		Yoram Elichai   yorame@gmail.com
***    Copyright (C) 2000 - All Rights Reserved
***/
#ifndef         _HISTOGRAM_
#define         _HISTOGRAM_


#ifdef __cplusplus
extern "C" {
#endif

#include	"Uigp/igp.h"


	// Histogram.c
void	histogram_range( int h[], int nH, float p0, float p1, float *r0, float *r1 );

void	histogram_write( int h[], int nH, char *file );


	// HistogramOrder.c
int		histogram_order( int H[], int nH, int a[] );


	// HistogramClustrringIsodata.c
void	histogram_clustring_isodata( int H[], int nH, int K, int nT, float vT, float mT, int Itration, float am[], int *nM );


#ifdef __cplusplus
}
#endif

#endif
