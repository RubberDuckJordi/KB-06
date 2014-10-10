xof 0303txt 0032
template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}

template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

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

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template VertexElement {
 <f752461c-1e23-48f6-b9f8-8350850f336f>
 DWORD Type;
 DWORD Method;
 DWORD Usage;
 DWORD UsageIndex;
}

template DeclData {
 <bf22e553-292c-4781-9fea-62bd554bdd93>
 DWORD nElements;
 array VertexElement Elements[nElements];
 DWORD nDWords;
 array DWORD data[nDWords];
}


Material material {
 1.000000;1.000000;1.000000;1.000000;;
 0.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;
}

Material material_4 {
 1.000000;1.000000;1.000000;1.000000;;
 0.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "material_4.tga";
 }
}

Frame SketchUp {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh SketchUp {
  20;
  4.000000;0.000000;5.000000;,
  -4.000000;0.000000;5.000000;,
  -4.000000;0.000000;-5.000000;,
  4.000000;0.000000;-5.000000;,
  -4.000000;0.100000;5.000000;,
  -4.000000;0.000000;5.000000;,
  4.000000;0.000000;5.000000;,
  4.000000;0.100000;5.000000;,
  4.000000;0.000000;5.000000;,
  4.000000;0.000000;-5.000000;,
  4.000000;0.100000;-5.000000;,
  4.000000;0.100000;5.000000;,
  4.000000;0.100000;-5.000000;,
  4.000000;0.000000;-5.000000;,
  -4.000000;0.000000;-5.000000;,
  -4.000000;0.100000;-5.000000;,
  -4.000000;0.100000;5.000000;,
  -4.000000;0.100000;-5.000000;,
  -4.000000;0.000000;-5.000000;,
  -4.000000;0.000000;5.000000;;
  10;
  3;0,1,2;,
  3;2,3,0;,
  3;4,5,6;,
  3;6,7,4;,
  3;8,9,10;,
  3;10,11,8;,
  3;12,13,14;,
  3;14,15,12;,
  3;16,17,18;,
  3;18,19,16;;

  MeshMaterialList {
   1;
   10;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;
   { material }
  }

  DeclData {
   1;
   2;0;3;0;;
   60;
   0,
   3212836864,
   0,
   0,
   3212836864,
   0,
   0,
   3212836864,
   0,
   0,
   3212836864,
   0,
   0,
   0,
   1065353216,
   0,
   0,
   1065353216,
   0,
   0,
   1065353216,
   0,
   0,
   1065353216,
   1065353216,
   0,
   0,
   1065353216,
   0,
   0,
   1065353216,
   0,
   0,
   1065353216,
   0,
   0,
   0,
   0,
   3212836864,
   0,
   0,
   3212836864,
   0,
   0,
   3212836864,
   0,
   0,
   3212836864,
   3212836864,
   0,
   0,
   3212836864,
   0,
   0,
   3212836864,
   0,
   0,
   3212836864,
   0,
   0;
  }
 }

 Frame ID10 {
  

  FrameTransformMatrix {
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
  }

  Mesh ID10 {
   4;
   4.000000;0.100000;-5.000000;,
   -4.000000;0.100000;-5.000000;,
   -4.000000;0.100000;5.000000;,
   4.000000;0.100000;5.000000;;
   2;
   3;0,1,2;,
   3;2,3,0;;

   MeshMaterialList {
    1;
    2;
    0,
    0;
    { material_4 }
   }

   DeclData {
    2;
    2;0;3;0;,
    1;0;5;0;;
    20;
    0,
    1065353216,
    0,
    995965258,
    1065219915,
    0,
    1065353216,
    0,
    3212780231,
    1065219915,
    0,
    1065353216,
    0,
    3212780231,
    3154258816,
    0,
    1065353216,
    0,
    995965258,
    3154258816;
   }
  }
 }
}