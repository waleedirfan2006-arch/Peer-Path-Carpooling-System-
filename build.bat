@echo off
echo ===================================================
echo   Compiling PeerPath Carpooling System (C++)
echo ===================================================

g++ -std=c++17 main.cpp Student.cpp Ride.cpp CarpoolSystem.cpp -o peerpath.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo [+] Compilation successful! Generated peerpath.exe
    echo [+] Run with: .\peerpath.exe
    echo ===================================================
) else (
    echo.
    echo [-] Compilation failed. Please inspect the errors above.
    echo ===================================================
)
