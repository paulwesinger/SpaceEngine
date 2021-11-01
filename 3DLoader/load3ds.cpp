#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include "../3DLoader/load3ds.h"
#include "../logs/logs.h"
#include "../utils/utils.h"

C3DSLoad::C3DSLoad(){
    _FaceCount = 0;
    _Filename = "";
    _Objectname = "";
}
C3DSLoad::C3DSLoad(std::string filename)
{
    _FaceCount = 0;
    _Filename = filename;
    _Objectname = "";
}
C3DSLoad::~C3DSLoad() {

}

std::vector<TEXTURECOORDS> &C3DSLoad::TextureCoordinates(){
    return texCoords;
}
std::vector<VECTOR> &C3DSLoad::Vecs(){
    return vecs;
}
std::vector<FACE> &C3DSLoad::Faces(){
    return faces;
}

bool C3DSLoad::Load3DS(std::string filename){

    if (filename == "" )
        return  false;
    _Filename = filename;
//-----------------------------------------------
    int i; //Index variable

    FILE *l_file; //File pointer

    unsigned short l_chunk_id; //Chunk identifier
    unsigned int l_chunk_lenght; //Chunk lenght

    unsigned char l_char; //Char variable
    unsigned short l_qty; //Number of elements in each chunk

    unsigned short l_face_flags; //Flag that stores some face information

         //Hiere mal ein paar testausgaben :

    loginfo ("Sizeof short " + IntToString(sizeof(short)));
    loginfo("sizeof int " +IntToString(sizeof(int)));
    logEmptyLine();


    if ((l_file=fopen (filename.c_str(), "rb"))== NULL)
        return 0;
    //Open the file:




    while (ftell (l_file) < filelength (fileno (l_file))) //Loop to scan the whole file
    //while(!EOF)
    {
        //getch(); //Insert this command for debug (to wait for keypress for each chuck reading)

        fread (&l_chunk_id, 2, 1, l_file); //Read the chunk header
        printf("ChunkID: %X\n",l_chunk_id);
        fread (&l_chunk_lenght, 4, 1, l_file); //Read the lenght of the chunk
        printf("ChunkLenght: %X\n",l_chunk_lenght);

        switch (l_chunk_id)
        {
            //----------------- MAIN3DS -----------------
            // Description: Main chunk, contains all the other chunks
            // Chunk ID: 4d4d
            // Chunk Lenght: 0 + sub chunks
            //-------------------------------------------
            case 0x4d4d:
            break;

            //----------------- EDIT3DS -----------------
            // Description: 3D Editor chunk, objects layout info
            // Chunk ID: 3d3d (hex)
            // Chunk Lenght: 0 + sub chunks
            //-------------------------------------------
            case 0x3d3d:
            break;

            //--------------- EDIT_OBJECT ---------------
            // Description: Object block, info for each object
            // Chunk ID: 4000 (hex)
            // Chunk Lenght: len(object name) + sub chunks
            //-------------------------------------------

            case 0x4000:
                i=0;
                char name[20];
                do
                {
                    fread (&l_char, 1, 1, l_file);
                    loginfo(IntToString(i));
                    name[i]=l_char;
                    i++;
                }while(l_char != '\0' && i<20);
                _Objectname = static_cast<std::string>(name);
                logwarn("Objectname : " + _Objectname);
            break;

            //--------------- OBJ_TRIMESH ---------------
            // Description: Triangular mesh, contains chunks for 3d mesh info
            // Chunk ID: 4100 (hex)
            // Chunk Lenght: 0 + sub chunks
            //-------------------------------------------
            case 0x4100:
            break;

            //--------------- TRI_VERTEXL ---------------
            // Description: Vertices list
            // Chunk ID: 4110 (hex)
            // Chunk Lenght: 1 x unsigned short (number of vertices)
            //             + 3 x float (vertex coordinates) x (number of vertices)
            //             + sub chunks
            //-------------------------------------------
            case 0x4110:
                fread (&l_qty, sizeof (unsigned short), 1, l_file);
                _VertexCount = l_qty;
                loginfo("Chunk ID 0x4110");
                printf("Number of vertices: %d\n",l_qty);
                for (i=0; i<l_qty; i++)
                {
                    VECTOR v;

                    fread (&v.x, sizeof(float), 1, l_file);
                    //printf("Vertices list x: %f\n",p_object->vertex[i].x);
                    fread (&v.y, sizeof(float), 1, l_file);
                    //printf("Vertices list y: %f\n",p_object->vertex[i].y);
                    fread (&v.z, sizeof(float), 1, l_file);
                    //printf("Vertices list z: %f\n",p_object->vertex[i].z);
                    vecs.push_back(v);
                }
                break;

            //--------------- TRI_FACEL1 ----------------
            // Description: Polygons (faces) list
            // Chunk ID: 4120 (hex)
            // Chunk Lenght: 1 x unsigned short (number of polygons)
            //             + 3 x unsigned short (polygon points) x (number of polygons)
            //             + sub chunks
            //-------------------------------------------
            case 0x4120:
                fread (&l_qty, sizeof (unsigned short), 1, l_file);
                _FaceCount = l_qty;
                loginfo("Chunk ID 0x4120");
                printf("Number of polygons: %d\n",l_qty);
                for (i=0; i<l_qty; i++)
                {
                    FACE face;
                    fread (&face.p0, sizeof (unsigned short), 1, l_file);
                    fread (&face.p1, sizeof (unsigned short), 1, l_file);
                    fread (&face.p2, sizeof (unsigned short), 1, l_file);
                    fread (&l_face_flags, sizeof (unsigned short), 1, l_file);
                    faces.push_back(face);
                }
                break;

            //------------- TRI_MAPPINGCOORS ------------
            // Description: Vertices list
            // Chunk ID: 4140 (hex)
            // Chunk Lenght: 1 x unsigned short (number of mapping points)
            //             + 2 x float (mapping coordinates) x (number of mapping points)
            //             + sub chunks
            //-------------------------------------------
            case 0x4140:
                loginfo("Chunk ID 0x410");
                fread (&l_qty, sizeof (unsigned short), 1, l_file);
                printf("Number of texturecoords %d\n",l_qty);
                _TextureCount = l_qty;
                for (i=0; i<l_qty; i++)
                {
                    TEXTURECOORDS tex;
                    fread (&tex.u, sizeof (float), 1, l_file);
                    fread (&tex.v, sizeof (float), 1, l_file);
                    texCoords.push_back(tex);
                }
                break;

            //----------- Skip unknow chunks ------------
            //We need to skip all the chunks that currently we don't use
            //We use the chunk lenght information to set the file pointer
            //to the same level next chunk
            //-------------------------------------------
            default:
                 fseek(l_file, l_chunk_lenght-6, SEEK_CUR);
        }
    }
    fclose (l_file); // Closes the file stream
    return true;
}

int C3DSLoad::FaceCount() {
    return _FaceCount;
}
int C3DSLoad::VertexCount(){
    return _VertexCount;
}
int C3DSLoad::TextureCount(){
    return  _TextureCount;
}

std::string C3DSLoad::Objectname() {
    return _Objectname;
}


long C3DSLoad::filelength(int f)
{
    struct stat buf;

    fstat(f, &buf);

    return(buf.st_size);
}
