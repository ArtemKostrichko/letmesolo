# Matrix Calculator (C++23)

Team project for a matrix calculator in modern C++23.

## Planned modules
- `core` — matrix model and linear algebra
- `io` — input and output
- `util` — shared helpers
- `report` — report steps and polymorphic execution
- `app` — application entry point
- `tests` — unit and smoke tests

## Build
```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build