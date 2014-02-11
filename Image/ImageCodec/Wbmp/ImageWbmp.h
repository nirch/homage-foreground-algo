#ifndef __IMAGE_WBMP_H__
#define __IMAGE_WBMP_H__


#ifdef __cplusplus
extern "C" {
#endif

struct image_type;
struct gio_type;
struct cst_type ;



	/* ImageReadWbmap.c */
struct image_type *image_read_wbmp_file( char *file );
struct image_type *image_read_wbmp_buffer( char *data, int bytes, int Fdata );
struct image_type *image_read_wbmp( struct gio_type *gio );
	/* ImageWriteWbmp.c */
int	image_write_wbmp( struct image_type *im, char *dir, char *name );
struct cst_type *	image_write_wbmp_cst( struct image_type *im );


#ifdef __cplusplus
}
#endif

#endif //__IMAGE_WBMP_H__
