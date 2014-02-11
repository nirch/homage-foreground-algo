#ifndef __IMAGE_TARGA_H__
#define __IMAGE_TARGA_H__

#ifdef __cplusplus
extern "C" {
#endif


image_type *	image_read_targa( char *file );

int image_write_targa( image_type *im, char *file );

#ifdef __cplusplus
}
#endif

#endif //__IMAGE_WBMP_H__
