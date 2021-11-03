project('easyloggingpp', 'cpp')
easyloggingpp_sys = include_directories(is_system : true)
easyloggingpp_inc = [include_directories('src'), easyloggingpp_sys]
easyloggingpp_src = files('src/easylogging++.cc')
easyloggingpp = static_library(
  'easyloggingpp',
  easyloggingpp_src,
  include_directories : easyloggingpp_inc
)
easyloggingpp_dep = declare_dependency(
  link_with : easyloggingpp,
  include_directories : easyloggingpp_inc
)
