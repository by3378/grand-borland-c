cmake_minimum_required( VERSION 3.10 )
project( cksdriver LANGUAGES C )

set(SOURCES 
    driver.c
    calculate.c
    file.c
    ar.c
    queue.c
    gene.c
)

include_directories(${CMAKE_SOURCE_DIR})

add_executable( driver ${SOURCES})


set_target_properties(driver PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)