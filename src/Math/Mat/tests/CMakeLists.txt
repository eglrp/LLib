cmake_minimum_required(VERSION 2.8)

project(math_mat_unittest)

add_definitions(-std=c++11)

enable_testing()
find_package(GTest REQUIRED)

# http://www.thebitbangtheory.com/2011/11/how-to-openmp-cmake/
find_package(OpenMP REQUIRED)
if(OPENMP_FOUND)  
message("OPENMP FOUND")  
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")  
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")  
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")  
endif()  

# https://github.com/AndiH/CMake/tree/master/CMake%2BCUDA
find_package(CUDA REQUIRED)
set(CUDA_NVCC_FLAGS -gencode arch=compute_52,code=sm_52;-G;-g)

add_executable(math_mat_unittest test_mat.cpp
                                 mat22_unittest.cpp
                                 mat33_unittest.cpp
                                 mat44_unittest.cpp
                                 matX_unittest.cpp)

target_link_libraries(math_mat_unittest GTest::GTest GTest::Main)
