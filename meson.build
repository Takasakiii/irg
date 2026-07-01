project(
    'irg',
    'c',
    meson_version: '>= 1.3.0',
    version: '0.1',
    default_options: ['warning_level=3', 'buildtype=debugoptimized'],
)


srcfiles = ['src/main.c', 'src/isometric.c']

cmake = import('cmake')
raylibsub = cmake.subproject('raylib')
raylibdep = raylibsub.dependency('raylib')

cc = meson.get_compiler('c')
lc = cc.find_library('c', required: true)

dependencies = [lc, raylibdep]

executable(
    'irg',
    sources: srcfiles,
    include_directories: [
        './includes'
    ],
    dependencies: dependencies,
)
