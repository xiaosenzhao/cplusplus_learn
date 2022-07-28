### install()
```
# install the binary generated from the target camke_examples_inst_bin target to the destination &{CMAKE_INSTALL_PREFIX}/bin
install (TARGETS cmake_examples_inst_bin DESTINATION bin)
```

```
# install the shared library generated from the target cmake_examples_inst target to the destination ${CAMKE_INSTALL_PREFIX}/bin
install (TARGETS cmake_examples_inst LIBRARY DESTINATION lib)
```

```

```
# install the header files for developing from the camke_examples_inst library into the ${CMAKE_INSTALL_PREFIX}/include directory.
install (FILES cmake-examples.conf DESTINATION etc)
```
