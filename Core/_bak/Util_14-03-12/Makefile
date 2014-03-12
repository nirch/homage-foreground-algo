HOME_UTIL = /home/users/util
HOME_IMAGE = /home/users/util/ImageLib
 
INCDIR  = -I${HOME_UTIL} \
        -I${HOME_IMAGE} 


OBJ =	Ubox/Obj/obj.o \
	Ubst/Obj/obj.o \
	Ucfg/Obj/obj.o \
	Ucode/Obj/obj.o \
	Uconfig3d/Obj/obj.o \
	Ucst/Obj/obj.o \
	UGeoApp/Obj/obj.o \	
	Ugio/Obj/obj.o \
	Uheap/Obj/obj.o \
	Uigp/Obj/obj.o \
	Uinf/Obj/obj.o \
	Ujet1/Obj/obj.o \
	Ujet2/Obj/obj.o \
	Ulz/Obj/obj.o \
	Utime/Obj/obj.o \
	Umat/Obj/obj.o \
	Uunity/Obj/obj.o \
	UZlib/Obj/obj.o \
	Uvec/Obj/obj.o \
	Ufbst/Obj/obj.o \	
	Uprm/Obj/obj.o \
	Uxml/Obj/obj.o \
	Uview/Obj/obj.o \
	Usynch/Obj/obj.o \
	Umedia/Obj/obj.o \
	Usmil/Obj/obj.o \
	Ujni/Obj/obj.o

#Udir/Obj/obj.o

 




lib:
	dgmake *
	ar rc libutil.a ${OBJ}
	ranlib libutil.a
