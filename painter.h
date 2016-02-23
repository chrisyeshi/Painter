#ifndef PAINTER_H
#define PAINTER_H

#include <iostream>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include "shape.h"

namespace yy {

// TODO: make painter to handle binding textures

class Painter
{
public:
    Painter();
    ~Painter();

    void initializeGL(const Shape& shape, const std::string& vert, const std::string& frag);
    void initializeGL(const std::string& vert, const std::string& frag);
    void updateAttributes(const std::vector<Shape::Attribute>& attributes);
    template <typename... Args>
    void paint(Args... args);

    template <typename Loc, typename Val, typename... Args>
    void setUniforms(Loc location, Val value, Args... args);

    template <typename Loc, typename Val>
    void setUniform(Loc location, Val value);

private:
    int nIndex;
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo, ibo;
    QOpenGLShaderProgram* program;

    template <typename Loc, typename Val, typename... Args>
    void setUniformsInternal(Loc location, Val value, Args... args);
    void setUniformsInternal() {}
};

// the variadic templated paint function
template <typename... Args>
void Painter::paint(Args... args)
{
    auto f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
    f->initializeOpenGLFunctions();
    GLint oProg, oVao;
    f->glGetIntegerv(GL_CURRENT_PROGRAM, &oProg);
    program->bind();
    setUniformsInternal(args...);
    f->glGetIntegerv(GL_VERTEX_ARRAY_BUFFER_BINDING, &oVao);
    vao.bind();
    f->glDrawElements(GL_TRIANGLES, nIndex, GL_UNSIGNED_INT, 0);
    vao.release();
    f->glBindBuffer(GL_ARRAY_BUFFER, oVao);
    program->release();
    f->glUseProgram(oProg);
}

template <typename Loc, typename Val, typename... Args>
void Painter::setUniforms(Loc location, Val value, Args... args)
{
    auto f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
    f->initializeOpenGLFunctions();
    GLint oProg;
    f->glGetIntegerv(GL_CURRENT_PROGRAM, &oProg);
    program->bind();
    setUniformsInternal(location, value, args...);
    program->release();
    f->glUseProgram(oProg);
}

template <typename Loc, typename Val>
void Painter::setUniform(Loc location, Val value)
{
    auto f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
    f->initializeOpenGLFunctions();
    GLint oProg;
    f->glGetIntegerv(GL_CURRENT_PROGRAM, &oProg);
    program->bind();
    program->setUniformValue(location, value);
    program->release();
    f->glUseProgram(oProg);
}

template <typename Loc, typename Val, typename... Args>
void Painter::setUniformsInternal(Loc location, Val value, Args... args)
{
    program->setUniformValue(location, value);
    setUniformsInternal(args...);
}

} // namespace yy

#endif // PAINTER_H
