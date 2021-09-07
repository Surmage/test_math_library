#pragma once
#include <iostream>

namespace Math
{
	class vec3 {
	public:
		float x;
		float y;
		float z;

		vec3() {
			x = 0;
			y = 0;
			z = 0;
		}
		vec3(float const nx, float const ny, float const nz) {
			x = nx;
			y = ny;
			z = nz;
		}
		vec3(vec3 const& v) { //copy constructor
			x = v.x;
			y = v.y;
			z = v.z;
		}

		void operator=(vec3 const& rhs) {
			this->x = rhs.x;
			this->y = rhs.y;
			this->z = rhs.z;
		}
		vec3 operator-() {
			vec3 newVec(-x, -y, -z);
			return newVec;
		}
		vec3 operator+(vec3 const& rhs) {
			vec3 newVec(x + rhs.x, y + rhs.y, z + rhs.z);
			return newVec;
		}
		void operator+=(vec3 const& rhs) {
			this->x += rhs.x;
			this->y += rhs.y;
			this->z += rhs.z;
		}
		vec3 operator-(vec3 const& rhs) {
			vec3 newVec(x - rhs.x, y - rhs.y, z - rhs.z);
			return newVec;
		}
		const vec3 operator-(vec3 const& rhs)const {
			vec3 newVec(x - rhs.x, y - rhs.y, z - rhs.z);
			return newVec;
		}
		void operator-=(vec3 const& rhs) {
			this->x -= rhs.x;
			this->y -= rhs.y;
			this->z -= rhs.z;
		}
		void operator*=(float const scalar) {
			this->x *= scalar;
			this->y *= scalar;
			this->z *= scalar;
		}
		vec3 operator*(float const scalar) {
			vec3 newVec(x * scalar, y * scalar, z * scalar);
			return newVec;
		}
		bool operator==(vec3 const& rhs) {
			return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z;
		}
		bool operator!=(vec3 const& rhs) {
			if ((x != rhs.x) || (y != rhs.y) || (z != rhs.z))
				return true;
			else
				return false;
		}
		float& operator[](unsigned int const i) {
			if (i > 2 || i < 0)
				std::cerr << "Error\n";
			else {
				if (i == 0) {
					return x;
				}
				else if (i == 1) {
					return y;
				}
				else if (i == 2) {
					return z;
				}
			}
			float invalid = -1;
			return invalid;
		}


		float setElement(unsigned int const i, float const value) {
			if (i > 2) {
				std::cerr << "Error\n";
				return -1;
			}

			if (i == 0)
				x = value;
			else if (i == 1)
				y = value;
			else if (i == 2)
				z = value;
			return 0;
		}
		float getElement(unsigned int const i)const {
			if (i > 2) {
				std::cerr << "Error\n";
				return -1;
			}

			if (i == 0)
				return x;
			else if (i == 1)
				return y;
			else if (i == 2)
				return z;
			return 0;
		}
	};

	float dot(vec3 const& a, vec3 const& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}
	float length(vec3 const& v) {
		return sqrt(powf(v.x, 2) + powf(v.y, 2) + powf(v.z, 2));
	}
	vec3 cross(vec3 const& a, vec3 const& b) {
		vec3 crossVec;
		crossVec.x = a.y * b.z - a.z * a.y;
		crossVec.y = -(a.x * b.z - a.z * b.x);
		crossVec.z = a.x * b.y - a.y * b.x;
		return crossVec;
	}
	vec3 normalize(vec3 const& v) { //convert to unit vector
		float vecLen = length(v);
		vec3 newVec;
		newVec.x = v.x / vecLen;
		newVec.y = v.y / vecLen;
		newVec.z = v.z / vecLen;
		return newVec;
	}

}



