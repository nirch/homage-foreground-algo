INCDIR  = -I${HOME_CORE}/Util \
		-I${HOME_CORE}/ImageLib \
		-I${HOME_AUDIO}/AudioLib 


OBJ =	VideoDecoder.o \
		VideoEncoder.o \
		VideoStreamEncoder.o \
		AudioStreamEncoder.o


lib: ${OBJ}	
	ar rc libVideoCodec.a ${OBJ}
	ranlib libVideoCodec.a 
