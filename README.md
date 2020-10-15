# Tp_numero4_orga
1) Utilizando como función hash f(x)= x mod 1301, conceptualice un archivo directo de 1300 posiciones y ubique los siguientes valores:

10168

21362

8515

7993

32434

29786

35175

50255

32305

24971

10177

53101

12901

Indiquen la cantidad máxima de claves, y cómo calcularía el factor de ocupación. ¿Existieron colisiones? Para 1500 registros ¿qué probabilidad de colisiones hay?


2) Suponga un archivo de organización directa de 512 posiciones. Usando una función hash con método de compresión y seleccionando el número primo adecuado, calcule las posiciones donde irían los siguientes registros alfanuméricos:

limon

gato

vodka

ojo

ojota

caradura

caradura

oh


3) ¿En qué se diferencia y qué ventajas tienen el manejo de colisiones dispersión, por distribución por almacenamiento por cubetas y por área de overflow separada?


Ejercicio de programación


1) Suponga un sistema para la gestión de una maratón de 42Km. El cupo máximo es de 12000 corredores. En la inscripción cada corredor provee: número de DNI, nombre, sexo, edad, categoría. Hay un último campo que es el tiempo (que se carga al finalizar la carrera).

Para la solución se deberá usar un archivo directo, donde deberá diseñar una función hash que mapee número de DNI a posición en el archivo (que es el número de corredor otorgado en el momento de la inscripción).

Implemente: función hash, archivo, altas, modificaciones, bajas. Carga de tiempos. Listados de tiempos general y por categoría.

¿Es eficiente esta solución al momento de imprimir los listados de clasificaciones generales y por categorías? ¿Usaría la misma solución si la toma de tiempo se hace de forma electrónica con sensores tipo RFID en la largada, media maratón (km 21) y final (Km 42)? ¿Qué cambiaría?


2) Suponga un sistema para el manejo de personal de una empresa. Los datos a almacenar son apellido y nombre, dirección, teléfono, y fecha de ingreso.

Para la solución se plantea un archivo directo donde el apellido y nombre es la clave de acceso.

Implemente una función hash, creación de archivo principal, alta, modificaciones, bajas. El manejo de colisiones se debe resolver por área separada de overflow.


