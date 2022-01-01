add_executable(ruletti "ruletti.cpp")

if(MSVC)
	set_target_properties(ruletti PROPERTIES LINK_FLAGS "/MANIFESTUAC:\"level='highestAvailable'\"")
	set_property(TARGET ruletti PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()