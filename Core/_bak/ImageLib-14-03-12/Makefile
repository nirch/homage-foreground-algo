HOME_UTIL = /home/users/util
HOME_IMAGE = /home/users/util/ImageLib
 
INCDIR  = -I${HOME_UTIL} \
        -I${HOME_IMAGE} 


OBJ =	Image/Obj/obj.o \
	Dithering/Obj/obj.o \
	ImageIo/Obj/obj.o \
	Image24To8/Obj/obj.o \
	ImageTransform/Obj/obj.o \
	Gif/Obj/obj.o \
	Jpeg/Obj/obj.o \
	Png/Obj/obj.o \
	Bmp/Obj/obj.o \
	EMS/Obj/obj.o \
	NPM/Obj/obj.o \
	WBMP/Obj/obj.o \
	Mng/Obj/obj.o \
	TARGA/Obj/obj.o \
	YUV/Obj/obj.o \
	PSD/Obj/obj.o \
	Codecs/Obj/obj.o



#obj: ${OBJ}
#	ld -r ${OBJ}   -o Obj/obj.o


lib:
	dgmake *
	ar rc libimage.a ${OBJ}
	ranlib libimage.a
