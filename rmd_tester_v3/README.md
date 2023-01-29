# libhal-starter

## 🧰 Setup

1. [Setup libhal tools](https://libhal.github.io/prerequisites/)
2. Add `libhal-trunk` remote conan server

    ```bash
    conan remote add libhal-trunk https://libhal.jfrog.io/artifactory/api/conan/trunk-conan --insert
    conan config set general.revisions_enabled=True
    ```

    > The "trunk" repository represents the latest packaged code based on
    > github.
    >
    > This command will insert `libhal-trunk` as the first server to check
    > before checking the conan center index. The second command will enable
    > revision mode which is required to use the `libhal-trunk` conan package
    > repository.

## 🏗️ Building Demos

Before building any demos, we have to make the build directory

```bash
cd demos
mkdir build
cd build
```

### Debug Builds

Debug builds are helpful as they reduce the amount of compile time optimizations
in order to make the debugging experience better. This comes at the cost of
slower code and larger binary sizes.

To build with this level:

```
conan install .. -s build_type=Debug --build=missing
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
make
```

### Release Builds

Release builds are harder to debug but are faster and have smaller binary sizes.

To build with this level:

```
conan install .. -s build_type=Release --build=missing
cmake .. -DCMAKE_BUILD_TYPE=Release" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
make
```
