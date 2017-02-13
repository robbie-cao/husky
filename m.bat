::Build script

@echo off
setlocal enabledelayedexpansion

::IAR path
::Set path to your own
::eg, D:\ProgramFiles\IAR
set IAR_PATH=C:\Program Files (x86)\IAR Systems
path %PATH%;%IAR_PATH%\Embedded Workbench 6.4\common\bin
:: Keil path
::Set path to your own
::eg, D:\ProgramFiles\Keil
set KEIL_PATH=C:\Keil
path %PATH%;%KEIL_PATH%\ARM\BIN40\;%KEIL_PATH%\UV4


::Help message
set pr_help=FALSE
if "%1"=="?" set pr_help=TRUE
if "%1"=="h" set pr_help=TRUE
if "%1"=="help" set pr_help=TRUE
if "%pr_help%"=="TRUE" (
        call :PrintHelp
        goto EXIT
        )

::Build command
set command=
if "%1"==""         set command=make
if "%1"=="m"        set command=make
if "%1"=="b"        set command=build
if "%1"=="r"        set command=build
if "%1"=="c"        set command=clean
if "%1"=="make"     set command=make
if "%1"=="build"    set command=build
if "%1"=="rebuild"  set command=build
if "%1"=="clean"    set command=clean

if "%command%"=="" (
        echo Error: Invalid command...
        call :PrintHelp
        goto EXIT
        )

set command2=
if "%1"==""         set command2=b
if "%1"=="m"        set command2=b
if "%1"=="b"        set command2=r
if "%1"=="r"        set command2=r
if "%1"=="c"        set command2=r
if "%1"=="make"     set command2=b
if "%1"=="build"    set command2=r
if "%1"=="rebuild"  set command2=r
if "%1"=="clean"    set command2=r

if "%command2%"=="" (
        echo Error: Invalid command...
        call :PrintHelp
        goto EXIT
        )


::Config to build
set config=
if "%2"==""         set config=Debug
if "%2"=="d"        set config=Debug
if "%2"=="r"        set config=Release
if "%2"=="debug"    set config=Debug
if "%2"=="release"  set config=Release

if "%config%"=="" (
        echo Error: Invalid config...
        call :PrintHelp
        goto EXIT
        )

::Target to build
set target=
if "%3"==""         set target=Dis
if "%3"=="s"        set target=Std
if "%3"=="a"        set target=App
if "%3"=="o"        set target=OTA
if "%3"=="b"        set target=BIM
if "%3"=="all"      set target=All
if "%3"=="dis"      set target=Dis
if "%3"=="std"      set target=Std
if "%3"=="app"      set target=App
if "%3"=="ota"      set target=OTA
if "%3"=="bim"      set target=BIM

if "%target%"=="" (
        echo Error: Invalid target...
        call :PrintHelp
        goto EXIT
        )

set build_std=FALSE
set build_app=FALSE
set build_ota=FALSE
set build_bim=FALSE
if "%target%"=="Std" set build_std=TRUE
if "%target%"=="App" set build_app=TRUE
if "%target%"=="OTA" set build_ota=TRUE
if "%target%"=="BIM" set build_bim=TRUE
if "%target%"=="All" (
        set build_app=TRUE
        set build_std=TRUE
        set build_ota=TRUE
        set build_bim=TRUE
        )
if "%target%"=="Dis" (
        set build_app=FALSE
        set build_std=TRUE
        set build_ota=FALSE
        set build_bim=FALSE
        )

::Remove previous built image
del /Q *.hex
del /Q *.bin
del /Q *.map

::Product list:
::Simple, ...
::More TBD

set tar=Std
for %%p in (Simple) do (
        set tar=Std
        ::FIXME - Above assignment not work, WHY?
        if "%build_std%"=="TRUE" (
            echo ***************************************************************************
            echo Build %%p Std %config%...
            echo ***************************************************************************
            ::Del previous built image if any and copy the new built image out after built
            del /Q Projects\%%p\Std%config%\Exe\*.hex
            del /Q Projects\%%p\Std%config%\Exe\*.sim
            del /Q Projects\%%p\Std%config%\Exe\*.bin
            del /Q Projects\%%p\Std%config%\List\*.map

            iarbuild Projects\%%p\Std.ewp -%command% %config% -log warnings
            if %ERRORLEVEL% NEQ 0 goto ERROR

            copy /Y Projects\%%p\Std%config%\Exe\*.hex .
            copy /Y Projects\%%p\Std%config%\Exe\*.bin .
            copy /Y Projects\%%p\Std%config%\List\*.map .

            echo ***************************************************************************
            echo Build %%p Std %config% done!
            )

        set tar=App
        ::FIXME - Above assignment not work, WHY?
        if "%build_app%"=="TRUE" (
            echo ***************************************************************************
            echo Build %%p App %config%...
            echo ***************************************************************************
            ::Del previous built image if any and copy the new built image out after built
            del /Q Projects\%%p\App%config%\Exe\*.hex
            del /Q Projects\%%p\App%config%\Exe\*.sim
            del /Q Projects\%%p\App%config%\Exe\*.bin
            del /Q Projects\%%p\App%config%\List\*.map

            iarbuild Projects\%%p\App.ewp -%command% %config% -log warnings
            if %ERRORLEVEL% NEQ 0 goto ERROR

            copy /Y Projects\%%p\App%config%\Exe\*.hex .
            copy /Y Projects\%%p\App%config%\Exe\*.bin .
            copy /Y Projects\%%p\App%config%\List\*.map .

            echo ***************************************************************************
            echo Build %%p App %config% done!
            )


        set tar=OTA
        ::FIXME - Above assignment not work, WHY?
        if "%build_ota%"=="TRUE" (
                echo ***************************************************************************
                echo Build %%p OTA %config%...
                echo ***************************************************************************
                ::Del previous built image if any and copy the new built image out after built
                del /Q Projects\%%p\Ota%config%\Exe\*.hex
                del /Q Projects\%%p\Ota%config%\Exe\*.sim
                del /Q Projects\%%p\Ota%config%\Exe\*.bin
                del /Q Projects\%%p\Ota%config%\List\*.map

                iarbuild Projects\%%p\OTA.ewp -%command% %config% -log warnings
                if %ERRORLEVEL% NEQ 0 goto ERROR

                copy /Y Projects\%%p\Ota%config%\Exe\*.hex .
                copy /Y Projects\%%p\Ota%config%\Exe\*.bin .
                copy /Y Projects\%%p\Ota%config%\List\*.map .

                echo ***************************************************************************
                echo Build %%p OTA %config% done!
                )

        set tar=BIM
        ::FIXME - Above assignment not work, WHY?
        if "%build_bim%"=="TRUE" (
                echo ***************************************************************************
                echo Build %%p BIM %config%...
                echo ***************************************************************************
                ::Del previous built image if any and copy the new built image out after built
                del /Q Projects\%%p\Bim%config%\Exe\*.hex
                del /Q Projects\%%p\Bim%config%\Exe\*.sim
                del /Q Projects\%%p\Bim%config%\Exe\*.bin
                del /Q Projects\%%p\Bim%config%\List\*.map

                iarbuild Projects\%%p\BIM.ewp -%command% %config% -log warnings
                if %ERRORLEVEL% NEQ 0 goto ERROR

                copy /Y Projects\%%p\Bim%config%\Exe\*.hex .
                copy /Y Projects\%%p\Bim%config%\Exe\*.bin .
                copy /Y Projects\%%p\Bim%config%\List\*.map .

                echo ***************************************************************************
                echo Build %%p BIM %config% done!
                )

        )

if "%target%"=="All" (
        if "%command%"=="" (
            goto DISP_MEMORY
            )
        echo ***************************************************************************
        echo Combine Bootloader + ImgA-OTA + ImgB-App
        ::Combine Bootloader + ImgA(OTA) + ImgB(App)
        Tools\srec_cat.exe Simple_BIM.hex -intel Simple_OTA.hex -intel Simple_App.hex -intel -O Simple.hex -intel -obs=16 -line-length=46
        Tools\srec_cat.exe Simple_BIM.hex -intel Simple_Rec.hex -intel Simple_App.hex -intel -O Simple.bin -binary
        if %ERRORLEVEL% NEQ 0 goto ERROR
        echo Combine Bootloader + ImgA-OTA
        ::Combine Bootloader + ImgA(OTA)
        Tools\srec_cat.exe Simple_BIM.hex -intel Simple_OTA.hex -intel -O Simple_BO.hex -intel -obs=16 -line-length=46
        if %ERRORLEVEL% NEQ 0 goto ERROR
        echo Combine Bootloader + ImgB-App
        ::Combine Bootloader + ImgB(App)
        Tools\srec_cat.exe Simple_BIM.hex -intel Simple_App.hex -intel -O Simple_BA.hex -intel -obs=16 -line-length=46
        if %ERRORLEVEL% NEQ 0 goto ERROR

        echo ***************************************************************************
        echo Combine image done!
        )

:DISP_MEMORY
echo ***************************************************************************
::Display memory size
findstr "memory" *.map
echo ***************************************************************************

echo Done
goto EXIT

:ERROR
echo There are errors. Please check!
goto EXIT

:PrintHelp
setlocal
echo Usage:
echo m.bat [command] [config] [target]
echo * command:
echo     - m / make [default]
echo     - b / build
echo     - r / rebuild
echo     - c / clean
echo * config:
echo     - d / debug [default]
echo     - r / release
echo * target:
echo     - all [default]
echo     - s / std
echo     - a / app
echo     - o / ota
echo     - b / bim
endlocal

:EXIT

