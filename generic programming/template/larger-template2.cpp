template <class T>      /* File: larger-template2.cpp */
inline const T& larger(const T& a, const T& b)
{
    return (a > b) ? a : b;
}
