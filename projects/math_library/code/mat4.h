#define _USE_MATH_DEFINES
#pragma once
#include <iostream>
#include "vec4.h"
#include "vec3.h"
#include <array>
#include <assert.h>
#include <math.h>

namespace Math
{
	class mat4 {
	public:
		std::array<vec4, 4> matrix;
		mat4()
			:matrix({ vec4{1, 0, 0, 0}, vec4{0, 1, 0, 0}, vec4{0, 0, 1, 0}, vec4{0, 0, 0, 1 } })
		{
		}
		mat4( vec4 const& r0, vec4 const& r1, vec4 const& r2, vec4 const& r3)
			:matrix({ r0, r1, r2, r3 })
		{
		}
		mat4( mat4 const& m)
		{
			for (unsigned int i = 0; i < 4; i++) {
				vec4 temp{ m.matrix[i].x, m.matrix[i].y, m.matrix[i].z, m.matrix[i].w };
				matrix[i] = temp;
			}
		}

		mat4 operator=(mat4 const& rhs) {
			for (int i = 0; i < 4; i++) {
				matrix[i].x = rhs.matrix[i].x;
				matrix[i].y = rhs.matrix[i].y;
				matrix[i].z = rhs.matrix[i].z;
				matrix[i].w = rhs.matrix[i].w;
			}
			return *this;
		}

		mat4 operator*(mat4 const& rhs)const {
			mat4 temp;
			for (int i = 0; i < 4; i++) {
				vec4 transpose;
				for (int j = 0; j < 4; j++) {
					vec4 tempVec = rhs.matrix[j];
					transpose.setElement(j, tempVec[i]);
				}
				for (int k = 0; k < 4; k++) {
					temp[k].setElement(i, dot(matrix[k], transpose));
				}
			}
			return temp;
		}
		vec4 operator*(vec4 const& rhs)const {
			vec4 temp;
			temp.x = matrix[0].x * rhs.x + matrix[1].x * rhs.y + matrix[2].x * rhs.z + matrix[3].x * rhs.w;
			temp.y = matrix[0].y * rhs.x + matrix[1].y * rhs.y + matrix[2].y * rhs.z + matrix[3].y * rhs.w;
			temp.z = matrix[0].z * rhs.x + matrix[1].z * rhs.y + matrix[2].z * rhs.z + matrix[3].z * rhs.w;
			temp.w = matrix[0].w * rhs.x + matrix[1].w * rhs.y + matrix[2].w * rhs.z + matrix[3].w * rhs.w;
			return temp;
		}
		bool operator==(mat4 const& rhs) {
			if (matrix[0] == rhs.matrix[0] && matrix[1] == rhs.matrix[1] && matrix[2] == rhs.matrix[2] && matrix[3] == rhs.matrix[3])
				return true;
			else
				return false;
		}
		bool operator!=(mat4 const& rhs) {
			if (matrix[0] != rhs.matrix[0] || matrix[1] != rhs.matrix[1] || matrix[2] != rhs.matrix[2] || matrix[3] != rhs.matrix[3])
				return true;
			else
				return false;
		}
		vec4& operator[](int const i) {
			if (i > 3) {
				std::cerr << "Error\n";
				return matrix[0];		
			}		
			else
				return matrix[i];
		}
		const vec4& operator[](int const i) const {
			if (i > 3) {
				std::cerr << "Error\n";
				return matrix[0];
			}
			else
				return matrix[i];
		}

	};

	mat4 rotationx(float const rad) {
		mat4 temp;

		temp[0][0] = 1;
		temp[1][1] = cos(rad);
		temp[1][2] = sin(rad);
		temp[2][1] = -sin(rad);
		temp[2][2] = cos(rad);
		temp[3][3] = 1;

		return temp;
	}
	mat4 rotationy(float const rad) {
		mat4 temp;

		temp[0][0] = cos(rad);
		temp[0][2] = -sin(rad);
		temp[1][1] = 1;
		temp[2][0] = sin(rad);
		temp[2][2] = cos(rad);
		temp[3][3] = 1;

		return temp;
	}
	mat4 rotationz(float const rad) {
		mat4 temp;

		temp[0][0] = cos(rad);
		temp[0][1] = sin(rad);
		temp[1][0] = -sin(rad);
		temp[1][1] = cos(rad);
		temp[2][2] = 1;
		temp[3][3] = 1;

		return temp;
	}

	mat4 rotationaxis(vec3 const v, float const rad) {
		vec3 normalizeAxis = normalize(v);

		float normAxisX = normalizeAxis[0];
		float normAxisY = normalizeAxis[1];
		float normAxisZ = normalizeAxis[2];

		vec4 column1((powf(normAxisX, 2) + ((powf(normAxisY, 2) + powf(normAxisZ, 2)) * cos(rad))),
			(normAxisX * normAxisY * (1 - cos(rad)) + normAxisZ * sin(rad)),
			(normAxisX * normAxisZ * (1 - cos(rad)) - normAxisY * sin(rad)), 0);

		vec4 column2((normAxisX * normAxisY * (1 - cos(rad)) - normAxisZ * sin(rad)),
			(powf(normAxisY, 2) + ((powf(normAxisX, 2) + powf(normAxisZ, 2)) * cos(rad))),
			(normAxisY * normAxisZ * (1 - cos(rad)) + normAxisX * sin(rad)), 0);

		vec4 column3((normAxisX * normAxisZ * (1 - cos(rad)) + normAxisY * sin(rad)),
			((normAxisY * normAxisZ) * (1 - cos(rad)) - normAxisX * sin(rad)),
			(powf(normAxisZ, 2) + ((powf(normAxisX, 2) + powf(normAxisY, 2)) * cos(rad))), 0);

		vec4 column4(
			((v.x * (powf(normAxisY, 2) + powf(normAxisZ, 2)) - normAxisX * (v.y * normAxisY + v.z * normAxisZ))
				* (1 - cos(rad) + (v.y * normAxisZ - v.z * normAxisY) * sin(rad))),

			((v.y * (powf(normAxisX, 2) + powf(normAxisZ, 2)) - normAxisY * (v.x * normAxisX + v.z * normAxisZ))
				* (1 - cos(rad) + (v.z * normAxisX - v.x * normAxisZ) * sin(rad))),

			((v.z * (powf(normAxisX, 2) + powf(normAxisY, 2)) - normAxisZ * (v.x * normAxisX + v.y * normAxisY))
				* (1 - cos(rad) + (v.x * normAxisY - v.y * normAxisX) * sin(rad))), 1);

		mat4 rotMatrix{ column1, column2, column3, column4 };
		return rotMatrix;
	}

	float determinant(mat4 const m) {
		float a, b, c, d, e, f, g, h, i, j, k, l, mm, n, o, p;
		a = m.matrix[0].x;
		b = m.matrix[0].y;
		c = m.matrix[0].z;
		d = m.matrix[0].w;

		e = m.matrix[1].x;
		f = m.matrix[1].y;
		g = m.matrix[1].z;
		h = m.matrix[1].w;

		i = m.matrix[2].x;
		j = m.matrix[2].y;
		k = m.matrix[2].z;
		l = m.matrix[2].w;

		mm = m.matrix[3].x;
		n = m.matrix[3].y;
		o = m.matrix[3].z;
		p = m.matrix[3].w;

		float deter =
			(a *
				(f * (k * p - l * o)
					- g * (j * p - l * n)
					+ h * (j * o - k * n))

				- b *
				(e * (k * p - l * o)
					- g * (i * p - l * mm)
					+ h * (i * o - k * mm))

				+ c *
				(e * (j * p - l * n)
					- f * (i * p - l * mm)
					+ h * (i * n - j * mm))

				- d *
				(e * (j * o - k * n)
					- f * (i * o - k * mm)
					+ g * (i * n - j * mm))

				);
		return deter;
	}
	mat4 transpose(mat4 const& m) {
		mat4 temp;
		vec4 transpose;
		for (int i = 0; i < 4; i++) {

			for (int j = 0; j < 4; j++) {
				transpose.setElement(j, m.matrix[j].getElement(i));
			}
			temp[i] = transpose;
		}
		return temp;
	}

	mat4 inverse(mat4 const& m) {
		float deter = determinant(m);
		mat4 temp;
		if (deter == 0) {
			return temp;
		}
		float a, b, c, d, e, f, g, h, i, j, k, l, mm, n, o, p;
		a = m.matrix[0].x;
		b = m.matrix[0].y;
		c = m.matrix[0].z;
		d = m.matrix[0].w;

		e = m.matrix[1].x;
		f = m.matrix[1].y;
		g = m.matrix[1].z;
		h = m.matrix[1].w;

		i = m.matrix[2].x;
		j = m.matrix[2].y;
		k = m.matrix[2].z;
		l = m.matrix[2].w;

		mm = m.matrix[3].x;
		n = m.matrix[3].y;
		o = m.matrix[3].z;
		p = m.matrix[3].w;

		temp[0].x = f * (k * p - l * o) //a
			- g * (j * p - l * n)
			+ h * (j * o - k * n); 
		temp[0].y = e * (k * p - l * o) //b 
			- g * (i * p - l * mm)
			+ h * (i * o - k * mm);	
		temp[0].z = e * (j * p - l * n) //c 
			- f * (i * p - l * mm)
			+ h * (i * n - j * mm);
		temp[0].w = e * (j * o - k * n) //d 
			- f * (i * o - k * mm)
			+ g * (i * n - j * mm);
		temp[1].x = b * (k * p - l * o) //e 
			- c * (j * p - l * n)
			+ d * (j * o - k * n);
		temp[1].y = a * (k * p - l * o) //f 
			- c * (i * p - l * mm)
			+ d * (i * o - k * mm);
		temp[1].z = a * (j * p - l * n) //g 
			- b * (i * p - l * mm)
			+ d * (i * n - j * mm);
		temp[1].w = a * (j * o - k * n) //h 
			- b * (i * o - k * mm)
			+ c * (i * n - j * mm);
		temp[2].x = b * (g * p - h * o) //i 
			- c * (f * p - h * n)
			+ d * (f * o - g * n);
		temp[2].y = a * (g * p - h * o) //j 
			- c * (e * p - h * mm)
			+ d * (e * o - g * mm);
		temp[2].z = a * (f * p - h * n) //k
			- b * (e * p - h * mm)
			+ d * (e * n - f * mm);
		temp[2].w = a * (f * o - g * n) //L
			- b * (e * o - g * mm)
			+ c * (e * n - f * mm);
		temp[3].x = b * (g * l - h * k) //m
			- c * (f * l - h * j)
			+ d * (f * k - g * j);
		temp[3].y = a * (g * l - h * k) //n
			- c * (e * l - h * i)
			+ d * (e * k - g * i);
		temp[3].z = a * (f * l - h * j) //o
			- b * (e * l - h * i)
			+ d * (e * j - f * i);
		temp[3].w = a * (f * k - g * j) //p 
			- b * (e * k - g * i)
			+ c * (e * j - f * i);
		
		
		temp[0].y *= -1;
		temp[0].w *= -1;
		temp[1].x *= -1;
		temp[1].z *= -1;
		temp[2].y *= -1;
		temp[2].w *= -1;
		temp[3].x *= -1;
		temp[3].z *= -1;

		//adjugate
		temp = transpose(temp);
		for (int i = 0; i < 4; i++) {
			temp[i].x = temp[i].x / deter;
			temp[i].y = temp[i].y / deter;
			temp[i].z = temp[i].z / deter;
			temp[i].w = temp[i].w / deter;
		}
		return temp;
	}

	int printMatrix(mat4 const& m) {
		for (int i = 0; i < 4; i++) {
			m.matrix[i].printVec4();
		}
		return 0;
	}


}
