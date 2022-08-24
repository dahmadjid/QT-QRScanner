add_compile_definitions(QT_MESSAGELOGCONTEXT)
ADD_DEFINITIONS( -DCWD=\"${CMAKE_SOURCE_DIR}\" )
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        Logger.cpp
        Benchmark.cpp
        mainwindow.ui
        Capture.cpp
        DetectedQRDialog.cpp
        DetectedQRDialog.ui
)
set(PROJECT_HEADERS 
        mainwindow.h
        Logger.h
        Benchmark.h
        Capture.h
        DetectedQRDialog.h 
)





add_executable(QRScanner
    ${PROJECT_SOURCES} 
    ${PROJECT_HEADERS}
)


target_link_libraries(QRScanner PRIVATE Qt6::Widgets ${OpenCV_LIBS})

set_target_properties(QRScanner PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)