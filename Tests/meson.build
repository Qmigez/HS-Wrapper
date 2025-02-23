
gtest_dep = dependency('gtest')

tests_exe = executable('tests',
    files(
        'main.cpp',
        
        'src/MetaTest.cpp',
        'src/UseCasesBlockTest.cpp',
        'src/SimpleTest.cpp'
        
    ),
    dependencies : [
        gtest_dep,
        hs_wrapper_dep
    ],
    include_directories : '../'
)

test('test', tests_exe)