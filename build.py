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
    try:
        requests.get("https://www.google.com")
    except requests.exceptions.ConnectionError:
        print("Please check your internet connection")
        sys.exit(1)

    # check if the user has cmake installed
    print("Checking if CMake is installed...\n")
    if os.system("cmake --version") != 0:
        print("Cmake is not installed..\n")
        print("Installing cmake...")
        # download cmake
        url = "https://github.com/Kitware/CMake/releases/download/v3.25.0-rc1/cmake-3.25.0-rc1-windows-x86_64.msi"
        r = requests.get(url, allow_redirects=True)
        open('cmake.msi', 'wb').write(r.content)
        # install cmake
        os.system("msiexec /i cmake.msi /quiet /norestart")
        # remove cmake.msi
        os.remove("cmake.msi")
        # add cmake to the path with $env:path += ";C:\Program Files\cmake\bin"
        os.system("$env:path += \";C:\Program Files\cmake\bin\"")
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
        url = "http://www.microsoft.com/en-us/download/confirmation.aspx?id=40760"
        r = requests.get(url, allow_redirects=True)
        open('MSBuild.exe', 'wb').write(r.content)
        # install MSBuild
        os.system("MSBuild.exe /quiet /norestart")
        # remove MSBuild.exe
        os.remove("MSBuild.exe")
        # add MSBuild to the path with $env:path += ";C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin"
        os.system("$env:path += \";C:\Program Files (x86)\Microsoft Visual Studio\\2022\Community\MSBuild\Current\Bin\"")
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
        url = ""
        r = requests.get(url, allow_redirects=True)
        open('vcpkg.zip', 'wb').write(r.content)
        # install vcpkg
    else:
        print("\nvcpkg is already installed")
    # installing dependencies
    print("\nInstalling dependencies...")
    os.system("vcpkg install sfml:x64-windows")
    os.system("vcpkg install asio:x64-windows")
    os.system("vcpkg install boost:x64-windows")
    print("\nDependencies installed successfully")

    # building the project
    print("\nBuilding the project...")
    os.system("cmake -S . -B build")
    os.system("cmake --build build")
    if os.system("msbuild build\ALL_BUILD.vcxproj") != 0:
        print("Error while building the project")
        sys.exit(1)
    print("\nProject built successfully")
    sys.exit(0)

elif os.name == 'posix':
    # check if the script is run as root
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
        print("\n\nvcpkg is not installed")
        print("installing vcpkg...")
        os.system("git clone https://github.com/Microsoft/vcpkg.git"))
        os.system("./vcpkg/bootstrap-vcpkg.sh")
        print("\n\nvcpkg installed")

    else :
        print("vcpkg is installed\n")
    # install dependencies with vcpkg
    print("Installing dependencies with vcpkg...\n")
    # get ports list
    # os.system("git clone https://github.com/microsoft/vcpkg.git vcpkg_tmp")
    # os.system("vcpkg install sfml --overlay-ports=vcpkg_tmp/ports/alsa")
    os.system("./vcpkg/vcpkg install sfml")
    os.system("./vcpkg/vcpkg install asio")
    os.system("./vcpkg/vcpkg install boost")
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



