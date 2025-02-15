add_executable(main main.c framework.c)
add_executable(benchmark benchmark.c framework.c)
target_link_libraries(benchmark libLinkedList)
target_link_libraries(main libLinkedList)