#ifndef VERTEX_BUFFER_OBJECT_H
#define VERTEX_BUFFER_OBJECT_H

#include "BufferObject.h"

class CBI_GL VertexBufferObject : public BufferObject
    {
    public:
	VertexBufferObject(unsigned int sizeOctet,void* bufferVertex,GLenum bufferUsage);
	virtual ~VertexBufferObject();
    };

#endif
