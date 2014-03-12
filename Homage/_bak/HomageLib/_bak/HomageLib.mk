LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES :=   $(LOCAL_PATH)/../../VimGui/.  $(LOCAL_PATH)/../../Core/Util/.

LOCAL_SRC_FILES := 	\
	VimMove.cpp


LOCAL_CFLAGS := -w

LOCAL_MODULE := VimMoveLib\VimMoveLib.vcxproj

#$(info "Building Static Library")

include $(BUILD_STATIC_LIBRARY)

