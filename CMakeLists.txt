cmake_minimum_required(VERSION 3.28)

project(cartpole)

include(CTest)
include(FetchContent)
find_package(Eigen3 3.4 REQUIRED NO_MODULE)
find_package(Boost REQUIRED)

FetchContent_Declare(
    HighFive
    GIT_REPOSITORY https://github.com/highfive-devs/highfive.git
    GIT_TAG v3.3.0
)
FetchContent_MakeAvailable(HighFive)

add_library(cartpole_core src/dynamics.cpp src/simulation.cpp src/adjoint.cpp
    src/functional.cpp
    src/helpers.cpp src/model.cpp
    src/kinematics.cpp
    src/data.cpp
    src/analysis.cpp
    src/discrete_dynamics.cpp
    src/energy.cpp) 

target_compile_features(cartpole_core PUBLIC cxx_std_23)
target_link_libraries(cartpole_core PUBLIC Eigen3::Eigen Boost::headers HighFive::HighFive)

add_executable(cartpole src/main.cpp)
target_link_libraries(cartpole PRIVATE cartpole_core)

target_include_directories(cartpole_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()