# sdl-imgui-example

An example of using [Dear ImGui](https://github.com/ocornut/imgui) with [SDL](https://libsdl.org).

![SDL and Dear ImGui](/img/screenshot.png "SDL and Dear ImGui")

More information in the following [article](https://decovar.dev/blog/2019/05/26/sdl-imgui/).

## Building

Assuming that dependencies will be resolved with [vcpkg](https://decovar.dev/blog/2022/10/30/cpp-dependencies-with-vcpkg/):

``` sh
$ cd /path/to/sdl-imgui-example
$ cmake --preset vcpkg-default-triplet
$ cmake --build --preset vcpkg-default-triplet
```
