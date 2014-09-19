xof 0303txt 0032
template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}


Mesh {
 8;
 0.000000;0.000000;0.000000;,
 0.000000;0.000000;-1.000000;,
 1.000000;0.000000;-1.000000;,
 1.000000;0.000000;0.000000;,
 0.000000;1.000000;0.000000;,
 0.000000;1.000000;-1.000000;,
 1.000000;1.000000;0.000000;,
 1.000000;1.000000;-1.000000;;
 12;
 3;0,0,1;,
 3;0,2,0;,
 3;2,0,3;,
 3;0,0,0;,
 3;1,0,0;,
 3;0,4,0;,
 3;4,0,5;,
 3;0,1,0;,
 3;0,0,3;,
 3;0,6,0;,
 3;6,0,4;,
 3;0,0,0;;
}