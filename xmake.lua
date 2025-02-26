add_rules("mode.debug", "mode.release")

set_languages("c++20")

target("r6-no-recoil")
    set_kind("binary")
    add_files("src/*.cpp")
    add_includedirs("include/*.hpp")

    if is_host("windows") then
        add_syslinks("gdi32", "user32")  -- Use Windows GDI for graphics
    end
