include(FetchContent)

cmake_minimum_required(VERSION 3.21)
project(retro-chat)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(retro-chat src/main.cpp include/chat.h include/network_system.h include/user.h)
# add_executable(retro-chat-client src/client.cpp include/chat.h include/network_system.h include/user.h)

# ----------------FETCHING DEPS----------------
# FETCHING: fmt
message(STATUS "FetchContent: fmt")
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG master
)
FetchContent_MakeAvailable(fmt)

target_include_directories(fmt INTERFACE ${fmt_SOURCE_DIR}/include)

# FETCHING: cxxopts
message(STATUS "FetchContent: cxxopts")
FetchContent_Declare(
        cxxopts
        GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
        GIT_TAG master
)
FetchContent_MakeAvailable(cxxopts)

target_include_directories(cxxopts INTERFACE ${cxxopts_SOURCE_DIR}/include)

# ----------------ADDING DEPS----------------
find_package(Boost 1.40.0 REQUIRED system)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

target_link_libraries(retro-chat fmt cxxopts ${Boost_SYSTEM_LIBRARY} ${Boost_ASIO_LIBRARY})
# target_link_libraries(retro-chat-client fmt cxxopts ${Boost_SYSTEM_LIBRARY} ${Boost_ASIO_LIBRARY})

# execute_process (COMMAND bash -c "pkg-config --cflags boost" OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE libs_cflags)
# execute_process (COMMAND bash -c "pkg-config --libs boost" OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE libs_linker_flags)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fsanitize=address -fno-optimize-sibling-calls")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${libs_linker_flags}")