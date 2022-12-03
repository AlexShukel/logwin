# Logwin

Navigation:

1. [How to build project](#project-build)

## Project build

### Prerequisites:

-   [Cmake](https://cmake.org/download/) executable
-   [Ninja](https://github.com/ninja-build/ninja/releases) executable

Add paths to these executables in `PATH` environment variable. [how to add environment variable on windows](<https://learn.microsoft.com/en-us/previous-versions/office/developer/sharepoint-2010/ee537574(v=office.14)>)

### Steps to build:

1. Run this command in project root. This will generate cmake configurations.

```shell
cmake -B build -G Ninja
```

2. Run this command in project root. This will build the project.

```shell
cmake --build build
```

TODO: add separate builds for debug and release

3. logwin.exe will appear in `build/cli/src` directory
