cmake_minimum_required(VERSION 3.10)

project(AOC17 VERSION 1.0)

# compiler arguments
if (MSVC)
   add_compile_options()
else()
   add_compile_options(-Wall -Werror -Wextra -pedantic)
endif()

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# enable interprocedural optimization if availible
if(ENABLE_IPO)
   include(CheckIPOSupported)
   check_ipo_supported( RESULT result OUTPUT output)
   if(result)
      set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
   else()
      message(SEND_ERROR "IPO is not supported: ${output}")
   endif()
endif()

# enable color in diagnortics
if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
   add_compile_options(-fcolor-diagnostics)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
   # require at least gcc 11.1
   if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 11.1)
      message(FATAL_ERROR "GCC version must be at least 11.1!  " ${CMAKE_CXX_COMPILER_VERSION})
   endif()
   add_compile_options(-fdiagnostics-color=always)
else()
   message(STATUS "No colored compiler diagnostic set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
endif()

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
endif()

# Test Results for each day
list(APPEND part_1 1175 50376 552 455 387096 6681 gynfwly 4902 9662 1980 715 283 1588 8140 577 bkgcdefiholnpmja 1244 2951 NDWHOYRUEA 376 144 5462 8281 1695 3745)  
list(APPEND part_2 1166 267 330785 186 28040648 2392 1526 7037 4903 899124dac21012ebc32e2f4d11eaec55 1512 195 3865118 1182 316 knmdfoijcbpghlea 11162912 7366 17540 574 2169301 2512135 911 1673 "")  

enable_testing()

# add utils subdirectory
add_subdirectory(Utils)

# add executable and test each day
foreach(day RANGE 1 25)
   
   # leading zero for single digit days
   if (${day} LESS 10)
      set(day "0${day}")
   endif()

   # set week
   if(day LESS 8)
      set(week 1)
   elseif(day LESS 15)
      set(week 2)
   elseif(day LESS 22)
      set(week 3)
   else()
      set(week 4)
   endif()

   # add each executable
   add_executable(day_${day} ${PROJECT_SOURCE_DIR}/week_${week}/day_${day}/day_${day}.cpp)
   set_target_properties(day_${day} PROPERTIES OUTPUT_NAME "day_${day}")
   target_link_libraries(day_${day} PUBLIC utils)

   # copy input over
   configure_file(${PROJECT_SOURCE_DIR}/week_${week}/day_${day}/input_${day} ${PROJECT_BINARY_DIR}/input_${day} COPYONLY)

   # set output for testing
   math(EXPR index ${day}-1)
   list(GET part_1 ${index} output_1)
   list(GET part_2 ${index} output_2)

   # test results
   add_test(NAME day_${day}_test COMMAND day_${day})
   set_tests_properties(day_${day}_test PROPERTIES PASS_REGULAR_EXPRESSION "${output_1}\n.*${output_2}" TIMEOUT 60)
   
endforeach()
