#include <array>

int bladesign(int a, int b) {
    int swapcount = 0;
    int bscan = 0;
    while (a != 0 && b != 0) {
        swapcount += (a & 1) * bscan;
        bscan += b & 1;
        a >>= 1;
        b >>= 1;
    }
    return bscan %2 == 0 ? 1 : -1;
}

template <int dimensions> struct multivector {
    std::array<double, 1<<dimensions > components;
    multivector<dimensions> operator *(multivector<dimensions> &other) {
        multivector<dimensions> result;
        for (int i = 0; i < result.components.size(); ++i) {
            result.components[i] = 0;
        }
        for (int i = 0; i < this->components.size(); ++i) {
            for (int j = 0; j < other.components.size(); ++j) {
                result.components[i ^ j] += bladesign(i, j) * this->components[i] * other.components[j];
            }
        }
        return result;
    }

    multivector<dimensions> operator +(multivector<dimensions> &other) {
        multivector<dimensions> result;
        for (int i = 0; i < result.components.size(); ++i) {
            result.components[i] = this->components[i] + other.components[i];
        }
        return result;
    }
    multivector<dimensions> operator -(multivector<dimensions> &other) {
        multivector<dimensions> result;
        for (int i = 0; i < result.components.size(); ++i) {
            result.components[i] = this->components[i] - other.components[i];
        }
        return result;
    }
};

template<int dimensions> multivector<dimensions> gscalar(double v) {
    multivector<dimensions> result;
    result.components[0] = v;
    return result;
}

template<int dimensions> multivector<dimensions> dot(multivector<dimensions> a, multivector<dimensions> b) {
    return gscalar<dimensions>(0.5)*(a*b + b*a);
}

template<int dimensions> multivector<dimensions> wedge(multivector<dimensions> a, multivector<dimensions> b) {
    return gscalar<dimensions>(0.5)*(a*b - b*a);
}

multivector<3> gvec3(double x, double y, double z) {
    multivector<3> result;
    result.components[1] = x;
    result.components[2] = y;
    result.components[4] = z;
    return result;
}