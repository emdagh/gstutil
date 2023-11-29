#pragma once

#include <memory>
#include <stdexcept>

#define THROW_NOT_IMPLEMENTED() throw not_implemented(__FUNCTION__)

class not_implemented : std::runtime_error
{
public:
    explicit not_implemented(const char* what)
        : std::runtime_error(what)
    {
    }
    virtual ~not_implemented()
    {
    }
};

template <typename T>
inline void deleter(T* obj)
{
    THROW_NOT_IMPLEMENTED();
};

template <typename T>
using gst_unique_ptr = std::unique_ptr<T, void (*)(T*)>; // decltype(deleter)>; // void (*)(GstObject*)>;

template <typename T>
gst_unique_ptr<T> gst_make_unique(T* t)
{
    return gst_unique_ptr<T>(t, deleter<T>);
}
