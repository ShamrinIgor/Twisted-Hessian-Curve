cmake_minimum_required(VERSION 3.9)

project(TwistedHessianCurve LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/src/cmake")
find_package(GMP REQUIRED)
find_package(NTL REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp src/Point.hpp src/Point.cpp
	src/CurveParams.hpp)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} ${GMP_LIBRARIES} ${NTL_LIBRARY} Threads::Threads)


