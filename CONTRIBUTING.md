# Contributing to twopow

Thank you for your interest in contributing to twopow. We hold this
single-function library to the same standard as any production system.

## Development setup

```bash
git clone https://github.com/dalamber/twopow.git
cd twopow
cmake --preset default
cmake --build --preset default
ctest --preset default
```

## Coding standards

- Code must pass `clang-format` (config in `.clang-format`) and `clang-tidy`.
- All changes require accompanying tests. Coverage must not regress.
- Commit messages follow [Conventional Commits](https://conventionalcommits.org).

## Pull requests

1. Fork and create a feature branch.
2. Ensure the full matrix passes locally where possible.
3. Open a PR using the provided template; link any related issue.

All contributions are licensed under Apache-2.0.
