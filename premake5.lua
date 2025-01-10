-- premake5.lua
workspace "ChessboardPlayground"
    configurations { "Debug", "Release" }
    platforms { "x64" }

project "ChessboardPlayground"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}"

    files { "src/**.h", "src/**.cpp" }

    includedirs { -- Path to GLFW and GLEW headers
        "vendor/GLFW/include",
        "vendor/GLEW/include",
        "vendor/GLM/include",
        "vendor/ImGui",              -- ImGui headers
        "vendor/ImGui/backends"      -- ImGui backends
    }

    externalincludedirs { "vendor/GLFW/include", "vendor/GLEW/include", "vendor/GLM/include"  } -- This is needed for XCode

    libdirs { -- Path to GLFW libraries
        "vendor/GLFW/lib",
        "vendor/GLEW/lib",
        "vendor/GLM/lib"
    }

    -- Link GLFW and macOS system frameworks
    links {
        "ImGui",  
        "GLEW",
        "GLM",
        "GLFW",                      -- Link GLFW
        "OpenGL.framework"            -- OpenGL on macOS
    }
    
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"


-- Add ImGui files to the project
group "Vendor"
    project "ImGui"
        kind "StaticLib"
        language "C++"
        cppdialect "C++17"

        targetdir "bin/%{cfg.buildcfg}/ImGui"
        objdir "bin-int/%{cfg.buildcfg}/ImGui"

        files {
            "vendor/ImGui/imgui.cpp",
            "vendor/ImGui/imgui_demo.cpp",
            "vendor/ImGui/imgui_draw.cpp",
            "vendor/ImGui/imgui_tables.cpp",
            "vendor/ImGui/imgui_widgets.cpp",
            "vendor/ImGui/backends/imgui_impl_glfw.cpp",
            "vendor/ImGui/backends/imgui_impl_opengl3.cpp"
        }

        includedirs {
            "vendor/ImGui",
            "vendor/GLFW/include",       -- Needed for imgui_impl_glfw
            "vendor/GLEW/include"        -- Needed for imgui_impl_opengl3
        }

        externalincludedirs { "vendor/GLFW/include", "vendor/GLEW/include"  } -- This is needed for XCode

