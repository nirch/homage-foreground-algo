/****************************
 ***	Configuration.h   ***
 ****************************/
#ifndef	 _VIM_CONFIGURATION_
#define	 _VIM_CONFIGURATION_





#ifdef TRIUM

#define	PDA
//#define CE
#define	COLOR_GRAY

//#define	DEPTH_DELTA

/* if define 1 bgp_type in each gp_type instead 4 */
#define	SINGLE_BGP

//#define		FLIP

//#define		SOUND


//#define	IMAGE_BACKGROUND



#define	QSHORT
//#define	QFLOAT



#define PLAYER



//#define	N3




#elif defined (IPAQ) || defined (CASIO) || defined (__SYMBIAN32__)
ccccc
#define	PDA
//#define	DEPTH_DELTA
//#define VERSION_0005


/* if define 1 bgp_type in each gp_type instead 4 */
#define	SINGLE_BGP

//#define		FLIP

//#define		SOUND


//#define	IMAGE_BACKGROUND



#define	QSHORT
//#define	QFLOAT



#define PLAYER


#define	VIM_CONST_EXAPND_TABLE



//#define	N3


#elif defined (PCPLAYER)


//#define	DEPTH_DELTA


/* if define 1 bgp_type in each gp_type instead 4 */
#define	SINGLE_BGP

//#define		FLIP

//#define		SOUND


//#define	IMAGE_BACKGROUND



#define	QSHORT
//#define	QFLOAT



#define PLAYER



//#define	N3


#elif defined (_VIM_ST)


//#define VERSION_0005

#define	DEPTH_DELTA

/* if define 1 bgp_type in each gp_type instead 4 */
//#define	SINGLE_BGP

#define		FLIP

#define		SOUND


//#define	IMAGE_BACKGROUND


#define	QSHORT
//#define	QFLOAT



//#define PLAYER



//#define	N3
#else

#define LIN

#define VERSION_0005

#define	DEPTH_DELTA

/* if define 1 bgp_type in each gp_type instead 4 */
//#define	SINGLE_BGP

#define		FLIP

#define		SOUND


//#define	IMAGE_BACKGROUND



#define	QSHORT
//#define	QFLOAT



//#define PLAYER



//#define	N3
#define	LS
#define REANDER_PLW

#define	BFRAME

#endif


#define	VIM_RELINQUISH
 
#endif
