#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <unordered_map>
#include <memory>
#include <cstring>
#include <QtOpenGL>

namespace yy
{

class Shape
{
public:
    class Attribute
    {
    public:
        Attribute() : type(GL_FLOAT), tupleSize(3), stride(0) {}

        GLenum type;
        int tupleSize, stride;
        std::vector<GLubyte> data;

        void setParams(GLenum type, int tupleSize, int stride)
        {
            this->type = type;
            this->tupleSize = tupleSize;
            this->stride = stride;
        }

        template <typename T>
        void setData(const std::vector<T>& in)
        {
            int nBytes = in.size() * sizeof(T);
            this->data.resize(nBytes);
            std::memcpy(data.data(), in.data(), in.size() * sizeof(T));
        }

        template <typename T>
        void set(GLenum type, int tupleSize, int stride, const std::vector<T>& data)
        {
            this->setParams(type, tupleSize, stride);
            this->setData<T>(data);
        }
    };

    Shape() {}
    ~Shape() {}

    std::vector<GLuint> indices;
    std::vector<Attribute> attributes;

public:
    // predefined shapes
    static Shape quad()
    {
        Shape shape;
        shape.attributes.resize(1);
        shape.attributes[0].set<GLfloat>(GL_FLOAT, 2, 0, {0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0});
        shape.indices = {0, 1, 2, 0, 2, 3};
        return shape;
    }

    static Shape cube()
    {
        Shape shape;
        shape.attributes.resize(1);
        shape.attributes[0].setParams(GL_FLOAT, 3, 0);
        shape.attributes[0].setData<GLfloat>({0.f, 0.f, 0.f, /**/ 1.f, 0.f, 0.f,
                                                     1.f, 1.f, 0.f, /**/ 0.f, 1.f, 0.f,
                                                     0.f, 0.f, 1.f, /**/ 1.f, 0.f, 1.f,
                                                     1.f, 1.f, 1.f, /**/ 0.f, 1.f, 1.f});
        shape.indices = { 0, 2, 1, /**/ 0, 3, 2, /**/ 4, 5, 6, /**/ 4, 6, 7,
                          0, 1, 5, /**/ 0, 5, 4, /**/ 1, 2, 6, /**/ 1, 6, 5,
                          2, 3, 7, /**/ 2, 7, 6, /**/ 3, 0, 4, /**/ 3, 4, 7 };
        return shape;
    }
};

} // namespace yy

#endif // SHAPE_H
