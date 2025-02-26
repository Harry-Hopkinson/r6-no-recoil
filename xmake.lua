add_rules("mode.debug", "mode.release")

set_languages("c++20")

target("r6-no-recoil")
    set_kind("binary")
    add_files("src/main.cpp")
    add_syslinks("gdi32", "user32", "kernel32")  -- Add missing system libraries
