cmake_minimum_required(VERSION 3.5)
project(Stream)

set(SRC)
set(INCL)
set(COMPILE_OPTION)
set(LINKLIBS)

list(APPEND INCL
  lib/asio/include
  )

list(APPEND SRC

 )

list(APPEND LINKLIBS
  pthread
 )

list(APPEND COMPILE_OPTION
  -O3
  -std=c++14
  )

add_executable(${PROJECT_NAME} client.cpp ${SRC})

target_include_directories(${PROJECT_NAME}	PRIVATE	${INCL}  )
target_link_libraries(${PROJECT_NAME} ${LINKLIBS})
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTION} )
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

