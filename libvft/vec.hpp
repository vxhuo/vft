
// Copyright (c) 2026 vxhuo
// This source code is licensed under the MIT license found in the
// LICENSE file

#pragma once

#include <type_traits>
#include <format>
#include <cmath>


namespace vft
{
    template<typename T>
    concept Arithmetic = std::is_arithmetic_v<T>;


    template<Arithmetic T>
    using FT = std::conditional_t<std::is_floating_point_v<T>, T, float>;


    template<Arithmetic T, unsigned char D = 2>
    struct vec;


    template<Arithmetic T>
    struct vec<T,2> final
    {
        T x{}, y{};




        [[nodiscard]] constexpr inline vec operator+(const vec o) const noexcept
        { return { x + o.x, y + o.y }; }

        [[nodiscard]] constexpr inline vec operator-(const vec o) const noexcept
        { return { x - o.x, y - o.y }; }

        [[nodiscard]] constexpr inline vec operator*(const T s) const noexcept
        { return { x * s, y * s }; }

        [[nodiscard]] constexpr inline vec operator/(const T s) const noexcept
        { return { x / s, y / s }; }


        constexpr inline vec& operator+=(const vec o) noexcept
        { x += o.x; y += o.y; return *this; }

        constexpr inline vec& operator-=(const vec o) noexcept
        { x -= o.x; y -= o.y; return *this; }

        constexpr inline vec& operator+=(const T s) noexcept
        { x += s; y += s; return *this; }

        constexpr inline vec& operator-=(const T s) noexcept
        { x -= s; y -= s; return *this; }
        
        constexpr inline vec& operator*=(const T s) noexcept
        { x *= s; y *= s; return *this; }

        constexpr inline vec& operator/=(const T s) noexcept
        { x /= s; y /= s; return *this; }

        [[nodiscard]] constexpr vec operator-() const noexcept
        { return {-x, -y}; }


        [[nodiscard]] constexpr inline bool operator==(const vec o) const noexcept
        { return x == o.x && y == o.y; }

        [[nodiscard]] constexpr inline bool operator!=(const vec o) const noexcept
        { return x != o.x || y != o.y; }


        [[nodiscard]] constexpr inline T& operator[](unsigned char id) noexcept 
        {
            if (id == 0) return x;
            return y;
        }

        [[nodiscard]] constexpr inline const T& operator[](unsigned char id) const noexcept
        {
            if (id == 0) return x;
            return y;
        }


        [[nodiscard]] inline const T* data() const noexcept { return &x; }

        constexpr vec<T,2> xy() const noexcept { return {x, y}; }
        constexpr vec<T,2> yx() const noexcept { return {y, x}; }


        template<unsigned char D>
        [[nodiscard]] constexpr T dot(const vec<T,D> v) const noexcept
        { return (x * v.x) + (y * v.y); }

        [[nodiscard]] constexpr inline T len_sq() const noexcept 
        { return (x * x) + (y * y); }

        [[nodiscard]] constexpr FT<T> len() const noexcept
        { return std::sqrt(static_cast<FT<T>>(len_sq())); }
                 
        constexpr inline void normalize() noexcept requires std::is_floating_point_v<T>
        { *this = *this / len(); }

        [[nodiscard]] constexpr inline FT<T> dist(const vec<T,2> v) const noexcept 
        { return std::sqrt(((v.x - x) * (v.x - x)) + ((v.y - y) * (v.y - y))); } 

        [[nodiscard]] constexpr inline T dist_sq(const vec<T,2> v) const noexcept 
        { return ((v.x - x) * (v.x - x)) + ((v.y - y) * (v.y - y)); } 

        template<unsigned char D>
        constexpr void lerp(const vec<T,D> to, const float t) noexcept 
        {
            x = x + (t * (to.x - x));
            y = y + (t * (to.y - y));
        }

        constexpr void abs() noexcept requires std::is_signed_v<T>
        {
            x = x < 0 ? -x : x;
            y = y < 0 ? -y : y;
        }

        constexpr inline void clamp(const T min, const T max) noexcept 
        {
            if (x >= max) x = max;
            else if (x <= min) x = min;
            if (y >= max) y = max;
            else if (y <= min) y = min;
        }

        [[nodiscard]] constexpr bool equal(const vec<T,2> o, const T epsilon) const noexcept
        { return dist_sq(o) <= epsilon * epsilon; }

        [[nodiscard]] constexpr FT<T> angle(const vec<T,2> o) const noexcept
        { return std::acos(std::clamp(static_cast<FT<T>>(dot(o)) / (len() * o.len()), FT<T>(-1), FT<T>(1))); }

        [[nodiscard]] constexpr vec<T,2> project(const vec<T,2> o) const noexcept
        { return o * (dot(o) / o.dot(o)); }

        [[nodiscard]] constexpr vec<T,2> reject(const vec<T,2> o) const noexcept
        { return *this - project(o); }

    };


    template<Arithmetic T>
    struct vec<T,3> final
    {
        T x{}, y{}, z{};




        [[nodiscard]] constexpr inline vec operator+(const vec o) const noexcept
        { return { x + o.x, y + o.y, z + o.z }; }

        [[nodiscard]] constexpr inline vec operator-(const vec o) const noexcept
        { return { x - o.x, y - o.y, z - o.z }; }

        [[nodiscard]] constexpr inline vec operator*(const T s) const noexcept
        { return { x * s, y * s, z * s }; }

        [[nodiscard]] constexpr inline vec operator/(const T s) const noexcept
        { return { x / s, y / s, z / s }; }


        constexpr inline vec& operator+=(const vec o) noexcept
        { x += o.x; y += o.y; z += o.z; return *this; }

        constexpr inline vec& operator-=(const vec o) noexcept
        { x -= o.x; y -= o.y; z -= o.z; return *this; }

        constexpr inline vec& operator+=(const T s) noexcept
        { x += s; y += s; z += s; return *this; }

        constexpr inline vec& operator-=(const T s) noexcept
        { x -= s; y -= s; z -= s; return *this; }
        
        constexpr inline vec& operator*=(const T s) noexcept
        { x *= s; y *= s; z *= s; return *this; }

        constexpr inline vec& operator/=(const T s) noexcept
        { x /= s; y /= s; z /= s; return *this; }

        [[nodiscard]] constexpr vec operator-() const noexcept
        { return {-x, -y, -z}; }


        [[nodiscard]] constexpr inline bool operator==(const vec o) const noexcept
        { return x == o.x && y == o.y && z == o.z; }

        [[nodiscard]] constexpr inline bool operator!=(const vec o) const noexcept
        { return x != o.x || y != o.y || z != o.z; }


        [[nodiscard]] constexpr inline T& operator[](unsigned char id) noexcept 
        {
            if (id == 0) return x;
            if (id == 1) return y;
            return z;
        }

        [[nodiscard]] constexpr inline const T& operator[](unsigned char id) const noexcept
        {
            if (id == 0) return x;
            if (id == 1) return y;
            return z;
        }


        [[nodiscard]] inline const T* data() const noexcept { return &x; }

        constexpr vec<T,2> xy() const noexcept { return {x, y}; }
        constexpr vec<T,2> yx() const noexcept { return {y, x}; }

        constexpr vec<T,3> xyz() const noexcept { return {x, y, z}; }
        constexpr vec<T,3> xzy() const noexcept { return {x, z, y}; }
        constexpr vec<T,3> yxz() const noexcept { return {y, x, z}; }
        constexpr vec<T,3> yzx() const noexcept { return {y, z, x}; }
        constexpr vec<T,3> zyx() const noexcept { return {z, y, x}; }
        constexpr vec<T,3> zxy() const noexcept { return {z, x, y}; }


        template<unsigned char D>
        [[nodiscard]] constexpr T dot(const vec<T,D> v) const noexcept
        { return (x * v.x) + (y * v.y) + (z * v.z); }
        
        constexpr inline void cross(const vec<T,3> v) noexcept 
        {
            T _x = (y * v.z) - (z * v.y);
            T _y = (z * v.x) - (x * v.z);
            T _z = (x * v.y) - (y * v.x);
            x = _x; y = _y; z = _z;
        }

        [[nodiscard]] constexpr inline T len_sq() const noexcept 
        { return (x * x) + (y * y) + (z * z); }

        [[nodiscard]] constexpr FT<T> len() const noexcept
        { return std::sqrt(static_cast<FT<T>>(len_sq())); }
                 
        constexpr inline void normalize() noexcept requires std::is_floating_point_v<T>
        { *this = *this / len(); }

        [[nodiscard]] constexpr inline FT<T> dist(const vec<T,3> v) const noexcept 
        { return std::sqrt(((v.x - x) * (v.x - x)) + ((v.y - y) * (v.y - y)) + ((v.z - z) * (v.z - z))); } 

        [[nodiscard]] constexpr inline T dist_sq(const vec<T,3> v) const noexcept 
        { return ((v.x - x) * (v.x - x)) + ((v.y - y) * (v.y - y)) + ((v.z - z) * (v.z - z)); } 

        template<unsigned char D>
        constexpr void lerp(const vec<T,D> to, const float t) noexcept 
        {
            x = x + (t * (to.x - x));
            y = y + (t * (to.y - y));
            z = z + (t * (to.z - z)); 
        }

        constexpr void abs() noexcept requires std::is_signed_v<T>
        {
            x = x < 0 ? -x : x;
            y = y < 0 ? -y : y;
            z = z < 0 ? -z : z;
        }

        constexpr inline void clamp(const T min, const T max) noexcept 
        {
            if (x >= max) x = max;
            else if (x <= min) x = min;
            if (y >= max) y = max;
            else if (y <= min) y = min;
            if (z >= max) z = max;
            else if (z <= min) z = min;
        }

        [[nodiscard]] constexpr bool equal(const vec<T,3> o, const T epsilon) const noexcept
        { return dist_sq(o) <= epsilon * epsilon; }

        [[nodiscard]] constexpr FT<T> angle(const vec<T,3> o) const noexcept
        { return std::acos(std::clamp(static_cast<FT<T>>(dot(o)) / (len() * o.len()), FT<T>(-1), FT<T>(1))); }

        [[nodiscard]] constexpr vec<T,3> project(const vec<T,3> o) const noexcept
        { return o * (dot(o) / o.dot(o)); }

        [[nodiscard]] constexpr vec<T,3> reject(const vec<T,3> o) const noexcept
        { return *this - project(o); }

    };


    template<Arithmetic T>
    struct vec<T,4> final
    {
        T x{}, y{}, z{}, w{};




        [[nodiscard]] constexpr inline vec operator+(const vec o) const noexcept
        { return { x + o.x, y + o.y, z + o.z, w + o.w }; }

        [[nodiscard]] constexpr inline vec operator-(const vec o) const noexcept
        { return { x - o.x, y - o.y, z - o.z, w - o.w }; }

        [[nodiscard]] constexpr inline vec operator*(const T s) const noexcept
        { return { x * s, y * s, z * s, w * s }; }

        [[nodiscard]] constexpr inline vec operator/(const T s) const noexcept
        { return { x / s, y / s, z / s, w / s }; }


        constexpr inline vec& operator+=(const vec o) noexcept
        { x += o.x; y += o.y; z += o.z; w += o.w; return *this; }

        constexpr inline vec& operator-=(const vec o) noexcept
        { x -= o.x; y -= o.y; z -= o.z; w -= o.w; return *this; }

        constexpr inline vec& operator+=(const T s) noexcept
        { x += s; y += s; z += s; w += s; return *this; }

        constexpr inline vec& operator-=(const T s) noexcept
        { x -= s; y -= s; z -= s; w -= s; return *this; }
        
        constexpr inline vec& operator*=(const T s) noexcept
        { x *= s; y *= s; z *= s; w *= s; return *this; }

        constexpr inline vec& operator/=(const T s) noexcept
        { x /= s; y /= s; z /= s; w /= s; return *this; }

        [[nodiscard]] constexpr vec operator-() const noexcept
        { return {-x, -y, -z, -w}; }


        [[nodiscard]] constexpr inline bool operator==(const vec o) const noexcept
        { return x == o.x && y == o.y && z == o.z && w == o.w; }

        [[nodiscard]] constexpr inline bool operator!=(const vec o) const noexcept
        { return x != o.x || y != o.y || z != o.z || w != o.w; }


        [[nodiscard]] constexpr inline T& operator[](unsigned char id) noexcept 
        {
            if (id == 0) return x;
            if (id == 1) return y;
            if (id == 2) return z;
            return w;
        }

        [[nodiscard]] constexpr inline const T& operator[](unsigned char id) const noexcept
        {
            if (id == 0) return x;
            if (id == 1) return y;
            if (id == 2) return z;
            return w;
        }

        [[nodiscard]] inline const T* data() const noexcept { return &x; }

        constexpr vec<T,2> xy() const noexcept { return {x, y}; }
        constexpr vec<T,2> yx() const noexcept { return {y, x}; }

        constexpr vec<T,3> xyz() const noexcept { return {x, y, z}; }
        constexpr vec<T,3> xzy() const noexcept { return {x, z, y}; }
        constexpr vec<T,3> yxz() const noexcept { return {y, x, z}; }
        constexpr vec<T,3> yzx() const noexcept { return {y, z, x}; }
        constexpr vec<T,3> zyx() const noexcept { return {z, y, x}; }
        constexpr vec<T,3> zxy() const noexcept { return {z, x, y}; }

        constexpr vec<T,4> xyzw() const noexcept { return {x, y, z, w}; }
        constexpr vec<T,4> xywz() const noexcept { return {x, y, w, z}; }
        constexpr vec<T,4> xzyw() const noexcept { return {x, z, y, w}; }
        constexpr vec<T,4> xzwy() const noexcept { return {x, z, w, y}; }
        constexpr vec<T,4> xwyz() const noexcept { return {x, w, y, z}; }
        constexpr vec<T,4> xwzy() const noexcept { return {x, w, z, y}; }
        constexpr vec<T,4> yxzw() const noexcept { return {y, x, z, w}; }
        constexpr vec<T,4> yxwz() const noexcept { return {y, x, w, z}; }
        constexpr vec<T,4> yzxw() const noexcept { return {y, z, x, w}; }
        constexpr vec<T,4> yzwx() const noexcept { return {y, z, w, x}; }
        constexpr vec<T,4> ywxz() const noexcept { return {y, w, x, z}; }
        constexpr vec<T,4> ywzx() const noexcept { return {y, w, z, x}; }
        constexpr vec<T,4> zxyw() const noexcept { return {z, x, y, w}; }
        constexpr vec<T,4> zxwy() const noexcept { return {z, x, w, y}; }
        constexpr vec<T,4> zyxw() const noexcept { return {z, y, x, w}; }
        constexpr vec<T,4> zywx() const noexcept { return {z, y, w, x}; }
        constexpr vec<T,4> zwxy() const noexcept { return {z, w, x, y}; }
        constexpr vec<T,4> zwyx() const noexcept { return {z, w, y, x}; }
        constexpr vec<T,4> wxyz() const noexcept { return {w, x, y, z}; }
        constexpr vec<T,4> wxzy() const noexcept { return {w, x, z, y}; }
        constexpr vec<T,4> wyxz() const noexcept { return {w, y, x, z}; }
        constexpr vec<T,4> wyzx() const noexcept { return {w, y, z, x}; }
        constexpr vec<T,4> wzxy() const noexcept { return {w, z, x, y}; }
        constexpr vec<T,4> wzyx() const noexcept { return {w, z, y, x}; }


        template<unsigned char D>
        [[nodiscard]] constexpr T dot(const vec<T,D> v) const noexcept
        { return (x * v.x) + (y * v.y) + (z * v.z) + (w * v.w); }
        
        [[nodiscard]] constexpr inline T len_sq() const noexcept 
        { return (x * x) + (y * y) + (z * z) + (w * w); }

        [[nodiscard]] constexpr FT<T> len() const noexcept
        { return std::sqrt(static_cast<FT<T>>(len_sq())); }
                 
        constexpr inline void normalize() noexcept requires std::is_floating_point_v<T>
        { *this = *this / len(); }

        [[nodiscard]] constexpr inline FT<T> dist(const vec<T,4> v) const noexcept 
        { return std::sqrt(((v.x - x) * (v.x - x)) + ((v.y - y) * (v.y - y)) + ((v.z - z) * (v.z - z)) + ((v.w - w) * (v.w - w))); } 

        [[nodiscard]] constexpr inline T dist_sq(const vec<T,4> v) const noexcept 
        { return ((v.x - x) * (v.x - x)) + ((v.y - y) * (v.y - y)) + ((v.z - z) * (v.z - z)) + ((v.w - w) * (v.w - w)); } 

        template<unsigned char D>
        constexpr void lerp(const vec<T,D> to, const float t) noexcept 
        {
            x = x + (t * (to.x - x));
            y = y + (t * (to.y - y));
            z = z + (t * (to.z - z)); 
            w = w + (t * (to.w - w)); 
        }

        constexpr void abs() noexcept requires std::is_signed_v<T>
        {
            x = x < 0 ? -x : x;
            y = y < 0 ? -y : y;
            z = z < 0 ? -z : z;
            w = w < 0 ? -w : w;
        }

        constexpr inline void clamp(const T min, const T max) noexcept 
        {
            if (x >= max) x = max;
            else if (x <= min) x = min;
            if (y >= max) y = max;
            else if (y <= min) y = min;
            if (z >= max) z = max;
            else if (z <= min) z = min;
            if (w >= max) w = max;
            else if (w <= min) w = min;
        }

        [[nodiscard]] constexpr bool equal(const vec<T,4> o, const T epsilon) const noexcept
        { return dist_sq(o) <= epsilon * epsilon; }

        [[nodiscard]] constexpr FT<T> angle(vec<T,4> o) const noexcept
        { return std::acos(std::clamp(static_cast<FT<T>>(dot(o)) / (len() * o.len()), FT<T>(-1), FT<T>(1))); }

        [[nodiscard]] constexpr vec<T,4> project(vec<T,4> o) const noexcept
        { return o * (dot(o) / o.dot(o)); }

        [[nodiscard]] constexpr vec<T,4> reject(const vec<T,4> o) const noexcept
        { return *this - project(o); }
    };



    template<Arithmetic T>
    constexpr vec<T,2> operator+(T s, vec<T,2> v) noexcept 
    { return {s + v.x, s + v.y}; }

    template<Arithmetic T>
    constexpr vec<T,3> operator+(T s, vec<T,3> v) noexcept 
    { return {s + v.x, s + v.y, s + v.z}; }

    template<Arithmetic T>
    constexpr vec<T,4> operator+(T s, vec<T,4> v) noexcept 
    { return {s + v.x, s + v.y, s + v.z, s + v.w}; }




    template<Arithmetic T>
    constexpr vec<T,2> operator-(T s, vec<T,2> v) noexcept 
    { return {s - v.x, s - v.y}; }

    template<Arithmetic T>
    constexpr vec<T,3> operator-(T s, vec<T,3> v) noexcept 
    { return {s - v.x, s - v.y, s - v.z}; }

    template<Arithmetic T>
    constexpr vec<T,4> operator-(T s, vec<T,4> v) noexcept 
    { return {s - v.x, s - v.y, s - v.z, s - v.w}; }




    template<Arithmetic T>
    constexpr vec<T,2> operator*(T s, vec<T,2> v) noexcept 
    { return {s * v.x, s * v.y}; }

    template<Arithmetic T>
    constexpr vec<T,3> operator*(T s, vec<T,3> v) noexcept 
    { return {s * v.x, s * v.y, s * v.z}; }

    template<Arithmetic T>
    constexpr vec<T,4> operator*(T s, vec<T,4> v) noexcept 
    { return {s * v.x, s * v.y, s * v.z, s * v.w}; }




    template<Arithmetic T>
    constexpr vec<T,2> operator/(T s, vec<T,2> v) noexcept 
    { return {s / v.x, s / v.y}; }

    template<Arithmetic T>
    constexpr vec<T,3> operator/(T s, vec<T,3> v) noexcept 
    { return {s / v.x, s / v.y, s / v.z}; }

    template<Arithmetic T>
    constexpr vec<T,4> operator/(T s, vec<T,4> v) noexcept 
    { return {s / v.x, s / v.y, s / v.z, s / v.w}; }




    template<Arithmetic T, unsigned char D>
    requires (D == 2 || D == 3 || D == 4)
    [[nodiscard]] constexpr T dot(vec<T,D> a, vec<T,D> b) noexcept 
    {
        if constexpr (D == 2)
        {
            return (a.x * b.x) + (a.y * b.y); 
        }
        else if constexpr (D == 3)
        {
            return (a.x * b.x) + (a.y * b.y) + (a.z * b.z); 
        }
        else if constexpr (D == 4)
        {
            return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
        }
    }


    template<Arithmetic T, unsigned char D>
    requires (D == 3)
    [[nodiscard]] constexpr vec<T,D> cross(const vec<T,D> a, const vec<T,D> b) noexcept 
    { return {(a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x)}; }


    template<Arithmetic T, unsigned char D>
    requires (D == 2 || D == 3 || D == 4)
    [[nodiscard]] constexpr T len_sq(const vec<T,D> v) noexcept 
    {
        if constexpr (D == 2)
        {
            return{ (v.x * v.x) + (v.y * v.y) }; 
        }
        else if constexpr (D == 3)
        {
            return{ (v.x * v.x) + (v.y * v.y) + (v.z * v.z) }; 
        }
        else if constexpr (D == 4)
        {
            return{ (v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w) }; 
        }
    }


    template<Arithmetic T, unsigned char D>
    [[nodiscard]] constexpr FT<T> len(const vec<T,D> v) noexcept requires (D == 2 || D == 3 || D == 4) 
    { return std::sqrt(static_cast<FT<T>>(len_sq(v))); }


    template<Arithmetic T, unsigned char D>
    requires (D == 2 || D == 3 || D == 4)
    [[nodiscard]] constexpr T dist_sq(vec<T,D> a, vec<T,D> b) noexcept 
    { return len_sq(b - a); }


    template<Arithmetic T, unsigned char D>
    requires (D == 2 || D == 3 || D == 4)
    [[nodiscard]] constexpr FT<T> dist(vec<T,D> a, vec<T,D> b) noexcept 
    { return len(b - a); }


    template<Arithmetic T, unsigned char D>
    requires (D == 2 || D == 3 || D == 4)
    [[nodiscard]] constexpr vec<T,D> normalize(const vec<T,D> v) noexcept requires std::is_floating_point_v<T>
    { return v / len(v); }


    template<Arithmetic T, unsigned char D>
    requires (D == 2 || D == 3 || D == 4)
    [[nodiscard]] constexpr vec<T,D> lerp(const vec<T,D> a, const vec<T,D> b, const float t) noexcept 
    { 
        if constexpr (D == 2)
        {
            return 
            {
                a.x + (t * (b.x - a.x)),
                a.y + (t * (b.y - a.y)) 
            };
        }
        else if constexpr (D == 3)
        {
            return
            {
                a.x + (t * (b.x - a.x)),
                a.y + (t * (b.y - a.y)),
                a.z + (t * (b.z - a.z))
            };
        }
        else if constexpr (D == 4)
        {
            return
            {
                a.x + (t * (b.x - a.x)),
                a.y + (t * (b.y - a.y)),
                a.z + (t * (b.z - a.z)),
                a.w + (t * (b.w - a.w))
            };
        }
    }


    template<Arithmetic T, unsigned char D>
    requires (D == 2 || D == 3 || D == 4)
    [[nodiscard]] constexpr inline vec<T,D> abs(const vec<T,D> v) noexcept requires std::is_signed_v<T>
    { 
        if constexpr (D == 2)
        {
            return 
            {
                v.x < 0 ? -v.x : v.x,
                v.y < 0 ? -v.y : v.y,
            };
        }
        else if constexpr (D == 3)
        {
            return
            {
                v.x < 0 ? -v.x : v.x,
                v.y < 0 ? -v.y : v.y,
                v.z < 0 ? -v.z : v.z,
            };
        }
        else if constexpr (D == 4)
        {
            return
            {
                v.x < 0 ? -v.x : v.x,
                v.y < 0 ? -v.y : v.y,
                v.z < 0 ? -v.z : v.z,
                v.w < 0 ? -v.w : v.w,
            };
        }
    }


    template<Arithmetic T, unsigned char D>
    requires (D == 2 || D == 3 || D == 4)
    [[nodiscard]] constexpr vec<T,D> clamp(const vec<T,D> v, const T min, const T max) noexcept 
    { 
        vec<T,D> c{};
        if constexpr (D == 2)
        {
            if (v.x >= max) c.x = max;
            else if (v.x <= min) c.x = min;
            else c.x = v.x;

            if (v.y >= max) c.y = max;
            else if (v.y <= min) c.y = min;
            else c.y = v.y;
        }
        else if constexpr (D == 3)
        {
            if (v.x >= max) c.x = max;
            else if (v.x <= min) c.x = min;
            else c.x = v.x;

            if (v.y >= max) c.y = max;
            else if (v.y <= min) c.y = min;
            else c.y = v.y;

            if (v.z >= max) c.z = max;
            else if (v.z <= min) c.z = min;
            else c.z = v.z;
        }
        else if constexpr (D == 4)
        {
            if (v.x >= max) c.x = max;
            else if (v.x <= min) c.x = min;
            else c.x = v.x;

            if (v.y >= max) c.y = max;
            else if (v.y <= min) c.y = min;
            else c.y = v.y;

            if (v.z >= max) c.z = max;
            else if (v.z <= min) c.z = min;
            else c.z = v.z;

            if (v.w >= max) c.w = max;
            else if (v.w <= min) c.w = min;
            else c.w = v.w;
        }
        return c;
    }


    template<Arithmetic T, unsigned char D>
    requires (D == 2 || D == 3 || D == 4)
    [[nodiscard]] constexpr vec<T,D> min(const vec<T,D> a, const vec<T,D> b) noexcept 
    {
        if constexpr (D == 2)
        {
            return
            {
                a.x < b.x ? a.x : b.x,
                a.y < b.y ? a.y : b.y,
            };
        }
        else if constexpr (D == 3)
        {
            return
            {
                a.x < b.x ? a.x : b.x,
                a.y < b.y ? a.y : b.y,
                a.z < b.z ? a.z : b.z,
            };
        }
        else if constexpr (D == 4)
        {
            return
            {
                a.x < b.x ? a.x : b.x,
                a.y < b.y ? a.y : b.y,
                a.z < b.z ? a.z : b.z,
                a.w < b.w ? a.w : b.w,
            };
        }
    }


    template<Arithmetic T, unsigned char D>
    requires (D == 2 || D == 3 || D == 4)
    [[nodiscard]] constexpr vec<T,D> max(const vec<T,D> a, const vec<T,D> b) noexcept 
    {
        if constexpr (D == 2)
        {
            return
            {
                a.x > b.x ? a.x : b.x,
                a.y > b.y ? a.y : b.y,
            };
        }
        else if constexpr (D == 3)
        {
            return
            {
                a.x > b.x ? a.x : b.x,
                a.y > b.y ? a.y : b.y,
                a.z > b.z ? a.z : b.z,
            };
        }
        else if constexpr (D == 4)
        {
            return
            {
                a.x > b.x ? a.x : b.x,
                a.y > b.y ? a.y : b.y,
                a.z > b.z ? a.z : b.z,
                a.w > b.w ? a.w : b.w,
            };
        }
    }


    template<Arithmetic T, unsigned char D>
    requires (D == 2 || D == 3 || D == 4)
    [[nodiscard]] constexpr bool equal(const vec<T,D> a, const vec<T,D> b, const T epsilon) noexcept
    { return dist_sq(a, b) <= epsilon * epsilon; }


    template<Arithmetic T, unsigned char D>
    requires (D == 2 || D == 3 || D == 4)
    [[nodiscard]] constexpr FT<T> angle(const vec<T,D> a, const vec<T,D> b) noexcept
    { return std::acos(std::clamp(static_cast<FT<T>>(dot(a,b)) / (len(a) * len(b)), FT<T>(-1), FT<T>(1))); }


    template<Arithmetic T, unsigned char D>
    requires (D == 2 || D == 3 || D == 4)
    [[nodiscard]] constexpr vec<T,D> project(const vec<T,D> a, const vec<T,D> b) noexcept
    { return b * (dot(a, b) / dot(b, b)); }


    template<Arithmetic T, unsigned char D>
    requires (D == 2 || D == 3 || D == 4)
    [[nodiscard]] constexpr vec<T,D> reject(const vec<T,D> a, const vec<T,D> b) noexcept
    { return a - project(a, b); }




    using vec2i = vec<int, 2>;
    using vec2u = vec<unsigned int, 2>;
    using vec2f = vec<float, 2>;
    using vec2d = vec<double, 2>;
    using vec2s = vec<short, 2>;
    using vec2c = vec<char, 2>;


    using vec3i = vec<int, 3>;
    using vec3u = vec<unsigned int, 3>;
    using vec3f = vec<float, 3>;
    using vec3d = vec<double, 3>;
    using vec3s = vec<short, 3>;
    using vec3c = vec<char, 3>;


    using vec4i = vec<int, 4>;
    using vec4u = vec<unsigned int, 4>;
    using vec4f = vec<float, 4>;
    using vec4d = vec<double, 4>;
    using vec4s = vec<short, 4>;
    using vec4c = vec<char, 4>;
}


namespace std
{
    template<typename T, unsigned char D>
    struct formatter<vft::vec<T,D>> : std::formatter<T>
    {
        constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
        auto format(const vft::vec<T,D>& v, format_context& ctx) const 
        {
            if constexpr (D == 2) 
            {
                return std::format_to(ctx.out(), "x: [{}]; y: [{}]", v.x, v.y);
            }
            else if constexpr (D == 3) 
            {
                return std::format_to(ctx.out(), "x: [{}]; y: [{}]; z: [{}]", v.x, v.y, v.z);
            }
            else if constexpr (D == 4) 
            {
                return std::format_to(ctx.out(), "x: [{}]; y: [{}]; z: [{}]; w: [{}]", v.x, v.y, v.z, v.w);
            }
        }
    };
}
