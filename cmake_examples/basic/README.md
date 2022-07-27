### 构建
```shell
mkdir build && cd build
cmake ..
make VERBOSE=1
```

### 清理
```
rm -rf build
```

CMakeLists.txt 的语法比较简单，由命令、注释和空格组成，其中命令是不区分大小写的。符号 # 后面的内容被认为是注释。命令由命令名称、小括号和参数组成，参数之间使用空格进行间隔。
`cmake_minimum_required`: 指定运行此配置文件所需的 CMake 的最低版本；
`project`: 项目名称
`add_executable`: 可执行文件

