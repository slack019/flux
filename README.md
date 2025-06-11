<h1 align ="center"> 🔨 Flux </h1> 

**C++ 20 modern utils and containers library**


<h2 align="center"> Installation </h2> 

**Use git for install**

```bash 
git clone --depth 1 https://github.com/slack019/flux.git flux/ 
```

<h2 align="center"> Build  </h2>

**You can use install.sh script or build independently**

**CMake Build Options:**

`-DFLUX_SHARED_LIBS` - if you want to build shared library (ON/OFF)

`-DBUILD_EXAMPLES` - if you want to build library examples(ON/OFF)

`-DBUILD_TESTS` - if you want to build library tests(ON/OFF)

`-DFLUX_INSTALL` - Generate target for installing flux (ON/OFF)

```bash
 
mkdir build 
cd build 
sudo cmake -S .. -B . -DFLUX_INSTALL=ON -DCMAKE_INSTALL_PREFIX=/usr/local 
cmake --build . --target install 

```

<h2 align="center"> Usage </h2>

```cpp

#include <iostream> // for std::cout

#include <flux/containers/string.hpp>

auto main() -> int { 
    fl::containers::string str {"Hello"};

    std::cout << str + " World!" << std::endl;
    return 0; 
} 

```


<h2 align="center"> License </h2>

Project have [MIT](https://opensource.org/license/mit) license  
