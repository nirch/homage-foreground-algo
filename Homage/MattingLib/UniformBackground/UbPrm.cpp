#include	<string.h>
#include "Uigp/igp.h"

#include "Uxml/XmlType.h"

#include "UniformBackground.h"




ubPrm_type *
ubPrm_alloc()
{
	ubPrm_type *prm;

	prm = (ubPrm_type *)malloc( sizeof(ubPrm_type) );

	prm->thin = 0;

	prm->fillBlob = 120*120;

//	prm->adjustContour = 0;

	prm->dx = 8;
	prm->av = 4;

	prm->enableEdge = 1;

	prm->in_d = 50;

	return( prm );
}

void
ubPrm_destroy( ubPrm_type *prm )
{
	free( prm );
}



int
CUniformBackground::ReadPrm( char *inFile )
{
	xml_type *xmlDoc;
	xmlTag_type *pTag,	*tag;



	if((xmlDoc = xml_parse_file(  inFile )) == NULL ){
		fprintf( stdout, "Reading %s  failed\n", inFile );
		return( -1 );
	}


	pTag = xmlTag_get_tag( xmlDoc->root, "UniformBackgroundPrm" );
	if( pTag == NULL ){
		xml_destroy(xmlDoc);
		return( -1 );
	}



	if( m_prm == NULL )
		m_prm = ubPrm_alloc();



	for( tag = pTag->firstChild ; tag != NULL ; tag = tag->next ){


		if ( (gp_stricmp(tag->name, "thin") == 0) ){
			m_prm->thin = atoi( tag->data );

			continue;
		}

		if ( (gp_stricmp(tag->name, "FillBlob") == 0) ){
			m_prm->fillBlob = atoi( tag->data );

			continue;
		}

		//if ( (gp_stricmp(tag->name, "AdjustContour") == 0) ){
		//	m_prm->adjustContour = atoi( tag->data );

		//	continue;
		//}

		if ( (gp_stricmp(tag->name, "Background-Dx") == 0) ){
			m_prm->dx = atoi( tag->data );

			continue;
		}

		if ( (gp_stricmp(tag->name, "Background-Av") == 0) ){
			m_prm->av = atoi( tag->data );

			continue;
		}

		if ( (gp_stricmp(tag->name, "Enable-Edge") == 0) ){
			m_prm->enableEdge = atoi( tag->data );
			continue;
		}

		if ( (gp_stricmp(tag->name, "Contour-In-D") == 0) ){
			m_prm->in_d = atof( tag->data );
			continue;
		}
	}



	xml_destroy(xmlDoc);


	fprintf( stdout, "Reading %s\n", inFile );

	return( 1 );
}
