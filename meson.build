project('space_tycoon_model', 'cpp')
inc = include_directories('include')
src = ['src/SpaceTycoonModel.cpp']
easyloggingpp_dep = dependency('easyloggingpp')
space_tycoon_model = static_library('space_tycoon_model', src, dependencies : [easyloggingpp_dep], include_directories: inc, install: true)
space_tycoon_model_dep = declare_dependency(include_directories: inc, link_with : space_tycoon_model)

gtest_dep = dependency('gtest', main : false, required : false)
gmock_dep = dependency('gmock', main : false, required : false)
test_src = ['tests/Main.Test.cpp']
test_runner_exe = executable('test_runner', test_src, dependencies : [gtest_dep, gmock_dep, space_tycoon_model_dep])
test('gtest test', test_runner_exe)
