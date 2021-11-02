@echo off
set vswhere="%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
set vcvars=""
for /f "usebackq delims=" %%i in (`%vswhere% -prerelease -latest -property installationPath`) do (
  if exist "%%i\VC\Auxiliary\Build\vcvars64.bat" (
    set vcvars="%%i\VC\Auxiliary\Build\vcvars64.bat"
  )
)

if %vcvars%=="" (
  echo vcvars not found
  exit /b 2
) else (
  call %vcvars%
  ninja
)
