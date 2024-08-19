add_library(MIDIIO SHARED)

target_link_libraries(MIDIIO PUBLIC winmm)

target_sources(
    MIDIIO

    PRIVATE

    MIDIIO.c

    PUBLIC

    MIDIIO.h
    MIDIIO.def
)
