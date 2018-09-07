#ifndef _LL_BOUNDINGBOX_H_
#define _LL_BOUNDINGBOX_H_

namespace LLib
{
    template <typename T>
    class BoundingBox3
    {
    private:
        union {
            struct {
                vec3<T> minB;
                vec3<T> maxB;
            };
            struct {
                T minX, minY, minZ;
                T maxX, maxY, maxZ;
            };
            T parameters[6];
        };

    public:

        BoundingBox3() {
            reset();
        }
    
        BoundingBox3(const BoundingBox3 &other) : minB(other.minB), maxB(other.maxB) {}
    
        explicit BoundingBox3(const std::vector<vec3<T>> &vs) {
            reset();
            for (const auto &v : vs)
                include(v);
        }
    
        BoundingBox3(const vec3<T> &minBound, const vec3<T> &maxBound) {
            reset();
            minB = minBound;
            maxB = maxBound;
        }
    
        explicit BoundingBox3(const OrientedBoundingBox3<T> &obb) {
            reset();
            std::vector<vec3<T>> vertices = obb.getVertices();
            for (const auto &v : vertices)
                include(v);
        }

    	void reset() {
            minX = minY = minZ = std::numeric_limits<T>::max();
            maxX = maxY = maxZ = -std::numeric_limits<T>::max();
        }

        void include(const vec3<T> &v) {
            if (v.x < minX)	minX = v.x;
            if (v.y < minY)	minY = v.y;
            if (v.z < minZ)	minZ = v.z;
    
            if (v.x > maxX)	maxX = v.x;
            if (v.y > maxY)	maxY = v.y;
            if (v.z > maxZ)	maxZ = v.z;
        }
    
        void include(const std::vector<vec3<T>> &v) {
            for (const auto &p : v)
                include(p);
        }

        void include(const BoundingBox3 &other) {
            if (other.minX < minX)	minX = other.minX;
            if (other.minY < minY)	minY = other.minY;
            if (other.minZ < minZ)	minZ = other.minZ;
    
            if (other.maxX > maxX)	maxX = other.maxX;
            if (other.maxY > maxY)	maxY = other.maxY;
            if (other.maxZ > maxZ)	maxZ = other.maxZ;
        }

        bool isInitialized() const {
            return (minX != std::numeric_limits<T>::max());
        }
        bool isValid() const {
            return (minX <= maxX && minY <= maxY && minZ <= maxZ);
        }

        void getVertices(vec3<T> *result) const {
            result[0] = vec3<T>(minX, minY, minZ);
            result[1] = vec3<T>(maxX, minY, minZ);
            result[2] = vec3<T>(maxX, maxY, minZ);
            result[3] = vec3<T>(minX, maxY, minZ);
            result[4] = vec3<T>(minX, minY, maxZ);
            result[5] = vec3<T>(maxX, minY, maxZ);
            result[6] = vec3<T>(maxX, maxY, maxZ);
            result[7] = vec3<T>(minX, maxY, maxZ);
        }
    
        std::vector< vec3<T> > getVertices() const {
            std::vector< vec3<T> > result;
            result.resize(8);
    
            getVertices(result.data());
    
            return result;
        }

        std::vector<LineSegment3<T>> getEdges() const
        {
            std::vector<LineSegment3<T>> result;
    
            auto v = getVertices();
    
            result.push_back(LineSegment3<T>(v[0], v[1]));
            result.push_back(LineSegment3<T>(v[1], v[2]));
            result.push_back(LineSegment3<T>(v[2], v[3]));
            result.push_back(LineSegment3<T>(v[3], v[0]));
    
            result.push_back(LineSegment3<T>(v[4], v[5]));
            result.push_back(LineSegment3<T>(v[5], v[6]));
            result.push_back(LineSegment3<T>(v[6], v[7]));
            result.push_back(LineSegment3<T>(v[7], v[4]));
    
            result.push_back(LineSegment3<T>(v[0], v[4]));
            result.push_back(LineSegment3<T>(v[1], v[5]));
            result.push_back(LineSegment3<T>(v[2], v[6]));
            result.push_back(LineSegment3<T>(v[3], v[7]));
    
            return result;
        }

        	//! point collision
	bool intersects(const vec3<T> &p) const {
        if (p.x >= minX && p.x <= maxX &&
            p.y >= minY && p.y <= maxY &&
            p.z >= minZ && p.z <= maxZ)
            return true;
		return false;
    }
    
    	//! bounding box collision
	bool intersects(const BoundingBox3<T>& other) const {
		return 
			minX <= other.maxX && other.minX <= maxX &&
			minY <= other.maxY && other.minY <= maxY &&
			minZ <= other.maxZ && other.minZ <= maxZ;
	}

	// TODO
    //! triangle collision
	// bool intersects(const vec3<T>& p0, const vec3<T>& p1, const vec3<T>& p2) const {
	// 	return intersection::intersectTriangleAABB(minB, maxB, p0, p1, p2);
    // }
    
	// TODO
	// bool intersect(const Ray<T> &r, T tmin, T tmax) const
	// {
	// 	//TODO move to intersection

	// 	//const T t0 = 0.0;
	// 	//const T t1 = r.t;

	// 	const T t0 = tmin;
	// 	const T t1 = tmax;

	// 	T txmin, txmax, tymin, tymax, tzmin, tzmax;

    //     auto sign = r.getSign();
    //     auto origin = r.getOrigin();
    //     auto invDir = r.getInverseDirection();

    //     txmin = (parameters[sign.x * 3] - origin.x) * invDir.x;
    //     txmax = (parameters[3 - sign.x * 3] - origin.x) * invDir.x;
    //     tymin = (parameters[sign.y * 3 + 1] - origin.y) * invDir.y;
    //     tymax = (parameters[3 - sign.y * 3 + 1] - origin.y) * invDir.y;

	// 	if ( (txmin > tymax) || (tymin > txmax) ) return false;

	// 	if (tymin > txmin)	txmin = tymin;
	// 	if (tymax < txmax)	txmax = tymax;

    //     tzmin = (parameters[sign.z * 3 + 2] - origin.z) * invDir.z;
    //     tzmax = (parameters[3 - sign.z * 3 + 2] - origin.z) * invDir.z;

	// 	if ( (txmin > tzmax) || (tzmin > txmax) ) 
	// 		return false;
	// 	if (tzmin > txmin)
	// 		txmin = tzmin;
	// 	if (tzmax < txmax)
	// 		txmax = tzmax;
	// 	return ( (txmin <= t1) && (txmax >= t0) );

	// }
    
    T getMaxExtent() const {
		T d0 = maxX - minX;
		T d1 = maxY - minY;
		T d2 = maxZ - minZ;
		return math::max(d0, d1, d2);
	}

	T getExtentX() const {
		return maxX - minX;
	}

	T getExtentY() const {
		return maxY - minY;
	}

	T getExtentZ() const {
		return maxZ - minZ;
	}

	vec3<T> getExtent() const {
		return vec3<T>(maxX - minX, maxY - minY, maxZ - minZ);
	}

	vec3<T> getMin() const {
		return vec3<T>(minX, minY, minZ);
	}

	vec3<T> getMax() const {
		return vec3<T>(maxX, maxY, maxZ);
	}

	vec3<T> getCenter() const {
		vec3<T> center = getMin() + getMax();
		center *= (T)0.5;
		return center;
	}

	void setMin(const vec3<T>& minValue) {
		minX = minValue.x;
		minY = minValue.y;
		minZ = minValue.z;
	}

	void setMax(const vec3<T>& maxValue) {
		maxX = maxValue.x;
		maxY = maxValue.y;
		maxZ = maxValue.z;
	}

	void setMinX(T v) { minX = v; }
	void setMinY(T v) { minY = v; }
	void setMinZ(T v) { minZ = v; }
	void setMaxX(T v) { maxX = v; }
	void setMaxY(T v) { maxY = v; }
	void setMaxZ(T v) { maxZ = v; }

	T getMinX() const { return minX; }
	T getMinY() const { return minY; }
	T getMinZ() const { return minZ; }
	T getMaxX() const { return maxX; }
	T getMaxY() const { return maxY; }
	T getMaxZ() const { return maxZ; }
	
	void scale(T x, T y, T z){
		vec3<T> s(x, y, z);

		for(size_t i = 0; i < 3; i++){
			T center = 0.5*(parameters[i] + parameters[i+3]);
			T diff = parameters[i+3] - parameters[i];
			diff *= s[i] * 0.5;
			parameters[i] = center - diff;
			parameters[i+3] = center + diff;
		}
	}

	void scale(const vec3<T> &s){
		for(size_t i = 0; i < 3; i++){
			T center = 0.5*(parameters[i] + parameters[i+3]);
			T diff = parameters[i+3] - parameters[i];
			diff *= s[i] * 0.5;
			parameters[i] = center - diff;
			parameters[i+3] = center + diff;
		}
	}

	void scale (T s){
		for(size_t i = 0; i < 3; i++){
			T center = 0.5*(parameters[i] + parameters[i+3]);
			T diff = parameters[i+3] - parameters[i];
			diff *= s * 0.5;
			parameters[i] = center - diff;
			parameters[i+3] = center + diff;
		}
	}

	BoundingBox3<T> operator*(T s){
		BoundingBox3<T> bb3 = *this;
		bb3.scale(s);
		return bb3;
	}

	BoundingBox3<T> operator*(const vec3<T> &s){
		BoundingBox3<T> bb3 = *this;
		bb3.scale(s);
		return bb3;
	}

	// TODO : transform, rotation, translate
	// void transform(const Matrix4x4<T>& m) {
    //     vec3<T> verts[8];
	// 	getVertices(verts);
	// 	reset();
	// 	for (const auto& p : verts) {
	// 		include(m.transformAffine(p));
	// 	}
	// }

	// void translate(const vec3<T>& t) {
	// 	minB += t;
	// 	maxB += t;
	// }

	
	// //! transforms the bounding box (see transform)
	// BoundingBox3<T> operator*(const Matrix4x4<T>& m) const {
	// 	BoundingBox3<T> res = *this;
	// 	res.transform(m);
	// 	return res;
	// }

	Plane<T> getTopPlane() const {
		vec3<T> p0 = vec3<T>(minX, minY, maxZ);
		vec3<T> p1 = vec3<T>(minX, maxY, maxZ);
		vec3<T> p2 = vec3<T>(maxX, minY, maxZ);
		return Plane<T>(p0, p1, p2);
	}


	Plane<T> getBottomPlane() const {
		vec3<T> p0 = vec3<T>(minX, minY, minZ);
		vec3<T> p1 = vec3<T>(minX, maxY, minZ);
		vec3<T> p2 = vec3<T>(maxX, minY, minZ);
		return Plane<T>(p0, p1, p2);
	}

	void setUnitCube(){
		minX = minY = minZ = 0;
		maxX = maxY = maxZ = 1;
	}

	
	//! generates vertices, indices, and normals which can be used to initialize a triMesh
	void makeTriMesh(vec3<T>* vertices, vec3ui* indices, vec3<T>* normals) const {

		//bottom
		vertices[0] = vec3<T>(minX, minY, minZ);
		vertices[1] = vec3<T>(maxX, minY, minZ);
		vertices[2] = vec3<T>(maxX, maxY, minZ);
		vertices[3] = vec3<T>(minX, maxY, minZ);
		indices[0].x = 0;	indices[0].y = 1;	indices[0].z = 2;
		indices[1].x = 2;	indices[1].y = 3;	indices[1].z = 0;
		normals[0] = normals[1] = normals[2] = normals[3] = vec3<T>(0,0,-1);
		//front
		vertices[4] = vec3<T>(minX, minY, minZ);
		vertices[5] = vec3<T>(maxX, minY, minZ);
		vertices[6] = vec3<T>(maxX, minY, maxZ);
		vertices[7] = vec3<T>(minX, minY, maxZ);
		indices[2].x = 4;	indices[2].y = 5;	indices[2].z = 6;
		indices[3].x = 6;	indices[3].y = 7;	indices[3].z = 4;
		normals[4] = normals[5] = normals[6] = normals[7] = vec3<T>(0,-1,0);
		//left
		vertices[8] = vec3<T>(minX, minY, minZ);
		vertices[9] = vec3<T>(minX, minY, maxZ);
		vertices[10] = vec3<T>(minX, maxY, maxZ);
		vertices[11] = vec3<T>(minX, maxY, minZ);
		indices[4].x = 8;	indices[4].y = 9;	indices[4].z = 10;
		indices[5].x = 10;	indices[5].y = 11;	indices[5].z = 8;
		normals[8] = normals[9] = normals[10] = normals[11] = vec3<T>(-1,0,0);
		//right
		vertices[12] = vec3<T>(maxX, minY, minZ);
		vertices[13] = vec3<T>(maxX, minY, maxZ);
		vertices[14] = vec3<T>(maxX, maxY, maxZ);
		vertices[15] = vec3<T>(maxX, maxY, minZ);
		indices[6].x = 12;	indices[6].y = 13;	indices[6].z = 14;
		indices[7].x = 14;	indices[7].y = 15;	indices[7].z = 12;
		normals[12] = normals[13] = normals[14] = normals[15] = vec3<T>(1,0,0);
		//back
		vertices[16] = vec3<T>(minX, maxY, minZ);
		vertices[17] = vec3<T>(maxX, maxY, minZ);
		vertices[18] = vec3<T>(maxX, maxY, maxZ);
		vertices[19] = vec3<T>(minX, maxY, maxZ);
		indices[8].x = 16;	indices[8].y = 17;	indices[8].z = 18;
		indices[9].x = 18;	indices[9].y = 19;	indices[9].z = 16;
		normals[16] = normals[17] = normals[18] = normals[19] = vec3<T>(0,1,0);
		//top
		vertices[20] = vec3<T>(minX, minY, maxZ);
		vertices[21] = vec3<T>(maxX, minY, maxZ);
		vertices[22] = vec3<T>(maxX, maxY, maxZ);
		vertices[23] = vec3<T>(minX, maxY, maxZ);
		indices[10].x = 20;	indices[10].y = 21;	indices[10].z = 22;
		indices[11].x = 22;	indices[11].y = 23;	indices[11].z = 20;
		normals[20] = normals[21] = normals[22] = normals[23] = vec3<T>(0,0,1);
	}

	//! generates vertices, indices, and normals which can be used to initialize a triMesh
	void makeTriMesh(std::vector<vec3<T>>& vertices, std::vector<vec3ui>& indices, std::vector<vec3<T>>& normals) const {
		//TODO check face and normal orientation
		vertices.resize(24);
		normals.resize(24);
		indices.resize(12);

    makeTriMesh(vertices.data(), indices.data(), normals.data());
	}

	void makeTriMesh(vec3<T>* vertices, vec3ui* indices) const {
		vertices[0] = vec3<T>(maxX, maxY, maxZ);
		vertices[1] = vec3<T>(minX, maxY, maxZ);
		vertices[2] = vec3<T>(minX, minY, maxZ);
		vertices[3] = vec3<T>(maxX, minY, maxZ);
		vertices[4] = vec3<T>(maxX, maxY, minZ);
		vertices[5] = vec3<T>(minX, maxY, minZ);
		vertices[6] = vec3<T>(minX, minY, minZ);
		vertices[7] = vec3<T>(maxX, minY, minZ);

		indices[0].x = 1;	indices[0].y = 2;	indices[0].z = 3; 
		indices[1].x = 1;	indices[1].y = 3;	indices[1].z = 0; 
		indices[2].x = 0;	indices[2].y = 3;	indices[2].z = 7; 
		indices[3].x = 0;	indices[3].y = 7;	indices[3].z = 4; 
		indices[4].x = 3;	indices[4].y = 2;	indices[4].z = 6; 
		indices[5].x = 3;	indices[5].y = 6;	indices[5].z = 7; 
		indices[6].x = 1;	indices[6].y = 6;	indices[6].z = 2; 
		indices[7].x = 1;	indices[7].y = 5;	indices[7].z = 6; 
		indices[8].x = 0;	indices[8].y = 5;	indices[8].z = 1; 
		indices[9].x = 0;	indices[9].y = 4;	indices[9].z = 5; 
		indices[10].x = 6;	indices[10].y = 5;	indices[10].z = 4; 
		indices[11].x = 6;	indices[11].y = 4;	indices[11].z = 7; 
	}

	//! generates vertices, indices which can be used to initialize a triMesh
	void makeTriMesh(std::vector<vec3<T>>& vertices, std::vector<vec3ui>& indices) const {
		//TODO check face and normal orientation
		vertices.resize(8);
		indices.resize(12);
		makeTriMesh(vertices.data(), indices.data());
	}

	// TODO
	// 	//! transforms a point in [-1;1]^3 to the bounding box space
    // Matrix4x4<T> cubeToWorldTransform() const {
    //     return  Matrix4x4<T>::translation(getCenter()) *  Matrix4x4<T>::scale((maxB - minB) * (T)0.5);
    // }
	
	// //! transforms a point from bounding box space to [-1;1]^3
	// Matrix4x4<T> worldToCubeTransform() const {
	// 	return cubeToWorldTransform().getInverse();	//TODO avoid the inverse
	// }

	BoundingBox3<T> &operator=(const BoundingBox3<T> &other){
		if(this != &other){
			this->minB = other.minB;
			this->maxB = other.maxB;
		}
	}

	friend std::ostream &operator<<(std::ostream &out, const BoundingBox3<T> &bb3){
		s << bb3.getMin() << ", " << bb3.getMax() << std::endl;
		return s;
	}
 
    };  // class BoundingBox3

    typedef BoundingBox3<float> BoundingBox3f;
    typedef BoundingBox3<double> BoundingBox3d;
    typedef BoundingBox3<int> BoundingBox3i;

    typedef BoundingBox3<float> BBox3f;
    typedef BoundingBox3<double> BBox3d;
    typedef BoundingBox3<int> BBox3i;

}  // LLib

#endif  // _LL_BOUNDINGBOX_H_


// TODO include -> extend