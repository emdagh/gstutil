#pragma once

#include <gst/gst.h>

#if GST_VERSION_MAJOR >= 1 && GST_VERSION_MINOR >= 18

template <typename OutputIt>
void gst_bin_get_sinks_by_factory_name(GstBin* bin, const char* name, OutputIt o_first)
{

    GstIterator* it = gst_bin_iterate_all_by_element_factory_name(bin, name);
    GValue val      = G_VALUE_INIT;
    gboolean done   = FALSE;
    do
    {
        switch (gst_iterator_next(it, &val))
        {
        case GST_ITERATOR_OK:
        {
            auto* sink = GST_ELEMENT(g_value_get_object(&val));
            *o_first++ = sink;
            g_value_reset(&val);
            break;
        }
        case GST_ITERATOR_RESYNC:
            gst_iterator_resync(it);
            break;
        case GST_ITERATOR_ERROR:
            GST_ERROR("Error iterating over %s's sink elements", GST_ELEMENT_NAME(bin));
        case GST_ITERATOR_DONE:
            g_value_unset(&val);
            done = TRUE;
            break;
        }
    } while (!done);

    gst_iterator_free(it);
}

#endif

template <typename OutputIt>
void gst_bin_get_sources(GstBin* bin, OutputIt o_first)
{
    GstIterator* it = gst_bin_iterate_sources(bin);
#if 1
    gst_iterator_foreach(
        it,
        +[](const GValue* val, gpointer user_data) {
            OutputIt o_first = static_cast<OutputIt>(user_data);
            *o_first++ = GST_ELEMENT(g_value_get_object(&val));
            g_value_reset(&val);
        },
        o_first);
#else
    GValue val      = G_VALUE_INIT;
    gboolean done   = FALSE;
    do
    {
        switch (gst_iterator_next(it, &val))
        {
        case GST_ITERATOR_OK:
        {
            auto* sink = GST_ELEMENT(g_value_get_object(&val));
            *o_first++ = sink;
            g_value_reset(&val);
            break;
        }
        case GST_ITERATOR_RESYNC:
            gst_iterator_resync(it);
            break;
        case GST_ITERATOR_ERROR:
            GST_ERROR("Error iterating over %s's sink elements", GST_ELEMENT_NAME(bin));
        case GST_ITERATOR_DONE:
            g_value_unset(&val);
            done = TRUE;
            break;
        }
    } while (!done);
#endif
    gst_iterator_free(it);
}

template <typename OutputIt>
void gst_bin_get_sinks(GstBin* bin, OutputIt o_first)
{
    GstIterator* it = gst_bin_iterate_sinks(bin);
#if 1
    gst_iterator_foreach(
        it,
        +[](const GValue* val, gpointer user_data) {
            OutputIt o_first = static_cast<OutputIt>(user_data);
            auto* sink = GST_ELEMENT(g_value_get_object(&val));
            *o_first++ = sink;
            g_value_reset(&val);
        },
        o_first);
#else
    GValue val    = G_VALUE_INIT;
    gboolean done = FALSE;
    do
    {
        switch (gst_iterator_next(it, &val))
        {
        case GST_ITERATOR_OK:
        {
            auto* sink = GST_ELEMENT(g_value_get_object(&val));
            *o_first++ = sink;
            g_value_reset(&val);
            break;
        }
        case GST_ITERATOR_RESYNC:
            gst_iterator_resync(it);
            break;
        case GST_ITERATOR_ERROR:
            GST_ERROR("Error iterating over %s's sink elements", GST_ELEMENT_NAME(bin));
        case GST_ITERATOR_DONE:
            g_value_unset(&val);
            done = TRUE;
            break;
        }
    } while (!done);
#endif
    gst_iterator_free(it);
}

template <typename OutputIt>
void gst_bin_get_elements_by_class_name(GstBin* bin, const gchar* className, OutputIt o_first)
{

    GstIterator* it = gst_bin_iterate_elements(bin);
#if 1
    gst_iterator_foreach(
        it,
        +[](const GValue* val, gpointer user_data) {
            auto o_first = static_cast<OutputIt>(user_data);
            auto* obj = g_value_get_object(&val);
            auto* cmp = G_OBJECT_CLASS_NAME(G_OBJECT_GET_CLASS(obj));
            if (!strcmp(cmp, className))
            {
                *o_first++ = GST_ELEMENT(obj);
            }
            g_value_reset(&val);
        },
        o_first);
#else
    GValue val      = G_VALUE_INIT;
    gboolean done   = FALSE;
    do
    {
        switch (gst_iterator_next(it, &val))
        {
        case GST_ITERATOR_OK:
        {
            auto* obj = g_value_get_object(&val);
            auto* cmp = G_OBJECT_CLASS_NAME(G_OBJECT_GET_CLASS(obj));
            if (!strcmp(cmp, className))
                *o_first++ = GST_ELEMENT(obj);
            g_value_reset(&val);
            break;
        }
        case GST_ITERATOR_RESYNC:
            gst_iterator_resync(it);
            break;
        case GST_ITERATOR_ERROR:
            GST_ERROR("Error iterating over %s's sink elements", GST_ELEMENT_NAME(bin));
        case GST_ITERATOR_DONE:
            g_value_unset(&val);
            done = TRUE;
            break;
        }
    } while (!done);
#endif
    gst_iterator_free(it);
}

template <typename OutputIt>
void gst_bin_get_elements_by_interface(GstBin* bin, GType type, OutputIt o_first)
{

    GstIterator* it = gst_bin_iterate_all_by_interface(bin, type);
    GValue val      = G_VALUE_INIT;
    gboolean done   = FALSE;
    do
    {
        switch (gst_iterator_next(it, &val))
        {
        case GST_ITERATOR_OK:
        {
            auto* sink = GST_ELEMENT(g_value_get_object(&val));
            *o_first++ = sink;
            g_value_reset(&val);
            break;
        }
        case GST_ITERATOR_RESYNC:
            gst_iterator_resync(it);
            break;
        case GST_ITERATOR_ERROR:
            GST_ERROR("Error iterating over %s's sink elements", GST_ELEMENT_NAME(bin));
        case GST_ITERATOR_DONE:
            g_value_unset(&val);
            done = TRUE;
            break;
        }
    } while (!done);

    gst_iterator_free(it);
}
