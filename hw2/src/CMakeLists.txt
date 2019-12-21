add_library(data_generator STATIC DataGenerator.cpp DataGenerator.hpp Data.hpp)
target_include_directories(data_generator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(decision_stump main.cpp)
target_link_libraries(decision_stump data_generator)
