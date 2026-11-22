# Firefox 115 ESR mingw build (scratch, private)

Builds Firefox 115.45.0esr for 32-bit Windows (`i686-w64-mingw32`) on a GitHub-hosted runner, for testing on a ReactOS VM.

- The Firefox source is **not** stored here. The workflow downloads the release tarball from Mozilla and checks its SHA512 against the published value.
- `patches/` holds the scratch changes, applied on top of that tarball with `patch -p1`.
- `stubs/fake_fxc.c` is a stand-in for the Windows shader compiler. It writes placeholder shader bytecode, so Direct3D 11 shader creation fails at run time. An empty `d3dcompiler_47.dll` is also created.
- `third_party/glslopt-shim` is a pass-through replacement for the `glslopt` crate, which does not compile with MinGW headers. Shaders are not optimized.
- `mozconfig.in` is the build configuration; the workflow fills in the paths.

Run the build from the Actions tab (`build-firefox-115-mingw`, manual trigger). The output is a zip of `dist/bin`, kept for 3 days.

Limits: a job is capped at 6 hours. If the build does not finish in one job, it has to be split across runs with a cache, which is not set up yet.
