-- SAP build configuration script
-- Author(s): Force67
--
-- Copyright (c) 2015-2017 Dev-Force
--
-- Distributed under the MIT license (See accompanying file LICENSE or copy at
-- https://opensource.org/licenses/MIT)

-- This is the root build file for Premake. Premake will start processing by loading this
-- file, and recursively load all dependencies until all dependencies are either
-- resolved or known not to exist (which will cause the build to fail). So if
-- you add a new build file, there must be some path of dependencies from this
-- file to your new one or Premake won't know about it.

premake.path = premake.path .. ";build"

local FX_NAME = "ShieldMod"

workspace "ShieldMod"
    configurations { "Debug", "Release" }

	targetdir '../bin/%{cfg.buildcfg}/'
	location "../build"
	platforms { "x64" }
    targetprefix ""
    buildoptions "/std:c++latest"
    --cppdialect "C++17"
    symbols "On"
    characterset "Unicode"
    -- Enable position-independent-code generation
    pic "On"
    systemversion "10.0.15063.0"
    startproject "luahook"
	
	
    defines { "FXNAME=\"" .. FX_NAME .. "\"", 
			  "FXNAME_WIDE=L\"" .. FX_NAME .. "\""}

    defines
    {
        "NOMINMAX",
        "WIN32_LEAN_AND_MEAN",
		"_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING",
        "_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING"

    }

    includedirs
    {
        "."
    }
	
	libdirs
	{
		"./shared/Lib",
	}

	
    filter "platforms:x64"
         architecture "x86_64"

    filter "configurations:Debug"
        defines { "GC_DBG" }

    filter "configurations:Release"
        --flags { "StaticRuntime" }
        optimize "Speed"

    filter {"system:windows", "configurations:Release", "kind:not StaticLib"}
        linkoptions "/PDB:\"symbols\\$(ProjectName).pdb\""

    filter { "system:windows", "kind:not StaticLib" }
        linkoptions "/manifestdependency:\"type='Win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\""

    -- Disable deprecation warnings and errors
    filter "action:vs*"
        defines
        {
            "_CRT_SECURE_NO_WARNINGS",
            "_CRT_SECURE_NO_DEPRECATE",
            "_CRT_NONSTDC_NO_WARNINGS",
            "_CRT_NONSTDC_NO_DEPRECATE",
            "_SCL_SECURE_NO_WARNINGS",
            "_SCL_SECURE_NO_DEPRECATE"
            
            --"_WINSOCK_DEPRECATED_NO_WARNINGS"
        }

	group "ShieldMod"
	include "./shieldmod"
	
    group "Base"
	include "./dawnhook"
	
	group "Shared"
	include "./shared"

    group "Vendor"
	include "vendor/minhook"
	include "vendor/imgui"
	include "vendor/udis86"
	--include "vendor/lua"

	
-- Cleanup
if _ACTION == "clean" then
    os.rmdir("../bin");
    os.rmdir("../build");
end
