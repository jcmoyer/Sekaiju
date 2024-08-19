add_library(MIDIClock SHARED)

target_link_libraries(MIDIClock PUBLIC winmm)

target_sources(
    MIDIClock

    PRIVATE

    MIDIClock.c

    PUBLIC

    MIDIClock.h
    MIDIClock.def
)
