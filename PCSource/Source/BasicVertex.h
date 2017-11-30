#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

// Data structure for basic geometry and colors
typedef struct BasicVertex {
	
	vec3 position = vec3();
	vec3 normal = vec3();
	vec2 uv = vec2();

	BasicVertex() {
		position = vec3();
		normal = vec3();
		uv = vec2();
	};

	BasicVertex(vec3 _pos, vec3 _normal, vec2 _uv) {
		position = _pos;
		normal = _normal;
		uv = _uv;
	};

	BasicVertex(float _x, float _y, float _z, float _r, float _g, float _b, float _u, float _v) {
		position	= vec3(_x, _y, _z);
		normal		= vec3(_r, _g, _b);
		uv			= vec2(_u, _v);
	};

} BasicVertex;