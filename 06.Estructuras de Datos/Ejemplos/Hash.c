#include <stdio.h>
#define SIZE 20

struct DataItem {
   int data;   
   int key;
};

struct DataItem* hashArray[SIZE]; 
struct DataItem* dummyItem;
struct DataItem* item;

int hashCode(int key) {
   return key % SIZE;
}

struct DataItem *search(int key) {
   //obtener el hash 
   int hashIndex = hashCode(key);  
   
   //mover en el array hasta que encuentre un elemento vacío 
   while(hashArray[hashIndex] != NULL) {
	
      if(hashArray[hashIndex]->key == key)
         return hashArray[hashIndex]; 
			
      //ir al siguiente cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SIZE;
   }        
   
   return NULL;        
}

void insert(int key,int data) {

   struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
   item->data = data;  
   item->key = key;

   //obtener el hash 
   int hashIndex = hashCode(key);

   //mover en el array hasta que encuentre un elemento vacío o eliminado cell
   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
      //ir al next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SIZE;
   }
	
   hashArray[hashIndex] = item;
}

/*
Un Hash o tabla de hash es una estructura de datos que implementa un conjunto 
asociativo de tipo clave-valor, una estructura que puede asociar valores a claves. 
La implementación usa una función de hash para convertir la clave en un índice 
de una matriz en la que se almacena el valor correspondiente.
Las tablas hash son muy eficientes para las operaciones de búsqueda, inserción 
y eliminación. Se utilizan en bases de datos para búsquedas rápidas, en cachés, 
conjuntos, etc.
*/
int main() {
   dummyItem = (struct DataItem*) malloc(sizeof(struct DataItem));
   dummyItem->data = -1;  
   dummyItem->key = -1; 

   insert(1, 20);
   insert(2, 70);
   insert(42, 80);
   insert(4, 25);
   insert(12, 44);
   insert(14, 32);
   insert(17, 11);
   insert(13, 78);
   insert(37, 97);

   item = search(37);

   if(item != NULL) {
      printf("Element found: %d\n", item->data);
   } else {
      printf("Element not found\n");
   }
}
