add_library(dataloader STATIC DataLoader.cpp DataLoader.hpp)
target_include_directories(dataloader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(regressor STATIC Regressor.cpp Regressor.hpp)
target_include_directories(regressor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test test.cpp)
target_link_libraries(test dataloader regressor)

add_executable(problem7 main.cpp)
target_compile_definitions(problem7 PUBLIC PROBLEM7)
target_link_libraries(problem7 dataloader regressor)

add_executable(problem8 main.cpp)
target_compile_definitions(problem8 PUBLIC PROBLEM8)
target_link_libraries(problem8 dataloader regressor)
