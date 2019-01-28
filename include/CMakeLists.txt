add_library(clrs INTERFACE)
add_library(clrs::clrs ALIAS clrs)
target_include_directories(clrs
  INTERFACE
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
# TODO: Try to pull dependency usage requirements through Conan.
target_compile_features(clrs PUBLIC cxx_std_11)
