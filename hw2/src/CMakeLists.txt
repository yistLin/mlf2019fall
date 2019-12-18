add_library(data_generator DataGenerator.cpp DataGenerator.hpp)
target_include_directories(data_generator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(decision_stump main.cpp)
target_link_libraries(decision_stump LINK_PUBLIC data_generator)
