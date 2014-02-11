/**************************
 ***	EmbedLink.h	***
 **************************/

#ifndef         EMBED_LINK
#define         EMBED_LINK


#include	"GpType/GpType.h"

#include        "RlLink/RlType.h"



	/* EmbedLink.c */
void	embed_link_get_prm(GP_prm **prm, int *prm_no, void (**check)() );

void	embed_link( vec2d *ctr, link_type *link, gp_array *agp );




	/* EmbedHunch */

void	embed_links_hunch( vec2d actr[], link_type *alink[], int link_no,
					gp_array *agp );

void	embed_link_hunch( vec2d *ctr, link_type *link,  gp_array *agp );




	/* EmbedLinkFit.c */
void	embed_link_fit( gp_array *agp );

	// EmbedFitJnt.c
void	embed_link_fit_jnt( gp_array *agp );

int		embed_link_fit_remove_short_polylink( gp_array *agp );



	// EmbedFitBorder.c
void	embed_link_fit_border( gp_array *agp );

	/* EmbedLinkFitCurve.c */
void	embed_link_fit_curve( gp_array *agp );

#endif
