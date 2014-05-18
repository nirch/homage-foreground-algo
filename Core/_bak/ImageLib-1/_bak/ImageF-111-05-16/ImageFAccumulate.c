 /*****************************
 ***	ImageFAccumulate.c	***
 *****************************/

#include	"ImageType/ImageType.h"



float 
imagef_accumulate( image_type *sim1, image_type *sim0,
						int x0, int y0, int width, int height )
{
float	*sp0,	*sp1;
int	row,	col,	i,	j;
float	sum;

	row = MIN( IMAGE_ROW(sim0), IMAGE_ROW(sim1) ); 
	col = MIN( IMAGE_COLUMN(sim0), IMAGE_COLUMN(sim1) ); 

	sum = 0;
	for( i = 0 ; i < height ; i++ ){
		sp0 = (float*)IMAGE_PIXEL( sim0, i+y0, x0 );
		sp1 = (float*)IMAGE_PIXEL( sim1, i+y0, x0 );
		for( j = 0 ; j < width ; j++ ){

			sum += (*sp1) * (*sp0);

			sp0++;
			sp1++;
		}
	}

	return( sum/( width * height) );
}



float 
imagef_accumulate_FC( image_type *sim0, image_type *sim1,
						int x0, int y0, int width, int height )
{
float	*sp0;
u_char	*sp1;
int	i,	j;
float	sum;

	sum = 0;
	for( i = 0 ; i < height ; i++ ){
		sp0 = (float*)IMAGE_PIXEL( sim0, i+y0, x0 );
		sp1 = IMAGE_PIXEL( sim1, i+y0, x0 );
		for( j = 0 ; j < width ; j++ ){

			sum += (*sp1) * (*sp0);

			sp0++;
			sp1++;
		}
	}

	return( sum/( width * height) );
}


float 
imagef_accumulateX( image_type *sim1, image_type *sim0,
						int x0, int y0, int width, int height )
{
float	*sp0,	*sp1;
int	row,	col,	i,	j;
float	sum;

	row = MIN( IMAGE_ROW(sim0), IMAGE_ROW(sim1) ); 
	col = MIN( IMAGE_COLUMN(sim0), IMAGE_COLUMN(sim1) ); 

	sum = 0;
	for( i = 0 ; i < height ; i++ ){
		sp0 = (float*)IMAGE_PIXEL( sim0, i+y0, x0 );
		sp1 = (float*)IMAGE_PIXEL( sim1, i+y0, x0 );
		for( j = 0 ; j < width ; j++ ){

			sum += (j+0.5)*(*sp1) * (*sp0);

			sp0++;
			sp1++;
		}
	}

	return( sum/( width * height) );
}


float 
imagef_accumulateY( image_type *sim1, image_type *sim0,
						int x0, int y0, int width, int height )
{
float	*sp0,	*sp1;
int	row,	col,	i,	j;
float	sum,	sum1;

	row = MIN( IMAGE_ROW(sim0), IMAGE_ROW(sim1) ); 
	col = MIN( IMAGE_COLUMN(sim0), IMAGE_COLUMN(sim1) ); 

	sum = 0;
	for( i = 0 ; i < height ; i++ ){
		sp0 = (float*)IMAGE_PIXEL( sim0, i+y0, x0 );
		sp1 = (float*)IMAGE_PIXEL( sim1, i+y0, x0 );

		sum1 = 0;
		for( j = 0 ; j < width ; j++ ){

//			sum += (i+0.5)*(*sp1) * (*sp0);
			sum1 += (*sp1) * (*sp0);

			sp0++;
			sp1++;
		}

		sum += ( i+ 0.5)* sum1;
	}

	return( sum/( width * height) );
}




void 
imagef_accumulate_0_X_Y( image_type *sim1, image_type *sim0,
						int x0, int y0, int width, int height,
						float a[3] )
{
float	*sp0,	*sp1;
int	row,	col,	i,	j;
float	sum,	sumX,	tmp;

	row = MIN( IMAGE_ROW(sim0), IMAGE_ROW(sim1) ); 
	col = MIN( IMAGE_COLUMN(sim0), IMAGE_COLUMN(sim1) ); 

	a[0] = a[1] = a[2] = 0;
	for( i = 0 ; i < height ; i++ ){
		sp0 = (float*)IMAGE_PIXEL( sim0, i+y0, x0 );
		sp1 = (float*)IMAGE_PIXEL( sim1, i+y0, x0 );

		sum = 0;
		sumX = 0;
		for( j = 0 ; j < width ; j++ ){

			tmp = (*sp1) * (*sp0);
			sum += tmp;

//			sumX += (j+0.5) * tmp;
			sumX += j * tmp;

			sp0++;
			sp1++;
		}

		a[0] += sum;
		a[1] += sumX + 0.5 * sum;
		a[2] += ( i+ 0.5)* sum;
	}

	tmp = 1.0 / ( width *height );
	a[0] *= tmp;
	a[1] *= tmp;
	a[2] *= tmp;
}


void 
imagef_accumulate_0_X_Y_XX_XY_YY( image_type *sim1, image_type *sim0,
						int x0, int y0, int width, int height,
						float a[6] )
{
float	*sp0,	*sp1;
float	sum,	sumX,	sumXX,	tmp;
int		i,	j;


	a[0] = a[1] = a[2] = a[3] = a[4] = a[5] = 0;
	for( i = 0 ; i < height ; i++ ){
		sp0 = (float*)IMAGE_PIXEL( sim0, i+y0, x0 );
		sp1 = (float*)IMAGE_PIXEL( sim1, i+y0, x0 );

		sum = 0;
		sumX = 0;
		sumXX = 0;
		for( j = 0 ; j < width ; j++ ){

			tmp = (*sp1) * (*sp0);
			sum += tmp;

//			sumX += (j+0.5) * tmp;
			sumX += j * tmp;
			sumXX += j*j*tmp;
			sp0++;
			sp1++;
		}

		a[0] += sum;
		a[1] += sumX + 0.5 * sum;
		a[2] += ( i+ 0.5)* sum;
		a[3] += sumXX + sumX + 0.25*sum;
		a[4] += ( i + 0.5 )*(sumX + 0.5 * sum);
		a[5] += ( i + 0.5 )*( i + 0.5 ) * sum;
	}

	tmp = 1.0 / ( width *height );
	a[0] *= tmp;
	a[1] *= tmp;
	a[2] *= tmp;
	a[3] *= tmp;
	a[4] *= tmp;
	a[5] *= tmp;
}


float 
imagef_accumulateXX( image_type *sim1, image_type *sim0,
						int x0, int y0, int width, int height )
{
float	*sp0,	*sp1;
int	row,	col,	i,	j;
float	sum;

	row = MIN( IMAGE_ROW(sim0), IMAGE_ROW(sim1) ); 
	col = MIN( IMAGE_COLUMN(sim0), IMAGE_COLUMN(sim1) ); 

	sum = 0;
	for( i = 0 ; i < height ; i++ ){
		sp0 = (float*)IMAGE_PIXEL( sim0, i+y0, x0 );
		sp1 = (float*)IMAGE_PIXEL( sim1, i+y0, x0 );
		for( j = 0 ; j < width ; j++ ){

			sum += (j+0.5)*(j+0.5)*(*sp1) * (*sp0);

			sp0++;
			sp1++;
		}
	}

	return( sum/( width * height) );
}


float 
imagef_accumulateXY( image_type *sim1, image_type *sim0,
						int x0, int y0, int width, int height )
{
float	*sp0,	*sp1;
int	row,	col,	i,	j;
float	sum;

	row = MIN( IMAGE_ROW(sim0), IMAGE_ROW(sim1) ); 
	col = MIN( IMAGE_COLUMN(sim0), IMAGE_COLUMN(sim1) ); 

	sum = 0;
	for( i = 0 ; i < height ; i++ ){
		sp0 = (float*)IMAGE_PIXEL( sim0, i+y0, x0 );
		sp1 = (float*)IMAGE_PIXEL( sim1, i+y0, x0 );
		for( j = 0 ; j < width ; j++ ){

			sum += (i+0.5)*(j+0.5)*(*sp1) * (*sp0);

			sp0++;
			sp1++;
		}
	}

	return( sum/( width * height) );
}


float 
imagef_accumulateYY( image_type *sim1, image_type *sim0,
						int x0, int y0, int width, int height )
{
float	*sp0,	*sp1;
int	row,	col,	i,	j;
float	sum;

	row = MIN( IMAGE_ROW(sim0), IMAGE_ROW(sim1) ); 
	col = MIN( IMAGE_COLUMN(sim0), IMAGE_COLUMN(sim1) ); 

	sum = 0;
	for( i = 0 ; i < height ; i++ ){
		sp0 = (float*)IMAGE_PIXEL( sim0, i+y0, x0 );
		sp1 = (float*)IMAGE_PIXEL( sim1, i+y0, x0 );
		for( j = 0 ; j < width ; j++ ){

			sum += (i+0.5)*(i+0.5)*(*sp1) * (*sp0);

			sp0++;
			sp1++;
		}
	}

	return( sum/( width * height) );
}



/*
float 
image1_ssd( image_type *sim1, image_type *sim0,
						int x0, int y0, int width, int height )
{
u_char	*sp0,	*sp1;
int	row,	col,	i,	j;
float	sum,	tmp;

	row = MIN( IMAGE_ROW(sim0), IMAGE_ROW(sim1) ); 
	col = MIN( IMAGE_COLUMN(sim0), IMAGE_COLUMN(sim1) ); 

	sum = 0;
	for( i = 0 ; i < height ; i++ ){
		sp0 = IMAGE_PIXEL( sim0, i+y0, x0 );
		sp1 = IMAGE_PIXEL( sim1, i+y0, x0 );
		for( j = 0 ; j < width ; j++ ){

			tmp = (int)(*sp1)  - (int) (*sp0);
			sum += tmp*tmp;

			sp0++;
			sp1++;
		}
	}

	return( sum/( width * height) );
}
*/