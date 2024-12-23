conf:
    cmake -B build -DCMAKE_BUILD_TYPE=Debug

build:
    cmake --build ./build --parallel

run:
    ./build/raytracing.cpp > output.ppm

clean:
    rm -rf ./build/*

conf-rel:
    cmake -B build -DCMAKE_BUILD_TYPE=Release
