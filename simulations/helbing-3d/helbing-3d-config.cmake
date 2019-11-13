include(${CMAKE_CURRENT_LIST_DIR}/helbing-3d-targets.cmake)
get_filename_component(HELBING-3D_INCLUDE_DIR1 "${CMAKE_CURRENT_LIST_DIR}/../../include/" ABSOLUTE)
get_filename_component(HELBING-3D_INCLUDE_DIR2 "${CMAKE_CURRENT_LIST_DIR}/../../include/helbing-3d/" ABSOLUTE)
set(HELBING-3D_INCLUDE_DIRS ${HELBING-3D_INCLUDE_DIR1} ${HELBING-3D_INCLUDE_DIR2})
include_directories(${HELBING-3D_INCLUDE_DIRS})
set(HELBING-3D_LIBRARIES helbing-3d)