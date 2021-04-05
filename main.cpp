#include <iostream>
#include "Graphe.h"

int main()
{
    Graphe g{"data_arcs.txt"};
    g.infoArc();
    g.infoSommet();

    return 0;
}
