HOME_UTIL = /home/users/util
HOME_IMAGE = /home/users/util/ImageLib
 
INCDIR  = -I${HOME_UTIL} \
        -I${HOME_IMAGE} 


OBJ = AgpColor/Obj/obj.o \
	AgpCutout/Obj/obj.o \
	AgpDepth/Obj/obj.o \
	AgpEdit/Obj/obj.o \
	AgpLayer/Obj/obj.o \
	AgpTool/Obj/obj.o \
	Contour/Obj/obj.o \
	Depth/Obj/obj.o \
	EmbedLink/Obj/obj.o \
	Filter/Obj/obj.o \
	GpTool/Obj/obj.o \
	Inf/Obj/obj.o \
	Layer/Obj/obj.o \
	LinkTool/Obj/obj.o \
	Mold/Obj/obj.o \
	N3Aux/Obj/obj.o \
	N3Prime/Obj/obj.o \
	RelValue/Obj/obj.o \
	RlLink/Obj/obj.o



lib:
	dgmake *
	ar rc libagp.a ${OBJ}
	ranlib libagp.a
