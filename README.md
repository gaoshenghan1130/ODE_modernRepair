# ODE_modernRepair
ode是比较老的运动模型库，采用现代clang和CMake会有许多报错，这里提供一个修复版。

# 编译方法
```bash
cd <your_path_to_ODE_modernRepair>
mkdir build
cd build
cmake ..         # 告诉 CMake 去源码目录生成构建文件
make
sudo make install  # 安装（默认安装到 /usr/local）
```
库的位置就在`usr/local/`,可以直接将编译后的`libode.so`和`include/ode`等复制到你的项目中使用。

# 原版README

[ODE官方文档](./ODE_original_Readme.md)

# 修复内容

- 解决了在现代clang和CMake下编译时的错误（强制修改cmake版本限制）
- 忽略非`static_cast`的类型转换报错，强制转换为警告。