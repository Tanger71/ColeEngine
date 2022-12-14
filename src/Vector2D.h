#pragma once
#include <iostream>

/**
 * @brief 2-Dimensional Vector class with operators.
 *
 * @author sawyercoletang
 *
 */
class Vector2D{
public:
    float x;
    float y;

    Vector2D();

    Vector2D(float x, float y);

    Vector2D& Add(const Vector2D& vec);
    Vector2D& Subtract(const Vector2D& vec);
    Vector2D& Multiply(const Vector2D& vec);
    Vector2D& Divide(const Vector2D& vec);
    bool Equals(const Vector2D& vec);

    Vector2D& AddToCopy(const Vector2D& vec);
    Vector2D& SubtractToCopy(const Vector2D& vec);
    Vector2D& MultiplyToCopy(const Vector2D& vec);
    Vector2D& DivideToCopy(const Vector2D& vec);

    friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

    Vector2D& operator+=(const Vector2D& vec);
    Vector2D& operator-=(const Vector2D& vec);
    Vector2D& operator*=(const Vector2D& vec);
    Vector2D& operator/=(const Vector2D& vec);

    Vector2D& operator*(const int& i);
    Vector2D& Zero();
    Vector2D& Unit();

    Vector2D Clone() const;

    friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);

};
