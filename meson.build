project('space_tycoon_model', 'cpp')
## Main library
inc = include_directories('include')
src = ['src/SpaceTycoonModel.cpp']
easyloggingpp_dep = dependency('easyloggingpp')
space_tycoon_model = static_library('space_tycoon_model', src, include_directories: inc, install: true, 
	dependencies : [easyloggingpp_dep])
space_tycoon_model_dep = declare_dependency(include_directories: inc, link_with : space_tycoon_model)

## Unit tests
gtest_dep = dependency('gtest', main : false, required : false)
gmock_dep = dependency('gmock', main : false, required : false)
test_src = ['tests/Main.Test.cpp', 'tests/EntityArray.Test.cpp', 'tests/EntityVectorUpdate.Test.cpp']
test_inc = include_directories('src', 'include')
test_runner_exe = executable('test_runner', test_src + src, include_directories: test_inc,
		dependencies : [gtest_dep, gmock_dep, easyloggingpp_dep])
test('gtest test', test_runner_exe)
