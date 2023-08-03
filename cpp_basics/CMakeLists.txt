# Wersja CMake - zostawić jak jest
cmake_minimum_required(VERSION 3.8)
project(cpp_basics)

set(CMAKE_CXX_STANDARD 17)

include_directories(include
        googletest-master/googlemock/include
        googletest-master/googletest/include)

# Tu będą wszystkie pliki .cpp projektu (na razie nie mamy żadnych)
set(SOURCE_FILES
        src/rectangle.cpp)

# Tu będą pliki .cpp używane tylko podczas testów jednostkowych
set(TEST_SOURCES
        test/main_test.cpp
        test/test_rectangle.cpp include/course.hpp src/course.cpp test/test_course.cpp)
#dodaje bibliotekę Google Test, kompiluje ją z użyciem CMakeLists.txt z folderu googletest-master
add_subdirectory(googletest-master)
link_libraries(gmock)

#Tworzy konfigurację o nazwie konfig_run (nazwę możemy dowolnie zmienić)
# do której dołącza plik main.cpp z funkcją main()
add_executable(konfig_run ${SOURCE_FILES} main.cpp)

#Tworzy konfigurację o nazwie konfig_test służącą do uruchamiania testów jednostkowych
add_executable(konfig_test ${SOURCE_FILES} ${TEST_SOURCES})


#add_executable(cpp_basics  src/rectangle.cpp include/rectangle.hpp tests/test_rectangle.cpp tests/main.cpp)
