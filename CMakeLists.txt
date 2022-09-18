cmake_minimum_required(VERSION 3.10)

find_package(Boost REQUIRED system)

add_executable(server server.cpp)
add_executable(client client.cpp)

target_link_libraries(server PUBLIC ${Boost_LIBRARIES})
target_link_libraries(client PUBLIC ${Boost_LIBRARIES})

target_include_directories(server PUBLIC ${Boost_INCLUDE_DIRS})
target_include_directories(client PUBLIC ${Boost_INCLUDE_DIRS})

