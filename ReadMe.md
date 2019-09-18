# Module to map events

## Install

1. Install dependencies
```
sudo apt install libeigen3-dev cmake
``` 
2. Compile module
```
git submodule update --init --recursive
mkdir build && cd build && cmake -DPYTHON_EXECUTABLE:FILEPATH=`which python3` -DCMAKE_BUILD_TYPE=Releas .. && cmake --build . && cd ..
```

## Test

1. Install additional python packages
```
pip3 install -r requirements.txt
```

2. Test (TODO)
```
```
 
## Overview

TODO
