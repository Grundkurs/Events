Events
=========

2D-Plattformer based on SFML Game Development By Example by Raimondas Pupius

Depenencies
=================
- SFML 2.5

- GCC 10.2.0 (Mingw-W64)

Compiling
=================

On Windows using MinGW-W64 Compiler
1. create subfolder in Source-Directory of CMakeLists.txt
2. add SFML-DLL Files to subfolder
2. open subfolder in your command-line-tool. 
   ```bash
   $ cmake -G "MinGW Makefiles" ..
   $ mingw32-make
   ```
3. start created executable "Events.exe"