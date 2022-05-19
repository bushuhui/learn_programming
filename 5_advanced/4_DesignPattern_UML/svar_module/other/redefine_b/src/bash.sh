g++ -fPIC a.cpp -shared -o libA.so
g++ -fPIC b.cpp -shared -o libB.so
g++ main.cpp libA.so libB.so -o main  -Wl,-rpath=. 
