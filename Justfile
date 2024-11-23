conf:
    cmake -B build -DCMAKE_BUILD_TYPE=Debug

build:
    cmake --build ./build

run:
    ./build/raytracing.cpp > output.ppm

clean:
    rm -rf ./build/*
