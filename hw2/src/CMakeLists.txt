project(MLF_HW2)

add_library(data_generator DataGenerator.cpp DataGenerator.hpp)
target_include_directories(data_generator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(decision_stump main.cpp)
target_link_libraries(decision_stump PRIVATE data_generator)

set_target_properties(decision_stump PROPERTIES CXX_STANDARD 17)
