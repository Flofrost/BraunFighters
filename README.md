# Braun Fighters

## Compiling

Dependencies:
    CImg : libcimg-dev

Build:
    g++ main.cpp sources/CPU.cpp -o BraunFighters.run -Dcimg_display=1 -lX11 -Wfatal-errors -Wno-narrowing