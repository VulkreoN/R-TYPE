##
## EPITECH PROJECT, 2022
## R-TYPE
## File description:
## build
##

import os
import sys

if os.name == 'nt':
    import ctypes
    import requests
    # check if the user is launching the script as administrator
    if not ctypes.windll.shell32.IsUserAnAdmin():
        print("Please run this script as administrator")
        sys.exit(1)
    # check if the user has internet connection
    print("checking internet connection...")
    try:
        requests.get("https://www.google.com")
        print("internet connection OK")
    except requests.exceptions.ConnectionError:
        print("Please check your internet connection")
        sys.exit(1)

    # install chocolatey
    print("installing chocolatey...")
    os.system("powershell -Command \"Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))\"")
    print("chocolatey installed")

    # check if the user has cmake installed
    print("Checking if CMake is installed...\n")
    if os.system("cmake --version") != 0:
        print("Cmake is not installed..\n")
        print("Installing cmake...")
        # download cmake
        os.system("choco install cmake --installargs 'ADD_CMAKE_TO_PATH=System'")
        os.system("cmake --version")
        print("Cmake installed successfully")
    else:
        print("\nCmake is already installed")

    # check if the user has msbuild installed
    print("Checking if MSBuild is installed...\n")
    if os.system("msbuild /version") != 0:
        print("MSBuild is not installed..\n")
        print("Installing MSBuild...")
        # download MSBuild
        os.system("choco install microsoft-build-tools")
        os.system("msbuild /version")
        print("MSBuild installed successfully")
    else:
        print("\nMSBuild is already installed")


    # check if the user has vcpkg installed
    print("Checking if vcpkg is installed...\n")
    if os.system("vcpkg --version") != 0:
        print("vcpkg is not installed..\n")
        print("Installing vcpkg...")
        # download vcpkg
        os.system("git clone https://github.com/Microsoft/vcpkg.git")
        # install vcpkg
        os.system(".\\vcpkg\\bootstrap-vcpkg.bat")
    else:
        print("\nvcpkg is already installed")


    # installing dependencies
    print("\nInstalling dependencies...")
    os.system("vcpkg install sfml:x64-windows")
    os.system("vcpkg install asio:x64-windows")
    os.system("vcpkg integrate install")

    # building the project
    print("\nBuilding the project...")
    os.system("cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release")
    os.system("cmake --build build --config Release")
    if os.system("msbuild -m build\R-TYPE.sln") != 0:
        print("Error while building the project")
        sys.exit(1)
    # copy asset folder to the build folder
    os.system("xcopy /E /I /Y assets build\Release\\assets")
    # copy font.ttf to the build folder
    os.system("copy font.ttf build\Release\\font.ttf")
    # create a shortcut of the game
    os.system("powershell -NoProfile -ExecutionPolicy ByPass New-Item -ItemType SymbolicLink -Path '.' -Name 'r-type_client.lnk' -Value 'build\Release\\r-type_client.exe'")
    os.system("powershell -NoProfile -ExecutionPolicy ByPass New-Item -ItemType SymbolicLink -Path '.' -Name 'r-type_server.lnk' -Value 'build\Release\\r-type_server.exe'")
    print("\nProject built successfully")
    sys.exit(0)

elif os.name == 'posix':
    # check if the script is run as root
    vcpkg_install = True
    if os.geteuid() != 0:
        print("You need to have root privileges to run this script.")
        sys.exit(1)
    # check if cmake is installed
    print("Checking if cmake is installed...\n")
    if os.system("cmake --version") != 0:
        print("\n\ncmake is not installed")
        print ("installing cmake...")
        os.system("curl -L https://github.com/Kitware/CMake/releases/download/v3.25.0-rc1/cmake-3.25.0-rc1-linux-x86_64.sh -o cmake.sh")
        os.system("chmod +x cmake.sh")
        os.system("./cmake.sh --skip-license --prefix=/usr/local")
        os.system("rm cmake.sh")
        print("\n\ncmake installed")
    else :
        print("cmake is installed\n")
    # check if vcpkg is installed
    print("Checking if vcpkg is installed...\n")
    if os.system("vcpkg --version") != 0:
        vcpgk_install = False
        print("\n\nvcpkg is not installed")
        print("installing vcpkg...")
        os.system("git clone https://github.com/Microsoft/vcpkg.git")
        os.system("./vcpkg/bootstrap-vcpkg.sh")
        print("\n\nvcpkg installed")

    else :
        print("vcpkg is already installed\n")
    # install dependencies with vcpkg
    print("Installing dependencies with vcpkg...\n")
    if not vcpkg_install:
        os.system("./vcpkg/vcpkg install sfml")
        os.system("./vcpkg/vcpkg install asio")
    else:
        os.system("vcpkg install sfml")
        os.system("vcpkg install asio")
    # os.system("rm -rf vcpkg_tmp")
    print("Dependencies installed successfully\n")
    # building the project
    print("Building the project...\n")
    os.system("cmake -S . -B build")
    if os.system("cmake --build build") != 0:
        print("Building the project failed")
        sys.exit(1)
    else :
        os.system("mv build/r-type_server r-type_server")
        os.system("mv build/r-type_client r-type_client")
        print("Project built successfully\n")
        sys.exit(0)
