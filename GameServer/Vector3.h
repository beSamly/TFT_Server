#pragma once

class Vector3
{
public:
    float x;
    float y;
    float z;

public:
    Vector3() : x(0), y(0), z(0) {};
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
    void SetX(float p_x) { x = p_x; }

    void SetZ(float p_z) { z = p_z; }
    float GetX() { return x; }
    float GetZ() { return z; }


    Vector3 operator+ (Vector3 const& obj) {
        Vector3 res;
        res.x = x + obj.x;
        res.y = y + obj.y;
        res.z = z + obj.z;
        return res;
    }

    Vector3 operator- (Vector3 const& obj) {

        Vector3 res;
        res.x = x - obj.x;
        res.y = y - obj.y;
        res.z = z - obj.z;
        return res;
    }

    Vector3 operator* (float value) {

        Vector3 res;
        res.x = x * value;
        res.y = y * value;
        res.z = z * value;
        return res;
    }

    bool operator== (Vector3 const& obj) { return x == obj.x && y == obj.y && z == obj.z ? true : false; }


    float GetMagnitude() {
        return sqrt(x * x + y * y + z * z);
    }

    Vector3 Normalized() {
        Vector3 res;
        float magnitude = GetMagnitude();
        res.x = x / magnitude;
        res.y = y / magnitude;
        res.z = z / magnitude;

        return res;
    }

    float Dot(Vector3 target) {
        Vector3 first = Normalized();
        Vector3 second = target.Normalized();
        return first.x * second.x + first.y * second.y + first.z * second.z;
    }
};
