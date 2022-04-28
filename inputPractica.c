#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

typedef struct {
	int idOrigen;
	int idDestino;
	int hora;
} vuelo;


int idLugar(int *a)
{
    while (*a < 1 || *a > 1160)
    {
        printf("El id ingresado no es valido; el valor debe estar entre 1 y 1160. Por favor ingrese nuevamente el valor\n");
        scanf("%d", a);
    }
}

int formatoHora(int *a)
{
    while (*a < 0 || *a > 23)
    {
        printf("La hora ingresada no es valida; el valor debe estar entre 0 y 23. Por favor ingrese nuevamente el valor\n");
        scanf("%d", a);
    }
}

void sendData(char *tuberia, vuelo **viaje) {	
	int fd = open(tuberia, O_WRONLY);
	if (fd == -1) {
		perror("No se pudo abrir la tuberia: \n");
		exit(-1);
	}
	
	if(write(fd, *viaje, sizeof(vuelo)) == -1) {
		perror("No se pudo escribir en la tuberia: \n");
	}
	
	close(fd);
}

int main()
{
	int opc = 0;
	// Ruta del archivo FIFO (tuberia)
    	char *tuberia = "./tuberiaInterfaz";
    	char *tuberia2 = "./buscador";
    	
	if (mkfifo(tuberia, 0777) == -1) {
		if (errno != EEXIST) { // Queremos que nos de los errores solamente de cuando el arhivo no este creado
			perror("Could not create fifo file: \n");			
		}
	}
	
	srand(time(NULL));
	vuelo * datos = malloc(sizeof(vuelo));
	vuelo **viaje = &datos; 


	do
	{
		printf("Bienvenido\n\n");
		printf("1. Ingresar origen\n");
		printf("2. Ingresar destino\n");
		printf("3. Ingresar hora\n");
		printf("4. Buscar tiempo de viaje medio\n");
		printf("5. Salir\n");
		scanf("%d", &opc);
		int origen;
		int destino;
		int hora;
		float viajeMedio = 0;
		switch (opc)
		{
		case 1:

		    printf("Ingrese el ID del origen ");
		    scanf("%d", &origen);
		    idLugar(&origen);
		    printf("El id ingresado fue %d\n", origen);
		    (*viaje)->idOrigen = origen;
		    break;

		case 2:

		    printf("Ingrese el ID del destino ");
		    scanf("%d", &destino);
		    idLugar(&destino);
		    printf("El id ingresado fue %d\n", destino);
		    (*viaje)->idDestino = destino;
		    break;

		case 3:
		    printf("Ingrese hora del dia ");
		    scanf("%d", &hora);
		    formatoHora(&hora);
		    printf("\nLa hora ingrasado fue %d\n", hora);
		    (*viaje)->hora = hora;
		    break;

		case 4:	
			printf("%i, %i, %i\n", (*viaje)->idOrigen, (*viaje)->idDestino, (*viaje)->hora);
			sendData(tuberia, viaje);
		    break;
		case 5:
		    printf("Adios\n");
		    // ELimina el archivo FIFO
		    free(datos);
		    unlink(tuberia);
		    break;

		default:
		    printf("Opcion incorrecta\n");
		    break;
		}
	} while (opc != 5);
}


