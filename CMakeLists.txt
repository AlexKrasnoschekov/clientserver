# CMakeList.txt: проект CMake для clientserver; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("clientserver")
set(SOURCE clientserver.cpp server.cpp client.cpp)
set(HEADER clientserver.h
			constants.h)

find_library(WS2_32_LIBRARY ws2_32)
# Добавьте источник в исполняемый файл этого проекта.
add_executable (clientserver "clientserver.cpp" "clientserver.h")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
