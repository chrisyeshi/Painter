#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <QtOpenGL>

namespace yy
{

class Shape
{
public:
    Shape() : tupleSize(0), stride(0) {}
    Shape(int tupleSize, int stride) : tupleSize(tupleSize), stride(stride) {}

    std::vector<GLfloat> verts;
    std::vector<GLuint> indices;
    int tupleSize, stride;

    // predefined shapes
    static Shape quad()
    {
        Shape shape(2, 0);
        shape.verts = {0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0};
        shape.indices = {0, 1, 2, 0, 2, 3};
        return shape;
    }

    static Shape cube()
    {
        Shape shape(3, 0);
        shape.verts = { 0.f, 0.f, 0.f, /**/ 1.f, 0.f, 0.f,
                        1.f, 1.f, 0.f, /**/ 0.f, 1.f, 0.f,
                        0.f, 0.f, 1.f, /**/ 1.f, 0.f, 1.f,
                        1.f, 1.f, 1.f, /**/ 0.f, 1.f, 1.f };
        shape.indices = { 0, 2, 1, /**/ 0, 3, 2, /**/ 4, 5, 6, /**/ 4, 6, 7,
                          0, 1, 5, /**/ 0, 5, 4, /**/ 1, 2, 6, /**/ 1, 6, 5,
                          2, 3, 7, /**/ 2, 7, 6, /**/ 3, 0, 4, /**/ 3, 4, 7 };
        return shape;
    }
};

} // namespace yy

#endif // SHAPE_H
