#! /bin/sh

# rm -rf build
# cmake -B build
# cmake --build build -j 8

rm -rf public
cp -r static public
./build/youpi-static.out
mv index.html human.html face.html human.svg face.svg public/

python -m http.server 8080 -d public/

