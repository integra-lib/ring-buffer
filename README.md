# ring-buffer

Fixed-size ring buffer over std::array, allocates nothing.

Part of [integra-lib](https://gitlab.integrasources.com/internal-projects/integra-lib).
Header-only C++20, no exceptions, no RTTI.

## Use it

```bash
git submodule add ../ring-buffer.git external/integra/ring-buffer
```

```cmake
add_subdirectory(external/integra/ring-buffer)
target_link_libraries(app PRIVATE Integra::ring_buffer)
```

```cpp
#include <integra/ring_buffer.hpp>
```

## Develop it

```bash
cmake -S . -B build && cmake --build build -j && ctest --test-dir build
```

Tests are built only when this repository is the top-level project, so a consumer
never builds them. Style and pipeline come from the `ci-shared` submodule; run
`git submodule update --init` before `pre-commit`.
