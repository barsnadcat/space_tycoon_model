project('space_tycoon_model', 'cpp')
## Disable defenition of min max macros in windows headers
add_project_arguments('-DNOMINMAX', language: ['cpp'])

## Main library
inc = include_directories('include')
subdir('src')

easyloggingpp_dep = dependency('easyloggingpp', required : false)
if not easyloggingpp_dep.found()
	cmake = import('cmake')
	easyloggingpp_proj = cmake.subproject('easyloggingpp', cmake_options: ['-Dbuild_static_lib=ON'])
	## easyloggingg does not have include directory
	easyloggingpp_dep = declare_dependency(link_with: easyloggingpp_proj.get_variable('cm_easyloggingpp'), include_directories: 'subprojects/easyloggingpp/src')
endif

space_tycoon_model = static_library('space_tycoon_model', src, include_directories: inc, dependencies: [easyloggingpp_dep])
space_tycoon_model_dep = declare_dependency(include_directories: inc, link_with: space_tycoon_model)

## Unit tests
gmock_dep = dependency('gmock', main : false, fallback: ['gtest', 'gmock_dep'])
test_src = [
	'tests/Main.Test.cpp', 
	'tests/EntityArray.Test.cpp', 
	'tests/Death.Test.cpp',
	'tests/Hunger.Test.cpp'
]
test_inc = include_directories('src', 'include')
test_runner_exe = executable('test_runner', test_src + src, include_directories: test_inc, dependencies: [gmock_dep, easyloggingpp_dep])
test('gtest test', test_runner_exe)
