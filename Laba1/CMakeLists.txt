# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)

include_directories(${PROJECT_SOURCE_DIR}/include)
# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Laba1")

# Включаем поддержку тестирования
include(CTest)

# Подключите Google Test
#include(FetchContent)
#FetchContent_Declare(
 # googletest
#)
#FetchContent_MakeAvailable(googletest)

# Включаем поддержку тестирования
enable_testing()
add_test(NAME ReporterTest COMMAND Reporter input.bin output 10.0)




# Включаем поддиректорию с тестами
add_subdirectory(tests)
# Включите подпроекты.
add_subdirectory(Main)
add_subdirectory(Creator)
add_subdirectory(Reporter)









