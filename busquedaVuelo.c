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

typedef struct {
	int idOrigen;
	int idDestino;
	int hora;
} vueloInterfaz;


void buscarVuelo(int idOrigen, int idDestino, int hora) {

 	int idO, idD, h, hashNum;
 	float meanTime;
 	char strIDO[5], strIDD[5], strHora[3];
 	
 	// Abrir archivo binario de salida:
	FILE *arch = fopen("practicaISal.dat", "rb");
 	if (arch == NULL) {
 		printf("Problema al crear el archivo %s. Termina el programa.\n", "practicaISal.dat");
 		exit(-1);
 	}
 	
 	// Hash
 	sprintf(strIDO, "%d", idOrigen);
 	sprintf(strIDD, "%d", idDestino);
 	sprintf(strHora, "%d", hora);
 	
 	strcat(strIDO, strIDD);
	strcat(strIDO, strHora);
	hashNum = atoi(strIDO) % 999983;
	
	// Lectura de cada dato individual
 	fseek(arch, hashNum*16, SEEK_SET);
 	fread(&idO, sizeof(int), 1, arch);
 	fread(&idD, sizeof(int), 1, arch);
 	fread(&h, sizeof(int), 1, arch);
 	fread(&meanTime, sizeof(float), 1, arch);

 	//printf("Se encontro: %i, %i, %i, %.2f\n", idO, idD, h, meanTime);
 	
 	if (idO == idOrigen && idD == idDestino && h == hora) {
		printf("Se encontro el vuelo: %i, %i, %i con tiempo de vuelo medio: %.2f.\n", idO, idD, h, meanTime);
 	} else {
 		fputs("No se ha encontrado ningun vuelo.\n", stdout);
 	}
 	
 	fclose(arch);
}


int main() {	
	vueloInterfaz dataVuelo;
	
	char *tuberia = "./tuberiaInterfaz";
    	char *tuberia2 = "./buscador";
    	
	int fd = open(tuberia, O_RDONLY);
	if (fd == -1) {
		perror("No se pudo abrir la tuberia: \n");
		exit(-1);
	}
	
	if(read(fd, &dataVuelo, sizeof(vueloInterfaz)) == -1) {
		perror("No se pudo leer de la tuberia: ");
	}
	
	close(fd);
	
	printf("La data que viene por la tuberia es %i, %i, %i\n", dataVuelo.idOrigen, dataVuelo.idDestino, dataVuelo.hora);
	
	buscarVuelo(dataVuelo.idOrigen, dataVuelo.idDestino, dataVuelo.hora);

	fputs("Esperando...\n", stdout);
	int a;
	int x = scanf("%d", &a);
 	return 0;
}


