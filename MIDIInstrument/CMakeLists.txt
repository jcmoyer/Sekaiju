add_library(MIDIInstrument)

# MIDIInstrument.c is missing an include for <crtdbg.h>
# This is the least invasive way to work around the problem.
if(MSVC)
    target_compile_options(MIDIInstrument PRIVATE "/FIcrtdbg.h")
else()
    message(WARNING
        "MIDIInstrument.c may need to include <crtdbg.h> on this compiler.")
endif()

target_sources(
    MIDIInstrument

    PRIVATE

    MIDIInstrument.c

    PUBLIC

    MIDIInstrument.h
)
