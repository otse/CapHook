project "Cap"
    language "C++"
    kind "StaticLib"
    
    vpaths
    {
        ["Headers/*"] = { "**.hpp", "**.h" },
        ["Sources/*"] = "**.cpp",
        ["Resources/*"] = "**.rc",
        ["*"] = "premake5.lua"
	}
	
	includedirs
    {
		"../dawnhook",
		"../shared",
		--"../vendor/lua",
		"../vendor/minhook",
		"../vendor/imgui",
		"../vendor/udis86",
		"."
    }

    files
    {
        "premake5.lua",
        "**.h",
        "**.hpp",
        "**.cpp",
        "**.cc",
        "**.rc",
        "**.c"
    }
