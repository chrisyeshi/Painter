#include "painter.h"
#include <cassert>
#include "shape.h"

namespace yy
{

Painter::Painter()
  : nFloat(0), nIndex(0)
  , vbo(QOpenGLBuffer::VertexBuffer)
  , ibo(QOpenGLBuffer::IndexBuffer)
  , program(nullptr)
{

}

Painter::~Painter()
{
    if (program) delete program;
}

void Painter::initializeGL(const Shape& shape, const std::string &vert, const std::string &frag)
{
    program = new QOpenGLShaderProgram();
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, vert.c_str());
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, frag.c_str());
    program->link();

    vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();
    nFloat = shape.verts.size();
    vbo.allocate(shape.verts.data(), shape.verts.size() * sizeof(GLfloat));
    program->enableAttributeArray(0);
    program->setAttributeBuffer(0, GL_FLOAT, 0, shape.tupleSize, shape.stride);

    ibo.create();
    ibo.bind();
    nIndex = shape.indices.size();
    ibo.allocate(shape.indices.data(), shape.indices.size() * sizeof(GLuint));

    vao.release();
}

void Painter::initializeGL(const std::string &vert, const std::string &frag)
{
    this->initializeGL(Shape::quad(), vert, frag);
}

} // namespace
