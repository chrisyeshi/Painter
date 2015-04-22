#ifndef PAINTER_H
#define PAINTER_H

#include <iostream>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

namespace yy
{

class Painter
{
public:
    Painter();
    ~Painter();

    void initializeGL(const std::string& vert, const std::string& frag);
//    void paint(GLuint texID);
    template <typename... Args>
    void paint(Args... args);

private:
    const int nFloat = 8;
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;
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
    glDrawArrays(GL_TRIANGLE_STRIP, 0, nFloat);
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
