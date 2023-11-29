#pragma once

#include <gst/gst.h>

extern "C" gulong gst_element_pad_add_probe(GstElement* elem,
                                            const gchar* probe_pad,
                                            GstPadProbeType mask,
                                            GstPadProbeCallback callback,
                                            gpointer user_data          = NULL,
                                            GDestroyNotify destroy_data = NULL);

