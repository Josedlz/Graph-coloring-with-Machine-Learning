# Implementation of an algorithm that solves the problem of finding the chromatic number in an arbitrary graph using ICLA (Irregular Cellular Learning Automatas).

In the attached paper within this repository, an interesting technique for finding the minimum number of colors necessary to properly color a graph is explained.

Intuitively, what the algorithm does is placing a Learning Automaton at each vertex of the graph that the program receives as its input. Each automaton will try to color itself so that its color is different from that of its neighbors, and each element on the probability vector it uses to choose each color will be rewarded and / or penalized according to a reward function (our choice in the implentation of the latter differs from the one shown in the paper due to efficiency considerations). In this way,
it will progressively stabilize its value as the iterations ensue.

This approach is interesting because it combines concepts in graph theory with those regarding to cellular automatas to solve a well-known problem.
