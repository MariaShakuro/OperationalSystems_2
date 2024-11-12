# CMakeList.txt: проект CMake для Laba_4; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Laba_4 "Laba_4.cpp" "Laba_4.h")
target_include_directories(Laba_4 PRIVATE ${PROJECT_SOURCE_DIR}/include)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Laba_4 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
