# CMake generated Testfile for 
# Source directory: D:/Labs 2 grade/OC/Laba_1/Laba1
# Build directory: D:/Labs 2 grade/OC/Laba_1/Laba1/out/build/x64-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ReporterTest "D:/Labs 2 grade/OC/Laba_1/Laba1/out/build/x64-debug/Reporter/Reporter.exe" "input.bin" "output" "10.0")
set_tests_properties(ReporterTest PROPERTIES  _BACKTRACE_TRIPLES "D:/Labs 2 grade/OC/Laba_1/Laba1/CMakeLists.txt;27;add_test;D:/Labs 2 grade/OC/Laba_1/Laba1/CMakeLists.txt;0;")
subdirs("tests")
subdirs("Main")
subdirs("Creator")
subdirs("Reporter")
