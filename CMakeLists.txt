cmake_minimum_required(VERSION 3.16)
project(group_80)

set(CMAKE_CXX_STANDARD 17)

# Enable profiling
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")

# Include directories (for headers)
include_directories(include)

# Manually list all source (.cpp) and header (.h) files
add_executable(group_80
    src/main.cpp
    src/Stock.cpp
    src/StdInReader.cpp
    src/FileReader.cpp
    src/InputWallet.cpp
    src/Strategy.cpp
    src/Wallet.cpp
    src/market_simulator.cpp
)

target_link_libraries(group_80 PRIVATE pthread)
