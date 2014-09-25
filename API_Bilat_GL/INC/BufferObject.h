#ifndef BUFFER_OBJECT_H
#define BUFFER_OBJECT_H

#include "envBilatGL.h"
#include "bilat_GL.h"

/**
 * Create Buffer in a valide OpenGL context
 *
 *
 * When can I instancied a BufferObject ?
 *
 * 	Using API :
 * 		in GLUTWindowCustomiser_A.init() ! (ps reshape,display are other possiblities)
 * 	Using GLUT :
 *  		after glutCreateWindow(...)
 */
class CBI_GL BufferObject
    {

    public:
	/**
	 * @param bufferUsage (GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY)
	 * @param target (GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, GL_PIXEL_PACK_BUFFER, or GL_PIXEL_UNPACK_BUFFER)
	 */
	BufferObject(GLenum target, unsigned int sizeOctet, void* bufferData, GLenum bufferUsage);
	virtual ~BufferObject();

	void bindBuffer();
	void unBindBuffer();

	void bufferData(unsigned int sizeOctet, void* bufferData,GLenum bufferUsage);
	void bufferSubData(unsigned int offset,unsigned int sizeOctet, void* bufferData);

	/**
	 * @param access (GL_READ_ONLY, GL_WRITE_ONLY, or GL_READ_WRITE)
	 */
	void* map(GLenum access);
	bool unMap(void);

	unsigned int getBufferID() const;

    protected:
	GLuint bufferID; //Identifiant OpenGL
	GLenum target;

    };

#endif
