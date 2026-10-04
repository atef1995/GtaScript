# GtaScript

A minimal [ScriptHookV](http://www.dev-c.com/gtav/scripthookv/) ASI plugin for **Grand Theft Auto V**. When injected into the game it registers a script thread that prints `my mod loaded` to the HUD in a continuous loop.

This is a starting-point / template project: the scaffolding (ScriptHookV SDK headers, script registration, build config) is in place so you can drop in your own gameplay logic.

## What it does

`ScriptMain()` runs on a ScriptHookV script thread and every tick calls the HUD natives:

```cpp
HUD::BEGIN_TEXT_COMMAND_PRINT("STRING");
HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("my mod loaded");
HUD::END_TEXT_COMMAND_PRINT(2000, true);
scriptWait(0);
```

The DLL is registered on `DLL_PROCESS_ATTACH` and unregistered on `DLL_PROCESS_DETACH`.

## Requirements

- Windows 10/11 (x64)
- Visual Studio with the **v145** C++ toolset (C++20, `/std:c++20`)
- [ScriptHookV](http://www.dev-c.com/gtav/scripthookv/) runtime installed in your GTA V folder (`ScriptHookV.dll` + `dinput8.dll`)
- A legitimately-owned copy of GTA V

## Layout

```
GtaScript.slnx              Solution
GtaScript/
  dllmain.cpp               Entry point + ScriptMain()
  pch.h / pch.cpp           Precompiled header
  framework.h               Windows header shim
  GtaScript.vcxproj         Project (builds a .asi)
  inc/                      ScriptHookV SDK headers
    main.h                  scriptRegister/scriptWait, game version enum, helpers
    natives.h               All native function declarations
    nativeCaller.h          Native invocation machinery
    enums.h, types.h
  lib/
    ScriptHookV.lib         Import library
```

`inc/` and `lib/` come from the ScriptHookV SDK and are vendored here so the project builds standalone.

## Building

1. Open `GtaScript.slnx` in Visual Studio.
2. Select configuration **Debug | x64** (or Release | x64).
3. Build.

The project produces `GtaScript.asi` (the target extension is overridden from `.dll` to `.asi`). A post-build step copies the output into the game directory:

```
xcopy /y /d "$(TargetPath)" "B:\EpicG\GTAV\"
```

**Edit this path** in `GtaScript.vcxproj` (PostBuildEvent) to point at your own GTA V install, or remove the step and copy the `.asi` manually. The build will otherwise still succeed but the copy will fail.

## Installing

Copy `GtaScript.asi` into the GTA V game folder (the same folder as `GTA5.exe` and `ScriptHookV.dll`). Launch the game; `my mod loaded` should appear on the HUD.

## Notes

- Only **x64** configurations link against `ScriptHookV.lib`; the Win32 configs are stubs and won't produce a usable plugin.
- ScriptHookV must match your GTA V version. Update the SDK headers in `inc/` when you update the runtime.
- Don't use this on GTA Online — ScriptHookV and ASI mods are for single-player only.
