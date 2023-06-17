cmake_minimum_required(VERSION 3.26)

project(systemc_learning)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
	AcceleraSystemC_Rel_2_3_3
  URL https://www.accellera.org/images/downloads/standards/systemc/systemc-2.3.3.tar.gz
  URL_HASH MD5=589d313f3477f42d259607e5dbd316b4
)

FetchContent_MakeAvailable(AcceleraSystemC_Rel_2_3_3)

add_subdirectory(hello_world)
add_subdirectory(module)
add_subdirectory(has_process)
add_subdirectory(simulation_process)
add_subdirectory(simulation_stage)
add_subdirectory(time_notation)
add_subdirectory(concurrency)
add_subdirectory(event)
add_subdirectory(combined_events)
add_subdirectory(delta_cycle)
add_subdirectory(sensitivity)
add_subdirectory(initialization)
add_subdirectory(method)
add_subdirectory(event_queue)
add_subdirectory(event_queue_combined)
