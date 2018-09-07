#ifndef _LL_BOUNDINGBOX_H_
#define _LL_BOUNDINGBOX_H_

namespace LLib
{
    template <typename T>
    class BoundingBox2
    {
    private:
        union {
            struct{
                vec2<T> minB;
                vec2<T> maxB;
            };

            struct{
                T minX, minY;
                T maxX, maxY;
            };

            T param[4];
        }; 

    public:
        BoundingBox2() {
            reset();
        }

        BoundingBox2(const std::vector<vec2<T>> &vs){
            reset();
            for(auto &v : vs)
                include(v);
        }

        BoundingBox2(const vec2<T>& minBound, const vec2<T>& maxBound) {
			reset();
			minB = minBound;
			maxB = maxBound;
		}

        void reset() {
			minX = minY = std::numeric_limits<T>::max();
			maxX = maxY = -std::numeric_limits<T>::max();
        }
        
        void include(const vec2<T> &v){
            if(v.x < minX) minX = v.x;
            if(v.y < minY) minX = v.y;

            if(v.x > maxX) maxX = v.x;
            if(v.y > maxY) maxY = v.y;
        }

        void include(const vector<vec2<T>> &vs){
            for(auto & v : vs)
                include(v);
        }

        void include(const BoundingBox2 &other) {
			if (other.minX < minX)	minX = other.minX;
			if (other.minY < minY)	minY = other.minY;

			if (other.maxX > maxX)	maxX = other.maxX;
			if (other.maxY > maxY)	maxY = other.maxY;
        }
        
        bool isInitialized() const {
			return (minX != std::numeric_limits<T>::max());
		}

		bool isValid() const {
			return (minX <= maxX && minY <= maxY);
        }
        
        void getVertices(vec2<T> *result) const {
			result[0] = vec2<T>(minX, minY);
			result[1] = vec2<T>(maxX, minY);
			result[2] = vec2<T>(maxX, maxY);
			result[3] = vec2<T>(minX, maxY);
        }
        
        std::vector< vec2<T> > getVertices() const {
			std::vector< vec2<T> > result;
			result.resize(4);

			getVertices(result.data());

			return result;
        }

        std::vector< LineSegment2<T> > getEdges() const
		{
			std::vector< LineSegment2<T> > result;

			auto v = getVertices();

			result.push_back(LineSegment2<T>(v[0], v[1]));
			result.push_back(LineSegment2<T>(v[1], v[2]));
			result.push_back(LineSegment2<T>(v[2], v[3]));
			result.push_back(LineSegment2<T>(v[3], v[0]));

            // TODO : wrong ?
			// result.push_back(LineSegment2<T>(v[4], v[5]));
			// result.push_back(LineSegment2<T>(v[5], v[6]));
			// result.push_back(LineSegment2<T>(v[6], v[7]));
			// result.push_back(LineSegment2<T>(v[7], v[4]));

			// result.push_back(LineSegment2<T>(v[0], v[4]));
			// result.push_back(LineSegment2<T>(v[1], v[5]));
			// result.push_back(LineSegment2<T>(v[2], v[6]));
			// result.push_back(LineSegment2<T>(v[3], v[7]));

			return result;
        }
        
        //! point collision
		bool intersects(const vec2<T>& p) const {
			if (p.x >= minX && p.x <= maxX &&
				p.y >= minY && p.y <= maxY) return true;
			else  return false;
        }
        

        //! bounding box collision
		bool intersects(const BoundingBox2<T>& other) const {
			return 
				minX <= other.maxX && other.minX <= maxX &&
				minY <= other.maxY && other.minY <= maxY;
        }

        // TODO
        // //! triangle collision
		// bool intersects(const vec2<T>& p0, const vec2<T>& p1, const vec2<T>& p2) const {
		// 	return intersection::intersectTriangleAABB(minB, maxB, p0, p1, p2);
		// }
        
        void setMinX(T v) { minX = v; }
		void setMinY(T v) { minY = v; }
		void setMaxX(T v) { maxX = v; }
		void setMaxY(T v) { maxY = v; }

		T getMinX() const { return minX; }
		T getMinY() const { return minY; }
		T getMaxX() const { return maxX; }
        T getMaxY() const { return maxY; }
        
        T getMaxExtent() const {
			T d0 = maxX - minX;
			T d1 = maxY - minY;
			return std::max(d0,d1);
		}

		T getExtentX() const {
			return maxX - minX;
		}

		T getExtentY() const {
			return maxY - minY;
		}

		vec2<T> getExtent() const {
			return vec2<T>(maxX - minX, maxY - minY);
		}

		vec2<T> getMin() const {
			return vec2<T>(minX, minY);
		}

		vec2<T> getMax() const {
			return vec2<T>(maxX, maxY);
		}

		vec2<T> getCenter() const {
			vec2<T> center = getMin() + getMax();
			center *= (T)0.5;
			return center;
		}

		void setMin(const vec2<T>& minValue) {
			minX = minValue.x;
			minY = minValue.y;
		}

		void setMax(const vec2<T>& maxValue) {
			maxX = maxValue.x;
			maxY = maxValue.y;
        }

    	void scale(T x, T y, T z){
		vec3<T> s(x, y, z);

		for(size_t i = 0; i < 2; i++){
			T center = 0.5*(parameters[i] + parameters[i+2]);
			T diff = parameters[i+2] - parameters[i];
			diff *= s[i] * 0.5;
			parameters[i] = center - diff;
			parameters[i+2] = center + diff;
            }
        }

        void scale(const vec3<T> &s){
            for(size_t i = 0; i < 3; i++){
                T center = 0.5*(parameters[i] + parameters[i+2]);
                T diff = parameters[i+2] - parameters[i];
                diff *= s[i] * 0.5;
                parameters[i] = center - diff;
                parameters[i+2] = center + diff;
            }
        }

        void scale (T s){
            for(size_t i = 0; i < 2; i++){
                T center = 0.5*(parameters[i] + parameters[i+2]);
                T diff = parameters[i+2] - parameters[i];
                diff *= s * 0.5;
                parameters[i] = center - diff;
                parameters[i+2] = center + diff;
            }
        }

        BoundingBox2<T> operator*(T s){
            BoundingBox2<T> bb2 = *this;
            bb2.scale(s);
            return bb2;
        }

        BoundingBox2<T> operator*(const vec2<T> &s){
            BoundingBox2<T> bb2 = *this;
            bb2.scale(s);
            return bb2;
        }

        // TODO
        // //! transforms the bounding box (conservatively)
		// void transform(const Matrix2x2<FloatType>& m) {
		// 	vec2<FloatType> verts[8];
		// 	getVertices(verts);
		// 	reset();
		// 	for (const auto& p : verts) {
		// 		include(m * p);
		// 	}
		// }

		// void translate(const vec2<FloatType>& t) {
		// 	minB += t;
		// 	maxB += t;
		// }

        
		// //! transforms the bounding box (see transform)
		// BoundingBox2<FloatType> operator*(const Matrix2x2<FloatType>& m) const {
		// 	BoundingBox2<FloatType> res = *this;
		// 	res.transform(m);
		// 	return res;
		// }
        

        void setUnitCube() {
            minX = minY = 0;
            maxX = maxY = 1;
        }

        BoundingBox2<T>& operator = (const BoundingBox2<T> &b) {
            for (int i = 0; i < 4; i++)
                parameters[i] = b.parameters[i];
            return *this;
        }

        friend std::ostream& operator<< (std::ostream& s, const BoundingBox2<T>& bb) {
            s << bb.getMin() << std::endl << bb.getMax() << std::endl;
            return s;
        }

    };  // class BoundingBox2

    typedef BoundingBox2<float> BoundingBox2f;
    typedef BoundingBox2<double> BoundingBox2d;
    typedef BoundingBox2<int> BoundingBox2i;

    typedef BoundingBox2<float> BBox2f;
    typedef BoundingBox2<double> BBox2d;
    typedef BoundingBox2<int> BBox2i;

}  // namespace LLib

#endif  // _LL_BOUNDINGBOX_H_

// TODO include -> extend