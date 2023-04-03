# LAB 1
*Wywołania systemowe*

## Komendy

### Build systemu
`cd ~/phoenix-rtos-project`
`TARGET=ia32-generic-qemu ./phoenix-rtos-build/build.sh clean all`

### Start systemu
`qemu-system-i386 -cpu pentium3  -smp 1  -serial stdio -display curses -hda ~/phoenix-rtos-project/_boot/ia32-generic-qemu/phoenix.disk -netdev user,id=net0 -device rtl8139,netdev=net0`
`cd /usr/bin`

## Inne
Na razie pomijam część z `telnet`, bo wygląda, że wywołania systemowe działają dobrze bez tego...  
Na razie pomijamy problem blokady deskryptorów przez inne procesy (tzn. proces może blokować > 1 proces, ale w tym przypadku tak nie będzie) -> przy rekusji

## Gdzie trzeba wprowadzać zmiany
* `phoenix-rtos-kernel\include\syscalls.h`
* `phoenix-rtos-kernel\syscalls.c`
* `phoenix-rtos-kernel\posix\posix.h`
* `phoenix-rtos-kernel\posix\posix.c`

main.c i Makefile powinny 'pojawić się' same...

### Co trzeba oddać 
1. `syscalls.c`
2. `syscalls.h`
3. `main.c`