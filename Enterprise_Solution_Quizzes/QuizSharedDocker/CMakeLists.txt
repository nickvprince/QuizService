cmake_minimum_required(VERSION 3.7)

project(Quiz_webserver_dev)

set(CMAKE_CXX_STANDARD 20)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR your_path_to_mysql_connectorcpp)

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(Threads)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include)
link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib)
add_executable(Quiz_webserver_dev main.cpp)
target_link_libraries(Quiz_webserver_dev ${Boost_LIBRARIES} Threads::Threads)
target_link_libraries(Quiz_webserver_dev curl mysqlcppconn)
target_compile_features(Quiz_webserver_dev PRIVATE cxx_range_for)  
