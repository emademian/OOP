cmake_minimum_required(VERSION 3.21)
project(lab10_11)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(lab10_11 main.cpp GUI.cpp GUI.h ActiuneUndo.cpp ActiuneUndo.h Console.cpp Console.h Locatar.cpp Locatar.h LocatarRepo.cpp LocatarRepo.h LocatarService.cpp LocatarService.h Notificare.h Notificare.cpp Teste.cpp Teste.h Validator.cpp Validator.h UndoStergere.h UndoAdaugare.cpp UndoAdaugare.h UndoModificare.cpp UndoModificare.h UndoStergere.cpp FileRepo.cpp FileRepo.h locatar.txt Observer.h cmake-build-debug/locatar.jpg MyTableModel.h)
target_link_libraries(lab10_11
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )
set(CMAKE_OSX_ARCHITECTURES  x86_64)

