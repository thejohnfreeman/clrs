add_library(clrs INTERFACE)
add_library(clrs::clrs ALIAS clrs)
target_include_directories(clrs
  INTERFACE
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
