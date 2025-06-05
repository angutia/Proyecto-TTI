# Proyecto TTI 
## Instrucciones para compilar y ejecutar la aplicación principal
```
g++ tests/EKF_GEOS3.cpp src/*cpp -lm -std=c++23 -o bin/main.exe
cd bin
main.exe
pause
```
## Instrucciones para compilar y ejecutar los tests unitarios
```
g++ tests/tests.cpp src/*.cpp -lm -std=c++23 -o bin/tests.exe
cd bin
tests.exe
pause
```