cmake_minimum_required(VERSION 2.8)

project(image-detect CXX)

# static library
find_package(OpenCV REQUIRED)
add_library(image-detect-static STATIC lib/src/image-detect.cpp)
target_include_directories(image-detect-static PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/include)
target_compile_options(image-detect-static PRIVATE --std=c++11)
target_link_libraries(image-detect-static ${OpenCV_LIBS})
set_target_properties(image-detect-static PROPERTIES OUTPUT_NAME image-detect)

# static shared
find_package(OpenCV REQUIRED)
add_library(image-detect-shared SHARED lib/src/image-detect.cpp)
target_include_directories(image-detect-shared PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/include)
target_compile_options(image-detect-shared PRIVATE --std=c++11)
target_link_libraries(image-detect-shared ${OpenCV_LIBS})
set_target_properties(image-detect-shared PROPERTIES OUTPUT_NAME image-detect)

# project
find_package(OpenCV REQUIRED)
add_executable(image-detect-bin main.cpp)
target_include_directories(image-detect-bin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/include)
target_compile_options(image-detect-bin PRIVATE --std=c++11)
target_link_libraries(image-detect-bin image-detect-static)
target_link_libraries(image-detect-bin ${OpenCV_LIBS})
set_target_properties(image-detect-bin PROPERTIES OUTPUT_NAME image-detect)