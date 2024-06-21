PROJECT(nvtt)

ADD_SUBDIRECTORY(squish)

SET(NVTT_SRCS
	nvtt.h 
	nvtt.cpp
	Compressor.h
	Compressor.cpp
	nvtt_wrapper.h
	nvtt_wrapper.cpp
	CompressDXT.h
	CompressDXT.cpp
	CompressRGB.h
	CompressRGB.cpp
	QuickCompressDXT.h
	QuickCompressDXT.cpp
	OptimalCompressDXT.h
	OptimalCompressDXT.cpp
	SingleColorLookup.h
	CompressionOptions.h
	CompressionOptions.cpp
	InputOptions.h
	InputOptions.cpp
	OutputOptions.h
	OutputOptions.cpp
	cuda/CudaUtils.h
	cuda/CudaUtils.cpp
	cuda/CudaMath.h
	cuda/Bitmaps.h
	cuda/CudaCompressDXT.h
	cuda/CudaCompressDXT.cpp)

IF(CUDA_FOUND)
	ADD_DEFINITIONS(-DHAVE_CUDA)
	WRAP_CUDA(CUDA_SRCS cuda/CompressKernel.cu)
	SET(NVTT_SRCS ${NVTT_SRCS} ${CUDA_SRCS})
	SET(LIBS ${LIBS} ${CUDA_LIBRARIES})
	INCLUDE_DIRECTORIES(${CUDA_INCLUDE_PATH})
ENDIF(CUDA_FOUND)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

ADD_DEFINITIONS(-DNVTT_EXPORTS)

IF(NVTT_SHARED)
	ADD_DEFINITIONS(-DNVTT_SHARED=1)
	ADD_LIBRARY(nvtt SHARED ${NVTT_SRCS})
ELSE(NVTT_SHARED)
	ADD_LIBRARY(nvtt ${NVTT_SRCS})
ENDIF(NVTT_SHARED)

TARGET_LINK_LIBRARIES(nvtt ${LIBS} nvcore nvmath nvimage squish)
set_target_properties(nvtt PROPERTIES FOLDER "External/nvtt")

if(MSVC)
    # reset default struct packing for MSVC
    target_compile_options(nvtt PRIVATE /Zp8)
endif()

# copy nvtt dll into correct Binaries folder
IF(NVTT_SHARED)
	add_custom_command(TARGET nvtt POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:nvtt> ${UNREAL_BINARIES_DIRECTORY}/nvtt${CMAKE_SHARED_LIBRARY_SUFFIX}
		COMMENT "Copying nvtt dll to UNREAL_BINARIES_DIRECTORY" VERBATIM
	)
ENDIF()