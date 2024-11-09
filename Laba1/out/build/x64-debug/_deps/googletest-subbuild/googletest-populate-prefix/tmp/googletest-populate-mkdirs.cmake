# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Labs 2 grade/OC/Laba_1/Laba1/out/build/x64-debug/_deps/googletest-src"
  "D:/Labs 2 grade/OC/Laba_1/Laba1/out/build/x64-debug/_deps/googletest-build"
  "D:/Labs 2 grade/OC/Laba_1/Laba1/out/build/x64-debug/_deps/googletest-subbuild/googletest-populate-prefix"
  "D:/Labs 2 grade/OC/Laba_1/Laba1/out/build/x64-debug/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "D:/Labs 2 grade/OC/Laba_1/Laba1/out/build/x64-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "D:/Labs 2 grade/OC/Laba_1/Laba1/out/build/x64-debug/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "D:/Labs 2 grade/OC/Laba_1/Laba1/out/build/x64-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Labs 2 grade/OC/Laba_1/Laba1/out/build/x64-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Labs 2 grade/OC/Laba_1/Laba1/out/build/x64-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
