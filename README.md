# Practica1SO-Majimenezh-Dpovedat
María Alejandra Jiménez Herrera
David Stiven Poveda Taborda 

El programa tiene 3 archivos c
inputPractica.c es la interfaz de usuario que recibe los datos para la búsqueda verificando que estén en los rangos requeridos 
cargarBinario.c es el que ordena los datos por medio de un hash y guarda la información que necesitamos en practicaISal.dat 
busquedaVuelo.c es el que se ejecuta con la búsqueda 

para la comunicación entre procesos usamos tuberías nombradas , la interfaz recibe los 3 datos (origen,destino,hora)y los manda a busquedaVuelo donde los recibe y 
realiza la búsqueda 

practicaISal.dat es el archivo binario que almacena los datos que saca cargarBinario, y a este archivo es sobre el que se realiza la búsqueda,

En el makefile ejecuta todo con  el comando make 
