#include <iostream>
#include <MeshReconstructWrapper/MeshReconstruct.h>
int main( )
{
  auto m = meshreconstruct::MeshReconstruct::getInstance();
  m->repairFile("a.csv","test.vrml","Obj",50,0.3,true,3,true,"Path");
}
