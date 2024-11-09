# Включаем поддержку тестирования
#enable_testing()


# Добавление исполняемых файлов для тестов
#add_executable(test_main test_main.cpp)



#add_executable(test_creator test_creator.cpp)
#add_test(NAME CreatorTest COMMAND test_main)


#add_executable(test_reporter test_reporter.cpp)
#add_test(NAME test_reporter COMMAND test_reporter)

# Подключите библиотеки Google Test
#target_link_libraries(test_main GTest::gtest_main)
# Добавьте тесты в CTest
#include(GoogleTest)
#gtest_discover_tests(test_main)