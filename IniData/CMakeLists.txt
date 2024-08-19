add_library(IniData)

target_sources(
    IniData

    PRIVATE

    IniData.c
    PtrArray.c

    PUBLIC

    IniData.h
    PtrArray.h
)
