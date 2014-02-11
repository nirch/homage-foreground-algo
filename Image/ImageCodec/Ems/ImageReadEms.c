/************************
 *	ImageReadEms.c	*
 ************************/

#include	"Uigp/igp.h"

#include	"Ugio/GioType.h"

#include	"ImageType/ImageType.h"
#include	"ImageEms.h"


static void image_read_ems_data( gio_type *gio, image_type	*im );


image_type *
image_read_ems_file( char *file )
{
gio_type	*gio;
image_type	*im;

	gio = gio_open_file_to_read( file );

	im = image_read_ems( gio );

	gio_close( gio );

	return( im );
}


image_type *
image_read_ems_buffer( char *data, int bytes, int Fdata )
{
gio_type	*gio;
image_type	*im;

	gio = gio_open_buffer_to_read( data, bytes, Fdata );

	im = image_read_ems( gio );

	gio_close( gio );

	return( im );
}


image_type *
image_read_ems( gio_type *gio )
{
long        length;
int			row, col;
image_type	*im;


	length = gio_bytes( gio );

	GIO_GETC( gio); 

	if ( length == 33 )
		row = col = 16;
	else if ( length == 129 )
		row = col = 32;
	else
		return NULL;

	im = image_create( row, col, 4, 1, 0 );

	image_read_ems_data( gio, im );

	return im;
}


static void 
image_read_ems_data( gio_type *gio, image_type	*im )
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

		/*Align
		if( fl_bit != 0x80 )
		{
			data = GIO_GETC( gio );
			fl_bit = 0x80;
		}*/
	}
}


