add_subdirectory(QR-Code-generator)
add_subdirectory(tinypngout)
set(LIBRARY qrtopng)

file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

add_library(${LIBRARY} STATIC ${SOURCES})
target_include_directories(${LIBRARY} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${LIBRARY} PRIVATE stdc++fs qr-code-generator tinypngoutput)
target_include_directories(${LIBRARY} PUBLIC QR-Code-generator tinypngout)