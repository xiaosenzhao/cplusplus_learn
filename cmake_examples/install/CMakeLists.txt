cmake_minimum_required (VERSION 3.5)
project (cmake_examples_install)

# shared_library
add_library (cmake_examples_inst SHARED src/hello.cpp)
target_include_directories (cmake_examples_inst PUBLIC ${PROJECT_SOURCE_DIR}/include)

# binary
add_executable (cmake_examples_inst_bin src/main.cpp)
target_link_libraries (cmake_examples_inst_bin PRIVATE cmake_examples_inst)

# install
install (TARGETS cmake_examples_inst_bin DESTINATION bin)
install (TARGETS cmake_examples_inst LIBRARY DESTINATION lib)
install (DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)
install (FILES cmake-examples.conf DESTINATION etc)
