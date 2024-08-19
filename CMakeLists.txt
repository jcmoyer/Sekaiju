cmake_minimum_required(VERSION 3.28)

project(Sekaiju)

add_subdirectory("MIDIIO")
add_subdirectory("MIDIData")
add_subdirectory("MIDIClock")
add_subdirectory("MIDIStatus")
add_subdirectory("MIDIInstrument")
add_subdirectory("IniData")
add_subdirectory("Sekaiju")

install(
    TARGETS
    Sekaiju
    # Dependencies
    MIDIIO MIDIData MIDIClock MIDIStatus MIDIInstrument IniData
    # Resources
    SekaijuJpn SekaijuEnu SekaijuChs
    DESTINATION .
)

install(
    DIRECTORY
    Sekaiju/instrument
    DESTINATION .
)

install(
    FILES
    Sekaiju/Sekaiju.ini
    DESTINATION .
)
