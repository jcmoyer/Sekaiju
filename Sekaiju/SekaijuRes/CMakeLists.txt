# TODO: These appear to compile with the ninja generator, but it doesn't
# generate DLLs. Not sure if cmake bug.

add_library(SekaijuJpn SHARED)
target_sources(SekaijuJpn PRIVATE SekaijuJpn.rc)
target_link_options(SekaijuJpn PRIVATE "/NOENTRY")
target_compile_definitions(SekaijuJpn PRIVATE _UNICODE UNICODE)

add_library(SekaijuEnu SHARED)
target_sources(SekaijuEnu PRIVATE SekaijuEnu.rc)
target_link_options(SekaijuEnu PRIVATE "/NOENTRY")
target_compile_definitions(SekaijuEnu PRIVATE _UNICODE UNICODE)

add_library(SekaijuChs SHARED)
target_sources(SekaijuChs PRIVATE SekaijuChs.rc)
target_link_options(SekaijuChs PRIVATE "/NOENTRY")
target_compile_definitions(SekaijuChs PRIVATE _UNICODE UNICODE)
