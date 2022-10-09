#ifndef LAB4_VECTOR_CPP
#define LAB4_VECTOR_CPP
#include <iostream>
#include <cmath>

template<typename T>
class Vector {
    T *values = nullptr;
    int length{};
public:
    Vector() = default;
    ~Vector(){
        delete[] values;
    }

    Vector(const Vector<T>&  v){
        *this = v;
    }

    Vector(Vector<T> &&v){
        *this = std::move(v);
    }

    Vector<T>& operator=(const Vector<T>& v){
        if(this == &v) return *this;
        delete[] values;

        length = v.length;
        values = new T[v.length];
        memcpy(values, v.values, (length)* sizeof(T));
        return *this;
    }

    Vector<T>& operator=(Vector<T>&& v) noexcept {
        std::swap(length, v.length);
        std::swap(values, v.values);
        return *this;
    }

    explicit Vector(int l) : length(l) {
        values = new T[length];
    }

    int size() const {
        return length;
    }

    void append(T var) {
        values = static_cast<T*>(std::realloc(values, ++length * sizeof(T)));
        values[length - 1] = var;
    }

    T &operator[](int i) {
        if (i >= length || i < -length) throw "Out of bounds";
        if (i < 0) {
            return values[length + i];
        } else {
            return values[i];
        }
    }

    const T &operator[](int i) const{
        if (i >= length || i < -length) throw "Out of bounds";
        if (i < 0) {
            return values[length + i];
        } else {
            return values[i];
        }
    }

    bool is_empty(){
        return length == 0;
    }

    template<typename V>
    friend std::ostream &operator<<(std::ostream &out, const Vector<V> &v);
    template<class V>
    friend std::istream &operator>>(std::istream &in, Vector<V> &v);
    template<class V>
    friend Vector<bool> operator>(const Vector<V> &v1, const Vector<V> &v2);
    template<class V>
    friend Vector<bool> operator<(const Vector<V> &v1, const Vector<V> &v2);
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const Vector<T> &v) {
    if (v.size() == 0) return out << "Nothing to print!\n";
    for(int i = 0; i < v.size(); i++){
        out << v[i];
        if(i != v.size() - 1) out << ',';
    }
    return out;
}

template <typename T>
std::istream &operator>>(std::istream &in, Vector<T> &v) {
    T temp;
    in >> temp;
    v.append(temp);
    return in;
}
template <typename T>
Vector<bool> operator>(const Vector<T> &v1, const Vector<T> &v2) {
    if(v1.length != v2.length) throw "Size mismatch";
    Vector<bool> res(v1.length);
    for (int i = 0; i < v1.size(); i++){
        res[i] = v1[i] > v2[i];
    }
    return res;
}

template <typename T>
Vector<bool> operator<(const Vector<T> &v1, const Vector<T> &v2) {
    if(v1.length != v2.length) throw "Size mismatch";
    Vector<bool> res(v1.length);
    for (int i = 0; i < v1.size(); i++){
        res[i] = v1[i] < v2[i];
    }
    return res;
}
#endif