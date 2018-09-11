#define VOXELIZER_IMPLEMENTATION
#include "../voxelizer.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "../../io/helper/tiny_obj_loader.h"

bool Voxelize(const char* filename, float voxelsizex, float voxelsizey, float voxelsizez, float precision)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename);

    if (!err.empty()) {
      printf("err: %s\n", err.c_str());
    }

    if (!ret) {
      printf("failed to load : %s\n", filename);
      return false;
    }

    if (shapes.size() == 0) {
      printf("err: # of shapes are zero.\n");
      return false;
    }

    // Only use first shape.
    {
        vx_mesh_t* mesh;
        vx_mesh_t* result;

        mesh = vx_mesh_alloc(attrib.vertices.size(), shapes[0].mesh.indices.size());

        for (size_t f = 0; f < shapes[0].mesh.indices.size(); f++) {
            mesh->indices[f] = shapes[0].mesh.indices[f].vertex_index;
        }

        for (size_t v = 0; v < attrib.vertices.size() / 3; v++) {
            mesh->vertices[v].x = attrib.vertices[3*v+0];
            mesh->vertices[v].y = attrib.vertices[3*v+1];
            mesh->vertices[v].z = attrib.vertices[3*v+2];
        }

        result = vx_voxelize(mesh, voxelsizex, voxelsizey, voxelsizez, precision);

        printf("Number of vertices: %ld\n", result->nvertices);
        printf("Number of indices: %ld\n", result->nindices);
    }
    return true;
}


int main(int argc, char** argv)
{
  if (argc < 4) {
    printf("Usage: voxelize input.obj voxelsizex voxelsizey voxelsizez precision\n");
    exit(-1);
  }

  const char* filename = argv[1];
  float voxelsizex = atof(argv[2]);
  float voxelsizey = atof(argv[3]);
  float voxelsizez = atof(argv[4]);
  float prec = atof(argv[5]);
  bool ret = Voxelize(filename, voxelsizex, voxelsizey, voxelsizez, prec);

  return ret ? EXIT_SUCCESS : EXIT_FAILURE;
}


// TODO:
#define TRIANGULATE
// #define POINT_CLOUD

// int main(int argc, char** argv) {
//     if (argc < 4) {
//         std::cout << "Usage: " << std::endl;
//         std::cout << "\t./voxelizer file.obj resolution precision" << std::endl;
//         return EXIT_FAILURE;
//     }

//     std::vector<tinyobj::shape_t> shapes;
//     std::vector<tinyobj::material_t> materials;
//     std::string err;
//     bool ret = tinyobj::LoadObj(shapes, materials, err, argv[1], NULL);

//     if (!err.empty()) {
//         std::cerr << err << std::endl;
//     }

//     if (!ret) {
//         return EXIT_FAILURE;
//     }

// #ifdef TRIANGULATE
//     std::ofstream file("mesh_voxelized_res.obj");
// #endif

// #ifdef POINT_CLOUD
//     std::ofstream file("mesh_voxelized_res.txt");
// #endif

//     size_t voffset = 0;
//     size_t noffset = 0;

//     for (size_t i = 0; i < shapes.size(); i++) {
//         vx_mesh_t* mesh;

//         mesh = vx_mesh_alloc(shapes[i].mesh.positions.size(), shapes[i].mesh.indices.size());

//         for (size_t f = 0; f < shapes[i].mesh.indices.size(); f++) {
//             mesh->indices[f] = shapes[i].mesh.indices[f];
//         }
//         for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
//             mesh->vertices[v].x = shapes[i].mesh.positions[3*v+0];
//             mesh->vertices[v].y = shapes[i].mesh.positions[3*v+1];
//             mesh->vertices[v].z = shapes[i].mesh.positions[3*v+2];
//         }

//         float res = std::atof(argv[2]);
//         float precision = std::atof(argv[3]);

// #ifdef TRIANGULATE
//         vx_mesh_t* result;
//         result = vx_voxelize(mesh, res, res, res, precision);

//         printf("Number of vertices: %ld\n", result->nvertices);
//         printf("Number of indices: %ld\n", result->nindices);

//         if (file.is_open()) {
//             file << "\n";
//             file << "o " << i << "\n";

//             for (int j = 0; j < result->nvertices; ++j) {
//                 file << "v " << result->vertices[j].x << " "
//                              << result->vertices[j].y << " "
//                              << result->vertices[j].z << "\n";
//             }

//             for (int j = 0; j < result->nnormals; ++j) {
//                 file << "vn " << result->normals[j].x << " "
//                               << result->normals[j].y << " "
//                               << result->normals[j].z << "\n";
//             }

//             size_t max = 0;

//             for (int j = 0; j < result->nindices; j += 3) {
//                 size_t i0 = voffset + result->indices[j+0] + 1;
//                 size_t i1 = voffset + result->indices[j+1] + 1;
//                 size_t i2 = voffset + result->indices[j+2] + 1;

//                 max = i0 > max ? i0 : max;
//                 max = i1 > max ? i1 : max;
//                 max = i2 > max ? i2 : max;

//                 file << "f ";

//                 file << i0 << "//" << result->normalindices[j+0] + noffset + 1 << " ";
//                 file << i1 << "//" << result->normalindices[j+1] + noffset + 1 << " ";
//                 file << i2 << "//" << result->normalindices[j+2] + noffset + 1 << "\n";
//             }

//             voffset += max;
//             noffset += 6;
//         }

//         vx_mesh_free(result);
//         vx_mesh_free(mesh);
// #endif

// #ifdef POINT_CLOUD
//         vx_point_cloud_t* result;
//         result = vx_voxelize_pc(mesh, res, res, res, precision);

//         printf("Number of vertices: %ld\n", result->nvertices);

//         if (file.is_open()) {
//             file << "\n";
//             for (int j = 0; j < result->nvertices; ++j) {
//                 file << result->vertices[j].x << " "
//                      << result->vertices[j].y << " "
//                      << result->vertices[j].z << "\n";
//             }
//         }

//         vx_point_cloud_free(result);
//         vx_mesh_free(mesh);
// #endif
//     }

//     file.close();

//     return EXIT_SUCCESS;
// }
