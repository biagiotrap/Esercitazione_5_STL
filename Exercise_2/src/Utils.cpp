#include "Utils.hpp"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<iomanip>
#include<cmath>


using namespace std;
namespace PolygonalLibrary{
bool ImportMesh(const string &filepath,
                PolygonalMesh& mesh)
{
    if(!ImportCell0Ds(filepath + "/Cell0Ds.csv",
                       mesh))
    {
        return false;
    }
    else
    {
        cout << "Cell0D marker:" << endl;
        for(auto it = mesh.Cell0DMarkers.begin(); it != mesh.Cell0DMarkers.end(); it++)
        {
            cout << "key:\t" << it -> first << "\t values:";
            for(const unsigned int id : it -> second){
              cout << "\t" << id;
            }
            cout << endl;
        }
    }
    if(!ImportCell1Ds(filepath + "/Cell1Ds.csv",
                       mesh))
    {
        return false;
    }
    else
    {
        cout << "Cell1D marker:" << endl;
        for(auto it = mesh.Cell1DMarkers.begin(); it != mesh.Cell1DMarkers.end(); it++)
        {
            cout << "key:\t" << it -> first << "\t values:";
            for(const unsigned int id : it -> second){
                cout << "\t" << id;
            }
            cout << endl;
        }
    }

    if(!ImportCell2Ds(filepath + "/Cell2Ds.csv",
                       mesh))
    {
        return false;
    }
    else{
        cout << "Cell2D marker:" << endl;
        for(auto it = mesh.Cell2DMarkers.begin(); it != mesh.Cell2DMarkers.end(); it++)
        {
            cout << "key:\t" << it -> first << "\t values:";
            for(const unsigned int id : it -> second){
                cout << "\t" << id;
            }
            cout << endl;
        }
    }
    return true;
}
bool ImportCell0Ds(const string &filename,
                   PolygonalMesh& mesh){
    ifstream file;
    file.open(filename);
    if(file.fail()){
        return false;
    }
    list<string> listLines;
    string data;
    string lines;
    string riga;
    getline(file,lines);
    while (getline(file, lines)){
        istringstream line(lines);
         while(getline(line,data,';')){
            riga+=data+" ";
        }
        listLines.push_back(riga);
        riga.clear();
    }
    mesh.NumberCell0D = listLines.size();
    if (mesh.NumberCell0D == 0)
    {
        cerr << "There is no cell 0D" << endl;
        return false;
    }
    mesh.Cell0DId.reserve(mesh.NumberCell0D);
    mesh.Cell0DCoordinates.reserve(mesh.NumberCell0D);
    for (const string& line : listLines){
        istringstream converter(line);
        unsigned int id;
        unsigned int marker;
        Vector2d coord;
        converter >>  id >> marker >> coord(0) >> coord(1);
        mesh.Cell0DId.push_back(id);
        mesh.Cell0DCoordinates.push_back(coord);
        if (mesh.Cell0DMarkers.find(marker) == mesh.Cell0DMarkers.end()){
            mesh.Cell0DMarkers.insert({marker, {id}});
        }
        else{
            mesh.Cell0DMarkers[marker].push_back(id);
        }
    }
    file.close();
    return true;
}
bool ImportCell1Ds(const string &filename,
                   PolygonalMesh& mesh)
{
    ifstream file;
    file.open(filename);
    if(file.fail()){
        return false;
    }
    list<string> listLines;
    string data;
    string lines;
    string riga;
    getline(file,lines);
    while (getline(file, lines)){
        istringstream line(lines);
        while(getline(line,data,';')){
            riga+=data+" ";
        }
        listLines.push_back(riga);
        riga.clear();
    }
    mesh.NumberCell1D = listLines.size();
    if (mesh.NumberCell1D == 0)
    {
        cerr << "There is no cell 1D" << endl;
        return false;
    }
    mesh.Cell1DId.reserve(mesh.NumberCell1D);
    mesh.Cell1DVertices.reserve(mesh.NumberCell1D);
    for (const string& line : listLines){
        istringstream converter(line);
        unsigned int id;
        unsigned int marker;
        Vector2i vertices;
        converter >>  id >> marker >> vertices(0) >> vertices(1);
        mesh.Cell1DId.push_back(id);
        mesh.Cell1DVertices.push_back(vertices);
        if (mesh.Cell1DMarkers.find(marker) == mesh.Cell1DMarkers.end()){
            mesh.Cell1DMarkers.insert({marker, {id}});
        }
        else{
            mesh.Cell1DMarkers[marker].push_back(id);
        }
    }
    file.close();
    return true;
}
bool ImportCell2Ds(const string &filename,
                   PolygonalMesh& mesh)
{
    ifstream file;
    file.open(filename);
    if(file.fail()){
        return false;
    }
    list<string> listLines;
    string data;
    string lines;
    string riga;
    getline(file,lines);
    while (getline(file, lines)){
        istringstream line(lines);
        while(getline(line,data,';')){
            riga+=data+" ";
        }
        listLines.push_back(riga);
        riga.clear();
    }
    mesh.NumberCell2D = listLines.size();
    if (mesh.NumberCell2D == 0)
    {
        cerr << "There is no cell 2D" << endl;
        return false;
    }
    mesh.Cell2DId.reserve(mesh.NumberCell2D);
    mesh.Cell2DNumberVertices.reserve(mesh.NumberCell2D);
    mesh.Cell2DNumberEdges.reserve(mesh.NumberCell2D);
    mesh.Cell2DVertices.reserve(mesh.NumberCell2D);
    mesh.Cell2DEdges.reserve(mesh.NumberCell2D);
    for (const string& line : listLines){
        istringstream converter(line);
        unsigned int id;
        converter>>id;
        mesh.Cell2DId.push_back(id);
        unsigned int marker;
        converter>>marker;
        if (mesh.Cell2DMarkers.find(marker) == mesh.Cell2DMarkers.end()){
            mesh.Cell2DMarkers.insert({marker, {id}});
        }
        else{
            mesh.Cell2DMarkers[marker].push_back(id);
        }
        unsigned int numVert;
        unsigned int numEd;
        converter>> numVert;
        mesh.Cell2DNumberVertices.push_back(numVert);
        vector<unsigned int> vertices={};
        vertices.resize(numVert);
        for(unsigned int i=0;i<numVert;i++){
            converter>>vertices[i];
        }
        mesh.Cell2DVertices.push_back(vertices);
        converter>> numEd;
        mesh.Cell2DNumberEdges.push_back(numEd);
        vector<unsigned int> edges={};
        edges.resize(numEd);
        for(unsigned int i=0;i<numEd;i++){
            converter>>edges[i];
        }
        mesh.Cell2DEdges.push_back(edges);
    }
    file.close();
    return true;
}
bool Triangoli(PolygonalMesh& mesh){
    double lato=0;
    double area=0;
    double tol=1e-16;
    vector<Vector2d> lati={};
    for(auto vertici:mesh.Cell2DVertices){
        if(size(vertici)==3){
            for(unsigned int i=0;i<3;i++){
                for(unsigned int n=0;n<size(mesh.Cell0DId);n++){
                    if(vertici[i]==mesh.Cell0DId[n]){
                        lati.push_back(mesh.Cell0DCoordinates[n]);
                    }
                }
            }
        }
        lato=(lati[0]-lati[2]).norm();
        if(lato<tol){
            cerr<<"Errore";
            return false;
        }
        for(unsigned int n=0; n<2;n++){
            lato=(lati[n]-lati[n+1]).norm();
            if(lato<tol){
                cerr<<"Errore";
                return false;
            }
        }
        lati[0]=lati[0]-lati[1];
        lati[1]=lati[0]-lati[2];
        area=(1/2)*(abs((lati[0][0]*lati[1][1]-lati[0][1]*lati[1][0])));
        if(area<tol){
            cerr<<"Errore";
            return false;
        }
        lati.clear();
    }
    return true;
}
}






