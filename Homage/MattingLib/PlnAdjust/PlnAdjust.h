
#ifndef _PLN_ADJUST_H_
#define _PLN_ADJUST_H_


#include "Uvec/Vec3d.h"
#include "Utime/GpTime.h"

#include "Uln/Cln/ClnType.h"

#include "ImageType/ImageType.h"


	// PlnAdjustStart.cpp
int	plnA_adjust_start( plnA_type *apl, float height );

	// PlnAdjustThin.cpp
int	plnA_adjust_thin( plnA_type *apl, int iFrame );


	// PlnAdjustIn.cpp
int	plnA_adjust_in( plnA_type *apl, plnA_type *bapl, plnA_type *eapl, float dT, int iFrame );


	// PlnAdjustCoherent.cpp
int	pln_coherent( plnA_type *apl, plnA_type *bpl, int height, int iFrame);


	// PlnAdjustEdge.cpp
int	plnA_adjust_edge( plnA_type *apl, plnA_type *eapl, float height, int iFrame );


#endif


