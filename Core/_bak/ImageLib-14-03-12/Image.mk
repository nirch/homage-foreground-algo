LOCAL_PATH := $(call my-dir)
ifeq ($(UNAME),Windows_NT)
LOCAL_PATH := $(call  my-dir)
else
LOCAL_PATH := $(abspath $(call my-dir)/../ImageLib/)
endif


include $(CLEAR_VARS)




LOCAL_C_INCLUDES := $(LOCAL_PATH)/.  $(LOCAL_PATH)/../Util/.

$(info $(LOCAL_C_INCLUDES))

LOCAL_SRC_FILES := 	\
	./Clustring/ImageClustringIsodata.c \
	./Codecs/ImageDecoder.cpp \
	./Codecs/ImageEncoder.cpp \
	./Histogram/Histogram.c \
	./Histogram/HistogramClustringIsoda.c \
	./Histogram/HistogramOrder.c \
	./Image/Image4CopyIn.c \
	./Image/image4From.c \
	./Image/ImageAppend.c \
	./Image/ImageBand.c \
	./Image/ImageCreate.c \
	./Image/ImageCrop.c \
	./Image/ImageDewarpLt2.c \
	./Image/ImageFlipH.c \
	./Image/ImageFlipV.c \
	./Image/ImageInterlive.c \
	./Image/ImageInterpolatePv.c \
	./Image/ImageIo.c \
	./Image/ImageLeak.c \
	./Image/ImageLevel.c \
	./Image/ImageLinearCombination.c \
	./Image/ImageMask.c \
	./Image/ImagePixel.c \
	./Image/ImageToR.c \
	./Image/ImageToY.c \
	./Image1/Image1Average.c \
	./Image1/Image1Bluring.c \
	./Image1/Image1Convolution.c \
	./Image1/Image1ConvolutionM.c \
	./Image1/Image1ConvolutionSeparably.c \
	./Image1/Image1CornerFilter.c \
	./Image1/Image1EqualNeighbor.c \
	./Image1/Image1FilterBox.c \
	./Image1/Image1FilterIir.c \
	./Image1/Image1FisherMatrix.c \
	./Image1/Image1From.c \
	./Image1/Image1Gravity.c \
	./Image1/Image1Histogram.c \
	./Image1/Image1Integral.c \
	./Image1/Image1Interpolate.c \
	./Image1/Image1Majority.c  \
	./Image1/Image1Mask.c \
	./Image1/Image1Median.c \
	./Image1/Image1NoiseEstimation.c \
	./Image1/Image1Pixel.c \
	./Image1/Image1Sample.c \
	./Image1/Image1Sample2.c \
	./Image1/Image1Ssd.c \
	./Image2/Image2Color.c \
	./Image2/Image2DynamicRange.c \
	./Image2/Image2Edge.c \
	./Image2/Image2EdgeSobol.c \
	./Image2/Image2Interpolate.c \
	./Image2/Image2Log.cpp \
	./Image2/Image2Ssd.c \
	./Image3/Image3Bilnear.c \
	./Image3/Image3Bluring.c \
	./Image3/Image3Color.c \
	./Image3/Image3DewarpLt2.c \
	./Image3/Image3Distance.c \
	./Image3/Image3Extend.c \
	./Image3/Image3From.c \
	./Image3/Image3MapTransform.c \
	./Image3/Image3Resize43.c \
	./Image3/Image3Sample2_1331.c \
	./Image3/Image3YCrCb.c \
	./Image6/Image6Convolution.c \
	./Image6/Image6From.c \
	./Image6/Image6Tool.c \
	./Image6/Image6YCrCb.c \
	./ImageApp/ImageApp1.c \
	./ImageApp/ImageApp2.c \
	./ImageApp/ImageAppW.c \
	./ImageC/ImageCTool.c \
	./ImageF/ImageAFEigen.cpp \
	./ImageF/ImageFAccumulate.c \
	./ImageF/ImageFArithmetic.cpp \
	./ImageF/ImageFDensity.c \
	./ImageF/ImageFDynamicRange.c \
	./ImageF/ImagefFilterBox.cpp \
	./ImageF/ImageFHistogram.c \
	./ImageF/ImageFLog.cpp \
	./ImageF/ImageFMedian.c \
	./ImageF/ImageFPyramid.c \
	./ImageF/ImageFResizeBilinear.c \
	./ImageF/ImageFYCrCb.c \
	./ImageLabel/Image1Blob.c \
	./ImageLabel/Image1Label.c \
	./ImageLabel/Image1LabelInletFilter.c \
	./ImageLabel/Image2BwLabel.c \
	./ImageMark/ImageDraw.c \
	./ImageMark/ImagePrint.c \
	./ImageResize/ImageResample.c \
	./ImageResize/ImageResize.c \
	./ImageResize/ImageResizeBilinear.c \
	./ImageResize/ImageResizeIpp.c \
	./ImageResize/imageSample.c \
	./ImageResize/imageSampleColumn.c \
	./ImageResize/ImageSampleDown.c \
	./ImageResize/ImageSampleDownTransparent.c \
	./ImageResize/ImageSampleG.c \
	./ImageResize/ImageSampleNew.c \
	./ImageResize/ImageSamplingF.c \
	./ImageTransform/Image3KLTransform.c \
	./ImageUS/ImageUSInterpolate.c \
	./ImageUS/ImageUSInterpolateV.c \
	./ImageUS/ImageUSTool.c \
	./VegetationIndex/ImageExG.c \
	./VegetationIndex/ImageNdi.c \
	./VegetationIndex/ImageNdrgi.c \
	./VegetationIndex/ImageNdrgiF.c \
	BMP/BmpDecoder.cpp \
	BMP/BmpEncoder.cpp \
	BMP/ImageReadBmp.c \
	BMP/ImageWriteBmp.c \
	Dithering/ImageDitherAll.c \
	Dithering/ImageDitherErr.c \
	Dithering/ImageDitherErrExp.c \
	Dithering/ImageDitherFloyd.c \
	Dithering/ImageDitherOrd.c \
	Dithering/ImageDitherPat.c \
	Dithering/ImageEnhancement.c \
	Dithering/ImageGrayEnhancement.c \
	Gif/GifDecoder.cpp \
	Gif/GifEncoder.cpp \
	Gif/ImageReadGif.c \
	Gif/ImageReadGifFrame.c \
	Gif/ImageWriteGif.c \
	Gif/LzwEncoding.c \
	Image/Guasian.c \
	Image/Image.c \
	Image/Image4to1.c \
	Image/Image4Tool.c \
	Image/ImageAdaptivePalette.c \
	Image/ImageAdd.c \
	Image/ImageAlpha.c \
	Image/ImageAux.c \
	Image/ImageBackgroundRemoval.c \
	Image/ImageComparison.c \
	Image/ImageCut.c \
	Image/ImageCutUarray.c \
	Image/ImageDifference.c \
	Image/ImageEqual.cpp \
	Image/ImageExtend.c \
	Image/ImageFields.c \
	Image/ImageFile.c \
	Image/ImageHistogram.c \
	Image/ImageHsiTune.c \
	Image/ImageLogo.c \
	Image/ImageNegative.c \
	Image/ImagePreview.c \
	Image/ImagePyramid.c \
	Image/ImageRgbYCrCb.c \
	Image/ImageRgbYiq.c \
	Image/ImageSline.c \
	Image/ImageSmartPalette.c \
	Image/ImageStretch.c \
	Image/ImageSubtruct.c \
	Image/ImageTransparent.c \
	Image/PaletteTool.c \
	Image1/Image1EdgeSobol.c \
	Image1/Image1Tool.c \
	Image2/Image2Accumulate.c \
	Image2/Image2Bilateral.c \
	Image2/Image2Convolution.c \
	Image2/Image2Derivative.c \
	Image2/Image2Pyramid.c \
	Image2/Image2Tool.c \
	Image24To8/Image24To8.c \
	Image24To8/Image24To8DitherFloyd.c \
	Image24To8/Image8to24.c \
	Image3/Image3Convolution.c \
	Image3/Image3DynamicRange.c \
	Image3/Image3Tool.c \
	ImageApp/ImageApp.c \
	ImageDump/ImageDump.c \
	ImageF/ImageFConvolution.c \
	ImageF/ImageFTool.c \
	ImageTransform/ImageDct.c \
	ImageTransform/ImageDct88.c \
	ImageTransform/ImageFFT.c \
	ImageTransform/ImageFourier.c \
	PSD/ImageReadPSD.c \
	PSD/PsdRead.c \
	PSD/PsdTool.c \
	PSD/PsdWrite.c \
	YUV/Image2YUV.cpp \
	YUV/ImageReadYuv.c \
	YUV/ImageYUVSampling.c
	
					
					
LOCAL_CFLAGS := -w
					
					
LOCAL_MODULE := Image

#$(info "Building Static Library")
include $(BUILD_STATIC_LIBRARY)

