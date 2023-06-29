# LAB 2
*Szeregowanie*

# TODO
1. Przeanalizować funkcję `schedule`?? (w `threads.c`)
2. Dodać wartość początkową w `slots` w deskryptorze procesu
3. Modyfikacja funkcji `schedule` tak, aby przełączała na inny wątek tylko wtedy, kiedy liczba jest równa 0, w przeciwnym wypadku zmniejsza liczbę o 1
4. Dodać wywołanie systemowe, które pozwala na zmianę bazowej wartości `slots` w deskryptorze procesu
5. Jakieś procesy, które mają ilość kwantów nietypową i zobaczyć co się dzieje
6. Deskryptor procesu w `proc_start`, a deskryptor wątku w `proc_threadCreate`

## Komendy

### Build systemu
`cd ~/phoenix-rtos-project`  
`TARGET=ia32-generic-qemu ./phoenix-rtos-build/build.sh clean all`  

### Start systemu
`qemu-system-i386 -cpu pentium3  -smp 1  -serial stdio -display curses -hda ~/phoenix-rtos-project/_boot/ia32-generic-qemu/phoenix.disk -netdev user,id=net0   -device rtl8139,netdev=net0`  
`cd /usr/bin`

### Start systemu

## Inne

## Gdzie trzeba wprowadzać zmiany
* `/phoenix-rtos-project/phoenix-rtos-kernel/proc/threads.c` 
* `/phoenix-rtos-project/phoenix-rtos-kernel/proc/threads.h` 
* `phoenix-rtos-kernel\syscalls.c`
* `phoenix-rtos-kernel\posix\posix.h`
* `phoenix-rtos-kernel\posix\posix.c`

### Co trzeba oddać 

