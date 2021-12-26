cmake_minimum_required (VERSION 3.22.1)
set (CMAKE_CXX_STANDARD 17)
project (server)

set(OpenCV_DIR /usr/local/Cellar/opencv/4.5.4_1/include/opencv4)
set(MYSQL_DIR  /usr/local/Cellar/mysql-connector-c++/8.0.27)
find_package(OpenCV)
include_directories( ${OpenCV_INCLUDE_DIRS} ${MYSQL_DIR}/include)

add_executable (server main_server.cc server.cc picture_rotation_90_left.cc picture_rotation_90_right.cc mysql_database.cc local_file_repository.cc)

target_link_libraries(server ${OpenCV_LIBS} )
target_link_libraries(server ${MYSQL_DIR}/lib/libmysqlcppconn8.2.8.0.27.dylib )
