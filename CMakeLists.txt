cmake_minimum_required(VERSION 3.20)

project(order-ci-demo VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTING "Build tests" ON)

add_library(orders
  src/OrderService.cpp
  src/LivePaymentGateway.cpp
)

target_include_directories(orders PUBLIC include)
target_compile_options(orders PRIVATE -Wall -Wextra -Wpedantic)

add_executable(order_app app/main.cpp)
target_link_libraries(order_app PRIVATE orders)

if(BUILD_TESTING)
  include(CTest)
  enable_testing()

  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  )
  set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  add_executable(order_service_test
    tests/OrderServiceTests.cpp
  )
  target_include_directories(order_service_test PRIVATE include tests)
  target_link_libraries(order_service_test PRIVATE orders GTest::gtest_main GTest::gmock)
  target_compile_options(order_service_test PRIVATE -Wall -Wextra -Wpedantic)

  include(GoogleTest)
  gtest_discover_tests(order_service_test)
endif()
