//---------------------------------------------------------------------------
#include <iostream>
#include <thread>
#include <gmds/ig/Mesh.h>
//---------------------------------------------------------------------------
using namespace gmds;

//---------------------------------------------------------------------------
bool isInCircle(const math::Point& APoint, const Face& AFace) {
    std::vector<Node> nodes = AFace.get<Node>();
    math::Point p0 = nodes[0].point();
    math::Point p1 = nodes[1].point();
    math::Point p2 = nodes[2].point();
    return false;
}
//---------------------------------------------------------------------------
void initBoxMesh(Mesh* AMesh, const double AXMax, const double AYMax){
    Node n0 = AMesh->newNode(0,0);
    Node n1 = AMesh->newNode(AXMax,0);
    Node n2 = AMesh->newNode(AXMax,AYMax);
    Node n3 = AMesh->newNode(0,AYMax);
    Face f1 = AMesh->newTriangle(n0,n1,n2);
    Face f2 = AMesh->newTriangle(n2,n0,n3);
    //update the connectivity N --> F
    n0.add(f1);
    n1.add(f1);
    n2.add(f1);

    n2.add(f2);
    n0.add(f2);
    n3.add(f2);

}
//---------------------------------------------------------------------------
int main(){
    std::cout<<"Concurrent triangulation with gmds and std::thread"<<std::endl;
    double x_max=10;
    double y_max=10;

    Mesh m(MeshModel(DIM3|N|F|F2N|N2F));

    initBoxMesh(&m, x_max,y_max);
    std::cout<<"The mesh has "<<m.getNbFaces()<<std::endl;
    std::thread t;
    return 0;
}
//---------------------------------------------------------------------------
