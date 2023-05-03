# LAB 3
*Synchronizacja, semafory*

# TODO
1. O co chodzi?
2. Implementacja

## Komendy
1. Start -> Ubuntu
2. `cd /mnt/d/__repos/wut_soi/lab_3`

### Build systemu

### Start systemu

## Inne

## Gdzie trzeba wprowadzać zmiany

### Co trzeba oddać 
Przy realizacji zadania do synchronizacji należy wykorzystać semafor (tylko operacje p i v) – klasa Semaphore zdefiniowana w pliku monitor.h znajdującym się na stronie przedmiotu. Zadanie należy wykonać z użyciem wątków (korzystając ze zmiennych globalnych). Bufor 9 elementowy FIFO. Danych jest 2 producentów i 2 konsumentów. Producenci produkują losowe liczby umieszczając je w buforze. Konsument A konsumuje wyłącznie liczby parzyste. Konsument B wyłącznie liczby nieparzyste. Odczyt (usunięcie) jest dozwolone, gdy liczba elementów w buforze jest większa niż 3.  

**stan semafora S**  
... jest to liczba jednostek zasobu, na jakie zgłoszono zapotrzebowanie  

**operacja V** 
... służy do zwalniania zasobu, po tym jak proces przestał go używać, możliwe, że od *verhoog*

**operacja P**   
... służy do pobierania zasobu, kiedy stanie się dostępny, możliwe, że od *proberen*    