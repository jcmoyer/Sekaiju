add_library(MIDIClock)

target_link_libraries(MIDIClock PUBLIC winmm)

target_sources(
    MIDIClock

    PRIVATE

    MIDIClock.c

    PUBLIC

    MIDIClock.h
)
