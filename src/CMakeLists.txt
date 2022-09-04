add_compile_definitions(QT_MESSAGELOGCONTEXT)
# add_compile_definitions(SCALED_DOWN)

if (WIN32)
add_compile_definitions(WINDOWS)
else()
add_compile_definitions(LINUX)
endif()

add_compile_options(-Wall -Wextra -Wpedantic)
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        Logger.cpp
        Benchmark.cpp
        Capture.cpp
        DetectedQRDialog.cpp
        Dropdown.cpp 
        # EmailToolDialog.cpp
        CSVParser.cpp
)
set(PROJECT_HEADERS 
        mainwindow.h
        Logger.h
        Benchmark.h
        Capture.h
        DetectedQRDialog.h 
        Dropdown.h 
        # EmailToolDialog.h
        CSVParser.h
        )



set(PROJECT_FORMS 
        mainwindow.ui
        DetectedQRDialog.ui
        Dropdown.ui
        # EmailToolDialog.ui
)

add_executable(QRScanner
    ${PROJECT_SOURCES} 
    ${PROJECT_HEADERS}
    ${PROJECT_FORMS}
)


target_link_libraries(QRScanner PRIVATE Qt6::Widgets ${OpenCV_LIBS}) # qrtopng)
set_target_properties(QRScanner PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)



