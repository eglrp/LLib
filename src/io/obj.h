#ifndef _LL_OBJ_H_
#define _LL_OBJ_H_

#include <iostream>

#define TINYOBJLOADER_IMPLEMENTATION
#include "helper/tiny_obj_loader.h"

namespace LLib
{
    void printObjInfo(const tinyobj::attrib_t& attrib,
                      const std::vector<tinyobj::shape_t>& shapes,
                      const std::vector<tinyobj::material_t>& materials);
            
    bool writeMat(const std::string& filename, const std::vector<tinyobj::material_t>& materials);

    std::string getFileBasename(const std::string& FileName);

    // TODO: LoadObjWithCallback

    class obj
    {
        private:
            tinyobj::attrib_t attrib;
            std::vector<tinyobj::shape_t> shapes;
            std::vector<tinyobj::material_t> materials;

        public:
            bool load(const char *filename, const char *basepath = nullptr, bool triangulate = true);
            bool write(const std::string& filename, bool coordTransform = false) const;
            void print() const { printObjInfo(attrib, shapes, materials); }
            

    };   //class obj

    inline bool obj::load(const char *filename, const char *basepath, bool triangulate)
    {
        std::string err;
        bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename, basepath, triangulate);
          if (!err.empty())
            std::cerr << err << std::endl;

        if (!ret) {
          printf("Failed to load/parse .obj.\n");
          return false;
        }

        return true;
    }

    bool obj::write(const std::string& filename, bool coordTransform) const {
        FILE* fp = fopen(filename.c_str(), "w");
        if (!fp) {
          fprintf(stderr, "Failed to open file [ %s ] for write.\n", filename.c_str());
          return false;
        }

        std::string basename = getFileBasename(filename);
        std::string material_filename = basename + ".mtl";

      int prev_material_id = -1;

      fprintf(fp, "mtllib %s\n\n", material_filename.c_str());

      // facevarying vtx
      for (size_t k = 0; k < attrib.vertices.size(); k+=3) {
        if (coordTransform) {
          fprintf(fp, "v %f %f %f\n",
            attrib.vertices[k + 0],
            attrib.vertices[k + 2],
            -attrib.vertices[k + 1]);
        } else {
          fprintf(fp, "v %f %f %f\n",
            attrib.vertices[k + 0],
            attrib.vertices[k + 1],
            attrib.vertices[k + 2]);
        }
      }

      fprintf(fp, "\n");

      // facevarying normal
      for (size_t k = 0; k < attrib.normals.size(); k += 3) {
        if (coordTransform) {
          fprintf(fp, "vn %f %f %f\n",
            attrib.normals[k + 0],
            attrib.normals[k + 2],
            -attrib.normals[k + 1]);
        } else {
          fprintf(fp, "vn %f %f %f\n",
            attrib.normals[k + 0],
            attrib.normals[k + 1],
            attrib.normals[k + 2]);
        }
      }

      fprintf(fp, "\n");

      // facevarying texcoord
      for (size_t k = 0; k < attrib.texcoords.size(); k += 2) {
        fprintf(fp, "vt %f %f\n",
          attrib.texcoords[k + 0],
          attrib.texcoords[k + 1]);
      }

      for (size_t i = 0; i < shapes.size(); i++) {
        fprintf(fp, "\n");

        if (shapes[i].name.empty()) {
          fprintf(fp, "g Unknown\n");
        } else {
          fprintf(fp, "g %s\n", shapes[i].name.c_str());
        }

        bool has_vn = false;
        bool has_vt = false;
        // Assumes normals and textures are set shape-wise.
        if(shapes[i].mesh.indices.size() > 0){
          has_vn = shapes[i].mesh.indices[0].normal_index != -1;
          has_vt = shapes[i].mesh.indices[0].texcoord_index != -1;
        }

        // face
        int face_index = 0;
        for (size_t k = 0; k < shapes[i].mesh.indices.size(); k += shapes[i].mesh.num_face_vertices[face_index++]) {
          // Check Materials
          int material_id = shapes[i].mesh.material_ids[face_index];
          if (material_id != prev_material_id) {
            std::string material_name = materials[material_id].name;
            fprintf(fp, "usemtl %s\n", material_name.c_str());
            prev_material_id = material_id;
          }

          unsigned char v_per_f = shapes[i].mesh.num_face_vertices[face_index];
          // Imperformant, but if you want to have variable vertices per face, you need some kind of a dynamic loop.
          fprintf(fp, "f");
          for(int l = 0; l < v_per_f; l++){
            const tinyobj::index_t& ref = shapes[i].mesh.indices[k + l];
            if(has_vn && has_vt){
              // v0/t0/vn0
              fprintf(fp, " %d/%d/%d", ref.vertex_index + 1, ref.texcoord_index + 1, ref.normal_index + 1);
              continue;
            }
            if(has_vn && !has_vt){
              // v0//vn0
              fprintf(fp, " %d//%d", ref.vertex_index + 1, ref.normal_index + 1);
              continue;
            }
            if(!has_vn && has_vt){
              // v0/vt0
              fprintf(fp, " %d/%d", ref.vertex_index + 1, ref.texcoord_index + 1);
              continue;
            }
            if(!has_vn && !has_vt){
              // v0 v1 v2
              fprintf(fp, " %d", ref.vertex_index + 1);
              continue;
            }
          }
          fprintf(fp, "\n");
        }
      }

      fclose(fp);

      //
      // Write material file
      //
      bool ret = writeMat(material_filename, materials);

      return ret;
    }

    inline std::string getFileBasename(const std::string& FileName)
    {
        if(FileName.find_last_of(".") != std::string::npos)
            return FileName.substr(0, FileName.find_last_of("."));
        return "";
    }

    inline bool writeMat(const std::string& filename, const std::vector<tinyobj::material_t>& materials) {
      FILE* fp = fopen(filename.c_str(), "w");
      if (!fp) {
        fprintf(stderr, "Failed to open file [ %s ] for write.\n", filename.c_str());
        return false;
      }

      for (size_t i = 0; i < materials.size(); i++) {

        tinyobj::material_t mat = materials[i];

        fprintf(fp, "newmtl %s\n", mat.name.c_str());
        fprintf(fp, "Ka %f %f %f\n", mat.ambient[0], mat.ambient[1], mat.ambient[2]);
        fprintf(fp, "Kd %f %f %f\n", mat.diffuse[0], mat.diffuse[1], mat.diffuse[2]);
        fprintf(fp, "Ks %f %f %f\n", mat.specular[0], mat.specular[1], mat.specular[2]);
        fprintf(fp, "Kt %f %f %f\n", mat.transmittance[0], mat.specular[1], mat.specular[2]);
        fprintf(fp, "Ke %f %f %f\n", mat.emission[0], mat.emission[1], mat.emission[2]);
        fprintf(fp, "Ns %f\n", mat.shininess);
        fprintf(fp, "Ni %f\n", mat.ior);
        fprintf(fp, "illum %d\n", mat.illum);
        fprintf(fp, "\n");
        // @todo { texture }
      }
    
      fclose(fp);

      return true;
    }

    inline void printObjInfo(const tinyobj::attrib_t& attrib,
                             const std::vector<tinyobj::shape_t>& shapes,
                             const std::vector<tinyobj::material_t>& materials) {
      std::cout << "# of vertices  : " << (attrib.vertices.size() / 3) << std::endl;
      std::cout << "# of normals   : " << (attrib.normals.size() / 3) << std::endl;
      std::cout << "# of texcoords : " << (attrib.texcoords.size() / 2)
                << std::endl;

      std::cout << "# of shapes    : " << shapes.size() << std::endl;
      std::cout << "# of materials : " << materials.size() << std::endl;

      for (size_t v = 0; v < attrib.vertices.size() / 3; v++) {
        printf("  v[%ld] = (%f, %f, %f)\n", static_cast<long>(v),
               static_cast<const double>(attrib.vertices[3 * v + 0]),
               static_cast<const double>(attrib.vertices[3 * v + 1]),
               static_cast<const double>(attrib.vertices[3 * v + 2]));
      }

      for (size_t v = 0; v < attrib.normals.size() / 3; v++) {
        printf("  n[%ld] = (%f, %f, %f)\n", static_cast<long>(v),
               static_cast<const double>(attrib.normals[3 * v + 0]),
               static_cast<const double>(attrib.normals[3 * v + 1]),
               static_cast<const double>(attrib.normals[3 * v + 2]));
      }

      for (size_t v = 0; v < attrib.texcoords.size() / 2; v++) {
        printf("  uv[%ld] = (%f, %f)\n", static_cast<long>(v),
               static_cast<const double>(attrib.texcoords[2 * v + 0]),
               static_cast<const double>(attrib.texcoords[2 * v + 1]));
      }

      // For each shape
      for (size_t i = 0; i < shapes.size(); i++) {
        printf("shape[%ld].name = %s\n", static_cast<long>(i),
               shapes[i].name.c_str());
        printf("Size of shape[%ld].mesh.indices: %lu\n", static_cast<long>(i),
               static_cast<unsigned long>(shapes[i].mesh.indices.size()));
        printf("Size of shape[%ld].path.indices: %lu\n", static_cast<long>(i),
               static_cast<unsigned long>(shapes[i].path.indices.size()));

        size_t index_offset = 0;

        assert(shapes[i].mesh.num_face_vertices.size() ==
               shapes[i].mesh.material_ids.size());

        assert(shapes[i].mesh.num_face_vertices.size() ==
               shapes[i].mesh.smoothing_group_ids.size());

        printf("shape[%ld].num_faces: %lu\n", static_cast<long>(i),
               static_cast<unsigned long>(shapes[i].mesh.num_face_vertices.size()));

        // For each face
        for (size_t f = 0; f < shapes[i].mesh.num_face_vertices.size(); f++) {
          size_t fnum = shapes[i].mesh.num_face_vertices[f];

          printf("  face[%ld].fnum = %ld\n", static_cast<long>(f),
                 static_cast<unsigned long>(fnum));

          // For each vertex in the face
          for (size_t v = 0; v < fnum; v++) {
            tinyobj::index_t idx = shapes[i].mesh.indices[index_offset + v];
            printf("    face[%ld].v[%ld].idx = %d/%d/%d\n", static_cast<long>(f),
                   static_cast<long>(v), idx.vertex_index, idx.normal_index,
                   idx.texcoord_index);
          }

          printf("  face[%ld].material_id = %d\n", static_cast<long>(f),
                 shapes[i].mesh.material_ids[f]);
          printf("  face[%ld].smoothing_group_id = %d\n", static_cast<long>(f),
                 shapes[i].mesh.smoothing_group_ids[f]);

          index_offset += fnum;
        }

        printf("shape[%ld].num_tags: %lu\n", static_cast<long>(i),
               static_cast<unsigned long>(shapes[i].mesh.tags.size()));
        for (size_t t = 0; t < shapes[i].mesh.tags.size(); t++) {
          printf("  tag[%ld] = %s ", static_cast<long>(t),
                 shapes[i].mesh.tags[t].name.c_str());
          printf(" ints: [");
          for (size_t j = 0; j < shapes[i].mesh.tags[t].intValues.size(); ++j) {
            printf("%ld", static_cast<long>(shapes[i].mesh.tags[t].intValues[j]));
            if (j < (shapes[i].mesh.tags[t].intValues.size() - 1)) {
              printf(", ");
            }
          }
          printf("]");

          printf(" floats: [");
          for (size_t j = 0; j < shapes[i].mesh.tags[t].floatValues.size(); ++j) {
            printf("%f", static_cast<const double>(
                             shapes[i].mesh.tags[t].floatValues[j]));
            if (j < (shapes[i].mesh.tags[t].floatValues.size() - 1)) {
              printf(", ");
            }
          }
          printf("]");

          printf(" strings: [");
          for (size_t j = 0; j < shapes[i].mesh.tags[t].stringValues.size(); ++j) {
            printf("%s", shapes[i].mesh.tags[t].stringValues[j].c_str());
            if (j < (shapes[i].mesh.tags[t].stringValues.size() - 1)) {
              printf(", ");
            }
          }
          printf("]");
          printf("\n");
        }
      }

      for (size_t i = 0; i < materials.size(); i++) {
        printf("material[%ld].name = %s\n", static_cast<long>(i),
               materials[i].name.c_str());
        printf("  material.Ka = (%f, %f ,%f)\n",
               static_cast<const double>(materials[i].ambient[0]),
               static_cast<const double>(materials[i].ambient[1]),
               static_cast<const double>(materials[i].ambient[2]));
        printf("  material.Kd = (%f, %f ,%f)\n",
               static_cast<const double>(materials[i].diffuse[0]),
               static_cast<const double>(materials[i].diffuse[1]),
               static_cast<const double>(materials[i].diffuse[2]));
        printf("  material.Ks = (%f, %f ,%f)\n",
               static_cast<const double>(materials[i].specular[0]),
               static_cast<const double>(materials[i].specular[1]),
               static_cast<const double>(materials[i].specular[2]));
        printf("  material.Tr = (%f, %f ,%f)\n",
               static_cast<const double>(materials[i].transmittance[0]),
               static_cast<const double>(materials[i].transmittance[1]),
               static_cast<const double>(materials[i].transmittance[2]));
        printf("  material.Ke = (%f, %f ,%f)\n",
               static_cast<const double>(materials[i].emission[0]),
               static_cast<const double>(materials[i].emission[1]),
               static_cast<const double>(materials[i].emission[2]));
        printf("  material.Ns = %f\n",
               static_cast<const double>(materials[i].shininess));
        printf("  material.Ni = %f\n", static_cast<const double>(materials[i].ior));
        printf("  material.dissolve = %f\n",
               static_cast<const double>(materials[i].dissolve));
        printf("  material.illum = %d\n", materials[i].illum);
        printf("  material.map_Ka = %s\n", materials[i].ambient_texname.c_str());
        printf("  material.map_Kd = %s\n", materials[i].diffuse_texname.c_str());
        printf("  material.map_Ks = %s\n", materials[i].specular_texname.c_str());
        printf("  material.map_Ns = %s\n",
               materials[i].specular_highlight_texname.c_str());
        printf("  material.map_bump = %s\n", materials[i].bump_texname.c_str());
        printf("    bump_multiplier = %f\n", static_cast<const double>(materials[i].bump_texopt.bump_multiplier));
        printf("  material.map_d = %s\n", materials[i].alpha_texname.c_str());
        printf("  material.disp = %s\n", materials[i].displacement_texname.c_str());
        printf("  <<PBR>>\n");
        printf("  material.Pr     = %f\n", static_cast<const double>(materials[i].roughness));
        printf("  material.Pm     = %f\n", static_cast<const double>(materials[i].metallic));
        printf("  material.Ps     = %f\n", static_cast<const double>(materials[i].sheen));
        printf("  material.Pc     = %f\n", static_cast<const double>(materials[i].clearcoat_thickness));
        printf("  material.Pcr    = %f\n", static_cast<const double>(materials[i].clearcoat_thickness));
        printf("  material.aniso  = %f\n", static_cast<const double>(materials[i].anisotropy));
        printf("  material.anisor = %f\n", static_cast<const double>(materials[i].anisotropy_rotation));
        printf("  material.map_Ke = %s\n", materials[i].emissive_texname.c_str());
        printf("  material.map_Pr = %s\n", materials[i].roughness_texname.c_str());
        printf("  material.map_Pm = %s\n", materials[i].metallic_texname.c_str());
        printf("  material.map_Ps = %s\n", materials[i].sheen_texname.c_str());
        printf("  material.norm   = %s\n", materials[i].normal_texname.c_str());
        std::map<std::string, std::string>::const_iterator it(
            materials[i].unknown_parameter.begin());
        std::map<std::string, std::string>::const_iterator itEnd(
            materials[i].unknown_parameter.end());

        for (; it != itEnd; it++) {
          printf("  material.%s = %s\n", it->first.c_str(), it->second.c_str());
        }
        printf("\n");
      }
    }
}   // namespace LLib

#endif  // _LL_OBJ_H_