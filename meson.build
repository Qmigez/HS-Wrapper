project('HS_Wrapper', 'cpp',
    version : '0.0.1',
    default_options : ['cpp_std=c++20']
)

headers_install_suffix = '/include/HSWrapper'
lib_install_suffix = '/lib'
examples_install_suffix = '/examples'

cmplr = meson.get_compiler('cpp')

hs_dep = cmplr.find_library('hs')

sources = files(
    'HSWrapper/Compile/src/Database.cpp',
    'HSWrapper/Compile/src/PlatformInfo.cpp',

    'HSWrapper/Runtime/src/Scratch.cpp',
    
    'HSWrapper/src/Exception.cpp',
    'HSWrapper/src/Meta.cpp',
    'HSWrapper/src/Pattern.cpp',
    'HSWrapper/src/Stream.cpp'
)

wrapper_headers = files(
    'HSWrapper/AbstractHandler.h',
    'HSWrapper/Enums.h',
    'HSWrapper/Exception.h',
    'HSWrapper/Meta.h',
    'HSWrapper/Pattern.h'
)

wrapper_compile_headers = files(
    'HSWrapper/Compile/Database.h',
    'HSWrapper/Compile/PlatformInfo.h'
)

wrapper_runtime_headers = files(
    'HSWrapper/Runtime/Scratch.h'
)

install_headers(wrapper_headers, install_dir : headers_install_suffix)
install_headers(wrapper_compile_headers, install_dir : headers_install_suffix / 'Compile')
install_headers(wrapper_runtime_headers, install_dir : headers_install_suffix / 'Runtime')

HS_Wrapper = both_libraries('HSWrapper',
    sources,
    dependencies : hs_dep,
    install : true,
    install_dir : lib_install_suffix
)

hs_wrapper_dep = declare_dependency(link_with : HS_Wrapper)

if get_option('examples').enabled()
    subdir('Examples')
endif

if get_option('tests').enabled()
    subdir('Tests')
endif
