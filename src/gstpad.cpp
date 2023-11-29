#include "gstpad.h"
#include <cstdint>
#include <gst/gst.h>
#include <iostream>
#include <mutex>

gulong gst_element_pad_add_probe(GstElement* elem, const char* probe_pad, GstPadProbeType mask,
								 GstPadProbeCallback callback, gpointer user_data, GDestroyNotify destroy_data)
{

	GstPad* pad = gst_element_get_static_pad(elem, probe_pad);
	if (!pad)
	{
		g_printerr("Failed to get %s pad in %s.\n", probe_pad, GST_ELEMENT_NAME(elem));
	}
	gulong res = gst_pad_add_probe(pad, mask, callback, user_data, destroy_data);
	gst_object_unref(pad);
	return res;
}

