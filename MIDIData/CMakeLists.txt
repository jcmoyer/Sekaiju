add_library(MIDIData SHARED)

target_sources(
    MIDIData

    PRIVATE

    MIDIData.c

    PUBLIC

    MIDIData.h
    MIDIData.def
)
