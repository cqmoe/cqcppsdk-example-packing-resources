cmake_minimum_required(VERSION 3.9)
project(cqcppsdk-example-packing-resources)

set(CMAKE_CXX_STANDARD 17)

include(extern/cqcppsdk/cqcppsdk.cmake)

file(READ "app_id.txt" APP_ID)
string(STRIP "${APP_ID}" APP_ID)
cq_set_app_id(${APP_ID})

include_directories(res src)

cq_add_std_app(src/main.cpp res/resource.rc)
cq_install_std_app()
