cmake_minimum_required(VERSION 3.21)

file(READ cupcake.json metadata)
string(JSON name GET "${metadata}" project name)
string(JSON version GET "${metadata}" project version)
string(JSON url ERROR_VARIABLE ignored GET "${metadata}" project url)

project(
  ${name}
  VERSION ${version}
  HOMEPAGE_URL ${url}
  LANGUAGES CXX
)

find_package(cupcake.cmake REQUIRED)

cupcake_project()

cupcake_find_packages(main)
cupcake_link_libraries(${PROJECT_NAME}.imports.main INTERFACE main)
cupcake_find_packages(tool PRIVATE)

cupcake_add_libraries()

cupcake_add_executables()

cupcake_enable_testing()

cupcake_install_project()
cupcake_install_cpp_info()
