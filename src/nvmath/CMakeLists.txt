PROJECT(nvmath)

SET(MATH_SRCS
	nvmath.h
	Vector.h
	Matrix.h
	Quaternion.h
	Box.h
	Color.h
	Montecarlo.h Montecarlo.cpp
	Random.h Random.cpp
	SphericalHarmonic.h SphericalHarmonic.cpp
	Basis.h Basis.cpp
	Triangle.h Triangle.cpp TriBox.cpp)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

# targets
ADD_DEFINITIONS(-DNVMATH_EXPORTS)

IF(NVMATH_SHARED)
	ADD_LIBRARY(nvmath SHARED ${MATH_SRCS})
ELSE(NVMATH_SHARED)
	ADD_LIBRARY(nvmath ${MATH_SRCS})
ENDIF(NVMATH_SHARED)

TARGET_LINK_LIBRARIES(nvmath ${LIBS} nvcore)
set_target_properties(nvmath PROPERTIES FOLDER "External/nvtt")

if(MSVC)
    # reset default struct packing for MSVC
    target_compile_options(nvmath PRIVATE /Zp8)
endif()
