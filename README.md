# Implemmentación de un algoritmo que resuelve el problema del número cromático en grafos
# haciendo uso de ICLA (Irregular Cellular Learning Automatas).

En el paper adjunto en este repositorio se describe una técnica interesante para
hallar el mínimo número de colores necesario para colorear adecuadamente un grafo.

De manera intuitiva, lo que hace el algoritmo es situar un autómata de aprendizaje
en cada vértice del grafo que el programa recibe en su input. Cada automáta intentará colorearse
de modo tal que su color sea diferente al del resto, progresivamente estabilizando su valor 
conforme transcurren las iteraciones. 

Este acercamiento es interesante porque combina los conceptos de grafos y automátas celulares
para resolver un problema muy conocido.
