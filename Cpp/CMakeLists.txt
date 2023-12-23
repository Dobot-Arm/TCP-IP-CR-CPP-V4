# 指定 CMake 的最低版本
cmake_minimum_required(VERSION 3.0)

# 设置项目的名称
project(DobotTcpDemo)

# 启用 C++11 标准
set(CMAKE_CXX_STANDARD 14)
add_compile_options(-std=c++14)
# 设置构建类型为 Realease
set(CMAKE_BUILD_TYPE Realease)


# 添加可执行文件，并指定源文件
add_executable(DobotTcpDemo main.cpp DobotTcpDemo.cpp api/BitConverter.cpp api/Dashboard.cpp api/DobotClient.cpp api/ErrorInfoBean.cpp api/ErrorInfoHelper.cpp api/Feedback.cpp)

# 链接线程库
find_package(Threads REQUIRED)
target_link_libraries(DobotTcpDemo Threads::Threads)