# ShSerial
![linux_badge](linux-status.svg)
## [Linux/Unix build logs:](https://github.com/MrSinho/ShCI)
  
```bash$$shci call$$:
apt install -y wget gcc cmake make gdb
```

```bash$$shci call$$:
cd ShSerial && mkdir build && cd build && cmake -G"MinGW Makefiles" -DSH_SERIAL_BUILD_EXAMPLE=ON .. && cmake --build .
