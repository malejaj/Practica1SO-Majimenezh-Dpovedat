#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define TABLE_SIZE 5904703

void generarArchivoSal() {
	char nombreArchivoEnt[] = "practica1.csv";
 	char nombreArchivoSal[] = "practicaISal.dat";
 	int i;
 	 
 	FILE *arch = fopen(nombreArchivoEnt, "r");
 	if (arch == NULL) {
 		printf("Problema al abrir el archivo %s. Termina el programa.\n", nombreArchivoEnt);
 		exit(-1);
 	}
 	
 	FILE *archSal = fopen(nombreArchivoSal, "wb");
 	if (archSal == NULL) {
 		printf("Problema al crear el archivo %s. Termina el programa.\n", nombreArchivoSal);
 		exit(-1);
 	}
 	 	
 	// Primero llegamos a la segunda linea
 	char linea[1000]; 
	 		 
 	fgets(linea, sizeof(linea), arch); // Saltamos los labels del csv
 	
 	// Recorremos todas las lineas del csv:
 	for (i=0; i<TABLE_SIZE; i++) {
 		char nro1[20] = "\0";
		int j = 0, k = 0;
		
		// Leemos linea por linea
 		fgets(linea, 1000, arch);
		
		// Extracción de campos individuales:
		
		// Id origen:
		while (linea[j] != ',') nro1[k++] = linea[j++];
		nro1[j] = '\0';
 		int idOrigen = atoi(nro1);	

 		j++;
 		k = 0;
 		
 		// Id destino:
		char nro2[5] = "\0";
 		while (linea[j] != ',') nro2[k++] = linea[j++];
 		nro2[j] = '\0';	
 		int idDestino = atoi(nro2);
 		
 		j++;
 		k = 0;
 		
 		// Hora:
 		char nro3[5] = "\0";
 		while (linea[j] != ',') nro3[k++] = linea[j++];
 		nro3[j] = '\0';
 		int hora = atoi(nro3);
 		
 		j++;
 		k = 0;
 		
 		// Tiempo medio:
 		char nro4[10] = "\0";
 		while (linea[j] != ',') nro4[k++] = linea[j++];
 		nro4[j] = '\0';
 		float meanTime = atof(nro4);
 		
		// Hash:
		strcat(nro1, nro2);
		strcat(nro1, nro3);
		int hashNum = atoi(nro1) % 999983;
		
		
		// Escritura en el archivo binario:
		fseek(archSal, hashNum*16, SEEK_SET);
			
		// ID ORIGEN
		fwrite(&idOrigen, sizeof(int), 1, archSal);
		
		//ID DESTINO
		fwrite(&idDestino, sizeof(int), 1, archSal); 
		
		// HORA
		fwrite(&hora, sizeof(int), 1, archSal);
 		
 		// MEAN TIME
		fwrite(&meanTime, sizeof(float), 1, archSal);
 		
 		printf("%i, %i, %i, %.2f\n", idOrigen, idDestino, hora, meanTime);
 	}
 	
 	fclose(arch);
 	fclose(archSal); 	
}


int main() {	
	generarArchivoSal();		
 	return 0;
}
