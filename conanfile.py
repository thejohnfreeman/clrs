from conans import ConanFile

class ClrsConan(ConanFile):
    name = 'clrs'
    license = 'MIT'
    author = 'John Freeman <jfreeman08@gmail.com>'
    url = 'https://github.com/thejohnfreeman/clrs'
    description = 'Data structures and algorithms from the CLRS book'
    topics = ('data structures', 'algorithms', 'containers', 'sorting')
    build_requires = (
        'autocheck/1.0.0@autocheck/stable',
        'gtest/1.8.1@bincrafters/stable',
    )
    generators = 'cmake_find_package'
    exports_sources = 'include/**/*.hpp'
    no_copy_source = True

    def package(self):
        self.copy('**/*.hpp')
