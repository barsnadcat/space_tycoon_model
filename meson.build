project('space_tycoon_model', 'cpp')
## Disable defenition of min max macros in windows headers
add_project_arguments('-DNOMINMAX', language: ['cpp'])

easyloggingpp_dep = dependency('easyloggingpp', fallback : ['easyloggingpp', 'easyloggingpp_dep'])

## Main library
inc = include_directories('include')
subdir('src') ## initializes src varible
space_tycoon_model = static_library('space_tycoon_model', src, include_directories: inc, dependencies: [easyloggingpp_dep])
space_tycoon_model_dep = declare_dependency(include_directories: inc, link_with: space_tycoon_model) ## For external use

## Unit tests
subdir('tests') ## initializes test_src varibale
test_inc = include_directories('src', 'include')
gmock_dep = dependency('gmock', main : false, fallback: ['gtest', 'gmock_dep'])
test_runner_exe = executable('test_runner', test_src + src, include_directories: test_inc, dependencies: [gmock_dep, easyloggingpp_dep])

test('gtest test', test_runner_exe) # For test execution
