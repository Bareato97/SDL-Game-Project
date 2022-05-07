#pragma once

class Vector2D {

    public:
        // 2d points 
        float x;
        float y;

        // constructor and constructor overloading for variable functions
        Vector2D();
        Vector2D(float x, float y);

        // The below sets of functions have essentially the same process.

        // performs arithmatic functions on vectors, returning the value onto vector1
        // vec1.add(vec2) for example
        // vec1 += vec2
        Vector2D& Add(const Vector2D& vec); 
        Vector2D& Subtract(const Vector2D& vec); 
        Vector2D& Multiply(const Vector2D& vec); 
        Vector2D& Divide(const Vector2D& vec); 

        Vector2D& operator+=(Vector2D& vec);
        Vector2D& operator-=(Vector2D& vec);
        Vector2D& operator*=(Vector2D& vec);
        Vector2D& operator/=(Vector2D& vec);

        // Allow for vector scaling
        Vector2D& operator*(const int& i);

        // Zeros vector
        Vector2D& Zero();

        //operator overloading for athrimatic
        // friend allows for access to private functions by another class. in this case it will allow other vector2Ds
        // to access these varibles to overload operators
        // this can be used to return to a 3rd varible for example
        // someVec = vec1 + vec2
        friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
        friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
        friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
        friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);   
};