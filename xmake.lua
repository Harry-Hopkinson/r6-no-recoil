add_rules("mode.debug", "mode.release")

-- Set the C++ standard to C++20
set_languages("c++20")

-- Fetch Raylib
includes("raylib.lua")

add_requires("raylib")

target("r6-no-recoil")
    set_kind("binary")
    add_files("src/*.cpp")
    add_includedirs("include/*.hpp")

    -- Link Raylib
    add_packages("raylib")
    if is_host("windows") then
    	add_syslinks("m", "pthread")  -- Windows: Do NOT link "dl"
    else
    	add_syslinks("m", "dl", "pthread")  -- Linux/macOS: Keep "dl"
    end
