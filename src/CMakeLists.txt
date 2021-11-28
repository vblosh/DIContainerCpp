# CMakeList.txt : CMake project for DIContainerCpp, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_library (DIContainer "DIContainer.cpp" "DIContainer.h" "ComPtr.h" "IContainer.h" "IComponent.h" "IUnknown.h" "ComponentBase.cpp" "ComponentBase.h")

# TODO: Add tests and install targets if needed.
