/************************
 ***   ImageTarga.c   ***
 ************************/
#include	<stdio.h>
#include	<fcntl.h>
#include 	<memory.h>
#include	<malloc.h>

#include	"Uigp/igp.h"

#include	"ImageType/ImageType.h"

#include	"ImageTarga.h"


#define		INTELL_SHORT( a )  \
		( ( (a & 0xff00) >> 8 ) | ((a & 0x00ff) << 8 ) )

struct	TARGA_HEADER {
	unsigned char	id_length;
	unsigned char	cm_type;
	unsigned char	image_type;
	unsigned char	cm_specification[5];

	short	x;
	short	y;
	short	width;
	short	higth;
	unsigned char	depth;
	unsigned char	descriptor;
};


struct	TARGA_FOOTER {
	int	extension_offset;
	int	developer_offset;
};

static void	set_targa_header( struct  TARGA_HEADER *t,
				int row, int column, int depth );

static int	get_targa_header( struct  TARGA_HEADER *t,
				int *row, int *column, int *depth );

static void 	set_targa_footer( struct  TARGA_FOOTER *f );


static void	image_wirte_targa_data( int fd, image_type *im );
static void	image4_wirte_targa_data( int fd, image_type *im );


static struct	TARGA_FOOTER	Targa_footer = { 0, 0 };

static char	*Targa_signature = "TRUEVISION-XFILE.";

	
// number of bytes written
// -1: could not open output file
int image_write_targa( image_type *im, char *file )
{
//char	file[200];
struct	TARGA_HEADER	T_header;
int	row,	column,	fd;
int bytes;

	//if( dir == NULL )
	//	sprintf( file, "%s.tga", image_name );
	//else	sprintf( file, "%s/%s.tga", dir, image_name );

	if( (fd = open( file , O_WRONLY|O_CREAT, 0644 )) == -1 )
	{
		return -1;
		//error( "image_dump_targa_file", "Can't open tagat file" );
	}

	column = IMAGE_COLUMN( im );
	row = IMAGE_ROW( im );


	set_targa_header( &T_header, row, column, 24 );
	write( fd, (char *)&T_header , sizeof( struct TARGA_HEADER) );



	if( im->depth == 4 )
		image4_wirte_targa_data( fd, im );
	else	image_wirte_targa_data( fd, im );



	write( fd, (char *)&Targa_footer , sizeof( struct TARGA_FOOTER) );

	write( fd, Targa_signature, 18 );


	bytes = tell(fd);
	close( fd );
	return bytes;
}


static void
image_wirte_targa_data( int fd, image_type *im )
{
u_char	*temp,	*sp,	*p;
int	column,	row;
int	i,	j;

	column = IMAGE_COLUMN( im );
	row = IMAGE_ROW( im );

	sp = im->data;
	temp = ( u_char * )malloc( column *3 );
	for( i = 0 ; i < row ; i++, sp += im->pad ){
		for( j = 0 , p = temp ; j < column ; j++ ){
			*p++ = *sp++;
			*p++ = *sp++;
			*p++ = *sp++;
		}
		write( fd, (char *)temp , column*3 );
	}
	free( temp );
}


static void
image4_wirte_targa_data( int fd, image_type *im )
{
u_char	*temp,	*p;
u_int	*sp;
int	column,	row;
int	i,	j;

	column = IMAGE_COLUMN( im );
	row = IMAGE_ROW( im );

	temp = ( u_char * )malloc( column *3 );

	sp = (u_int *)im->data;

	for( i = 0 ; i < row ; i++, sp += im->pad ){
		for( j = 0 , p = temp ; j < column ; j++ ){
/*
			*p++ = (*sp)>>16;
			*p++ = ( (*sp)>>8 ) & 0xff;
			*p++ = (*sp) & 0xff;
*/
                        *p++ = IMAGE4_BLUE( *sp );
                        *p++ = IMAGE4_GREEN( *sp );
                        *p++ = IMAGE4_RED( *sp );

			sp++;
		}
		write( fd, (char *)temp , column*3 );
	}
	free( temp );
}





static void
set_targa_header( struct  TARGA_HEADER *t, int row, int column, int depth )
{
int	i;
	t->id_length = 0;
	t->cm_type = 0;
	t->image_type = (depth == 24 )? 2 : 3;

	for( i = 0 ; i < 5 ; i++  )
		t->cm_specification[i] = 0;

	t->x = 0;
	t->y = 0;

#ifdef WIN32
	t->width = column;
	t->higth = row;
#else
	t->width = INTELL_SHORT( column );
	t->higth = INTELL_SHORT( row );
#endif
	t->depth = depth;

	t->descriptor = 0x20;
}

static int
get_targa_header( struct  TARGA_HEADER *t, int *row, int *column, int *depth )
{
/*
	if( t->descriptor != 0x20 )	return( -1 );
*/

#ifdef  WIN32
	*column = t->width;
	*row = t->higth;
#else
	*column = INTELL_SHORT(t->width );
	*row = INTELL_SHORT( t->higth );
#endif
	*depth = t->depth;
	return(1);
}


static void
set_targa_footer( struct  TARGA_FOOTER *f )
{
	f->extension_offset = 0;
	f->developer_offset = 0;

	/*
	strncpy( f->signature, "TRUEVISION-XFILE.\0", 18 );
	*/
}



image_type *
image_read_targa( char *file )
{
image_type	*im;
//char	file[200];
struct	TARGA_HEADER	T_header;
int	row,	column,	i,	j,	fd,	depth;
u_int   *p;
unsigned char	*temp,	*sp;
int	r,	g,	b;
int	crow;


//	sprintf( file, "%s/%s%s", dir, image_name, extension );

#ifdef WIN32
	if( (fd = open( file, O_RDONLY | O_BINARY, 0644 )) == -1 )
#else
	if( (fd = open( file, O_RDONLY, 0644 )) == -1 )
#endif
		//error( "image_read_targa_file", "Can't open tagat file");
		return NULL;// error opening input file


	read( fd, (char *)&T_header , sizeof( struct TARGA_HEADER) );
	get_targa_header( &T_header, &row, &column, &depth );

	if( depth != 24 ){
		//warning( "image_read_targa_file", "depth != 24" );
#ifdef DEBUG
		printf("Read Targa File: depth != 24\n");
#endif
		return( NULL );
	}


	im = image_create( row, column, 4, 1, 0 );

	temp = ( unsigned char * )malloc( column *3 );

	for( i = 0 ; i < row ; i++ ){
		read( fd, (char *)temp , column*3 );

		crow = ( T_header.descriptor == 0x20 )? i : row -i-1;
		p = IMAGE4_PIXEL( im, crow, 0 );

		for( j = 0 , sp = temp ; j < column ; j++ ){
			b = *sp++;
			g = *sp++;
			r = *sp++;
			*p++ = IMAGE4_RGB( r, g, b );
		}
	}
	free( temp );

	close( fd );


	return( im );
}
