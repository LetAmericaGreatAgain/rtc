cmake_minimum_required(VERSION 3.29)
project(rtc)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(/utf-8)

add_library(ffm_rtc SHARED RtcManager.cpp WebSocketHelper.cpp WebSocketHelper.h DataChannelListener.cpp
        DataChannelListener.h IceModel.cpp IceModel.h ffm_rtc.cpp ffm_rtc.h)

target_include_directories(ffm_rtc PRIVATE "D:/clib/libdatachannel/include")

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(ffm_rtc nlohmann_json::nlohmann_json)

target_link_libraries(ffm_rtc "E:/CLionProjects/test/rtc/lib/datachannel.lib")


add_executable(rtc main.cpp)

target_link_libraries(rtc "E:/CLionProjects/test/rtc/lib/ffm_rtc.lib")
