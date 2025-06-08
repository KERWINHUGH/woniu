# 设置最低的 CMake 版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(project)

# 设置 C++ 编译标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")

# 收集源文件
file(GLOB_RECURSE SRCS
    ${CMAKE_SOURCE_DIR}/*.cpp
)

# 生成目标可执行文件
add_executable(${PROJECT_NAME} ${SRCS})

# 设置 CMake 构建输出目录
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# 为了兼容 Makefile 中的 'clean' 命令，CMake 提供 'clean' 目标
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/cmake_clean.cmake
)

# 清理 CMake 构建目录
include_directories(${CMAKE_SOURCE_DIR})
