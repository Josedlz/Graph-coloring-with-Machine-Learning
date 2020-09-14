# Implementación de un algoritmo que resuelve el problema del número cromático en grafos haciendo uso de ICLA (Irregular Cellular Learning Automatas).

En el paper adjunto en este repositorio se describe una técnica interesante para
hallar el mínimo número de colores necesario para colorear adecuadamente un grafo.

De manera intuitiva, lo que hace el algoritmo es situar un autómata de aprendizaje
en cada vértice del grafo que el programa recibe en su input. Cada automáta intentará colorearse
de modo tal que su color sea diferente al de sus vecinos, y las probabilidades con las que escogerá
cada color se verán recompensadas y/o penalizadas de acuerdo a una función de recompensa. De este modo, 
progresivamente estabilizará su valor conforme transcurran las iteraciones. 

Este acercamiento es interesante porque combina los conceptos de grafos y automátas celulares
para resolver un problema muy conocido.
