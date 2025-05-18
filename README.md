# ODE_modernRepair
ode是比较老的运动模型库，采用现代clang和CMake会有许多报错，这里提供一个修复版。

# 编译方法
```
cd <your_path_to_ODE_modernRepair>
mkdir build
cd build
cmake ..         # 告诉 CMake 去源码目录生成构建文件
make
sudo make install  # 安装（默认安装到 /usr/local）
