/*******************
 *** LnWrite.c   ***
 *******************/

#include	<string.h>

#include	"PlnType.h"


static void	pln_write_1( pln_type *pl, FILE *fp );

int
pln_write( pln_type *aPl[], int nPl, char *file )
{
FILE	*fp;
int	i;


	if( (fp = fopen( file, "wb")) == NULL )
		return( -1 );




	fprintf( fp, "transform\n" );
	fprintf( fp, "%.6f  %.6f  %.6f\n", 0.0,0.0, 1.0 );

	for( i = 0 ; i < nPl ; i++ ){
		pln_write_1( aPl[i], fp );
	}

	fclose( fp );

	return( 1 );

}


static void
pln_write_1(pln_type *pl, FILE *fp )
{
ln_type	*l;
int	no;




	no = lnL_no( pl->link );

	fprintf( fp, "polylink\n" );
	fprintf( fp, "%d   %d   %d\n", no, 0, 0 );
	fprintf( fp, "%.6f  %.6f\n", pl->ctr.x, pl->ctr.y );




	for( l = pl->link ;  l != NULL ; l = LN_NEXT(l) )
			fprintf( fp, "%.6f  %.6f  %.6f\n", l->v.x, l->v.y, l->a );
}



void	
pln_dump( pln_type *aPl[], int nPl, char *prefix, int index, char *suffix )
{
	char	file[256];

	if( gpDump_filename( prefix, index, suffix, ".ctr", file ) < 0 )
		return;


	pln_write( aPl, nPl, file );
}