/***
***    author:		Yoram Elichai   yorame@gmail.com
***    Copyright (C) 2000 - All Rights Reserved
***/
/*******************
 ***   Box2d.h   ***
 *******************/


#ifndef         BOX2D_TYPE
#define         BOX2D_TYPE

#ifdef __cplusplus
extern "C" {
#endif


#include	<stdio.h>

#include	"Uvec/Vec2d.h"



typedef struct box2f_type {

	union {
		struct {
			float	x0;
			float	y0;
		};

		vec2f_type	p0;
	};


	union {
		struct {
			float	x1;
			float	y1;
		};

		vec2f_type	p1;
	};

} box2f_type ;


typedef box2f_type box2d ;




typedef struct box2d_type {

	union {
		struct {
			double	x0;
			double	y0;
		};

		vec2d_type	p0;
	};


	union {
		struct {
			double	x1;
			double	y1;
		};

		vec2d_type	p1;
	};

} box2d_type ;



typedef struct box2i {
	int	x0,	x1;
	int	y0,	y1;
} box2i ;



typedef struct rect_type {
	int	x0,	x1;
	int	y0,	y1;
}	rect_type;



#define		BOX2D_SET( b, xmin, ymin, xmax, ymax ) \
			{ \
				(b).x0 = xmin;	\
			    	(b).x1 = xmax;	\
			    	(b).y0 = ymin;	\
			    	(b).y1 = ymax;	\
			}

#define         BOX2D_INIT( b, x, y ) \
			{ \
				(b).x0 = (b).x1 = x;	\
			   	(b).y0 = (b).y1 = y;	\
			}


#define		BOX2D_COPY( sb, b ) \
{ \
	(b).x0 = (sb).x0;	\
	(b).x1 = (sb).x1;	\
	(b).y0 = (sb).y0;	\
	(b).y1 = (sb).y1;	\
}


#define         BOX2D_UPDATE( b, x, y ) \
			{ \
				if( x < (b).x0 )	(b).x0 = x; \
				else	if( x > (b).x1 )        (b).x1 = x; \
				if( y < (b).y0 )	(b).y0 = y; \
				else	if( y > (b).y1 )        (b).y1 = y; \
			}


#define         BOX2D_UPDATE_BOX( b, b1 ) \
{ \
				if( (b1).x0 < (b).x0 )	(b).x0 = (b1).x0; \
				if( (b1).y0 < (b).y0 )	(b).y0 = (b1).y0; \
				if( (b1).x1 > (b).x1 )	(b).x1 = (b1).x1; \
				if( (b1).y1 > (b).y1 )	(b).y1 = (b1).y1; \
}


#define         BOX2D_IS_IN( b, vx, vy ) \
			(	vx >= (b).x0 && vx <= (b).x1  &&  \
				vy >= (b).y0 && vy <= (b).y1 )

#define         BOX2D_IS_IN_O( b, vx, vy ) \
			(	vx > (b).x0 && vx < (b).x1  &&  \
				vy > (b).y0 && vy < (b).y1 )


#define		BOX2D_SWAP( sb, b ) \
			{ \
				(b).x0 = (sb).y0;	\
				(b).x1 = (sb).y1;	\
				(b).y0 = (sb).x0;	\
				(b).y1 = (sb).x1;	\
			}



#define		BOX2D_IS_BOX_IN( b, b1 )	(  BOX2D_IS_IN( b, (b1).x0, (b1).y0 ) && \
											BOX2D_IS_IN( b, (b1).x1, (b1).y1 ) )


#define         BOX2D_IS_EQUAL( b, b1 )  \
						( b.x0 == b1.x0 && b.y0 == b1.y0 && b.x1 == b1.x1 && b.y1 == b1.y1)


#define		BOX_WIDTH( b )	( b->x1 - b->x0)
#define		BOX_HEIGHT( b )	( b->y1 - b->y0)



box2d *box2d_alloc();

	/* Box2Tool.c */
int	box2_segment( box2d *b, vec2d *p, vec2d *p1, int Fp1,
						vec2d *v0, vec2d *v1 );


void	box_shift( box2d *b, float a, float y );

void	box_update( box2d *b, box2d *b1 );

void	box2d_union( box2d ab[], int no, box2d *b );

void	box2d_round( box2d *b );

//return positive value if the box are separate and negative value for intersect 
float	box2d_distance( box2d *b, box2d *b1 );


int	box2d_read_from_file( char *file, box2d *b );


	/* Box2iTool.c */
int		box2i_select( box2i *b, int select_t, int x, int y );

void	box2i_set( box2i *b, box2d *box, float margin );

void	box2i_crop( box2i *b, int x0, int y0, int x1, int y1 );

void	box2i_extend( box2i *b, int margin );

void	box2i_extendI( box2i *b, int margin, int width, int height );


void	box2i_translate( box2i *b, int x, int y );


int	box2i_read( FILE *fp, box2i *b );

int	box2i_write( FILE *fp, box2i *b );

int	box2i_read_from_file( char *file, box2i *lb, box2i *gb );

int	box2i_write_to_file( char *file, box2i *lb, box2i *gb );


void	box2iA_dump( box2i ab[], int nB, char *prefix, int index, char *suffix );
void	box2fA_dump( box2f_type ab[], int nB, char *prefix, int index, char *suffix );


void	box2iA_remove_in( box2i ab[], int *nB );


#ifdef __cplusplus
}
#endif

#endif
