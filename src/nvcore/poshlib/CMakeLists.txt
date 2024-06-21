
SET(POSHLIB_SRCS
	posh.c
	posh.h)

ADD_LIBRARY(posh STATIC ${POSHLIB_SRCS})
set_target_properties(posh PROPERTIES FOLDER "External/nvtt")

if(MSVC)
    # reset default struct packing for MSVC
    target_compile_options(posh PRIVATE /Zp8)
endif()