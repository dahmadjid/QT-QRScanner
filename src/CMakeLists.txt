add_compile_definitions(QT_MESSAGELOGCONTEXT)
ADD_DEFINITIONS( -DCWD=\"${CMAKE_SOURCE_DIR}\" )
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

target_include_directories(QRScanner PUBLIC /home/madjid/Codes/qt/qtbase-dev/include/ 
                /home/madjid/Codes/qt/qtbase-dev/include/QtWidgets/
                /home/madjid/Codes/qt/qtbase-dev/include/QtCore/
                /home/madjid/Codes/qt/qtbase-dev/include/QtGui/)


target_link_libraries(QRScanner PRIVATE ${OpenCV_LIBS} /home/madjid/Codes/qt/qtbase-dev/lib/libQt6Core.a
/home/madjid/Codes/qt/qtbase-dev/lib/libQt6Gui.a
/home/madjid/Codes/qt/qtbase-dev/lib/libQt6Widgets.a
glib-2.0) # qrtopng)
set_target_properties(QRScanner PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)



