#ifndef		_AGP_COLOR_
#define		_AGP_COLOR_

#include        "Uigp/igp.h"
#include        "GpType/GpType.h"
#include		"ImageType/PaletteType.h"

#ifdef __cplusplus
extern "C" {
#endif


	/* AgpYCrCbRgb.c */
void	agp_YCrCb_Rgb( gp_array *agp );


	/* AgpRgbYCrCb.c */
void	agp_Rgb_YCrCb( gp_array *agp );


	/* AgpGrbRgb.c */
void	agp_Grb_Rgb( gp_array *agp );

	/* AgpRgbRange.c */
void	agp_rgb_range( gp_array *agp, int Fval );




	/* AgpColorF.c */
void    agp_color_F( gp_array *agp, box2d *box, vec2d *p, int step_no );


	// AgpColorFN.c
void	agp_color_FN( gp_array *agp, vec2d *p, box2d *box,
				int op, int Fprofile, int color[] );


	/* AgpRgbY.c */
void	agp_Rgb_Y( gp_array *agp );


	/* AgpChangeProfile.c */
void	agp_change_profile( gp_array *agp, qcolor_type *deltaC, float scale );

int		agp_get_extrem_gistogram( gp_array *agp );


	/* AgpAdaptivePalette.c */
void	agp_adaptive_palette( gp_array *agp[], int nAgp,
							palette_type *palette, int nColor );



#ifdef __cplusplus
}
#endif

#endif
