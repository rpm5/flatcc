include_directories (
    "${PROJECT_SOURCE_DIR}/include"
)

set(SOURCES
    builder.c
    emitter.c
    verifier.c
    json_parser.c
    json_printer.c
)

add_library(flatccrt SHARED ${SOURCES})
add_library(flatccrt-static STATIC ${SOURCES})

if (FLATCC_INSTALL)
    install(TARGETS flatccrt DESTINATION lib${LIB_SUFFIX})
endif()
