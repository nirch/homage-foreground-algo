#ifndef _TF_TYPE_
#define _TF_TYPE_

//#ifdef __cplusplus
//extern "C" {
//#endif


#define TF_MAX	32


typedef struct	tf_type {
	int	iFrame;

	int	nA;
	float	a[TF_MAX];

} tf_type;


typedef struct tfA_type {

	union {
		int	NT;
		int NA;
	};

	union {
		int	nT;
		int	nA;
	};

	union {
		tf_type	**t;
		tf_type	**a;
	};


}	tfA_type;


tf_type *	tf_alloc( int nT );

tf_type *	tf_copy( tf_type *stf, tf_type *tf );



void	tf_destroy( tf_type *tf );

void	tf_clear( tf_type *t );


int	tfA_nearest( tf_type *tf, float a0, float T );



tfA_type *	tfA_alloc( int no );

void	tfA_destroy( tfA_type *aS );


void	tfA_clear( tfA_type *aS );

tfA_type *	tfA_copy( tfA_type *as, tfA_type *at );


int	tfA_write( tfA_type *aS, char *file );


tfA_type *	tfA_read( char *file );


tf_type *	tfA_average( tfA_type *tfA );


tfA_type *	tfA_transform( tfA_type *stfA, struct matrix_type *m );


void	tfA_set( tfA_type *tfA, int iFrame, float a[], int nA );


int	tfA_get( tfA_type *tfA, int iFrame, float a[], int *nA );

tf_type *	tfA_get( tfA_type *tfA, int iFrame );

int	tfA_range( tfA_type *atf, int *i0, int *i1 );


	// TfMean.cpp
int	tfA_mean( tfA_type *tfA, float T, float *av, float *var, int aI[] );



//#ifdef __cplusplus
//}
//#endif


#endif

