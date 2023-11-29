void gst_element_wait_event(GstElement* el, GstMessageType type, GstClockTime time, WaitEventCallback cb, gpointer user_data)
{
	/* Listen to the bus */
	GstBus* bus = gst_element_get_bus(el);

	GstMessage* msg = nullptr;

	while ((msg = gst_bus_timed_pop_filtered(bus, time, type)))
	{
		/* Parse message */
		if (cb != NULL)
		{
			if (cb(el, msg, user_data))
			{
				gst_message_unref(msg);
				break;
			}
		}
		gst_message_unref(msg);
	}

	/* Free resources */
	gst_object_unref(bus);
}
