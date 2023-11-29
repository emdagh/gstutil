#pragma once

#include "stringutil.h"
#include <gst/gst.h>
#include <sstream>
#include <string>

#define GST_META_ANY_API_GET_TYPE(T) gst_meta_any_api_get_type<T>(clean_meta_name(#T "API"))
#define GST_META_ANY_GET(buf, T) ((GstAnyMeta<T>*)gst_buffer_get_meta(buf, GST_META_ANY_API_GET_TYPE(T)))
#define GST_META_ANY_ADD(buf, T)                                                                                       \
    ((GstAnyMeta<T>*)gst_buffer_add_meta(buf, gst_meta_any_get_info<T>(clean_meta_name(#T)), (gpointer)NULL))
#define DEBUG_METHOD()                                                                                                 \
    {                                                                                                                  \
        g_debug("%s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);                                                       \
    }
#define DEBUG_VALUE_OF(VAL) g_debug("%s=%s", #VAL, lexical_cast(VAL).c_str())
#define DEBUG_VALUE_AND_TYPE_OF(VAL)                                                                                   \
    {                                                                                                                  \
        g_debug("%s=%s (%s)", #VAL, lexical_cast(VAL).c_str(), demangle(typeid(VAL).name()).c_str());                  \
    }

template <typename T>
gboolean gst_meta_any_init(GstMeta* meta, gpointer params, GstBuffer* buffer);
template <typename T>
gboolean gst_meta_any_transform(GstBuffer* transbuf, GstMeta* meta, GstBuffer* buffer, GQuark type, gpointer data);
template <typename T>
void gst_meta_any_free(GstMeta* meta, GstBuffer* buffer);

static inline std::string clean_meta_name(const std::string& in)
{
    return replace_all(in, "::", "_");
}

template <typename T, typename std::enable_if<std::is_default_constructible<T>::value, bool>::type = true>
struct GstAnyMeta
{
    GstMeta meta;
    T data;
};

template <typename T>
GType gst_meta_any_api_get_type(const std::string& name)
{

    static volatile GType type;
    static const gchar* tags[] = {NULL};

    if (g_once_init_enter(&type))
    {
        DEBUG_METHOD();
        DEBUG_VALUE_OF(name);
        GType _type = gst_meta_api_type_register(name.c_str(), tags);
        g_once_init_leave(&type, _type);
    }
    return type;
}

template <typename T>
const GstMetaInfo* gst_meta_any_get_info(const std::string& name)
{
    static const GstMetaInfo* meta_info = NULL;

    if (g_once_init_enter(&meta_info))
    {
        DEBUG_METHOD();
        std::string api = std::string(name) + "API";
        DEBUG_VALUE_OF(name);
        DEBUG_VALUE_OF(api);
        GType type = gst_meta_any_api_get_type<T>(api);
        const GstMetaInfo* meta = gst_meta_register(type,
                                                    name.c_str(), //"GstAnyMeta",
                                                    sizeof(GstAnyMeta<T>),
                                                    (GstMetaInitFunction)gst_meta_any_init<T>,
                                                    (GstMetaFreeFunction)gst_meta_any_free<T>,
                                                    (GstMetaTransformFunction)gst_meta_any_transform<T>);
        g_once_init_leave(&meta_info, meta);
    }
    return meta_info;
}

template <typename T>
gboolean gst_meta_any_init(GstMeta* meta, gpointer params, GstBuffer* buffer)
{
    DEBUG_METHOD();
    GstAnyMeta<T>* any = (GstAnyMeta<T>*)meta;
    if (any)
    {
        memset(&any->data, 0, sizeof(T));
    }

    return TRUE;
}
template <typename T>
gboolean gst_meta_any_transform(GstBuffer* transbuf, GstMeta* meta, GstBuffer* buffer, GQuark type, gpointer data)
{
    DEBUG_METHOD();
    GstAnyMeta<T>*smeta, *dmeta;
    smeta = (GstAnyMeta<T>*)meta;

    dmeta = GST_META_ANY_ADD(transbuf, T);
    if (!dmeta)
        return FALSE;
    dmeta->data = smeta->data;
    return TRUE;
}

template <typename T>
void gst_meta_any_free(GstMeta* meta, GstBuffer* buffer)
{
    DEBUG_METHOD();
    GstAnyMeta<T>* any = (GstAnyMeta<T>*)meta;
    // using S = decltype(any->data);
    any->data.~T();
}
