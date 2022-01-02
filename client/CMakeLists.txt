cmake_minimum_required (VERSION 3.1)
set (CMAKE_CXX_STANDARD 17)
project (client)

add_subdirectory(./libraries/nativefiledialog-extended)

add_executable (client main_client.cc client.cc file_picker_gui.cc file_picker_cmd.cc network_utils.cc)

target_link_libraries(client PRIVATE nfd)
