
add_rules("mode.debug", "mode.release")


set_languages("c++26")


set_toolchains("gcc")
add_cxxflags(
    "-Wall",
    "-Wextra",
    "-Werror",
    "-Wpedantic",
    "-Wshadow",
    "-Wconversion",
    "-O3",
    "-march=native",
    "-fno-exceptions",
    "-fno-rtti",
    "-mavx",
    "-std=c++26")

-- add_cxxflags("-g")


add_requires("raylib")


target("vft")
    set_default(true)
    set_kind("binary")
    add_files("src/*.cpp")
    add_headerfiles("libvft/*.hpp")
    add_includedirs("src", {public = true})
    add_packages("raylib")

