#ifndef		_LOG_AGP_
#define		_LOG_AGP_

#include	<stdio.h> 

#include	"GpType/GpType.h"



FILE *	log_open( char *file );

void	log_close( FILE *fp );

void	log_gp_to_file( gp_array *agp, char *file );


void	log_gp( FILE *fp, gp_array *agp, int i0, int j0);


void	log_jnt( FILE *fp, jnt_type *jnt );


#endif