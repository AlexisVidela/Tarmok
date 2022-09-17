#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include"TarmokLib.h"
#define SIZE 200
/*-----Biblioteca-----
typedef struct: define un tipo de estructura
malloc: cantidad de memoria en bytes
sizeof(): saber el tamaño del parameto pasado()
NULL : indica a ningun lado
EXIT_FAILURE :indicar que una función terminó con alguna falla
fopen : abrir un archivo txt
fclose: cierra un archivo txt
fwrite: escribe un archivo
fread : lee un archivo
fflush: limpia canal de flujo
feof : devuelve un valor distinto de cero si una operación de lectura ha intentado leer más allá del final del archivo
fgets: lee caracter de una linea de un archivo
atoi/atof: guarda una cadena (arch) en una VAR en forma de Int(entero)/Float(decimal)
strcpy: copia la cadena a la cual señala
strcmp: evalua que la cadena de caracteres sea exactamente igual

*/


int op,i;
Nodo *ListNodo;
Arreglo ListA;
Arreglo Direc;
Arreglo AnioA;
Arreglo DelP;
Movie pelicula;
int Gen,Opc5,CantDP;
//Programa Principal
int main(){

	
	DeTxtALista(&ListNodo);
	DeListaaArreglo(ListNodo,&ListA);
	
	
	do{
		MenuPrincipal();
		scanf("%d",&op);
		switch(op){
			case 1: {
				MasPopulares(ListA);
				break;
			};
			case 2: {
				Depurar_Arreglo(ListA,&Direc);
				CantPelixDirec(ListA,Direc);
				break;
			}
			case 3: {
				Depurar_ArregloXanio(ListA,&AnioA);
				MasCarasxAnio(ListA,AnioA);
				break;
			}
			case 4: {
				printf("--------Generos disponibles--------\n");
				MenuGenero();
				scanf("%d",&Gen);
				PeliXGen(Gen,ListA);
				break;
			}
			case 5: {
				printf("Recomendacio por:\n [1]Genero\n [2]Rating\n");
				scanf("%d",&Opc5);
				switch(Opc5){
					
				 case 1:{
				 	MenuGenero();
				 	scanf("%d",&Opc5);
				 	RecmXGen(Opc5,ListA);
					break;
				 }
				 case 2:{
				 	RecmXRat(ListA);
					break;
				 }
				
				}
				break;
			}
			case 6: {
				Guardado_ArchBin(ListA);
				Listar_ArchBin(ListA);
				break;
			}
			case 7:{
					printf("Cuantas Peliculas quiere Borrar? \n");
					scanf("%d",&CantDP);
					i=1;
					while(i<=CantDP){
						printf("Pelicula Num : \n");
						scanf("%d",&DelP.Mv[i].anio);
						i++;
					}
					DelP.cant=CantDP;
					DeletPeli(DelP,&ListA,CantDP);
				break;
			}
			case 8: {
				MostrarArreglo(ListA);
				break;
			}
			case 9: {
				GuardarTxt(ListA);
				break;
			}
			case 10: {
				CartelSalir();
				break;
			}
			default: {
				printf("Ingrese un valor entre 1 y 10.\n");
			}	

		}
	}while(op != 10);
	
return 0;
}





