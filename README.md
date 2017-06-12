# File splitter and recover

---
## Acerca del programa

Es una implementación de RAID 5 utilizando pipes y procesos en paralelo. Permite dividir y recuperar archivos. Para mas info pinche [aqui](http://es.wikipedia.org/wiki/RAID#RAID_5 "Raid 5")

## Compilacion

Ubiquese en la carpeta principal (donde se encuentra el Makefile) y ejecute `make`
para compilar los 3 ejecutables: main, CUT y JOIN. El codigo objeto se compilara 
en la carpeta "build/obj" y los ejecutables en la carpeta "build/".


## Ejecucion

Para la ejecucion debe ejecutar el programa principal __`raid5`__ junto a las
opciones __`--cut <input> N`__ si quiere cortar el archivo _input_ en _N_ partes, o con
__`--join <archivo-original>`__ si quiere restaurar el archivo original.

Ejm:

> Si quiere cortar el archivo doc.pdf en 6 partes debe ejecutar:  
> __`$ ./raid5 doc.pdf --cut  6`__  
>
> Si quiere volver volver a unir doc.pdf entonces:  
> __`$ ./raid5 --join doc.pdf`__

Debe estar en la carpeta "build/" para ejecutar el programa de la forma antes vista.

El programa JOIN recuperara la parte faltante - si es que hubiera - y unira todas
las partes para restaurar el programa original.
