all: ejecutarInput

# Compila input
compilarInput: inputPractica.c
	gcc -o inputPractica inputPractica.c
	
# Compilar buscador
compilarBuscador: busquedaVuelo.c
	gcc -o busqueda busquedaVuelo.c
	
# Crear terminal y compila y ejecuta menu
ejecutarInput: compilarInput crearTerminal inputPractica
	./inputPractica
	
# Compila buscador, crea una nueva terminal y ejecuta buscador en esa terminal
crearTerminal: compilarBuscador
	gnome-terminal -- ./busqueda
	
ejecutarBuscador: compilarBuscador busqueda
	./busqueda
