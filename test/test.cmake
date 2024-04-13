
# get dir list
file(GLOB TEST_LIST RELATIVE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/*)
foreach(test ${TEST_LIST})
  if(IS_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${test})
    add_executable(${test} ${CMAKE_CURRENT_LIST_DIR}/${test}/${test}.cpp)
    add_test(NAME ${test} COMMAND ${test})
  endif()
endforeach()
