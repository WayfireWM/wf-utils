project(
        'wf-utils',
        'cpp',
        version: '0.3',
        license: 'MIT',
        meson_version: '>=0.50.0',
        default_options: [
        'cpp_std=c++17',
                'warning_level=2',
                'werror=false',
        ],
)

add_project_arguments(['-Wno-deprecated-declarations'], language: ['cpp'])

sources = [
'action/action.cpp',
'condition/condition.cpp',
'condition/logic_condition.cpp',
'condition/test_condition.cpp',
'lexer/lexer.cpp',
'lexer/literal.cpp',
'lexer/symbol.cpp',
'parser/action_parser.cpp',
'parser/condition_parser.cpp',
'parser/rule_parser.cpp',
'rule/rule.cpp',
'rule/rule_interface.cpp',
'variant.cpp',
]

wfutils_inc = include_directories('.')

lib_wfutils = library('wf-utils',
    sources,
    dependencies: [],
    include_directories: wfutils_inc,
    install: true,
    version: meson.project_version())

pkgconfig = import('pkgconfig')
pkgconfig.generate(
    libraries:    lib_wfutils,
    version:      meson.project_version(),
    filebase:     meson.project_name(),
    name:         meson.project_name(),
    description: 'Utilities library for Wayfire')

install_headers([], subdir: 'wayfire/utils')

wfutils = declare_dependency(link_with: lib_wfutils,
    include_directories: wfutils_inc)

# -------------------------------------------------------------------------------------------------
# Install headers
headers_action = [
'action/action.hpp',
]

headers_condition = [
'condition/condition.hpp',
'condition/logic_condition.hpp',
'condition/test_condition.hpp',
]

headers_lexer = [
'lexer/lexer.hpp',
'lexer/literal.hpp',
'lexer/symbol.hpp',
]

headers_parser = [
'parser/action_parser.hpp',
'parser/condition_parser.hpp',
'parser/rule_parser.hpp',
]

headers_rule = [
'rule/rule.hpp',
'rule/rule_interface.hpp',
]

headers_root = [
'utils.hpp',
'variant.hpp',
]

install_headers(headers_action, subdir: 'wayfire/action')
install_headers(headers_condition, subdir: 'wayfire/condition')
install_headers(headers_lexer, subdir: 'wayfire/lexer')
install_headers(headers_parser, subdir: 'wayfire/parser')
install_headers(headers_rule, subdir: 'wayfire/rule')
install_headers(headers_root, subdir: 'wayfire')

# -------------------------------------------------------------------------------------------------
# Unit tests
#subdir('test')

# -------------------------------------------------------------------------------------------------
# Documentation
# TODO: Figure out how to do this with meson.

cdata = configuration_data()
cdata.set('TOP_SRCDIR', meson.source_root())
cdata.set('TOP_BUILDDIR', meson.build_root())
cdata.set('OUTPUT_DIR', join_paths(meson.build_root(),'docs'))
cdata.set('README_PATH', join_paths(meson.source_root(),'README.md'))
cdata.set('VERSION', meson.project_version())
cdata.set('PROJECT_NAME', meson.project_name())

doxyfile = configure_file(input: 'Doxyfile.in',
                          output: 'Doxyfile',
                          configuration: cdata,
                          install: false)

doxygen = find_program('doxygen')

doc_target = run_target('doc',command: [doxygen, doxyfile])
