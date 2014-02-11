#ifndef         _VIM_FILE_
#define         _VIM_FILE_


/* vim_file.type        */
#define         VF_NORMAL       0
#define         VF_AUX          1
#define         VF_SKL          2       /* skl int sparete file */
#define         VF_UNUION       3       /* object are union of .vim file */
 
#define         VF_CONST        8       /* const color backgrond */ 



typedef struct vim_file { 

	int	type;

	char	file[256];

	int	no;	/* index in  file .vim */

	int	byte;

}	vim_file;


#define		VIM_FILE_ALLOC()	((vim_file *)malloc( sizeof(vim_file) ))




#endif
