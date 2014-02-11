#ifndef __IMAGE_NPM_H__
#define __IMAGE_NPM_H__

#ifdef __cplusplus
extern "C" {
#endif


struct image_type;
struct gio_type;
struct cst_type ;



	/* ImageReadNpm.c */
struct image_type *image_read_npm_file( char *file );
struct image_type *image_read_npm_buffer( char *data, int bytes, int Fdata );
struct image_type *image_read_npm( struct gio_type *gio );
	/* ImageWriteNpm.c */
int	image_write_npm( struct image_type *im, char *dir, char *name );
struct cst_type *	image_write_npm_cst( struct image_type *im );


#ifdef __cplusplus
}
#endif
#endif //__IMAGE_NPM_H__
