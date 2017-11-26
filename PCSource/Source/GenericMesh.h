#pragma once

#include "BasicVertex.h"
#include <stdint.h>

class GenericMesh
{

protected:

	BasicVertex * vertices;
	uint16_t vertexCount;
	uint16_t * indices;
	uint16_t indexCount;

public:



	GenericMesh(BasicVertex * _vertices, uint16_t _vertexCount, uint16_t * _indices, uint16_t _indexCount);
	GenericMesh(char * _fileName);
	~GenericMesh();

	virtual void SetBuffers() = 0;

	inline uint16_t * getIndexData() { return indices; }

	inline uint16_t GetIndexCount() { return indexCount; }
	inline uint16_t GetVertexCount() { return vertexCount; }
};

