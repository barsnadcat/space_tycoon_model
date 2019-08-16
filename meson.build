project('space_tycoon_model', 'cpp')
inc = include_directories('include')
src = ['src/SpaceTycoonModel.cpp']
space_tycoon_model = static_library('space_tycoon_model', src, include_directories: inc, install: true)
space_tycoon_model_dep = declare_dependency(include_directories: inc, link_with : space_tycoon_model)
