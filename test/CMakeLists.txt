find_package(GTest REQUIRED)

add_executable(Tests
        ElementTests.cpp
        DLLTests.cpp
        AVLtests.cpp
)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(Tests
        PRIVATE
        StructuresLib
        GTest::gtest
        GTest::gtest_main
        ${CURSES_LIBRARIES}
)

add_test(
        NAME Tests
        COMMAND Tests
)