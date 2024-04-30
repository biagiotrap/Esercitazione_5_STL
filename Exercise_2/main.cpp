#include <iostream>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"

using namespace std;

using namespace PolygonalLibrary;
int main()
{
    PolygonalMesh mesh;
    string filepath = "PolygonalMesh";
    if(!ImportMesh(filepath,
                    mesh))
    {
        return 1;
    }
    bool triangoli=Triangoli(mesh);
    return 0;
}
