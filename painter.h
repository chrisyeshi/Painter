#ifndef PAINTER_H
#define PAINTER_H

#include <iostream>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

namespace yy
{

class Shape;

class Painter
{
public:
    Painter();
    ~Painter();

    void initializeGL(const Shape& shape, const std::string& vert, const std::string& frag);
    void initializeGL(const std::string& vert, const std::string& frag);
    template <typename... Args>
    void paint(Args... args);

private:
    int nFloat, nIndex;
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo, ibo;
    QOpenGLShaderProgram* program;

    template <typename Loc, typename Val, typename... Args>
    void setUniform(Loc location, Val value, Args... args);
    void setUniform() {}
};

// the variadic templated paint function
template <typename... Args>
void Painter::paint(Args... args)
{
    program->bind();
    setUniform(args...);
    vao.bind();
    glDrawElements(GL_TRIANGLES, nIndex, GL_UNSIGNED_INT, 0);
    vao.release();
    program->release();
}

template <typename Loc, typename Val, typename... Args>
void Painter::setUniform(Loc location, Val value, Args... args)
{
    program->setUniformValue(location, value);
    setUniform(args...);
}

} // namespace yy

#endif // PAINTER_H
