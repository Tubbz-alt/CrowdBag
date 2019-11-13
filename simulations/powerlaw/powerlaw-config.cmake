include(${CMAKE_CURRENT_LIST_DIR}/powerlaw-targets.cmake)
get_filename_component(POWERLAW_INCLUDE_DIR1 "${CMAKE_CURRENT_LIST_DIR}/../../include/" ABSOLUTE)
get_filename_component(POWERLAW_INCLUDE_DIR2 "${CMAKE_CURRENT_LIST_DIR}/../../include/powerlaw/" ABSOLUTE)
set(POWERLAW_INCLUDE_DIRS ${POWERLAW_INCLUDE_DIR1} ${POWERLAW_INCLUDE_DIR2})
include_directories(${POWERLAW_INCLUDE_DIRS})
set(POWERLAW_LIBRARIES powerlaw)
