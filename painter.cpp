#include "painter.h"
#include <cassert>

namespace yy
{

Painter::Painter()
  : program(nullptr)
{

}

Painter::~Painter()
{
    if (program) delete program;
}

void Painter::initializeGL(const std::string &vert, const std::string &frag)
{
    program = new QOpenGLShaderProgram;
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, vert.c_str());
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, frag.c_str());
    program->link();

    vao.create();
    vao.bind();
    vbo.create();
    vbo.bind();
    float quad[] = {0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0};
    assert(nFloat == sizeof(quad) / sizeof(float));
    vbo.allocate(quad, sizeof(quad));
    program->enableAttributeArray(0);
    program->setAttributeBuffer(0, GL_FLOAT, 0, 2);
    vao.release();
}

} // namespace
