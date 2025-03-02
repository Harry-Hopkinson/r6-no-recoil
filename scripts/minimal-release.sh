git switch main
g++ -static -O2 -s -o minimal.exe src/main.cpp -lgdi32 -luser32 -lkernel32 -mwindows
