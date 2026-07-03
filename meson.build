project(
    'irg',
    'c',
    meson_version: '>= 1.3.0',
    version: '0.1',
    default_options: ['warning_level=3', 'buildtype=debugoptimized'],
)

srcfiles = ['src/main.c', 'src/isometric.c', 'src/camera.c']

cmake = import('cmake')
raylibsub = cmake.subproject('raylib')
raylibdep = raylibsub.dependency('raylib')

cc = meson.get_compiler('c')
lc = cc.find_library('c', required: true)

dependencies = [lc, raylibdep]

klibfolder = include_directories('subprojects/klib')

executable(
    'irg',
    sources: srcfiles,
    include_directories: ['./includes', klibfolder],
    dependencies: dependencies,
)
