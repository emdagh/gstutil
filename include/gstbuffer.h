#pragma once

template <typename OutputIt>
void gst_buffer_get_meta_filtered(GstBuffer* buf, GType type, OutputIt o_first)
{
    gpointer state = NULL;
    // GstMeta *
    while (GstMeta* meta = gst_buffer_iterate_meta_filtered(buf, &state, type))
    {
        *o_first++ = meta;
    }
}

