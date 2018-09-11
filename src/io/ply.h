#ifndef _LL_PLY_H_
#define _LL_PLY_H_

#include <string>
#include <iostream>
#include <fstream>

#include "helper/tinyply.h"

namespace LLib
{
    // TODO:
    // const size_t numVerticesBytes = vertices->buffer.size_bytes();
	// std::vector<float3> verts(vertices->count);
	// std::memcpy(verts.data(), vertices->buffer.get(), numVerticesBytes);

    struct float2 { float x, y; };
    struct float3 { float x, y, z; };
    struct double3 { double x, y, z; };
    struct uint3 { uint32_t x, y, z; };
    struct uint4 { uint32_t x, y, z, w; };

    struct geometry
    {
        std::vector<float3> vertices;
        std::vector<float3> normals;
        std::vector<float2> texcoords;
        std::vector<uint3> triangles;
    };

    class ply
    {
        private:
            tinyply::PlyFile file;
            std::shared_ptr<tinyply::PlyData> vertices, normals, faces, texcoords;
        public:
            ply(const std::string &filepath) { load(filepath); }
            // TODO:
            ply(const geometry &geo);

            void load(const std::string &filepath);
            void write_ascii(const std::string &filepath);    
            void write_binary(const std::string &filepath);    
            void print();

            // TODO:
            geometry export2geometry();

    };  // class ply

    inline void ply::load(const std::string &filepath)
    {
        std::ifstream ss(filepath, std::ios::binary);
		if (ss.fail()) throw std::runtime_error("failed to open " + filepath);

		file.parse_header(ss);

		try { vertices = file.request_properties_from_element("vertex", { "x", "y", "z" }); }
		catch (const std::exception & e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

		// try { normals = file.request_properties_from_element("vertex", { "nx", "ny", "nz" }); }
		// catch (const std::exception & e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

		// try { texcoords = file.request_properties_from_element("vertex", { "u", "v" }); }
		// catch (const std::exception & e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

		// Providing a list size hint (the last argument) is a 2x performance improvement. If you have 
		// arbitrary ply files, it is best to leave this 0. 
		try { faces = file.request_properties_from_element("face", { "vertex_indices" }, 3); }
		catch (const std::exception & e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

        file.read(ss);
    }

    void ply::write_ascii(const std::string &filename)
    {

    	std::filebuf fb_ascii;
    	fb_ascii.open(filename + "-ascii.ply", std::ios::out);
    	std::ostream outstream_ascii(&fb_ascii);
    	if (outstream_ascii.fail()) throw std::runtime_error("failed to open " + filename);

    	// Write an ASCII file
        file.write(outstream_ascii, false);

    }

    void ply::write_binary(const std::string &filename)
    {
        std::filebuf fb_binary;
    	fb_binary.open(filename + "-binary.ply", std::ios::out | std::ios::binary);
        std::ostream outstream_binary(&fb_binary);
    	if (outstream_binary.fail()) throw std::runtime_error("failed to open " + filename);

    	// Write a binary file
    	file.write(outstream_binary, true);        
    }

    inline void ply::print()
    {
        std::cout << "........................................................................\n";
		for (auto c : file.get_comments()) std::cout << "Comment: " << c << std::endl;
		for (auto e : file.get_elements())
		{
			std::cout << "element - " << e.name << " (" << e.size << ")" << std::endl;
			for (auto p : e.properties) std::cout << "\tproperty - " << p.name << " (" << tinyply::PropertyTable[p.propertyType].str << ")" << std::endl;
		}
		std::cout << "........................................................................\n";

        if (vertices) std::cout << "\tRead " << vertices->count << " total vertices "<< std::endl;
		if (normals) std::cout << "\tRead " << normals->count << " total vertex normals " << std::endl;
		if (texcoords) std::cout << "\tRead " << texcoords->count << " total vertex texcoords " << std::endl;
		if (faces) std::cout << "\tRead " << faces->count << " total faces (triangles) " << std::endl;

    }
}   // namespace LLib

#endif  // _LL_PLY_H_