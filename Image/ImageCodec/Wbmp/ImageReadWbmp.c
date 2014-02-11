/************************
 *	ImageReadWbmp.c	*
 ************************/

#include	"Uigp/igp.h"

#include	"Ugio/GioType.h"

#include	"ImageType/ImageType.h"
#include	"ImageWbmp.h"


static int image_read_wbmp_int( gio_type *gio );

static void image_read_wbmp_data( gio_type *gio, image_type	*im );


image_type *
image_read_wbmp_file( char *file )
{
gio_type	*gio;
image_type	*im;

	gio = gio_open_file_to_read( file );

	im = image_read_wbmp( gio );

	gio_close( gio );

	return( im );
}


image_type *
image_read_wbmp_buffer( char *data, int bytes, int Fdata )
{
gio_type	*gio;
image_type	*im;

	gio = gio_open_buffer_to_read( data, bytes, Fdata );

	im = image_read_wbmp( gio );

	gio_close( gio );

	return( im );
}


image_type *
image_read_wbmp( gio_type *gio )
{
int			row, col;
image_type	*im;


	GIO_GETC( gio); //wbh.wbhTypeField
	GIO_GETC( gio); //wbh.wbhFixHeaderField

	col = image_read_wbmp_int( gio );
	row = image_read_wbmp_int( gio );

	im = image_create( row, col, 4, 1, 0 );

	image_read_wbmp_data( gio, im );

	return im;
}


static int 
image_read_wbmp_int( gio_type *gio )
{
int val, val_t;

	val = GIO_GETC( gio);
	if ( val & 0x80 )
	{
		val_t = GIO_GETC( gio);
		val = (val_t&0x7F) | ((val&0x7F)<<7);
	}

	return val;
}


static void 
image_read_wbmp_data( gio_type *gio, image_type	*im )
{
int     i, j;
u_int	*p;
u_char  fl_bit,	data;

	p = (u_int *)im->data;

	data = GIO_GETC( gio );
	fl_bit = 0x80;

	for (i = 0; i < IMAGE_ROW( im ) ; i++ )
	{
		for (j = 0; j < IMAGE_COLUMN( im ); j++) 
		{
			if ( !fl_bit )
			{
				data = GIO_GETC( gio );
				fl_bit = 0x80;
			}

			*p++ = (data & fl_bit) ? 0x00FFFFFF : 0;
			fl_bit >>= 1;
		}

		if( fl_bit != 0x80 )
		{
			data = GIO_GETC( gio );
			fl_bit = 0x80;
		}
	}
}

/*
static void 
image_read_wbmp_data1( gio_type *gio, image_type	*im )
{
int		bperlin;
int		i, j, k, ind_col;
int		c;
u_char	fl_bit;
u_int	*p;

	p = (u_int *)im->data;

	bperlin = ((IMAGE_COLUMN( im ) + 7) / 8);

	for (i = 0; i < IMAGE_ROW( im ); i++ ) 
	for (j = 0, ind_col = 0; j < bperlin; j++ ) 
	{
		c = GIO_GETC( gio);
		fl_bit = 0x80;
		for (k = 0; k < 8 && ind_col < IMAGE_COLUMN( im ); 
							k++, p++, ind_col++ ) 
		{
			*p = (c & fl_bit) ? 0x00FFFFFF : 0;
			fl_bit >>= 1;
		}
	}

}
*/