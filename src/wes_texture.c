/*
gl-wes-v2:  OpenGL 2.0 to OGLESv2.0 wrapper
Contact:    lachlan.ts@gmail.com
Copyright (C) 2009  Lachlan Tychsen - Smith aka Adventus

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


#include <stdlib.h>
#include <string.h>
#include "wes.h"
#include "wes_gl_defines.h"

GLvoid
wes_convert_BGR2RGB(const GLubyte* inb, GLubyte* outb, GLint size)
{
    int i;
    for(i = 0; i < size; i += 3){
        outb[i + 2] = inb[i];
        outb[i + 1] = inb[i + 1];
        outb[i] = inb[i + 2];
    }
}

GLvoid
wes_convert_BGRA2RGBA(const GLubyte* inb, GLubyte* outb, GLint size)
{
    int i;
    for(i = 0; i < size; i += 4){
        outb[i + 2] = inb[i];
        outb[i + 1] = inb[i + 1];
        outb[i] = inb[i + 2];
        outb[i + 3] = inb[i + 3];
    }
}

GLvoid
wes_convert_I2LA(const GLubyte* inb, GLubyte* outb, GLint size)
{
    int i;
    for(i = 0; i < size; i += 1){
        outb[i*2 + 1] = outb[i*2] = inb[i];
    }
}


GLvoid
glTexImage2D(GLenum target, GLint level, GLenum internalFormat, GLsizei width, GLsizei height,
           GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
    GLvoid* data = (GLvoid*) pixels;

    /* conversion routines */
	/*if (format == GL_BGR){
        data = (GLvoid*) malloc(width * height * 3);
        wes_convert_BGR2RGB((GLubyte*) pixels, (GLubyte*) data, width * height * 3);
        format = GL_RGB;
    } else if (format == GL_BGRA){
        data = (GLvoid*) malloc(width * height * 4);
        wes_convert_BGRA2RGBA((GLubyte*) pixels, (GLubyte*) data, width * height * 4);
        format = GL_RGBA;
    } else if (format == GL_INTENSITY){
        data = (GLvoid*) malloc(width * height * 2);
        wes_convert_I2LA((GLubyte*) pixels, (GLubyte*) data, width * height * 2);
        format = GL_LUMINANCE_ALPHA;
	}*/

    wes_gl->glTexImage2D(target, level, format, width, height, 0, format, type, data);

    if (data != pixels)
        free(data);
}



GLvoid glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
{
	wes_gl->glTexSubImage2D(target,level,xoffset,yoffset,width,height,format,type,pixels);
}


void glCopyTexImage2D( GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border )
{
	wes_gl->glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
}


GLvoid
wes_halveimage(GLint nw, GLint nh, GLint byteperpixel, char* data, char* newdata)
{
    int i, j;
    for(i = 0; i < nw; i++){
        for(j = 0; j < nh; j++){
            memcpy(&newdata[(i + j * nw) * byteperpixel], &data[(i + j * nw *2) * 2*byteperpixel], byteperpixel);
        }
    }
}

GLvoid
gluBuild2DMipmaps(GLenum target, GLint components, GLsizei width, GLsizei height,
                GLenum format, GLenum type, const GLvoid *pixels )
{
    int i = 1;
    GLuint byteperpixel = 0;
    char *data = NULL, *newdata = NULL;
    switch(type)
    {
        case GL_UNSIGNED_BYTE:
            byteperpixel = components;
            break;

        case GL_UNSIGNED_SHORT_4_4_4_4:
        case GL_UNSIGNED_SHORT_5_5_5_1:
        case GL_UNSIGNED_SHORT_5_6_5:
            byteperpixel = 2;
            break;
    }

    if (byteperpixel == 0)
    {
        return;
    }

    glTexImage2D(target, 0, format, width, height, 0, format, type, pixels);

    data = (char*) malloc(width * height * byteperpixel);
    memcpy(data, pixels, width * height * byteperpixel);
    while(width != 1 || height != 1){
        width  >>= 1;
        height >>= 1;
        if (width == 0) width = 1;
        if (height == 0) height = 1;
        newdata = (char*) malloc(width * height * byteperpixel);
        wes_halveimage(width, height, byteperpixel, data, newdata);
        glTexImage2D(target, i++, format, width, height, 0, format, type, newdata);
        free(data);
        data = newdata;
    }

    if (newdata != NULL)
        free(newdata);
}

void glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
	{
	glTexImage2D(GL_TEXTURE_2D, level, internalformat,  width, 1, border, format, type, pixels);
	}

void glTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
	{
	glTexImage2D(GL_TEXTURE_2D, level, internalformat,  width, height, border, format, type, pixels);
	}
void glTexSubImage1D( GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels )
	{
	glTexSubImage2D(target,level,xoffset,0,width,1,format,type,pixels);
	}

void glTexSubImage3D( GLenum target, GLint level,
										 GLint xoffset, GLint yoffset,
										 GLint zoffset, GLsizei width,
										 GLsizei height, GLsizei depth,
										 GLenum format,
										 GLenum type, const GLvoid *pixels)
	{
	glTexSubImage2D(target,level,xoffset,yoffset,width,height,format,type,pixels);
	}
