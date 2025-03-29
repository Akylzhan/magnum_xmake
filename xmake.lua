add_rules("mode.debug", "mode.release")

if not is_cross() then
    add_rules("plugin.compile_commands.autoupdate", {outputdir = "$(buildir)"})
end

if is_plat("linux") then
    set_toolchains("clang")
    set_runtimes("c++_shared")
elseif is_plat("wasm") then
    add_requires("emscripten")
    add_requireconfs("emscripten.openssl", { system = true })
    set_toolchains("emcc@emscripten")
end

add_repositories("wasm_support https://github.com/Akylzhan/xmake-repo magnum_wasm")

add_requires("magnum feecd28993169c7857701a8d648fca4e2ec50487", { configs = { sdl2 = true, deprecated = false, ldflags = is_plat("wasm") and "-sMIN_WEBGL_VERSION=2" or nil } })
add_requireconfs("magnum.libsdl2", { configs = { wayland = false } })
-- https://github.com/mosra/corrade/blob/4ee45ba341febe1744733abd1449460124363c8f/modules/FindCorrade.cmake#L685
add_requireconfs("magnum.corrade", { override = true, version = "4ee45ba341febe1744733abd1449460124363c8f"})
-- TODO: set dependency on files in resources
add_requires("corrade 4ee45ba341febe1744733abd1449460124363c8f")
if is_cross() then
    add_requireconfs("magnum.corrade.corrade", { configs = {toolchains = "clang", runtimes = "c++_shared"} })
    add_requireconfs("corrade 4ee45ba341febe1744733abd1449460124363c8f", { configs = {toolchains = "clang", runtimes = "c++_shared"} })
end

add_requires("abseil b3b568d90373ed9f75e07c747bc51011557f1b2d", { configs = { cxx_standard = "20" } })
add_requires("entt", "flatbuffers")

target("magnum_xmake")
    set_languages("c++20")
    set_kind("binary")
    add_packages("magnum", "abseil", "entt", "flatbuffers", "corrade")
    add_rules("@corrade/resource")
    add_files("src/*.cpp", "assets/resources/*.conf")

    set_warnings("allextra", "error", "pedantic")
    add_cxxflags("-Wthread-safety", "-Wunsafe-buffer-usage", "-fsafe-buffer-usage-suggestions")
    if is_plat("linux") then
        add_links("GL")
    elseif is_plat("wasm") then
        add_ldflags("-sUSE_GLFW=3 -sASYNCIFY -sASSERTIONS -sMIN_WEBGL_VERSION=2", {expand = false})
    end