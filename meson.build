project('space_tycoon_model', 'cpp')
inc = include_directories('include')
src = ['src/SpaceTycoonModel.cpp']
easyloggingpp_dep = dependency('easyloggingpp')
space_tycoon_model = static_library('space_tycoon_model', src, dependencies : [easyloggingpp_dep], include_directories: inc, install: true)
space_tycoon_model_dep = declare_dependency(include_directories: inc, link_with : space_tycoon_model)
