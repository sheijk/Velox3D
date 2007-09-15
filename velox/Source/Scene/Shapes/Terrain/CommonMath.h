#ifndef GEOMCLIPTERRAIN_COMMONMATH_H_INCLUDE
#define GEOMCLIPTERRAIN_COMMONMATH_H_INCLUDE

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
// #include <gmtl/gmtl.h>

namespace geomclip {

    //--------------------------------------------------------------------------
    class Vector3f {
    public:
        union {
            struct {
                float x, y, z;
            };
            float dim[3];
        };

        Vector3f() {}
        
        Vector3f(float ix, float iy, float iz) {
            x = ix;
            y = iy;
            z = iz;
        }
    };

    inline void setZero(Vector3f& vec) {
        vec.x = vec.y = vec.z = 0.f;
    };

    inline void set(Vector3f* vec, float x, float y, float z) {
        vec->x = x;
        vec->y = y;
        vec->z = z;
    }
    
    inline Vector3f vector3f(float x, float y, float z) {
        Vector3f vec;
        set(&vec, x, y, z);
        return vec;
    }
    
   
    inline void add(Vector3f* out, const Vector3f& l, const Vector3f& r) {
        out->x = l.x + r.x;
        out->y = l.y + r.y;
        out->z = l.z + r.z;
    }

    inline Vector3f operator+(const Vector3f& l, const Vector3f& r) {
        Vector3f result;
        add(&result, l, r);
        return result;
    }

    inline Vector3f operator+=(Vector3f& l, const Vector3f& r) {
        l = l + r;
		return l;
    }

    inline void minus(Vector3f* out, const Vector3f& l, const Vector3f& r) {
        out->x = l.x - r.x;
        out->y = l.y - r.y;
        out->z = l.z - r.z;
    }

    inline Vector3f operator-(const Vector3f& l, const Vector3f& r) {
        Vector3f result;
        minus(&result, l, r);
        return result;
    }

    inline Vector3f operator-=(Vector3f& l, const Vector3f r) {
        l = l - r;
    }

    inline float dot(const Vector3f& l, const Vector3f& r) {
        return l.x*r.x + l.y*r.y + l.z*r.z;
    }

    inline float length(const Vector3f& v) {
        return sqrt( dot(v, v) );
    }
    
    inline void cross(Vector3f* out, const Vector3f& l, const Vector3f& r) {
        out->x = l.y * r.z - l.z * r.y;
        out->y = - l.x * r.z + l.z * r.x;
        out->z = l.x * r.y - l.y * r.x;
    }

    inline Vector3f crossOf(const Vector3f& l, const Vector3f& r) {
        Vector3f result;
        cross(&result, l, r);
        return result;
    }

    inline void scale(Vector3f* io, float factor) {
        io->x *= factor;
        io->y *= factor;
        io->z *= factor;
    }

    inline Vector3f operator*(const Vector3f& l, float r) {
        Vector3f result = l;
        scale(&result, r);
        return result;
    }

    inline Vector3f operator*(float l, const Vector3f& r) {
        Vector3f result = r;
        scale(&result, l);
        return result;
    }

    inline void normalize(Vector3f* io) {
        scale( io, 1 / length(*io) );
    }

    //--------------------------------------------------------------------------
    
	class Quat {
	public:
		float x, y, z, w;
        
		Quat() {
			set(.0f, .0f, .0f, .0f);
		}

		Quat(Vector3f normalizedAxis, float angleDegrees) {
			setRotation(normalizedAxis, angleDegrees);
		}

		void setRotation(Vector3f normalizedAxis, float angleDegrees) {
			const float sinAngle = sinf(angleDegrees * float(M_PI) / 180.f);
			
			x = normalizedAxis.x * sinAngle;
			y = normalizedAxis.y * sinAngle;
			z = normalizedAxis.z * sinAngle;
			
			w = cos(angleDegrees);
			
			normalize();
		}
		
		void set(float newx, float newy, float newz, float neww) {
			x = newx;
			y = newy;
			z = newz;
			w = neww;
		}
		
		void invert() {
			x = -x;
			y = -y;
			z = -z;
		}
		
		void negate() {
			x = -x;
			y = -y;
			z = -z;
			w = -w;
		}
		
		void normalize() {
			const float length = x*x + y*y + z*z + w*w;
			
			x /= length;
			y /= length;
			z /= length;
			w /= length;
		}

		void setToConcatenation(const Quat& left, const Quat& right) {
			w = left.w * right.w - left.x * right.x - left.y * right.y - left.z * right.z;
			x = left.w * right.x + left.x * right.w + left.y * right.z - left.z * right.y;
			y = left.w * right.y + left.y * right.w + left.z * right.x - left.x * right.z;
			z = left.w * right.z + left.z * right.w + left.x * right.y - left.y * right.x;
		}
		
		void rotate(Vector3f& rot) const {
			Quat v;
			v.x = rot.x;
			v.y = rot.y;
			v.z = rot.z;
			v.w = 1.0f;
			
			Quat neg(*this);
			neg.invert();
			
			Quat res;
			res.setToConcatenation(*this, v);
			
			Quat res2;
			res2.setToConcatenation(res, neg);

			rot.x = res2.x;
			rot.y = res2.y;
			rot.z = res2.z;
		}
	};
    
    //--------------------------------------------------------------------------
    template<typename T>
    class Point {
    public:
        T x;
        T y;

        Point() {
            x = T();
            y = T();
        }

        Point(T xpos, T ypos) {
            x = xpos;
            y = ypos;
        }

		template<typename T2>
		explicit Point(Point<T2> source) {
			x = source.x;
			y = source.y;
		}

        void set(T newX, T newY) {
            x = newX;
            y = newY;
        }

		void operator+=(const Point<T>& other) {
			x += other.x;
			y += other.y;
		}

		T length() const {
			return sqrt( x*x + y*y );
		}
    };

	template<typename T>
	Point<T> operator+(const Point<T>& l, const Point<T>& r) {
		return Point<T>( l.x + r.x, l.y + r.y );
	}

	template<typename T>
	Point<T> operator-(const Point<T>& l, const Point<T>& r) {
		return Point<T>( l.x - r.x, l.y - r.y );
	}

	template<typename T>
	Point<T> operator/(const Point<T>& p, T dividor) {
		return Point<T>( p.x / dividor, p.y / dividor );
	}

	template<typename T>
	void operator*=( Point<T>& p, T scale ) {
		p.x *= scale;
		p.y *= scale;
	}

	template<typename T>
	Point<T> operator*( const Point<T>& a, T scale ) {
		Point<T> result = a;
		result *= scale;
		return result;
	}

	inline Point<float> rotate(const Point<float>& oldPos, float angle) {
		return Point<float>( 
			oldPos.x * cos(angle) + oldPos.y * sin(angle),
			- oldPos.x * sin(angle) + oldPos.y * cos(angle) );
	}

	//template<typename T>
	//T distance(const Point<T>& a, const Point<T>& b) {
	//	Point<T> d = a - b;
	//	return sqrt( d.x*d.x + d.y*d.y );
	//}

	/** assumes both intervals are of equal size */
	template<typename T>
	void cutRange(T smin, T smax, T rmin, T rmax, T* resultMin, T* resultMax) {
		if( smin > rmin ) {
			*resultMin = std::max( smin, rmax );
			*resultMax = smax;
		}
		else {
			*resultMin = smin;
			*resultMax = std::min( smax, rmin );
		}
	}

    /**
     * A single rectangle. Left/right are the min/max coords
     * on the x axis and top/bottom the min/max coords on the
     * y axis
     *
     * @invariant left <= right
     * @invariant top <= bottom
     */
    template<typename T>
    class Rect {
    public:
        T top;
        T left;
        T right;
        T bottom;

        Rect(T l, T t, T r, T b) {
            top = t;
            left = l;
            right = r;
            bottom = b;
        }

		template<typename T2>
		explicit Rect(const Rect<T2>& s) {
			top = s.top;
			left = s.left;
			bottom = s.bottom;
			right = s.right;
		}

        Rect() {
            top = T();
            left = T();
            right = T();
            bottom = T();
        }

        void set(T l, T t, T r, T b) {
            top = t;
            left = l;
            right = r;
            bottom = b;
        }

		void set(const Rect<T>& other) {
			left = other.left;
			right = other.right;
			top = other.top;
			bottom = other.bottom;
		}

        bool empty() const {
            return bottom <= top || right <= left;
        }

        bool intersects(const Rect& other) const {
            return ! intersection(other).empty();
        }

		bool contains(const Point<T>& p) const {
			return contains( p.x, p.y );
		}

		bool contains(T x, T y) const {
			return x >= left && 
				x < right &&
				y >= top &&
				y < bottom;
		}

        Rect intersection(const Rect& other) const {
            return Rect( std::max(left, other.left),
                         std::max(top, other.top),
                         std::min(right, other.right),
                         std::min(bottom, other.bottom));
        }

        T width() const { return right - left; }
        T height() const { return bottom - top; }

        void moveBy(T x, T y) {
            left += x;
            right += x;
            top += y;
            bottom += y;
        }

		void scaleBy(T h, T v) {
			left *= h;
			right *= h;
			top *= v;
			bottom *= v;
		}

		void extend(T amount) {
			left -= amount;
			right += amount;
			top -= amount;
			bottom += amount;
		}
        
        void recenterAt(T x, T y) {
            T xdiff = x - left - (width() * 0.5f);
            T ydiff = y - top - (height() * 0.5f);

            moveBy(xdiff, ydiff);
        }

        void recenterAt(const Point<T>& t) {
            recenterAt(t.x, t.y);
        }

		/** false for x.isInside(y) iff x == y */
        bool isInsideAndSmaller(const Rect<T>& other) const {
            return left >= other.left &&
                right < other.right &&
                top >= other.top &&
                bottom < other.bottom;
        }

        void makeIntersection(const Rect<T>& other) {
            left = std::max( left, other.left );
            right = std::min( right, other.right );
            top = std::max( top, other.top );
            bottom = std::min( bottom, other.bottom );
        }

		/* assumes that this and other are of equal size */
		void minus(const Rect<T>& other, Rect<T>* outA, Rect<T>* outB) const {
			GCT_ASSERT( outA != NULL );
			GCT_ASSERT( outB != NULL );

			if( other.isEmpty() ) {
				outA->set( *this );
				outB->set( 0, 0, 0, 0 );
			}
			else {
				T aleft, aright;
				cutRange( left, right, other.left, other.right, &aleft, &aright );
				T atop = top;
				T abottom = bottom;

				T bleft = std::max( left, other.left );
				T bright = std::min( right, other.right );
				T btop, bbottom;
				cutRange( top, bottom, other.top, other.bottom, &btop, &bbottom );

				outA->set( aleft, atop, aright, abottom );
				if( outA->isEmpty() )
					outA->set( 0, 0, 0, 0 );

				outB->set( bleft, btop, bright, bbottom );
				if( outB->isEmpty() )
					outB->set( 0, 0, 0, 0 );
			}
		}

		bool isEmpty() const {
			return left >= right || top >= bottom;
		}

		Point<T> topleft() { return Point<T>( left, top ); }
		Point<T> topright() { return Point<T>( right, top ); }
		Point<T> bottomleft() { return Point<T>( left, bottom ); }
		Point<T> bottomright() { return Point<T>( right, bottom ); }

        bool operator==(const Rect<T>& other) const {
            return left == other.left &&
                right == other.right &&
                top == other.top &&
                bottom == other.bottom;
        }
        
        bool operator!=(const Rect<T>& other) const {
            return left != other.left ||
                right != other.right ||
                top != other.top ||
                bottom != other.bottom;
        }
    };
    
    //--------------------------------------------------------------------------
    
    class Orientation {
    public:
        Vector3f pos;
        Vector3f viewDir;
        Vector3f upDir;

        Orientation() {
            pos = Vector3f(0.f, 0.f, 0.f);
            viewDir = Vector3f(0.f, 0.f, -1.f);
            upDir = Vector3f(0.f, 1.f, 0.f);
        }

        Orientation(float px, float py, float pz,
                    float vx, float vy, float vz,
                    float ux, float uy, float uz)
        {
            makeLookAt(px, py, pz,
                       vx, vy, vz,
                       ux, uy, uz);
        }

        Orientation(const Vector3f& inPos,
                    const Vector3f& inLookAt,
                    const Vector3f& inUpDir)
        {
            makeLookAt(inPos, inLookAt, inUpDir);
        }
        
        void makeLookAt(float px, float py, float pz,
                        float lx, float ly, float lz,
                        float ux, float uy, float uz)
        {
            makeLookAt(Vector3f(px, py, pz),
                       Vector3f(lx, ly, lz),
                       Vector3f(ux, uy, uz));
        }

        void makeLookAt(const Vector3f& inPos,
                        const Vector3f& inLookAt,
                        const Vector3f& inUpDir)
        {
            pos = inPos;
            viewDir = inLookAt - inPos;
            ::geomclip::normalize(&viewDir);
            Vector3f right;
            cross(&right, viewDir, inUpDir);
            cross(&upDir, right, viewDir);
            ::geomclip::normalize(&upDir);
        }

        void normalize() {
            ::geomclip::normalize( &viewDir ); 
            ::geomclip::normalize( &upDir ); 
        }
    };

    //--------------------------------------------------------------------------

	inline float interpolate(float t, float a, float b) {
		return (1.f - t) * a + t * b;
	}

	inline float cosineInterpolate(float t, float a, float b) {
		float t2 = (1.0f - cos(t*float(M_PI))) / 2.0f;
		return (1.f - t2) * a + t2 * b;
	}

	/** may be incorrect, hasn't been tested */
	inline float cubicInterpolate(float t, float a, float b, float c, float d) {
		const float t2 = t*t;
		const float a0 = d - c - a + b;
		const float a1 = a - b - a0;
		const float a2 = c - a;
		const float a3 = b;

		return (a0*t*t2) + (a1*t2) + (a2*t) + a3;
	}

	//--------------------------------------------------------------------------

    inline void rotate(Vector3f* io, float angle, const Vector3f& axis) {
        Vector3f normalizedAxis = axis;
        normalize(&normalizedAxis);
        
        Quat rot(normalizedAxis, angle);
        rot.rotate(*io); 
    }

    inline void rotate(Orientation* io, float angle, const Vector3f& axis) {
        Vector3f normalizedAxis = axis;
        normalize(&normalizedAxis);
        Quat rot(normalizedAxis, angle);

        rot.rotate( io->viewDir );
        rot.rotate( io->upDir );
    }
    
} // ns

#endif
