#pragma once

#include <gst/gst.h>

 template <typename T>
  class gst_iterator
  {
    GstIterator* _m;
    GValue _val;

public:
    explicit gst_iterator(GstIterator* it)
        : _m(it)
    {
        _val = G_VALUE_INIT;
    }
    gst_iterator(const gst_iterator& other)
        : _m(gst_iterator_copy(other._m))
    {
        g_value_copy(other._val, _val);
    }

    bool operator==(const gst_iterator& other) const;
    bool operator!=(const gst_iterator& other) const;

    typename T::reference operator * () const { return *_cur; }

    gst_iterator& operator++()
    {
        if (++_cur == _end)
            _cur = _beg;
        return *this;
    }
    gst_iterator operator++(int)
    {
        gst_iterator copy(*this);
        ++*this;
        return copy;
    };
  };
