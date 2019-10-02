project('ReadMpls', 'cpp',
  default_options : ['buildtype=release', 'b_ndebug=if-release', 'cpp_std=c++14'],
  meson_version : '>=0.48.0',
  version : '4'
)

add_project_arguments('-ffast-math', language : 'cpp')

sources = [
  'ReadMpls/ReadMpls.cpp'
]

vapoursynth_dep = dependency('vapoursynth').partial_dependency(compile_args : true, includes : true)

libbluray_dep = dependency('libbluray')

if host_machine.cpu_family().startswith('x86')
  add_project_arguments('-mfpmath=sse', '-msse2', language : 'cpp')
endif

shared_module('readmpls', sources,
  dependencies : [vapoursynth_dep, libbluray_dep],
  install : true,
  install_dir : join_paths(vapoursynth_dep.get_pkgconfig_variable('libdir'), 'vapoursynth'),
  gnu_symbol_visibility : 'hidden'
)
