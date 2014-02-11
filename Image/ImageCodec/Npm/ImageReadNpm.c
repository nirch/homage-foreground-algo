/************************
 *	ImageReadNpm.c	*
 ************************/


#include	"Uigp/igp.h"

#include	"Ugio/GioType.h"

#include	"ImageType/ImageType.h"
#include	"ImageNpm.h"


image_type *
image_read_npm_file( char *file )
{
gio_type	*gio;
image_type	*im;

	gio = gio_open_file_to_read( file );

	im = image_read_npm( gio );

	gio_close( gio );

	return( im );
}


image_type *
image_read_npm_buffer( char *data, int bytes, int Fdata )
{
gio_type	*gio;
image_type	*im;

	gio = gio_open_buffer_to_read( data, bytes, Fdata );

	im = image_read_npm( gio );

	gio_close( gio );

	return( im );
}


image_type *
image_read_npm( gio_type *gio )
{
image_type	*im;
int			i, j;
u_int		*p;
u_char		fl_bit,	data;

	im = image_create( 28, 72, 4, 1, 0 );

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

			*p++ = (data & fl_bit) ? 0 : 0x00FFFFFF;
			fl_bit >>= 1;
		}

		if( fl_bit != 0x80 )
		{
			data = GIO_GETC( gio );
			fl_bit = 0x80;
		}
	}

	return im;
}

/*
image_type *
image_read_npm1( gio_type *gio )
{
image_type	*im;
int			i, j, k;
int			c;
u_char		fl_bit;
u_int		*p;

	im = image_create( 28, 72, 4, 1, 0 );

	p = (u_int *)im->data;

	for (i = 0; i < 28; i++ ) 
	for (j = 0; j < 9; j++ ) 
	{
		c = GIO_GETC( gio);
		fl_bit = 0x80;
		for (k = 0; k < 8; k++, p++ ) 
		{
			*p = (c & fl_bit) ? 0 : 0x00FFFFFF;
			fl_bit >>= 1;
		}
	}

	return( im );
}
*/