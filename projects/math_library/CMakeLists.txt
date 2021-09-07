#--------------------------------------------------------------------------
# math_library project
#--------------------------------------------------------------------------

PROJECT(math_library)
FILE(GLOB math_library_headers code/*.h)
FILE(GLOB math_library_sources code/*.cc)

SET(files_math_library ${math_library_headers} ${math_library_sources})
SOURCE_GROUP("math_library" FILES ${files_math_library})

ADD_EXECUTABLE(math_library ${files_math_library})
TARGET_LINK_LIBRARIES(math_library core render)
ADD_DEPENDENCIES(math_library core render)