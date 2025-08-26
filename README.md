# order-ci-demo

Minimal C++ project with:
- Dependency injection via interface
- Unit tests using GoogleTest + GoogleMock
- GitHub Actions CI
- CMake build, g++ toolchain (Debian/Ubuntu friendly)

## Build & Test (local)

```bash
sudo apt update
sudo apt install -y build-essential cmake git

cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j

# run tests
ctest --test-dir build --output-on-failure

# run app
./build/order_app
