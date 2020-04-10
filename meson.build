project('space_tycoon_model', 'cpp')
## Main library
inc = include_directories('include')
src = ['src/SpaceTycoonModel.cpp']

easyloggingpp_dep = dependency('easyloggingpp', required : false)
if not easyloggingpp_dep.found()
	cmake = import('cmake')
	easyloggingpp_proj = cmake.subproject('easyloggingpp', cmake_options: '-Dbuild_static_lib=ON')
	easyloggingpp_dep = easyloggingpp_proj.get_variable('cm_easyloggingpp_dep')
endif

space_tycoon_model = static_library('space_tycoon_model', src, include_directories: inc)
space_tycoon_model_dep = declare_dependency(include_directories: inc, link_with : space_tycoon_model)

## Unit tests
gtest_dep = dependency('gtest', main : false, required : false)
gmock_dep = dependency('gmock', main : false, required : false)
test_src = ['tests/Main.Test.cpp']
test_runner_exe = executable('test_runner', test_src, 
		dependencies : [gtest_dep, gmock_dep, space_tycoon_model_dep, easyloggingpp_dep])
test('gtest test', test_runner_exe)
