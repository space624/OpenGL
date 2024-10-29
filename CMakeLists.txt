# 版本
cmake_minimum_required(VERSION 3.12)

# 项目名称
project(OpenGL)

# C++版本
set(CMAKE_CXX_STANDARD 17)

add_definitions (-DDEBUG)
#set(EXECUTABLE_OUTPUT_PATH ../)

#拷贝资源路径都放到ASSETS中
file(GLOB ASSETS "./assets")
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

# 找glfw的头文件
include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/include)

#找glfw库
link_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/lib)


add_subdirectory(wrapper)
add_subdirectory(application)
add_subdirectory(glframework)

# 所有cpp,放入srcs变量中
#aux_source_directory(. SRCS)

# 编译链接生成exe
add_executable(glStudy "main.cpp" "glad.c" "application/application.cpp")

#链接
#target_link_libraries(glStudy glfw3.lib wrapper)
target_link_libraries(glStudy glfw3.lib wrapper app fw)
