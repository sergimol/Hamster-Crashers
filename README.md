# The SqueakShip
## Documento de diseño de videojuego 
![pasted image 0](https://user-images.githubusercontent.com/62880649/111375437-889edf00-869e-11eb-92d6-65eb4820882b.png)

Andrés Carnicero, Sergio Molinero, Alberto Muñoz, Daniel Illanes, Óscar García, Sergio Alfonso, Samuel Blázquez, Diego Castillo, Javier Muñoz
Versión 1.1- 16 de marzo de 2021 
Resumen 
 
 ## Género:  
Beat ‘em up
 ## Modos:  
SinglePlayer
Multiplayer: De 2 a 4 jugadores 
 Online - Offline
Party - Arcade


 ## Público objetivo:  
  Mayores de 16 años. 
 ## Plataformas: 
  PC con teclado y ratón o Mando
    
 
## Hitos:  
  Fecha de propuesta del concepto (23/02/2021)
Hito 1(17/03/2021)
Hito 2(28/04/2021)
  Fecha de lanzamiento (19/05/2021) 
 

- Página del juego: https://github.com/sergimol/Hamster-Crashers
- Página de Gestión: www.pivotaltracker.com/n/projects/2489769
## Logotipo y portada del juego 
 ![pasted image 0 (1)](https://user-images.githubusercontent.com/62880649/111375614-c00d8b80-869e-11eb-8bff-927ba0685797.png)

 
## Tabla de contenidos 
 
1. Aspectos Generales y Descripción del Juego
2. Menús y modos de juego 
 1. Modos de Juego
 2.Control
3. Jugabilidad 
 1. Mecánica 
 2. Dinámica 
 3. Estética 
 4.Eventos
5.    Arquitectura
6.    Contenido 
 1. Contexto y universo 
 2. Historia 
 3. Narrativa 
 4. Niveles 
 5. Personajes
 6. Enemigos
 7. Modificadores
 8. Sonido SFX 
7.    Referencias 


## Aspectos generales  y Descripción del juego

The SqueakShip es un beat em up, cooperativo a 4 jugadores en el que encarnaremos a unos hamsters en una, tanto diminuta como gigantesca aventura épica por una casa en la que escaparán de su dueño hacia un cohete de juguete situado en el jardín. 
Hay 4 hamsters seleccionables y cada uno tiene una jugabilidad única, además el jugador tendrá que estar atento, pues los hamsters tiene una peculiaridad, les puede dar un infarto...

### Menús y modos de juego
Desde el menú principal se podrá acceder a la opción “Jugar”, “Opciones” y “Salir”.

Al entrar en “Jugar” se dará a elegir entre  “Singleplayer”, “Multiplayer Local” u “Online”.

Imagen del menú 

Al entrar en algún modo de juego se dará a elegir entre “Modo Party” y “Modo Arcade”.

Menú de selección de personaje contará con 4 ranuras para elegir personaje

Imagen del menú  de selección

Al entrar en “Opciones” se mostrarán diversas opciones: XXX

Imagen del menú de opciones

Al pulsar en “Salir”, se abrirá un mensaje de confirmación que confirme si se quiere dejar el juego.

Imagen del mensaje de confirmación

Desde el menú de pausa se podrá acceder a la opción “Continuar”, “Opciones” y a la opción “Salir”, que llevará al jugador al nivel principal.

Imagen del menú  de pausa
Interfaz In-Game de cada personaje

![sardinillaHead1](https://user-images.githubusercontent.com/62880649/111375857-0b279e80-869f-11eb-8baa-f59f2a2cf8aa.png)


- Corazón: Indica nivel de infarto, en Modo 1 representa el porcentaje y en el Modo 2 el valor.
- Cara: Icono personaje 
- Rectángulo verde: Barra Vida

#### 2.1  Modos de Juego
Habrá dos modos de juego principales: 
 - Party (Elementos aleatorios)
El juego tendrá elementos aleatorios que generarán tensión al usuario, pues ciertos eventos escaparán a su control y dará más juego al gameplay.
 - Arcade (sin aleatoriedad)
El jugador tendrá control absoluto sobre los eventos que afectan a su personaje, sabiendo en cada momento cómo actuar para avanzar en el nivel sin fallar.

Ambos modos se podrán jugar como jugador único o en multijugador (local y en línea) hasta 4 jugadores. Las cantidades de enemigos aumentarán en x% por cada jugador extra que se una a la partida.

#### 2.2 Control
WASD/Joystick para movimiento 
Click derecho/RT para ataque fuerte  
Click izquierdo/LT para ataque ligero
X para habilidad


### Jugabilidad 

![unnamed](https://user-images.githubusercontent.com/62880649/111376021-3e6a2d80-869f-11eb-9cf8-7aa8fd6377a3.png)

		Imagen esquemática de pantalla de juego
 
#### 3.1 Mecánica
	
ASPECTOS GENERALES DE LOS HAMSTERS 
 
##### Movimiento
El movimiento será como en cualquier beat em up, mezcla de scroll lateral con movimiento entre diferentes planos verticales.
*El jugador podrá moverse 8 direcciones en una velocidad continua, cambiando su posición (X) y (Y) en . Cuando el jugador se mueva en el suelo de forma vertical (profundidad) irá algo más lento, lo justo para dar sensación de mayor profundidad (Y).
*Salto: el jugador podrá saltar, cambiando su altura (Z). En el aire tendrá la capacidad de moverse para cambiar de posición en (X) y (Y).
 
##### Combate
El sistema de combate será una combinación de 3 movimientos, ataque ligero, ataque fuerte y el uso de una habilidad.
 
Al atacar, si el jugador está en el suelo no podrá moverse en ningún eje hasta acabar la animación, sin embargo si está saltando sí podrá hacerlo (se entra en detalle más adelante).
Si el jugador consigue asestar un golpe, romperá la acción del enemigo, es decir, si estaba a punto de atacar, el enemigo parará su ataque, además de aplicarle un pequeño aturdimiento.
 
El ataque por defecto quitará X puntos de vida al enemigo, sin embargo, habrá una pequeña probabilidad de asestar un crítico (daño extra) (es posible que aumente la probabilidad cuanto mayor sea el combo), saltando un pequeño pop up avisando al jugador y causando más daño.
 
Ataque ligero 
Ataque fuerte
Ataque en salto
 
##### Combos
Son combinaciones de ataques que si se asestan seguidos dentro de un margen de tiempo específico (pequeño) dan lugar a animaciones y golpes diferentes, llegando a causar aturdimiento y más daño de lo normal.
Al final de cada combo, el enemigo o enemigos en cuestión serán aturdidos, enviándoles más lejos o contra el suelo.
Existen 6 combinaciones de ataques, que serán representados con los botones de un mando Xbox:
-Ligero x4: (X) + (X) + (X) + (X)
-Fuerte x4: (Y) + (Y) + (Y) + (Y)
-Ligero + Fuerte: (X) + (Y)
-Salto + sucesión de ligeros: (A) + (X) + … (X) ... + (X)
Este combo es especial, si el jugador salta y acierta un ataque ligero a un enemigo, tanto él como el enemigo se quedarán suspendidos un pequeño tiempo en el aire. Ambos se mantienen en movimiento en la dirección del ataque, si el jugador vuelve a acertar otro ataque ligero, seguirán en el aire repitiendo el proceso anterior, pudiendo encadenar cuantos ataques ligeros sea capaz de acertar. Sin embargo, para no hacerlo ilimitado, a partir de 3 golpes encadenados habrá una pequeña probabilidad de lanzar al enemigo algo más lejos y aturdirlo, para que el jugador no pueda seguir el combo.
-Salto + sucesión de Ligeros (opcional) + Fuerte: (A) + (X) + … (X) + (Y) este combo también es especial, pues puede ir ligado al anterior, primero se explicará su primera versión.
Si el jugador salta y acierta un ataque fuerte, mandará al enemigo contra el suelo, aturdiéndole directamente.
Realmente este movimiento lo puede usar en cualquier momento que esté el jugador en el aire, como pone en la explicación del combo, se puede usar mientras estés encadenando ataques ligeros, cortando el combo.
 
 
 
##### Habilidad (Ataque especial)
Cada hámster tendrá una habilidad especial que podrá utilizar con cierto cooldown para no ser utilizada de forma abusiva. Cada habilidad será explicada en el apartado de Personajes en Contenido [5.5].
 
 
	
##### Pasiva
Se ve reflejada en sus estadísticas (vida, ataque y defensa) aunque todos balanceados como para poder ser usados en modo SinglePlayer. Cada pasiva será explicada en el apartado de Personajes en Contenido [5.5].
 
##### Sistema de infarto
El Sistema de infarto variará dependiendo del modo de juego elegido. Se comprobará cada X tiempo si el hámster recibe un infarto. 
 
El infarto llevará al jugador inmediatamente a un estado de KO en el que no podrá ser atacado, permaneciendo su barra de vida intacta y activando la mecánica Postmortem. Podrá ser reanimado durante un periodo de tiempo limitado recuperando la vida que poseía hasta el momento.
 
##### -Modo 1
El hámster tiene una probabilidad de recibir un infarto durante el transcurso del juego. La probabilidad evolucionará de esta manera (todas las probabilidades serán balanceadas en posterior playtesting):
 
Cada hámster tiene una probabilidad constante de recibir un infarto (0.25%). Dependiendo de cada acción tomada, esta probabilidad aumentará en diferentes cantidades y con diferentes límites:
Cada input consecutivo de ataque aumenta la probabilidad (un x%), hasta un límite de L%.
Cada input de habilidad aumenta bastante la probabilidad (un x2%), pudiendo alcanzar el 100%.
Cada input de salto aumenta la probabilidad (un x/n%) hasta un límite de L%.
 
Cuando la probabilidad esté alta se indicará mediante un corazón palpitante en la interfaz junto con la vida del personaje afectado.
 
Al pasar x tiempo sin ejecutar ningún tipo de ataque/habilidad, la probabilidad se reducirá hasta la original a razón de x3% por segundo. Si el personaje se mantiene completamente quieto, se reducirá el doble de rápido.
 
 
##### Modificadores
El sistema de infarto se verá afectado por distintos “power-ups” que aparecerán por el escenario y afectarán al gameplay de diversas maneras (Ver apartado ‘Modificadores’ en Contenido [5.7]).
 
##### Postmortem
El Postmortem es una mecánica de los hamsters que ocurre en el preciso instante en el que les da un infarto. El espíritu del hámster afectado escapará de su cuerpo y podrá ejecutar diferentes acciones dependiendo de si se está jugando en modo un jugador o multijugador: 
 
 
##### -Modo un jugador
El jugador deberá presionar x cantidad de teclas/botones en una secuencia indicada junto a la interfaz de infarto en un límite de tiempo (x segundos). Si el jugador falla, deberá comenzar una nueva secuencia antes de que termine el tiempo. Si el tiempo se acaba, el jugador morirá y se reiniciará desde el último checkpoint. En caso de que se complete la secuencia, el hámster se reanimará y volverá al juego con las estadísticas que tenía antes de sufrir el infarto. 
 
##### -Modo multijugador
El jugador podrá moverse libremente por el mapa en forma de espíritu. Cuando el jugador se encuentre sobre un aliado, este saldrá remarcado en el color del hámster muerto. En ese instante, el jugador podrá pulsar el botón/tecla x, para poseer al aliado marcado. En este momento, el jugador deberá presionar una serie de teclas/botones en una secuencia indicada junto a la interfaz de infarto en un límite de tiempo (x segundos). Mientras el jugador mantenga un combo de más de x1 botones, la probabilidad de infarto del aliado poseído será anulada. Si el jugador falla, el jugador poseído volverá a tener probabilidad de infarto hasta que se vuelva a acertar x1 botones de la secuencia. Si el jugador es reanimado, su espíritu volverá a su cuerpo y se restablecerá la vida que tenía al recibir el infarto. Si el tiempo se acaba y el jugador no ha sido reanimado, el jugador morirá, reapareciendo en el siguiente checkpoint que alcancen sus aliados.
 
### ASPECTOS GENERALES DE LOS ENEMIGOS
 
Existen varios tipos de enemigos, cuyas estadísticas variarán dependiendo del nivel
(Cada enemigo concreto se puede ver en el apartado Enemigos en Contenido [5.6]):
 
#### Enemigos ligeros
Se mueven hacia los jugadores, haciendo X daño al atacar. Su cadencia de ataque será media (entre Y y Z segundos). No aguantan muchos golpes.
 
#### Enemigos fuertes
Se mueven hacia los jugadores, haciendo X daño al atacar (Más que los ligeros). Su cadencia de ataque será lenta (entre Y y Z segundos). Aguantan más golpes que los enemigos ligeros.
 
#### Enemigos a distancia
Se posicionarán a cierta distancia de los jugadores, haciendo X daño al atacar. Su cadencia de ataque será lenta (entre Y y Z segundos). Después de atacar permanecerán un tiempo en su sitio (W segundos) antes de moverse o atacar de nuevo. No aguantan muchos golpes.
 
#### Obstáculos móviles
Se moverán por el escenario independientemente de la posición de los jugadores, haciendo X daño por contacto. Los jugadores deberán esquivarlos.
 
#### Jefes
##### “El Monstruo”
Dinosaurio de Juguete 
##### “La Bestia”
Gato gordo fumador del Jardín (Es el gato de Guille).
Sección de scroll automático en el sentido del movimiento del gato.
Cada x tiempo da una calada y expulsa una fila de humo que daña los jugadores a los que alcanza.
##### “La Mano”
Ataca de manera similar a “Mom” en The Binding of Isaac.
Ataca con puños que caen del cielo, en ocasiones con cuchillos que se clavan en el suelo.
 
### 3.2 Dinámica
En una partida típica, el jugador comienza observando como su dueño le ha soltado en su cuarto, y él debe de sobrevivir a las distintas adversidades. El nivel va a estar repleto de enemigos, creando así una dinámica frenética, que, unida al sistema de infartos, crea una atmósfera muy divertida donde debes aprender a controlar tus ataques sabiendo que asumes el riesgo de que te de un infarto.
 
El tiempo estimado para completar el juego es entre 20-40 minutos.
El juego se considera ganado una vez haya derrotado al escapar del nivel microondas, y en multijugador cuando se termine la batalla final entre los jugadores.
 
La dinámica general del juego es sencilla, entretener con un gameplay beat ‘em up bastante casual y hacer reír al jugador o jugadores con el humor y tono recurrente, además de dar una pequeña vuelta al género con el sistema de infarto, que causará incertidumbre en todas las partidas.
A pesar de poder jugar de forma individual, la experiencia óptima sería jugándolo en multijugador con amigos, para que funcione todo el componente social.
### Dinámica de los niveles
Los niveles irán distribuidos de manera lineal, los jugadores tendrán que ir de un punto A a un punto B, pasando por diferentes eventos como zonas con enemigos, oleadas, objetos interactuables, jefes… Los niveles por ende deberán estar muy pulidos y con un aparente contenido nuevo constantemente para no aburrir al jugador, además los niveles contarán con zonas marcadas por la verticalidad, se verán algunos ejemplos más adelante.
Aquí se presenta un esquema de un nivel.
![concept nivel](https://user-images.githubusercontent.com/62880649/111376340-9e60d400-869f-11eb-93dd-9388d7ec6103.jpg)

Como en todo beat em up, el nivel irá distribuido internamente en varios subniveles.
Al entrar en cada subnivel, los bordes y la cámara se ajustarán al escenario de esa zona (la cámara no es estática, sigue a los jugadores) y los jugadores no podrán seguir avanzando hasta que eliminen a todos los enemigos.
Cuando eliminen a los enemigos, se les indicará a los jugadores seguir avanzando en la dirección que toque, moviendo la cámara con ellos (centrando su X en el punto central de los personajes y su Y en la altura del nivel), hasta llegar a la siguiente zona donde se volverán a establecer los bordes.
Al llegar a una zona, los enemigos aparecerán por la izquierda y derecha (dependiendo de la zona).
Los subniveles no serán simplemente planos, tendrán pequeños obstáculos o zonas con mayor elevación (algo de verticalidad) para dividir el propio subnivel en otras zonas de juego.
 
 
Algunos ejemplos de elementos de los escenarios son los siguientes:
 
![unnamed (1)](https://user-images.githubusercontent.com/62880649/111376414-b33d6780-869f-11eb-9e68-3440dd22f4ba.png)
 
Obstáculos como puertas destructibles para seguir avanzando

![unnamed (2)](https://user-images.githubusercontent.com/62880649/111376463-c2bcb080-869f-11eb-87bc-edc05a7356d7.png)
---------------------------------------------------------------------------------------------------------------------------
 
 
Obstáculos en medio del camino, su colocación conduce indirectamente a una separación espacial del subnivel, dividiéndolo en 3 zonas.

![unnamed (3)](https://user-images.githubusercontent.com/62880649/111376545-df58e880-869f-11eb-8961-c47e947deb01.png)

![cap](https://user-images.githubusercontent.com/62880649/111376609-f566a900-869f-11eb-975c-6e4e99172e22.PNG)

El mismo ejemplo tenemos aquí pero con algo de verticalidad

 ![pasted image 0 (2)](https://user-images.githubusercontent.com/62880649/111376664-07e0e280-86a0-11eb-9f09-40ff75f6a348.png)

Cambios de dirección en eje z, como estos
![pasted image 0 (3)](https://user-images.githubusercontent.com/62880649/111376697-15966800-86a0-11eb-80a1-75d1ce9a4a0a.png)

![desnivel](https://user-images.githubusercontent.com/62880649/111376728-20e99380-86a0-11eb-8c23-0939eac7122b.png)

### 3.3 Estética 
El juego está ambientado desde el punto de vista de un hámster que vive en una jaula, por lo que los escenarios del juego son los distintos lugares del hogar dónde el dueño les suelta: Salón, cocina, jardín… Dichas instancias se verán masificadas debido al diminuto tamaño de los hámsters , dando una sensación de que cualquier cosa como un Roomba es un temible enemigo.
 
La estética a nivel artístico será la siguiente.
Un pixelart cuidado pero sin excesivo detalle, como en los ejemplos y concepts propuestos, todo tomará un tono muy amigable y colorido a simple vista, pero cuando entra la acción, los ataques y golpes resultarán en efectos visuales viscerales y algo “gore”, con salpicaduras de sangre y moratones en enemigos y hamsters. Justo se pretende hacer el contraste de una apariencia agradable y feliz con lo visceral.

 ![CONCEPTBIEN](https://user-images.githubusercontent.com/62880649/111376791-3363cd00-86a0-11eb-880a-96849b076165.jpg)
 
La música, realizada por David Carmona Fauste, dependerá del nivel pero siempre con un tono épico y de ritmo de batalla.
Algunos ejemplos que se tomarán como referencia:
Four Brave Champions (Castle Crashers) 
Main Theme (Super Smash Bros. Ultimate)
Gusty Garden Galaxy (Super Mario Galaxy)
 
La estética a nivel de contexto y universo se tratará en el apartado de contenido.
 
 
 
 
### 3.4 Eventos
Cinemáticas:
Inicio
Vuelta a la jaula
Salida al jardín
Huida del gato hasta casa
Montar el roomba
Encuentro con el niño
Entrada al microondas
Salida de la cocina
Lanzamiento del cohete
 
 
## Arquitectura

Enlace a Diagrama de arquitectura UML:
https://drive.google.com/file/d/1JMsT8iXRrHDzoSAlwVHi91fyuZQ65k0B/view?usp=sharing

## Contenido
 
### 5.1 Contexto y universo 
El juego transcurre por las instancias de la casa del dueño de nuestros protagonistas pero desde el punto de vista de los animales, convirtiendo así la historia de unos hamsters recorriendo una casa, en una épica aventura de un pelotón de hamsters tratando de llegar a su destino, sorteando escenarios y acabando con enemigos considerablemente más grandes que ellos.
 

### 5.2 Historia 
Los hamsters son la mascota del niño que vive en la casa, para ellos no es un simple niño, es “LA MANO” un ser que cada día los coge y los suelta en “LA PRUEBA” un circuito con obstáculos y enemigos que los hamsters nunca han podido superar (La Prueba es ciertamente la habitación del niño, un recorrido con juguetes).
Los hamsters se piensan que si superan la prueba “LA MANO” les llevará a la “SQUEAKSHIP”, un cohete de juguete que hay en el jardín y que los hamsters ven desde la ventana de la habitación.

El objetivo de los hamsters es superar de una vez la prueba. Cuando lo consiguen descubren que la “LA MANO” al único sitio que los lleva es de vuelta a la jaula.
Ahí los hamsters deciden escapar e ir al cohete por su cuenta, tirando la jaula al suelo y saliendo por la puerta-ventana que se encontraba medio abierta, dando al jardín.

Allí los hamsters correrán hasta el cohete escapando de un pájaro, pero justo delante del cohete, descubren que la amenaza de pájaro era simplemente el comienzo pues aparece el “GATO GORDO” de la familia, tienen que escapar de él hasta entrar a la casa.

Allí se encuentran desolados en el “PÁRAMO” un gran pasillo que da a la cocina. La única opción que ven los hamsters de atravesar el pasillo es montarse en el robot de limpieza.
Al llegar a la cocina vuelven a ver otra ventana abierta por donde se ve el cohete.

Tras cruzar la cocina, justo antes de llegar a la ventana, aparece el niño. Tras una “intensa” pelea con “LA MANO” el niño se enfada y mete a los hamsters al microondas con un propósito fatal. Sin embargo estos sabotean el microondas, explotando y saliendo volando por la ventana, cayendo justo en la plataforma del cohete.

Al ir a montarse se dan cuenta de que solo hay espacio para 1 y tendrán que luchar entre ellos.
El vencedor se sube al cohete mientras los otros lo contemplan, lamentablemente, el cohete explota en el cielo.


### 5.3 Narrativa 
Este apartado hace alusión a la forma en la que se pondrá en contexto al jugador y se le explicará la historia.

Se va a intentar que no haya ningún tipo de texto explicativo para la trama.
La puesta en contexto de cada nivel (cómo se entra a cada nivel) será de forma muy clásica, una serie de dibujos (SIN TEXTO) seguidos hechos a mano.

Aún así, durante el nivel ocurrirán eventos que también dotarán de narrativa a la aventura, como la aparición de los jefes como el gato, el pájaro o el niño.


### 5.4 Niveles
#### Nivel 1: La Prueba
El primer nivel ocurrirá en la habitación del niño.
#### Nivel 2: Terrenos de la Horda
El segundo nivel ocurrirá en el jardín de la casa
Ataques dispersos de pájaro
##### Nivel 2.1: La Bestia
Sección de huida: Gato Gordo
#### Nivel 3: El Páramo
Sección sobre Roomba
#### Nivel 4: El Purgatorio
El tercer nivel ocurrirá en la cocina de la casa.
##### Boss Final: “La Mano” (Manos de Niño)
##### Nivel 4.1: La Rueda Infernal
Sección de microondas contrarreloj.
#### Escenario Final: The SqueakShip
Pelea Final entre todos en plataforma del cohete
 
### 5.5 Personajes
Existen 5 arquetipos de hámster, uno de ellos desbloqueable una vez se haya completado el juego una vez.
 
#### Sardinilla, The Plumster
- Sardinilla es un tanque, por lo que a priori podemos decir que sus ataques son a melee, tendrá más vida que el resto y se moverá más lento.
- Habilidad: Sardinilla podrá rodar, avanzando rápidamente en el eje horizontal y arrollando a sus enemigos.
- Pasiva: Sardinilla dispondrá de +X de vida extra en comparación con el resto de personajes, pero será ligeramente más lento.
![sardinillaGrande](https://user-images.githubusercontent.com/62880649/111377228-b08f4200-86a0-11eb-915f-ec6c172011ca.png)

#### Keta, The Stripe
- Keta es un DPS con ataques a melee, con una gran capacidad de movimiento que le permite asesinar rápidamente a los enemigos y huir de situaciones arriesgadas.
- Habilidad: Keta genera una nube tóxica que perdurará en el escenario durante X tiempo. Los enemigos que se encuentren dentro sufrirán Z daño por segundo y serán ralentizados (W% de velocidad máxima).
- Pasiva: Keta es un Y% más rápido que el resto de personajes. Además, tiene una ligera posibilidad de envenenar a sus enemigos.
![DEFINITIVO](https://user-images.githubusercontent.com/62880649/111377271-bc7b0400-86a0-11eb-9dc1-63fd8ece5118.png)


#### Monchi, The Master
- Monchi es un DPS con ataques caster, con una gran capacidad de disparo que es ideal para matar enemigos desde la lejanía.
- Habilidad: Monchi disparará una ráfaga de pipas en el eje horizontal durante x segundos. Durante este tiempo, Monchi tendrá un y% menos de velocidad de movimiento.
- Pasiva: A diferencia del resto de personajes, Monchi recuperará Z% de vida al consumir alimentos. Además tiene una probabilidad de que el último golpe de un combo se coma al enemigo, recuperando vida.
![mofletesGRANDE](https://user-images.githubusercontent.com/62880649/111377331-cb61b680-86a0-11eb-9bf2-1d5f6050075a.png)
![Monchi](https://user-images.githubusercontent.com/62880649/111377359-d583b500-86a0-11eb-8c6a-4e59db45e980.png)

#### Canelón, The Arzobisp of Cabestreros
- Canelón es un Healer, DPS, con capacidad de sanar en área y atacar a melee con el bastón que le otorga sus poderes.
- Habilidad: 
- Canelón tiene 2 estados que cambian cuando se activa la habilidad.
- Dorime: Invoca un extracto de la Tierra Santa, que será un área marcada con un resplandor verde donde los aliados recuperarán +X de vida y además los enemigos quedarán aturdidos durante un breve momento. 
- Belcebú: Invoca un extracto de la Tierra de Satanás, que será un área marcada con un resplandor rojo donde los enemigos perderán X de vida.
- Pasiva: Canelón atacará con su largo bastón obteniendo rango de ataque adicional.
![dorimeGRANDE](https://user-images.githubusercontent.com/62880649/111377395-e0d6e080-86a0-11eb-83fb-0330f300fb94.png)
![anuelBrrr](https://user-images.githubusercontent.com/62880649/111377430-ecc2a280-86a0-11eb-860d-c9836f5ec716.png)
      
### 5.6 Enemigos
Ni los enemigos ni sus tipos son definitivos. Se irán definiendo a lo largo del desarrollo.
 

### Nivel 1 - Habitación
 	Enemigos:
Soldados (Ligero)
Pinypons (Fuerte)
Juguetes de cuerda (Obstáculo móvil)
Dinosaurio juguete (Boss)
	Obstáculos:
Globos
Legos
Cartones+Rollos papel
 

### Nivel 2 - Jardín
 	Enemigos:
Cucarachas (Ligero)
Gnomo de jardín (Fuerte)
Topos (Obstáculo móvil)
Pájaro (Obstáculo móvil)
Gato (Jefe)
	Obstáculos:
Ramas
Rocas
 

### Nivel 3 - Roomba
 	Enemigos:
Polvo/Suciedad (Obstáculo móvil)
Arañas (Fuerte) [Caen del techo hacia la plataforma roomba]
 
	Obstáculos:
Globos
 

### Nivel 4 - Cocina
 	Enemigos:
Taza de té (Ligero)
Suciedad (Obstáculo móvil)
Comida Pocha (Fuerte)
 
	Obstáculos:
Cubiertos
Agua
Platos
 

### Nivel 4.1 - Microondas
 	Enemigos:
Soldados
Obstáculos:
Muelle 
	

### 5.7 Modificadores y objetos
 
Modificador
Disponibilidad
Función
Imágen

#### Adrenalina
Desde el nivel 3
 La “barra de infarto” permanece X segundos sin modificarse, pero al acabar se sitúa en un X% muy alto (>= 90% (igual 90 es locura)) 



#### Calmante
Desde el nivel 2
Disminuye de golpe la barra de infarto, pero reduce la velocidad X segundos.



#### Comida ligera
Desde el nivel 1
Recupera un 25% de la vida máxima del personaje que pase por encima



#### Comida contundente
Desde el nivel 1
Recupera un 50% de la vida máxima del personaje que pase por encima



 

### 5.8 Logros
 

### 5.9 Sonido SFX 
Efectos
Ataques melee
Pasos
Sonidos de hamster?
Disparos
Salto
Muerte
Sonidos habilidades activas (dar con el bastón, pedo)
Daño recibido
Paro cardiaco


Daño 
Transformación a fantasma

 


## Referencias 
Castle Crashers (The Behemoth, 2008)
Streets of rage 4 (Dotemu, Lizardcube, Guard Crush Games, 2020)
Golden Axe (Sega, 1989)
Double Dragon (Technos Japan, 1987)
Battletoads (Rare, 1991)
