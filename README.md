# Usage

- Compile inline_det function generator:
```g++ -o gen inline_det_gen.cpp```

- Create inline_det_#.hpp file:
```gen <matrix_size>```

`gen 7` is maximum that works fine (probably). This is assuming you actually will try to compile generated file. If you want more then `gen 11` is maximum i managed to wait for; it also generates file ~4.5GB long.

- Change lines 6-8 in `main.cpp` so they match your chosen matrix size
```C++
#define MAT_SIZE 7
#define inline_det inline_det_7
#include "inline_det_7.hpp"
```

- Compile main.cpp
```g++ -o main main.cpp```

- Run it:
```./main```
