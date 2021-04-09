# HttpSolution
Basic Http rest implementation
How to build
- Install vcpkg from : https://github.com/microsoft/vcpkg
- Build cpprestsdk
  - vcpkg install cpprestsdk:x64-windows
  - .\vcpkg.exe export cpprestsdk:x64-windows --nuget  --nuget-id=cpprestsdk_x64_2_10_18 --nuget-version=9.03.0
- Start Visual Studio 2019
- Open the project
- Open the Package Manager Console
- Type : Install-Package cpprestsdk_x64_2_10_18 -Source "VCPKG directory"
