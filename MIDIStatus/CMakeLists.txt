add_library(MIDIStatus SHARED)

target_sources(
    MIDIStatus

    PRIVATE

    MIDIStatus.c

    PUBLIC

    MIDIStatus.h
    MIDIStatus.def
)
