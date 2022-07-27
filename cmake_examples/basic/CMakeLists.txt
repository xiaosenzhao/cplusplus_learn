# cmake 最低版本号要求
cmake_minimum_required (VERSION 3.5)

#项目信息
project (Demo)

#指定c++版本
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED True)

#指定源文件
set (SOURCES src/main.cc src/MathFuncitons.cc)

#指定生成目标
add_executable (Demo ${SOURCES})

#指定头文件路径
target_include_directories (Demo PRIVATE ${PROJECT_SOURCE_DIR}/include)
