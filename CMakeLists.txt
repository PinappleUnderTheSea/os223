set(PLUGIN_NAME "helloworld")
project(${PLUGIN_NAME})

set(SRCS src/helloworldplugin.cpp)

# 载入Qt基础库
find_package(Qt5 REQUIRE COMPONENT Core Widgets)
#载入控制中心开发库
find_package(DdeControlCenter REQUIRED)

# 设置动态库的名称、类型,shared是动态库。
add_library(${PLUGIN_NAME} SHARED ${SRCS})
# 设置项目需要的访问的头文件，这里是控制中心的插件头文件
target_include_directories(${PLUGIN_NAME} PUBLIC ${DdeControlCenter_INCLUDE_DIR})
# 设置项目链接的依赖，这里是Qt和控制中心的控件动态库
target_link_libraries(${PLUGIN_NAME} PRIVATE
${DdeControlCenter_LIBRARIES})

install(TARGETS ${PLUGIN_NAME} LIBRARY DESTINATION lib/dde-control-center/plugins/)