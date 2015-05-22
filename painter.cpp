#include "painter.h"
#include <cassert>
#include "shape.h"

namespace yy
{

Painter::Painter()
  : nIndex(0)
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
    vbo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vbo.bind();

    // get total bytes
    int nBytes = 0;
    for (auto attr : shape.attributes)
        nBytes += attr.data.size();
    // put into buffer
    vbo.allocate(nBytes);
    int offset = 0;
    for (unsigned int loc = 0; loc < shape.attributes.size(); ++loc)
    {
        const Shape::Attribute& attr = shape.attributes[loc];
        vbo.write(offset, reinterpret_cast<const void*>(attr.data.data()), attr.data.size());
        program->enableAttributeArray(loc);
        program->setAttributeBuffer(loc, attr.type, offset, attr.tupleSize, attr.stride);
        offset += attr.data.size();
    }
    // index buffer object
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

void Painter::updateAttributes(const std::vector<Shape::Attribute> &attributes)
{
    // the structure needs to be the same
    // update vbo
    vbo.bind();
    int offset = 0;
    for (unsigned int loc = 0; loc < attributes.size(); ++loc)
    {
        const Shape::Attribute& attr = attributes[loc];
        vbo.write(offset, reinterpret_cast<const void*>(attr.data.data()), attr.data.size());
        offset += attr.data.size();
    }
}

} // namespace
