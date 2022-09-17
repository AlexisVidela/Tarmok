#include <stdio.h>
#include<stdlib.h>
#include<string.h>

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
//Arreglo con inf de Pelicula
typedef struct {
	int id;
	char titulo[60];
	char director[60];
	char genero[60];
	int likes;
	int cantidadVotantes;
	float votoPromedio;
	int anio;
	float costo;
	char color[60];
	float rating;
} Movie;

//Doblete o Nodo
typedef struct nodos {
	Movie inf;
	struct nodos *next;
} Nodo;

//Arreglo para peliculas a color
typedef struct {
	Movie Mv[SIZE];
	int cant;
} Arreglo;

//Crea puntero
Nodo * CrearNodo(Movie pelicula) {
	//lexico local
	Nodo *nuevo;
	//inicio de la accion
	nuevo = (Nodo *) malloc (sizeof(Nodo));
	if (nuevo==NULL) {
		exit(EXIT_FAILURE);
	} else {
		nuevo->inf = pelicula;
		nuevo->next=NULL;
	}
}

//Inserta un nodo al comienzo de la lista
void Insertar(Nodo **primero,Movie peli) {
//lexico local
	Nodo *nuevo;
//inicio de la accion
	nuevo = (Nodo *) malloc (sizeof(Nodo));
	nuevo->inf = peli;
	nuevo->next = *primero;
	*primero=nuevo;
}

//Muestra toda la lista
void MostrarLista(Nodo *primero) {
	while(primero!=NULL) {
		printf("%s",primero->inf.titulo);
		primero = primero->next;
	}
}

//pasa toda la inf del Txt a Lista
void DeTxtALista(Nodo **primero) {
	//Lexico Local
	Movie peli;
	char cadena[60];
	FILE *f;
	int i;
	f = fopen("peliculas.txt", "r");
	i = 1;
	//inicio de la accion
	while(!feof(f)) {
		fgets(cadena, 60, f);
		peli.id = atoi(cadena);
		fgets(cadena,60,f);
		strcpy(peli.titulo,cadena);
		fgets(cadena,60, f);
		strcpy(peli.director,cadena);
		fgets(cadena,60,f);
		strcpy(peli.genero,cadena);
		fgets(cadena,60,f);
		peli.likes = atoi(cadena);
		fgets(cadena,60,f);
		peli.cantidadVotantes = atoi(cadena);
		fgets(cadena,60,f);
		peli.votoPromedio = atof(cadena);
		fgets(cadena,60,f);
		peli.anio = atoi(cadena);
		fgets(cadena,60,f);
		peli.costo = atof(cadena);
		fgets(cadena,60,f);
		strcpy(peli.color,cadena);
		Insertar(primero,peli);
	}
	fclose(f);
}

//verifica que peliculas (lista) son a color y las guarda (arreglo)
void DeListaaArreglo(Nodo *prim, Arreglo *dato) {
//lexico local
	int i;
//inicio de la accion
	i = 1;
	while(prim != NULL) {
		if((strcmp (prim->inf.color,"Color\n")==0) || (strcmp (prim->inf.color,"Color")==0)) {
			dato->Mv[i].id = prim->inf.id;
			strcpy(dato->Mv[i].titulo, prim->inf.titulo);
			strcpy(dato->Mv[i].director,prim->inf.director);
			strcpy(dato->Mv[i].genero,prim->inf.genero);
			dato->Mv[i].likes = prim->inf.likes;
			dato->Mv[i].cantidadVotantes = prim->inf.cantidadVotantes;
			dato->Mv[i].votoPromedio = prim->inf.votoPromedio;
			dato->Mv[i].anio = prim->inf.anio;
			dato->Mv[i].costo = prim->inf.costo;
			strcpy(dato->Mv[i].color,prim->inf.color);
			i = i + 1;
		}
		prim = prim->next;
		dato->cant = i;
	}
}

//muestra el arreglo con todas las peliculas
void MostrarArreglo(Arreglo dato) {
//lexico local
	int i;
//inicio de la accion
	for(i=1; i<dato.cant; i++) {
		printf("id: %d, pelicula N°: %d \n",dato.Mv[i].id,i);
		printf("Titulo: %s",dato.Mv[i].titulo);
		printf("Director: %s",dato.Mv[i].director);
		printf("Genero: %s",dato.Mv[i].genero);
		printf("Likes: %d \n",dato.Mv[i].likes);
		printf("Cantidad De Votantes: %d\n",dato.Mv[i].cantidadVotantes);
		printf("Voto Promedio: %f \n",dato.Mv[i].votoPromedio);
		printf("anio: %d \n",dato.Mv[i].anio);
		printf("costo: %f \n",dato.Mv[i].costo);
		printf("color: %s \n",dato.Mv[i].color);
	}
}

//guarda en un nuevo arreglo 1 pelicula por cada director
void Depurar_Arreglo(Arreglo dato,Arreglo *dato2) {
	//lexico local
	int ii,jj,kk;
	int Dif;

	//inci0
	ii=1;
	kk=2;		//ka vale 2 por que en k1 ya se coloco el 1er elemento como unico (que no se repite aun  *ref)
	Dif=0;
	dato2->Mv[ii] = dato.Mv[ii];  //asigno el 1er valor de mi arreglo al nuevo arreglo  (*ref)
	while(ii<dato.cant) {       //mientras el arreglo principal no llegue al final
		jj=1;				//jota volvera al valor inicial para poder comparar el nuevo arreglo con el nuevo elemento seleccionado del arreglo principal
		while(jj<kk) {				//mientras el arregle nuevo no supere su total
			if(strcmp (dato.Mv[ii].director,dato2->Mv[jj].director)==0) {  //compare el arreglo 1 con todo el arreglo 2
				Dif=0;								//si son iguales Dif es Falso
				jj=kk;								//jota terminara su ciclo por que ya hay un numero igual a el
			} else {
				Dif=1;									//si son diferente Dif es Verdadero
			}
			jj++;		//si jota es distinto ciclara
		}

		if (Dif==1) {				//si el numero que comparamos es diferente lo agregamos al nuevo arreglo
			dato2->Mv[kk]=dato.Mv[ii];				//lo agrego en una nueva posicion al final del nuevo arreglo
			kk=kk+1;  //ka se le sumara 1 para un nuevo elemento
		}
		ii++;  //a ii se le suma 1 para hacer todo el ciclado de arreglo nuevo para comparar el nuevo elemento en ii con todo el arreglo nuevo en busca de ver si se repite o no
	}
	dato2->cant=kk;  //guardo la medida del nuevo arreglo depurado
}

//compara el arreglo Orig con el arrreglo Depurado
void CantPelixDirec(Arreglo dato,Arreglo dato2) {
	//lexico local
	int ii,jj;
	int cantP;
	//incio
	jj=1;
	while(jj<dato2.cant) { //mientras el nuevo arreglo no llegue a su final
		cantP=0;			//cantidad de peliculas sera 0
		ii=1;
		while(ii<dato.cant) {			//mientras el arreglo principal no llegue a su final
			if(strcmp (dato2.Mv[jj].director,dato.Mv[ii].director)==0) { //comparar si el valor de arreglo principal en esa posicion es igual al valor de arreglo nuevo en esta posicion
				cantP++; //si es igual sumara 1 a cantP haciendo referencia a que tiene una pelicula mas producida x el
			} else {
			}
			ii++; //ciclar en arreglo principal  completo por cada seccion del nuevo arreglo asi buscara por cada director que cantidad de peliculas hizo
		}

		printf("Hizo %d Pelicula/s ",cantP); //y la cantida de veces que su nombre aparecio en una pelicula
		printf("el Director : %s",dato2.Mv[jj].director); //nombre del directon que se comparo con todo el arreglo principal
		jj++; //ciclo con un nuevo director todo lo anterior
	}
}

//guardar datos en un archivo Binario
int Guardado_ArchBin(Arreglo dato2) {
	//lexico local
	FILE *Arch_B;
	int ii;

	//inicio
	Arch_B = fopen("Peliculas.dat","wb");
	if (Arch_B == NULL) {
		return 0;
	}

	ii=1;
	while(ii<dato2.cant) { //mientras no sea el final del archivo
		printf("------escribiendo archivo binario------\n");
		fwrite(&dato2.Mv[ii],sizeof(Arreglo),1,Arch_B); //escribe en arreglo dentro del archivo (dirc de memoria del arreglo,tamaño c/ elem,cuantos arcivos va a escribir,el archivo)
		ii++; //cicla
	}
	fflush(Arch_B); //limpia canal de flujo
	fclose(Arch_B); //carramos el archivo
	return 1;
}

//muestra los datos guardados en un archivo Binario
int Listar_ArchBin(Arreglo dato2) {
	//lexico local
	FILE *Arch_B;
	int ii;
	//inicio
	Arch_B = fopen("Peliculas.dat","rb");
	if (Arch_B == NULL) {
		return 0;
	}
	for(ii=1; ii<dato2.cant; ii++) {
		printf("------leyendo archivo binario------\n");
		fread(&dato2.Mv[ii],sizeof(Arreglo),1,Arch_B);
		printf("AB_Titulo: %s",dato2.Mv[ii].titulo);
		printf("AB_Genero: %s",dato2.Mv[ii].genero);
		printf("AB_anio: %d\n",dato2.Mv[ii].anio);
	}
	fclose(Arch_B);
	return 1;
}

//muestra las 10 mas populares por likes
void MasPopulares(Arreglo dato) {
	//Lexico
	Movie Aux;
	int i,j;
	int Lim;
	//inicio
	Lim =dato.cant;
	i=2;
	while(i<Lim) {
		Aux=dato.Mv[i];
		j=i-1;
		while(j>0 && dato.Mv[j].likes<Aux.likes) {
			dato.Mv[j+1]=dato.Mv[j];
			j=j-1;
		}
		dato.Mv[j+1]=Aux;
		i=i+1;
	}
	printf("Top 10 Mas populares :\n");
	i=1;
	while(i<11) {
		printf("Pelicula : %s Likes :%d \n",dato.Mv[i].titulo,dato.Mv[i].likes);
		i++;
	}

}

//guarda en un nuevo arreglo 1 pelicula por anio
void Depurar_ArregloXanio(Arreglo dato,Arreglo *dato2) {
	//lexico local
	int ii,jj,kk;
	int Dif;

	//inci0
	ii=1;
	kk=2;		//ka vale 2 por que en k1 ya se coloco el 1er elemento como unico (que no se repite aun  *ref)
	Dif=0;
	dato2->Mv[ii] = dato.Mv[ii];  //asigno el 1er valor de mi arreglo al nuevo arreglo  (*ref)
	while(ii<dato.cant) {       //mientras el arreglo principal no llegue al final
		jj=1;				//jota volvera al valor inicial para poder comparar el nuevo arreglo con el nuevo elemento seleccionado del arreglo principal
		while(jj<kk) {				//mientras el arregle nuevo no supere su total
			if(dato.Mv[ii].anio==dato2->Mv[jj].anio) {  //compare el arreglo 1 con todo el arreglo 2
				Dif=0;								//si son iguales Dif es Falso
				jj=kk;								//jota terminara su ciclo por que ya hay un numero igual a el
			} else {
				Dif=1;									//si son diferente Dif es Verdadero
			}
			jj++;		//si jota es distinto ciclara
		}

		if (Dif==1) {				//si el numero que comparamos es diferente lo agregamos al nuevo arreglo
			dato2->Mv[kk]=dato.Mv[ii];				//lo agrego en una nueva posicion al final del nuevo arreglo
			kk=kk+1;  //ka se le sumara 1 para un nuevo elemento
		}
		ii++;  //a ii se le suma 1 para hacer todo el ciclado de arreglo nuevo para comparar el nuevo elemento en ii con todo el arreglo nuevo en busca de ver si se repite o no
	}
	dato2->cant=kk;  //guardo la medida del nuevo arreglo depurado
}

//ordena el arreglo1 por costo y el arreglo2 por anio y los va comparando
void MasCarasxAnio(Arreglo dato,Arreglo dato2) {
	//Lexico
	Movie Aux;
	int i,j,Mm,Mx;
	int Lim;
	//inicio
	printf("Cuantas peliculas por anio quiere ver? : \n");
	scanf("%d",&Mx);
	Lim =dato.cant;
	//----------ordane el arreglo por costo---------
	i=2;
	while(i<Lim) {
		Aux=dato.Mv[i];
		j=i-1;
		while(j>0 && dato.Mv[j].costo<Aux.costo) {
			dato.Mv[j+1]=dato.Mv[j];
			j=j-1;
		}
		dato.Mv[j+1]=Aux;
		i=i+1;
	}
	//------ordena el arreglo 2 por anio
	i=2;
	Lim=dato2.cant;
	while(i<Lim) {
		Aux=dato2.Mv[i];
		j=i-1;
		while(j>0 && dato2.Mv[j].anio<Aux.anio) {
			dato2.Mv[j+1]=dato2.Mv[j];
			j=j-1;
		}
		dato2.Mv[j+1]=Aux;
		i=i+1;
	}
	Lim =dato.cant;
	i=1;
	while (i<dato2.cant) {
		j=1;
		Mm=1;
		while(j<Lim) {
			if (dato2.Mv[i].anio==dato.Mv[j].anio) {
				if (Mm<=Mx) {
					printf("Top :%d [ %d ]---%s",Mm,dato.Mv[j].anio,dato.Mv[j].titulo);
					printf("costo: %f\n",dato.Mv[j].costo);
					printf("------------\n");
					Mm++;
				}
			}
			j++;
		}
		i++;
	}

}

//menu por genero
void MenuGenero() {
	printf("1] Action \n");
	printf("2] Comedy \n");
	printf("3] Adventure \n");
	printf("4] Drama \n");
	printf("5] Horror \n");
	printf("6] Sci-Fi \n");
	printf("7] Fantasy \n");
	printf("8] Animation \n");
}

//dependiendo el genero muestra las peliculas del genero elegido
void PeliXGen(int Gen,Arreglo dato) {
	int i;
	switch(Gen) {
		case 1: {
			i=1;
			while(i<dato.cant) {
				if((strcmp (dato.Mv[i].genero,"Action\n")==0) || (strcmp (dato.Mv[i].genero,"action\n")==0)) {
					printf("%s",dato.Mv[i].titulo);
				}
				i++;
			}
			break;
		}
		case 2: {
			i=1;
			while(i< dato.cant) {
				if((strcmp (dato.Mv[i].genero,"Comedy\n")==0) || (strcmp (dato.Mv[i].genero,"comedy\n")==0)) {
					printf("%s",dato.Mv[i].titulo);
				}
				i++;
			}
			break;
		}
		case 3: {
			i=1;
			while(i<dato.cant) {
				if((strcmp (dato.Mv[i].genero,"Adventure\n")==0) || (strcmp (dato.Mv[i].genero,"adventure\n")==0)) {
					printf("%s",dato.Mv[i].titulo);
				}
				i++;
			}
			break;
		}
		case 4: {
			i=1;
			while(i<dato.cant) {
				if((strcmp (dato.Mv[i].genero,"Drama\n")==0) || (strcmp (dato.Mv[i].genero,"drama\n")==0)) {
					printf("%s",dato.Mv[i].titulo);
				}
				i++;
			}
			break;
		}
		case 5: {
			i=1;
			while(i<dato.cant) {
				if((strcmp (dato.Mv[i].genero,"Horror\n")==0) || (strcmp (dato.Mv[i].genero,"horror\n")==0)) {
					printf("%s",dato.Mv[i].titulo);
				}
				i++;
			}
			break;
		}
		case 6: {
			i=1;
			while(i<dato.cant) {
				if((strcmp (dato.Mv[i].genero,"Sci-Fi\n")==0) || (strcmp (dato.Mv[i].genero,"sci-fi\n")==0)) {
					printf("%s",dato.Mv[i].titulo);
				}
				i++;
			}
			break;
		}
		case 7: {
			i=1;
			while(i<dato.cant) {
				if((strcmp (dato.Mv[i].genero,"Fantasy\n")==0) || (strcmp (dato.Mv[i].genero,"fantasy\n")==0)) {
					printf("%s",dato.Mv[i].titulo);
				}
				i++;
			}
			break;
		}
		case 8: {
			i=1;
			while(i<dato.cant) {
				if((strcmp (dato.Mv[i].genero,"Animation\n")==0) || (strcmp (dato.Mv[i].genero,"animation\n")==0)) {
					printf("%s",dato.Mv[i].titulo);
				}
				i++;
			}
			break;
		}
	}
}

//recomendadas por genero
void RecmXGen(int Opc5,Arreglo dato){
	int i,j;
	Movie Aux;
	//----------ordane el arreglo por votopromedio---------
	i=2;
	while(i<dato.cant) {
		Aux=dato.Mv[i];
		j=i-1;
		while(j>0 && dato.Mv[j].votoPromedio<Aux.votoPromedio) {
			dato.Mv[j+1]=dato.Mv[j];
			j=j-1;
		}
		dato.Mv[j+1]=Aux;
		i=i+1;
	}
	switch(Opc5) {
		case 1: {//genero action
			i=1;
			j=1;
			while(i<dato.cant) {
				if((strcmp (dato.Mv[i].genero,"Action\n")==0) || (strcmp (dato.Mv[i].genero,"action\n")==0)) {
					if (j<=5){
					printf("%d ) ---%s VtProm: %f\n",j,dato.Mv[i].titulo,dato.Mv[i].votoPromedio);
					j++;
					}
				}
				i++;
			}
			break;
		}
		case 2: {
			i=1;
			j=1;
			while(i<dato.cant) {
				if((strcmp (dato.Mv[i].genero,"Comedy\n")==0) || (strcmp (dato.Mv[i].genero,"comedy\n")==0)) {
				if (j<=5){
					printf("%d ) ---%s VtProm: %f\n",j,dato.Mv[i].titulo,dato.Mv[i].votoPromedio);
					j++;
					}
				}
				i++;
			}
			break;
		}
		case 3: {
			i=1;
			j=1;
			while(i<dato.cant) {
				if((strcmp (dato.Mv[i].genero,"Adventure\n")==0) || (strcmp (dato.Mv[i].genero,"adventure\n")==0)) {
				if (j<=5){
					printf("%d ) ---%s VtProm: %f\n",j,dato.Mv[i].titulo,dato.Mv[i].votoPromedio);
					j++;
					}
				}
				i++;
			}
			break;
		}
		case 4: {
			i=1;
			j=1;
			while(i<dato.cant) {
				if((strcmp (dato.Mv[i].genero,"Drama\n")==0) || (strcmp (dato.Mv[i].genero,"drama\n")==0)) {
				if (j<=5){
					printf("%d ) ---%s VtProm: %f\n",j,dato.Mv[i].titulo,dato.Mv[i].votoPromedio);
					j++;
					}
				}
				i++;
			}
			break;
		}
		case 5: {
			i=1;
			j=1;
			while(i<dato.cant) {
				if((strcmp (dato.Mv[i].genero,"Horror\n")==0) || (strcmp (dato.Mv[i].genero,"horror\n")==0)) {
				if (j<=5){
					printf("%d ) ---%s VtProm: %f\n",j,dato.Mv[i].titulo,dato.Mv[i].votoPromedio);
					j++;
					}
				}
				i++;
			}
			break;
		}
		case 6: {
			i=1;
			j=1;
			while(i<dato.cant) {
				if((strcmp (dato.Mv[i].genero,"Sci-Fi\n")==0) || (strcmp (dato.Mv[i].genero,"sci-fi\n")==0)) {
				if (j<=5){
					printf("%d ) ---%s VtProm: %f\n",j,dato.Mv[i].titulo,dato.Mv[i].votoPromedio);
					j++;
					}
				}
				i++;
			}
			break;
		}
		case 7: {
			i=1;
			j=1;
			while(i<dato.cant) {
				if((strcmp (dato.Mv[i].genero,"Fantasy\n")==0) || (strcmp (dato.Mv[i].genero,"fantasy\n")==0)) {
				if (j<=5){
					printf("%d ) ---%s VtProm: %f\n",j,dato.Mv[i].titulo,dato.Mv[i].votoPromedio);
					j++;
					}
				}
				i++;
			}
			break;
		}
		case 8: {
			i=1;
			j=1;
			while(i<dato.cant) {
				if((strcmp (dato.Mv[i].genero,"Animation\n")==0) || (strcmp (dato.Mv[i].genero,"animation\n")==0)) {
				if (j<=5){
					printf("%d ) ---%s VtProm: %f\n",j,dato.Mv[i].titulo,dato.Mv[i].votoPromedio);
					j++;
					}
				}
				i++;
			}
			break;
		}
	}
}

//recomendadas por rating
void RecmXRat(Arreglo dato){
	Movie Aux;
	int i,j,Cc,Ww;
	//inicio
	i=1;
	//calcula voto promedio del catalogo completo
	while(i<dato.cant){
		Cc=dato.Mv[i].votoPromedio+Cc;
		i++;
	}
	Cc=Cc/dato.cant;
	i=1;
	//calcula el rating
	while(i<dato.cant){
		Ww=(dato.Mv[i].votoPromedio*dato.Mv[i].cantidadVotantes)+(Cc*25000);
		Ww=Ww/(dato.Mv[i].cantidadVotantes+25000);
		dato.Mv[i].rating=Ww;
		i++;
	}
	//ordena el areglo por rating
	i=2;
	while(i<dato.cant) {
		Aux=dato.Mv[i];
		j=i-1;
		while(j>0 && dato.Mv[j].rating<Aux.rating) {
			dato.Mv[j+1]=dato.Mv[j];
			j=j-1;
		}
		dato.Mv[j+1]=Aux;
		i=i+1;
	}
	i=1;
	while(i<=5){
		printf("[%f]-------%s",dato.Mv[i].rating,dato.Mv[i].titulo);
		i++;
	}	
}

//elimina la cantidad de peliculas que desee
void DeletPeli(Arreglo ListD,Arreglo *dato,int CantP){
	Movie Aux;
	int i,j,p;
	char Delet[60]="Eliminada\n";
	//-----------ordena el arreglo donde se guardaron las pelis que se ibana borrar
	i=2;
	while(i<=ListD.cant) {
		Aux=ListD.Mv[i];
		j=i-1;
		while(j>0 && ListD.Mv[j].anio>Aux.anio) {
			ListD.Mv[j+1]=ListD.Mv[j];
			j=j-1;
		}
		ListD.Mv[j+1]=Aux;
		i=i+1;
	}
	//--------cada peli que se vaya a borrar le cambia el titulo a "eliminada"	
	i=1;
	j=1;
	while(i<dato->cant){
		if (i==ListD.Mv[j].anio){
				strcpy(dato->Mv[i].titulo, Delet);
			j++;
		}
		i++;
	}
	//---------ordena los borrados arriba
	while(CantP>=0){
	i=1;
	while(i<dato->cant) {
		j=i-1;
		while(j>=0 &&(strcmp (dato->Mv[i].titulo,Delet)==0)) {
				p=i;
				while(p<dato->cant){
					dato->Mv[p]=dato->Mv[p+1];
					p++;
		 		}
			dato->cant=dato->cant-1;			
			j=j-1;
		}
		i=i+1;
	}
	CantP--;
   }

	i=1;
	while(i<dato->cant){
		printf("[%d] %s",i,dato->Mv[i].titulo);
		i++;
	}
		
}

//guarda el listado en un txt
int GuardarTxt(Arreglo dato2) {
	//lexico local
	FILE *Arch_B;
	int ii;

	//inicio
	Arch_B = fopen("New_Peliculas.txt","wb");
	if (Arch_B == NULL) {
		return 0;
	}

	ii=1;
	while(ii<dato2.cant) { //mientras no sea el final del archivo
		printf("------Guardando datos------\n");
		fwrite(&dato2.Mv[ii],sizeof(Movie)/*(Arreglo)*/,1,Arch_B); //escribe en arreglo dentro del archivo (dirc de memoria del arreglo,tamaño c/ elem,cuantos arcivos va a escribir,el archivo)
		ii++; //cicla
	}
	fflush(Arch_B); //limpia canal de flujo
	fclose(Arch_B); //carramos el archivo
	return 1;
}

//Muestra por pantalla el menu principal
void MenuPrincipal() {
	printf("______________________________________________\n");
	printf("|                                            |\n");
	printf("|    ttttttt aaa  rrrr  m    m ooooo k  k    |\n");
	printf("|       t   a   a r   r mm  mm o   o k k     |\n");
	printf("|       t   aaaaa rrrrr m mm m o   o kk      |\n");
	printf("|       t   a   a r  r  m    m o   o k k     |\n");
	printf("|       t   a   a r   r m    m ooooo k   k   |\n");
	printf("|____________________________________________|\n");
	printf("	[1]  Peliculas mas populares\n");
	printf("	[2]  Cantidad de peliculas de cada director \n");
	printf("	[3]  Peliculas mas caras de cada anio \n");
	printf("	[4]  Peliculas de un genero particular \n");
	printf("	[5]  Recomendaciones \n");
	printf("	[6]  Exportar y Listar en Archibo_BIN \n");
	printf("	[7]  Eliminar Peliculas\n");
	printf("	[8]  Mostrar Peliculas\n");
	printf("	[9]  Guarda en Txt \n");
	printf("	[10] Salir \n");
}

//Muestra un mensaje al salir del programa
void CartelSalir() {
	printf("________________________________________\n");
	printf("|                                      |\n");
	printf("|    ¡Gracias por utilizar Tarmok!     |\n");
	printf("|______________________________________|\n");
}






