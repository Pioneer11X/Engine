#pragma once

// Data structure for basic geometry and colors
typedef struct BasicVertex {
	float x;
	float y;
	float z;

	float r;
	float g;
	float b;

	float u = 1.0f;
	float v = 1.0f;


	BasicVertex() { x = 0.0f; y = 0.0f; z = 0.0f; r = 1.0f; g = 1.0f; b = 1.0f; }
	BasicVertex(float x, float y, float z, float r, float g, float b, float _u = 1.0f, float _v = 1.0f) { this->x = x; this->y = y; this->z = z; this->r = r; this->g = g; this->b = b; u = _u; v = _v; }
	BasicVertex operator+(const BasicVertex& rhs) {
		return BasicVertex(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z, this->r + rhs.r , this->g + rhs.g , this->b + rhs.g);
	}
	BasicVertex operator+(const float& rhs) {
		return BasicVertex(this->x + rhs, this->y + rhs, this->z += rhs, this->r, this->g, this->b);
	}
	BasicVertex operator*(const BasicVertex& rhs) {
		return BasicVertex(this->x * rhs.x, this->y * rhs.y, this->z *= rhs.z, this->r, this->g, this->b);
	}
	BasicVertex operator*(const float& rhs) {
		return BasicVertex(this->x * rhs, this->y * rhs, this->z * rhs, this->r, this->g, this->b);
	}

} BasicVertex;