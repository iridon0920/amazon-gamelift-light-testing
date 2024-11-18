cmake_minimum_required(VERSION 3.22)
project(amazon_gamelift_light_testing)

set(CMAKE_CXX_STANDARD 20)

# 環境変数の存在確認
if(DEFINED ENV{GAMELIFT_SDK_PATH})
    set(GAMELIFT_SDK_PATH $ENV{GAMELIFT_SDK_PATH})
else()
    message(FATAL_ERROR "GAMELIFT_SDK_PATH環境変数が設定されていません。GameLift SDKのパスを設定してください。")
endif()

# パスの存在確認
if(NOT EXISTS ${GAMELIFT_SDK_PATH})
    message(FATAL_ERROR "GameLift SDKがこのパスに存在しません: ${GAMELIFT_SDK_PATH}")
endif()
set(GAMELIFT_SDK_PATH "/mnt/c/Users/irii.keita/Documents/dev/GameLift-Cpp-ServerSDK-5.1.3/cmake-build/prefix")

include_directories(${GAMELIFT_SDK_PATH}/include)
link_directories(${GAMELIFT_SDK_PATH}/lib)

add_executable(amazon_gamelift_light_testing main.cpp)
target_link_libraries(amazon_gamelift_light_testing PRIVATE aws-cpp-sdk-gamelift-server)

find_package(OpenSSL REQUIRED)
target_link_libraries(amazon_gamelift_light_testing PRIVATE OpenSSL::SSL OpenSSL::Crypto)