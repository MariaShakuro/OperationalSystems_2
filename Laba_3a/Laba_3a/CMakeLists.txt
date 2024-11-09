# CMakeList.txt: проект CMake для Laba_3a; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Laba_3a "Laba_3a.cpp" "Laba_3a.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Laba_3a PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
