# CMakeList.txt: ������ CMake ��� Laba_4; �������� �������� ��� � �����������,
# ������� ����� ������ ��� ����������� �������.
#

# �������� �������� � ����������� ���� ����� �������.
add_executable (Sender "Sender.cpp" "Sender.h")
target_include_directories(Sender PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Sender PRIVATE ${PROJECT_SOURCE_DIR}/include)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Sender PROPERTY CXX_STANDARD 20)
endif()

# TODO: �������� ����� � ������� �������, ���� ��� ����������.