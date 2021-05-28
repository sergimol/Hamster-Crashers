THE SQUEAKSHIP


![H4thv5](https://user-images.githubusercontent.com/62661210/120047344-a1b7fa80-c014-11eb-9cb7-911a31d6d375.png)


Juegos Asados


# Pagina Web
https://juegosasados.itch.io/the-squeakship

# Pivotal
https://www.pivotaltracker.com/n/projects/2489769


### GDD ###

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
 
- Repositorio del juego: https://juegosasados.itch.io/the-squeakship 
- Repositorio del juego: https://github.com/sergimol/Hamster-Crashers
- Página de Gestión: www.pivotaltracker.com/n/projects/2489769

## Logotipo y portada del juego 

![LOGOSQUEAKSHIPSINASADOS](https://user-images.githubusercontent.com/62880649/111395594-88faa280-86bd-11eb-9e75-4038ffe65ff4.jpg)

 
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

The SqueakShip es un beat em up, cooperativo a 4 jugadores en el que encarnaremos a unos hamsters en una aventura épica, tanto diminuta como gigantesca en una casa de la que escaparán de su dueño usando un cohete de juguete situado en el jardín. 
Hay 5 hamsters seleccionables y cada uno tiene una jugabilidad única, además el jugador tendrá que estar atento, pues los hamsters tiene una peculiaridad, les puede dar un infarto...


### Menús y modos de juego
Desde el menú principal se podrá acceder a las opciones  “Un Jugador”, “Multijugador Local”, “Opciones” y “Salir”.

![pasted image 0 (4)](https://user-images.githubusercontent.com/62880649/120045333-09b81200-c010-11eb-83ab-044d01736ca0.png)

Al entrar en “Un Jugador” se dará a elegir entre 5 hamsters (1 de ellos bloqueado hasta completar el juego una vez).

![pasted image 0 (6)](https://user-images.githubusercontent.com/62880649/120045444-4dab1700-c010-11eb-81b4-86baa8e8e188.png)

Al entrar en “Multijugador Local” se dará a elegir entre 3 opciones (de 2 a 4 jugadores), lo que dará paso a la selección de personajes.

Al entrar en “Opciones” se mostrarán diversas opciones. Estas son: “Música”, “Sonido” y “Resolucion”.

Imagen del menú de opciones

Al pulsar en “Salir”, se cerrará el juego.

Imagen del mensaje de confirmación

Desde el menú de pausa se podrá acceder a la opción “Continuar”, “Opciones” y a la opción “Salir”, que llevará al jugador al nivel principal.

Imagen del menú  de pausa
Interfaz In-Game de cada personaje

![pasted image 0 (5)](https://user-images.githubusercontent.com/62880649/120045474-5ef42380-c010-11eb-9af4-6444f8a90b06.png)


Corazón: Indica nivel de infarto
Cara: Icono personaje 
Rectángulo verde: Barra Vida
Icono RB: Marcador de habilidad


#### 2.1  Modos de Juego

Habrá dos modos de juego principales: 
Un Jugador:
El sistema de infarto
Multijugador Local:
Los enemigos ganarán una cantidad de vida por cada hamster adicional

#### 2.2 Control
WASD/Joystick para movimiento 
Click derecho/Y para ataque fuerte  
Click izquierdo/X para ataque ligero
R/RB para habilidad



### Jugabilidad 

![pasted image 0 (7)](https://user-images.githubusercontent.com/62880649/120045511-79c69800-c010-11eb-98a5-8d156e4b299b.png)


		Imagen esquemática de pantalla de juego
 
#### 3.1 Mecánica
	
ASPECTOS GENERALES DE LOS HAMSTERS 
 
##### Movimiento
El movimiento será como en cualquier beat em up, mezcla de scroll lateral con movimiento entre diferentes planos verticales.
*El jugador podrá moverse 8 direcciones en una velocidad continua, cambiando su posición (X) y (Y) en . Cuando el jugador se mueva en el suelo de forma vertical (profundidad) irá algo más lento, lo justo para dar sensación de mayor profundidad (Y).
*Salto: el jugador podrá saltar, cambiando su altura (Z). En el aire tendrá la capacidad de moverse para cambiar de posición en (X) y (Y).

 
##### Combate
EEl sistema de combate será una combinación de 3 movimientos, ataque ligero, ataque fuerte y el uso de una habilidad.
 
Al atacar, el jugador sufrirá una reducción en su velocidad hasta acabar la animación, tanto en tierra como en el aire.
Si el jugador consigue asestar un golpe, romperá la acción del enemigo, es decir, si estaba a punto de atacar, el enemigo parará su ataque, además de aplicarle un pequeño aturdimiento. Asimismo, aplicará un empuje ligero.
 
El ataque por defecto quitará 20 puntos de vida al enemigo, sin embargo, habrá una pequeña probabilidad de asestar un crítico (daño extra), que será mayor en los golpes finales de un combo.
 
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
-Salto + sucesión de ligeros: (A) + (X) + (X) + (X)
Este combo es especial, si el jugador salta y acierta un ataque ligero a un enemigo, tanto él como el enemigo se quedarán suspendidos un pequeño tiempo en el aire. Ambos se mantienen en movimiento en la dirección del ataque, si el jugador vuelve a acertar otro ataque ligero, seguirán en el aire repitiendo el proceso anterior, pudiendo encadenar cuantos ataques ligeros sea capaz de acertar. Sin embargo, para no hacerlo ilimitado, a partir de 3 golpes encadenados habrá una de lanzar al enemigo algo más lejos y aturdirlo, para que el jugador no pueda seguir el combo.
-Salto + sucesión de Ligeros + fuerte(opcional): (A) + (X) + (X) + (Y) este combo también es especial, pues puede ir ligado al anterior, primero se explicará su primera versión.
Si el jugador salta y acierta un ataque fuerte, mandará al enemigo contra el suelo, aturdiéndole directamente.
Este movimiento lo puede usar en cualquier momento que esté el jugador en el aire, como pone en la explicación del combo, se puede usar mientras estés encadenando ataques ligeros, cortando el combo.

 
##### Habilidad (Ataque especial)
Cada hámster tendrá una habilidad especial que podrá utilizar con cierto cooldown para no ser utilizada de forma abusiva. Cada habilidad será explicada en el apartado de Personajes en Contenido [5.5].
 
	
##### Pasiva
Se ve reflejada en sus estadísticas (vida, ataque y defensa) aunque todos balanceados como para poder ser usados en modo Un Jugador. Cada pasiva será explicada en el apartado de Personajes en Contenido [5.5].
 
##### Sistema de infarto
El Sistema de infarto variará dependiendo del modo de juego elegido. Se comprobará cada 5 segundos si el hámster recibe un infarto. 
 
El infarto llevará al jugador inmediatamente a un estado de KO, permaneciendo su barra de vida intacta y activando la mecánica Postmortem. Podrá ser reanimado durante un periodo de tiempo limitado recuperando la vida que poseía hasta el momento.
 
El hámster tiene una probabilidad de recibir un infarto durante el transcurso del juego. La probabilidad evolucionará de esta manera (todas las probabilidades serán balanceadas en posterior playtesting):
 
Cada hámster tiene una probabilidad constante de recibir un infarto (0.25%). Dependiendo de cada acción tomada, esta probabilidad aumentará en diferentes cantidades y con diferentes límites:
Cada input consecutivo de ataque aumenta la probabilidad (un x%), hasta un límite de L%.
Cada input de habilidad aumenta bastante la probabilidad (un x2%), pudiendo alcanzar el 100%.
 
Cuando la probabilidad sea alta, se indicará mediante un corazón palpitante en la interfaz junto con la vida del personaje afectado. Asimismo se indicará mediante vibración del mando
 
Al pasar x tiempo sin ejecutar ningún tipo de ataque/habilidad, la probabilidad se reducirá hasta la original a razón de x3% por segundo. Si el personaje se mantiene completamente quieto, se reducirá el doble de rápido.
 
##### Items
A lo largo del nivel se presentarán una serie de cajas destructibles. Éstas podrán tener dentro un item aleatorio (Ver apartado ‘Items’ en Contenido [5.7]) o nada, dependiendo de una probabilidad.

 
##### Postmortem
El Postmortem es una mecánica de los hamsters que ocurre en el preciso instante en el que les da un infarto. El espíritu del hámster afectado escapará de su cuerpo y podrá ejecutar diferentes acciones dependiendo de si se está jugando en modo un jugador o multijugador: 

 
##### -Modo un jugador
El jugador deberá presionar x cantidad de teclas/botones en una secuencia indicada junto a la interfaz de infarto en un límite de tiempo (x segundos). Si el jugador falla, deberá comenzar una nueva secuencia antes de que termine el tiempo. Mientras se encuentre en este estado, los enemigos podrán seguir atacándole. En caso de que se complete la secuencia, el hámster se reanimará y volverá al juego. 

 
##### -Modo multijugador
El jugador podrá moverse libremente por el mapa en forma de espíritu. Cuando el jugador se encuentre sobre un aliado, este saldrá remarcado en el color del hámster muerto. En ese instante, el jugador podrá pulsar el botón/tecla x, para poseer al aliado marcado. En este momento, el jugador deberá presionar una serie de teclas/botones en una secuencia indicada junto a la interfaz de infarto en un límite de tiempo (x segundos). Mientras el jugador mantenga un combo de más de x1 botones, la probabilidad de infarto del aliado poseído será anulada. Si el jugador falla, el jugador poseído volverá a tener probabilidad de infarto hasta que se vuelva a acertar x1 botones de la secuencia. Si el jugador es reanimado, su espíritu volverá a su cuerpo y se restablecerá la vida que tenía al recibir el infarto. Si el tiempo se acaba y el jugador no ha sido reanimado, el jugador morirá, reapareciendo en el siguiente checkpoint que alcancen sus aliados.
 
### ASPECTOS GENERALES DE LOS ENEMIGOS
 
Existen varios tipos de enemigos, cuyas estadísticas variarán dependiendo del nivel
(Cada enemigo concreto se puede ver en el apartado Enemigos en Contenido [5.6]):
 
#### Enemigos ligeros
Se mueven hacia los jugadores, haciendo poco daño al atacar. Su cadencia de ataque será corta y será entre un rango de tiempo fijo. No aguantan muchos golpes.

 
#### Enemigos fuertes
Se mueven hacia los jugadores, funcionando su ataque igual que el de los enemigos ligeros. Aguantan más golpes que los enemigos ligeros y disponen de un ataque especial que hace daño por segundo después de su segundo ataque básico.

 
#### Enemigos a distancia
Se moverán por el escenario independientemente de la posición de los jugadores, haciendo X daño por contacto. Los jugadores deberán esquivarlos.

 
#### Obstáculos móviles
Se moverán por el escenario independientemente de la posición de los jugadores, haciendo X daño por contacto. Los jugadores deberán esquivarlos.
 
#### Jefes
##### “El Monstruo”
Marioneta calcetín de mano
Ataca estampandose contra el tren sobre el que están los jugadores
Se queda una vez estampado para permitir a los hamsters atacar.

##### “La Bestia”

Gato gordo del Jardín.
Sección de scroll automático en el sentido del movimiento del gato.
Empuja a los Aliados al golpearlos

##### “La Mano”
Ataca de manera similar a “Mom” en The Binding of Isaac.
Son 2 entidades que comparten vida y se mantienen estáticos un tiempo para permitir que los hamsters le bajen la vida:
Una mano que funciona igual que “El Monstruo”, con el comportamiento añadido de hacer un barrido que solo puede ser esquivado saltando. Este nuevo movimiento sucederá 		después del 3º, 4º o 5º manotazo.
Un puño que cae del cielo y golpea a los aliados.

 
### 3.2 Dinámica
En una partida típica, el jugador comienza observando como su dueño le ha soltado en su cuarto, y él debe de sobrevivir a las distintas adversidades. El nivel va a estar repleto de enemigos, creando así una dinámica frenética, que, unida al sistema de infartos, crea una atmósfera muy divertida donde debes aprender a controlar tus ataques sabiendo que asumes el riesgo de que te de un infarto.
 
El tiempo estimado para completar el juego es entre 20-40 minutos.
El juego se considera ganado una vez haya derrotado al escapar del nivel microondas, y en multijugador cuando se termine la batalla final entre los jugadores.
 
La dinámica general del juego es sencilla, entretener con un gameplay beat ‘em up bastante casual y hacer reír al jugador o jugadores con el humor y tono recurrente, además de dar una pequeña vuelta al género con el sistema de infarto, que causará incertidumbre en todas las partidas.
A pesar de poder jugar de forma individual, la experiencia óptima sería jugándolo en multijugador con amigos, para que funcione todo el componente social.

### Dinámica de los niveles

En una partida típica, el jugador comienza observando como su dueño le ha soltado en su cuarto, y él debe de sobrevivir a las distintas adversidades. El nivel va a estar repleto de enemigos, creando así una dinámica frenética, que, unida al sistema de infartos, crea una atmósfera muy divertida donde debes aprender a controlar tus ataques sabiendo que asumes el riesgo de que te de un infarto.
 
El tiempo estimado para completar el juego es entre 20-50 minutos.
El juego se considera ganado una vez haya derrotado al escapar del nivel microondas, dando paso a la escena final y los créditos.
 
La dinámica general del juego es sencilla, entretener con un gameplay beat ‘em up bastante casual y hacer reír al jugador o jugadores con el humor y tono recurrente, además de dar una pequeña vuelta al género con el sistema de infarto, que causará incertidumbre en todas las partidas.
A pesar de poder jugar de forma individual, la experiencia óptima sería jugándolo en multijugador con amigos, para que funcione todo el componente social.

![concept nivel (1)](https://user-images.githubusercontent.com/62880649/120045802-230d8e00-c011-11eb-9299-cb9cfd208af5.jpg)

Como en todo beat em up, el nivel irá distribuido internamente en varios subniveles.
Al entrar en cada subnivel, los bordes y la cámara se ajustarán al escenario de esa zona (la cámara no es estática, sigue a los jugadores) y los jugadores no podrán seguir avanzando hasta que eliminen a todos los enemigos.
Cuando eliminen a los enemigos, se les indicará a los jugadores seguir avanzando en la dirección que toque, moviendo la cámara con ellos (centrando su X en el punto central de los personajes y su Y en la altura del nivel), hasta llegar a la siguiente zona donde se volverán a establecer los bordes.
Al llegar a una zona, los enemigos aparecerán por la izquierda y derecha (dependiendo de la zona).
Los subniveles no serán simplemente planos, tendrán pequeños obstáculos o zonas con mayor elevación (algo de verticalidad) para dividir el propio subnivel en otras zonas de juego.


### 3.3 Estética 
El juego está ambientado desde el punto de vista de un hámster que vive en una jaula, por lo que los escenarios del juego son los distintos lugares del hogar dónde el dueño les suelta: Salón, cocina, jardín… Dichas instancias se verán masificadas debido al diminuto tamaño de los hámsters , dando una sensación de que cualquier cosa como un Roomba es un temible enemigo.

La estética a nivel artístico será la siguiente.
Un pixelart cuidado pero sin excesivo detalle, como en los ejemplos y concepts propuestos, todo tomará un tono muy amigable y colorido a simple vista, pero cuando entra la acción, los ataques y golpes resultarán en efectos visuales viscerales y algo “gore”, con salpicaduras de sangre y moratones en enemigos y hamsters. Justo se pretende hacer el contraste de una apariencia agradable y feliz con lo visceral.

![pasted image 0 (8)](https://user-images.githubusercontent.com/62880649/120045909-55b78680-c011-11eb-8e03-f9465b1bd68c.png)

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
Encuentro con el niño
Entrada al microondas
Salida de la cocina
Lanzamiento del cohete



## Arquitectura

![pasted image 0 (9)](https://user-images.githubusercontent.com/62880649/120045988-7b449000-c011-11eb-9e61-f0bd82c30013.png)

Enlace a Diagrama de arquitectura UML:
https://drive.google.com/file/d/1JMsT8iXRrHDzoSAlwVHi91fyuZQ65k0B/view?usp=sharing

## 5. Contenido

### 5.1 Contexto y universo  
El juego transcurre por las instancias de la casa del dueño de nuestros protagonistas pero desde el punto de vista de los animales, convirtiendo así la historia de unos hamsters recorriendo una casa, en una épica aventura de un pelotón de hamsters tratando de llegar a su destino, sorteando escenarios y acabando con enemigos considerablemente más grandes que ellos.


### 5.2 Historia 
Los hamsters son la mascota del niño que vive en la casa, para ellos no es un simple niño, es “LA MANO” un ser que cada día los coge y los suelta en “LA PRUEBA” un circuito con obstáculos y enemigos que los hamsters nunca han podido superar (La Prueba es ciertamente la habitación del niño, un recorrido con juguetes).
Los hamsters se piensan que si superan la prueba “LA MANO” les llevará a la “SQUEAKSHIP”, un cohete de juguete que hay en el jardín y que los hamsters ven desde la ventana de la habitación.

El objetivo de los hamsters es superar de una vez la prueba. Cuando lo consiguen descubren que la “LA MANO” al único sitio que los lleva es de vuelta a la jaula.
Ahí los hamsters deciden escapar e ir al cohete por su cuenta, tirando la jaula al suelo y saliendo por la puerta-ventana que se encontraba medio abierta, dando al jardín.

Allí los hamsters correrán hasta el cohete, pero justo delante del cohete, aparece el “GATO GORDO” de la familia, tienen que escapar de él hasta entrar a la casa, Llegando a la cocina.

Tras cruzar la cocina, justo antes de llegar a la ventana, aparece el niño. Tras una “intensa” pelea con “LA MANO” el niño se enfada y mete a los hamsters al microondas con un propósito fatal. Sin embargo estos sabotean el microondas, explotando y saliendo volando por la ventana, cayendo justo en la plataforma del cohete.

Al ir a montar, el cohete es lanzado y explota, dando fin al juego.


### 5.3 Narrativa 
Este apartado hace alusión a la forma en la que se pondrá en contexto al jugador y se le explicará la historia.

No hay ningún tipo de texto explicativo para la trama.
La puesta en contexto de cada nivel (cómo se entra a cada nivel) es de forma clásica, una serie de dibujos seguidos (SIN TEXTO) hechos a mano.

Aún así, durante el nivel ocurrirán eventos que también dotarán de narrativa a la aventura, como la aparición de los jefes como el gato o la mano.



### 5.4 Niveles
#### Nivel 1: La Prueba
El primer nivel ocurrirá en la habitación del niño.
#### Nivel 2: Terrenos de la Horda
El segundo nivel ocurrirá en el jardín de la casa
##### Nivel 2.1: La Bestia
Sección de huida: Gato Gordo
#### ivel 3: El Purgatorio
El tercer nivel ocurrirá en la cocina de la casa.
Boss Final: “La Mano” (Manos de Niño)

#### Nivel 3.1: La Rueda Infernal
Sección de microondas contrarreloj.

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
![pasted image 0 (10)](https://user-images.githubusercontent.com/62880649/120046165-e1311780-c011-11eb-8e2e-e4631982f183.png)
![pasted image 0 (11)](https://user-images.githubusercontent.com/62880649/120046174-ec844300-c011-11eb-84ee-d0657dc8e27d.png)


#### Ángel, The Senior
Ángel es un DPS de tipo Berserk.
Habilidad: Obtiene el poder la furia de mil convocatorias de MD y aumenta su velocidad de ataque y daño un X% durante Y segundos.
Pasiva: Está doblado por un actor muy conocido en los lares de la UCM.

![pasted image 0 (12)](https://user-images.githubusercontent.com/62880649/120046234-0c1b6b80-c012-11eb-8e1f-56e7cbfa6f0e.png)

### 5.6 Enemigos
Ni los enemigos ni sus tipos son definitivos. Se irán definiendo a lo largo del desarrollo.


### Nivel 1 - Habitación

Enemigos:
Soldados de plástico (Ligero)
![pasted image 0 (13)](https://user-images.githubusercontent.com/62880649/120046290-235a5900-c012-11eb-9546-342786f67eab.png)

Soldados de plomo (Ligero)
![pasted image 0 (14)](https://user-images.githubusercontent.com/62880649/120046318-2fdeb180-c012-11eb-9f2e-159d3f1e237a.png)

Mono a cuerda (Fuerte)
![pasted image 0 (15)](https://user-images.githubusercontent.com/62880649/120046336-3836ec80-c012-11eb-80d4-fbdfa25e389a.png)


Automóviles (Obstáculo móvil)
![pasted image 0 (16)](https://user-images.githubusercontent.com/62880649/120046352-4127be00-c012-11eb-9a00-46b92b1cfdc8.png)

La Mano (Boss)
![pasted image 0 (17)](https://user-images.githubusercontent.com/62880649/120046370-4b49bc80-c012-11eb-8739-db7a6ab839a5.png)

Obstáculos:
Cajas
![pasted image 0 (18)](https://user-images.githubusercontent.com/62880649/120046401-5d2b5f80-c012-11eb-9671-db115ee3dd8a.png)



### Nivel 2 - Enemigos:
Mariquitas (Ligero)
![pasted image 0 (19)](https://user-images.githubusercontent.com/62880649/120046439-703e2f80-c012-11eb-93af-c255b4cfb0b1.png)

Soldados (Ligero)
![pasted image 0 (20)](https://user-images.githubusercontent.com/62880649/120046456-7a602e00-c012-11eb-9400-2f68122c2973.png)

Rata (Fuerte)
![pasted image 0 (21)](https://user-images.githubusercontent.com/62880649/120046472-83e99600-c012-11eb-8cf7-343036048315.png)

Gato (Jefe)
![pasted image 0 (22)](https://user-images.githubusercontent.com/62880649/120046485-8cda6780-c012-11eb-90ca-b68ae424a536.png)

Obstáculos:
Cajas
![pasted image 0 (23)](https://user-images.githubusercontent.com/62880649/120046501-95cb3900-c012-11eb-9620-29e44ef42b43.png)




### Nivel 3 - - Cocina
Enemigos:
Naranja (Ligero)
![pasted image 0 (24)](https://user-images.githubusercontent.com/62880649/120046541-ac719000-c012-11eb-938c-2bcf43633a3e.png)

Mariquitas (Ligero)
![pasted image 0 (19)](https://user-images.githubusercontent.com/62880649/120046439-703e2f80-c012-11eb-93af-c255b4cfb0b1.png)

Rata (Fuerte)
![pasted image 0 (21)](https://user-images.githubusercontent.com/62880649/120046472-83e99600-c012-11eb-8cf7-343036048315.png)

Bosses (Manos)
![pasted image 0 (25)](https://user-images.githubusercontent.com/62880649/120046574-c14e2380-c012-11eb-95fd-69d47210be8e.png) ![pasted image 0 (26)](https://user-images.githubusercontent.com/62880649/120046585-c9a65e80-c012-11eb-9927-297806350ae1.png)
Obstáculos:
Fogones
![pasted image 0 (27)](https://user-images.githubusercontent.com/62880649/120046606-d2973000-c012-11eb-893d-26f9c4cc8de2.png)

Cajas
![pasted image 0 (28)](https://user-images.githubusercontent.com/62880649/120046621-daef6b00-c012-11eb-91b2-f051fc867e23.png)




### Nivel 3.1 - Microondas
Obstáculos:
Batería
![pasted image 0 (29)](https://user-images.githubusercontent.com/62880649/120046656-f0fd2b80-c012-11eb-802e-8dfdd28930c5.png)


### 5.7 Objetos

#### Queso

Desde el nivel 1
Recupera 20 de vida
![chees](https://user-images.githubusercontent.com/62880649/120046737-20ac3380-c013-11eb-89df-afa1927ad075.png)

### Manzana
Desde el nivel 1
Recupera 35 de vida
![apple](https://user-images.githubusercontent.com/62880649/120046786-39b4e480-c013-11eb-9eac-fc3af04adfaf.png)







### 5.9 Sonido SFX 
#### Efectos
Golpe
Golpe Fuerte
Ataque
Muerte
Ataque al corazón
Boss Gato
Boss Mano
Enemigo Mono
Tren
Coche
Soldados
Minijuegos
Posesión
Habilidades
Botones
Recoger items
Trampa
#### Música y Ambiente
Menú principal
Lvl 1
Lvl 2
Lvl 3
Lvl 4
Pájaros
Microondas
#### Miscelánea
Tutoriales (Ángel)
Transiciones

## 6 - QA

![Difi-Impresiones](https://user-images.githubusercontent.com/62880649/120051186-ee550300-c01f-11eb-8907-6c9f693fc201.png)

A pesar de querer sacar 2 demos y poder comprobar que las mecánicas y niveles funcionaban como lo previsto, sólo fuimos capaces de sacar una demo tras el Hito 2, aun así, nos ha sido de gran utilidad, pues al estar centrado en la sensación de juego de combate, nos dio un backup para saber que por lo menos el combate iba pulido gracias a las conclusiones de este formulario .

El feedback general era positivo, la gente veía fluidas las animaciones, el golpes y los sonidos eran adecuados. Nos comentaron que a veces la sensación era extraña porque el golpe no iba en timing con la animación, era un error que teníamos anotado y que finalmente pudimos arreglar en los enemigos pero no en los hamsters por la arquitectura del sistema de combos, que no merecía la pena refactorizar.

Lo más claro del QA fue ver que los enemigos era demasiado fáciles, poca gente perdía siquiera vida durante la demo, el problema era el timing de ataque de los enemigos
Lo ajustamos y subimos algo el timing de ataques y dificultad, aunque tampoco nos hemos excedido. 
Este QA no sólo nos ha dado info sobre el feedback del juego, también nos ha enseñado un poco más a hacer QA, pues vimos que había preguntas realmente inútiles, como el uso de los mandos y el teclado o “Impresiones generales”.

El plan era sacar una demo con otro formulario con sugerencias y algunas preguntas pero sobretodo nos interesaba hacer QA más privado, observando al usuario y viendo si los niveles y sistema de infarto son lo acordado y previsto.
![Control](https://user-images.githubusercontent.com/62880649/120051202-02990000-c020-11eb-9f31-293b8917a459.png)
![Cooldown-Anims](https://user-images.githubusercontent.com/62880649/120051217-0fb5ef00-c020-11eb-8972-33de78cc9652.png)
![Sonidos-Habilidad](https://user-images.githubusercontent.com/62880649/120051225-1a708400-c020-11eb-94dc-4ccf6bd6908a.png)
![Dificultad](https://user-images.githubusercontent.com/62880649/120051247-28bea000-c020-11eb-99bd-b91702045428.png)




## Referencias 
Castle Crashers (The Behemoth, 2008)
Streets of rage 4 (Dotemu, Lizardcube, Guard Crush Games, 2020)
Golden Axe (Sega, 1989)
Double Dragon (Technos Japan, 1987)
Battletoads (Rare, 1991)
