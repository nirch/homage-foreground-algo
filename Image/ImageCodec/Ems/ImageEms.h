#ifndef __IMAGE_EMS_H__
#define __IMAGE_EMS_H__

#ifdef __cplusplus
extern "C" {
#endif

struct image_type;
struct gio_type;
struct cst_type ;

	/* ImageReadEms.c */
struct image_type *image_read_ems_file( char *file );
struct image_type *image_read_ems_buffer( char *data, int bytes, int Fdata );
struct image_type *image_read_ems( struct gio_type *gio );
	/* ImageWriteEms.c */


//retCode : 0 : success
//			-1: couldn't open output file
//			-2: error while writing out.
int image_write_ems( struct image_type *im, char *dir, char *name,
							int BitsPerPixel, int Align );
int image_write_ems_file( struct image_type *im, FILE *fp, 
							int BitsPerPixel, int Align);
struct cst_type *image_write_ems_cst( struct image_type *im, 
							int BitsPerPixel, int Align );


#ifdef __cplusplus
}
#endif
#endif //__IMAGE_EMS_H__
