cmake_minimum_required (VERSION 3.5)
project (hello_library)

# create a library
add_library (hello_library SHARED src/hello.cpp)
# 重命名
# add_library (hello::library ALIAS hello_library)

target_include_directories (hello_library PUBLIC  ${PROJECT_SOURCE_DIR}/include)

# bin
add_executable (hello_binary src/main.cpp)
target_link_libraries (hello_binary PRIVATE hello::library)
