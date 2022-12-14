#include <cmath>
#include "Vector2D.h"

//TODO: learn: why are some not added to Vector2D:: , why are some this-> and some ... TLDR: learn operator definitions

Vector2D::Vector2D() {
    x = 0.0f;
    y = 0.0f;
}

Vector2D::Vector2D(float x, float y) {
    this->x = x;
    this->y = y;
}

Vector2D& Vector2D::Add(const Vector2D& vec) {
    this->x += vec.x;
    this->y += vec.y;

    return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D &vec) {
    this->x -= vec.x;
    this->y -= vec.y;

    return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D &vec) {
    this->x *= vec.x;
    this->y *= vec.y;

    return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vec){
    this->x /= vec.x;
    this->y /= vec.y;

    return *this;
}

bool Vector2D::Equals(const Vector2D& vec){
    return this->x == vec.x && this->y == vec.y; ///// todo: make float equals rather than ==
}


Vector2D& Vector2D::AddToCopy(const Vector2D& vec){
    Vector2D newVec = Vector2D(this->x, this->y);
    return newVec.Add(vec);
}

Vector2D& Vector2D::SubtractToCopy(const Vector2D& vec){
    Vector2D newVec = Vector2D(this->x, this->y);
    return newVec.Add(vec);
}

Vector2D& Vector2D::MultiplyToCopy(const Vector2D& vec){
    Vector2D newVec = Vector2D(this->x, this->y);
    return newVec.Add(vec);
}

Vector2D& Vector2D::DivideToCopy(const Vector2D& vec){
    Vector2D newVec = Vector2D(this->x, this->y);
    return newVec.Add(vec);
}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2){
    return v1.AddToCopy(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2){
    return v1.SubtractToCopy(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2){
    return v1.MultiplyToCopy(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2){
    return v1.DivideToCopy(v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec){
    return this->Add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec){
    return this->Subtract(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec){
    return this->Multiply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec){
    return this->Divide(vec);
}

Vector2D& Vector2D::operator*(const int& i) {
    this->x *= static_cast<float>(i);
    this->y *= static_cast<float>(i);
    return *this;
}

Vector2D& Vector2D::Zero() {
    this->x = 0.0f;
    this->y = 0.0f;
    return *this;
}

Vector2D& Vector2D::Unit() {
    float mag = std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2));
    if (this->x != 0) this->x /= mag;
    if (this->y != 0) this->y /= mag;
    return *this;
}

Vector2D Vector2D::Clone() const{
    Vector2D vec = Vector2D(this->x, this->y);
    return vec;
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec){
    stream << "Vec2D(" << vec.x << "," << vec.y << ")";
    return stream;
}
