add_library(IniData SHARED)

target_sources(
    IniData

    PRIVATE

    IniData.c
    PtrArray.c

    PUBLIC

    IniData.h
    PtrArray.h
    IniData.def
)
