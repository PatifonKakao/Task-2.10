# задаем набор исходников
set(SOURCES
Threads_Calculator.h
Threads_Calculator.cpp
)

# создаем статическую библиотеку
add_library(Threads_Calculator_lib ${SOURCES})

# добавлем путь к исходникам для возожности подключения библиотеки
target_include_directories(Threads_Calculator_lib PUBLIC ${SRC_ROOT_DIR})

# группируем исходники по типу по категориям
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES})

# В solution эта библиотека лежит в Threads_Calculator_lib
set_property(TARGET Threads_Calculator_lib PROPERTY FOLDER "Threads_Calculator_lib")

# включаем в сборку проекnа подпроект с тестами
add_subdirectory(tests)