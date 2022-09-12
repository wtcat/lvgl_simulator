static_library(mtracer)

include_dirs(tracer/include)
target_sources(mtracer
	PRIVATE
	empty.c
)
library_link(mtracer 
	${CMAKE_CURRENT_SOURCE_DIR}/tracer/tracer.lib)