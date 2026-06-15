from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout


class TwopowConan(ConanFile):
    name = "twopow"
    version = "0.1.0"
    license = "Apache-2.0"
    author = "Anton Shpakovskiy"
    url = "https://github.com/dalamber/twopow"
    description = "Deterministic base-2 exponentiation for modern C++"
    topics = ("math", "exponentiation", "cpp20", "satire")
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = (
        "CMakeLists.txt",
        "include/*",
        "src/*",
        "cmake/*",
        "LICENSE",
    )

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.cache_variables["TWOPOW_BUILD_TESTS"] = False
        tc.cache_variables["TWOPOW_BUILD_CLI"] = False
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["twopow"]
