cmake_minimum_required(VERSION 3.5)
project(Stream)

set(SRC)
set(INCL)
set(COMPILE_OPTION)
set(LINKLIBS)

list(APPEND INCL
  lib/asio/include
  /usr/local/include/opencv4
  )

list(APPEND SRC
  client.cpp 
 )

list(APPEND LINKLIBS
  pthread
  ${PROJECT_SOURCE_DIR}/lib/opencv4/libopencv_core.so.4.3.0
  ${PROJECT_SOURCE_DIR}/lib/opencv4/libopencv_highgui.so.4.3.0
  ${PROJECT_SOURCE_DIR}/lib/opencv4/libopencv_imgcodecs.so.4.3.0

 )

list(APPEND COMPILE_OPTION
  -O3
  -std=c++14
  )

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME}	PRIVATE	${INCL}  )
target_link_libraries(${PROJECT_NAME} ${LINKLIBS})
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTION} )
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

