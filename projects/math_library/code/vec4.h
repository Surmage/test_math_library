#pragma once
#include <iostream>
#include <assert.h>

namespace Math
{
	class vec4 {
	public:
		float x;
		float y;
		float z;
		float w;

		vec4() {
			x = 0;
			y = 0;
			z = 0;
			w = 0;
		}
		vec4(float const nx, float const ny, float const  nz, float const  nw) {
			x = nx;
			y = ny;
			z = nz;
			w = nw;
		}
		vec4(vec4 const& v) {
			x = v.x;
			y = v.y;
			z = v.z;
			w = v.w;
		}

		void operator=(vec4 const& rhs) {
			this->x = rhs.x;
			this->y = rhs.y;
			this->z = rhs.z;
			this->w = rhs.w;
		}
		vec4 operator-() {
			vec4 newVec(-x, -y, -z, -w);
			return newVec;
		}
		vec4 operator+(vec4 const& v) {
			vec4 newVec(x + v.x, y + v.y, z + v.z, w + v.w);
			return newVec;
		}
		void operator+=(vec4 const& rhs) {
			this->x += rhs.x;
			this->y += rhs.y;
			this->z += rhs.z;
			this->w += rhs.w;
		}
		vec4 operator-(vec4 const& rhs) {
			vec4 newVec(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
			return newVec;
		}
		void operator-=(vec4 const& rhs) {
			this->x -= rhs.x;
			this->y -= rhs.y;
			this->z -= rhs.z;
			this->w -= rhs.w;
		}
		void operator*=(float const scalar) {
			this->x *= scalar;
			this->y *= scalar;
			this->z *= scalar;
			this->w *= scalar;
		}
		vec4 operator*(float const scalar) {
			vec4 newVec(x * scalar, y * scalar, z * scalar, w * scalar);
			return newVec;
		}
		bool operator==(vec4 const& rhs) {
			return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z && this->w == rhs.w;
		}

		bool operator!=(vec4 const& rhs) {
			if ((x != rhs.x) || (y != rhs.y) || (z != rhs.z) || (w != rhs.w))
				return true;
			else
				return false;
		}
		float& operator[](unsigned int const i) {
			assert(i >= 0 && i <= 3);
			switch (i) {
			case 1: return y;
			case 2: return z;
			case 3: return w;
			case 0:
			default: return x;
			}
		}
		const float operator[](unsigned int const i) const {
			assert(i >= 0 && i <= 3);
			switch (i) {
			case 1: return y;
			case 2: return z;
			case 3: return w;
			case 0:
			default: return x;
			}
		}


		float setElement(unsigned int const i, float const value) {
			if (i > 3) {
				std::cerr << "Error\n";
				return -1;
			}

			if (i == 0)
				this->x = value;
			else if (i == 1)
				this->y = value;
			else if (i == 2)
				this->z = value;
			else if (i == 3)
				this->w = value;
			return 0;
		}
		float getElement(unsigned int const i)const {
			if (i > 3) {
				std::cerr << "Error\n";
				return -1;
			}

			if (i == 0)
				return x;
			else if (i == 1)
				return y;
			else if (i == 2)
				return z;
			else if (i == 3)
				return w;
			return 0;
		}
		void printVec4()const {
			std::cout << x << ", " << y << ", " << z << ", " << w << "\n";
		}
	};

	float dot(vec4 const& a, vec4 const& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}
	float length(vec4 const& v) {
		return sqrt(powf(v.x, 2) + powf(v.y, 2) + powf(v.z, 2) + powf(v.w, 2));
	}
	vec4 normalize(vec4 const& v) { //convert to unit vector
		float vecLen = length(v);
		vec4 newVec;
		newVec.x = v.x / vecLen;
		newVec.y = v.y / vecLen;
		newVec.z = v.z / vecLen;
		newVec.w = v.w;
		return newVec;
	}
}
