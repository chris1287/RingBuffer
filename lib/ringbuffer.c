#include "ringbuffer.h"
#include <glib.h>

struct _t_ring_buffer
{
	GQueue *ring_queue;
	gsize ring_size;
};

#ifdef TRACE
#define DBG(fmtstr, args ...) \
	g_print("(DBG) " fmtstr "\n", ##args)
#else
#define DBG
#endif

t_ring_buffer *ring_buffer_new(gsize p_buffer_size)
{
	t_ring_buffer *l_rb_new = NULL;

	DBG("ring_buffer_new has been called - buffer size %"G_GSIZE_FORMAT"", p_buffer_size);
	
	if(p_buffer_size == 0) // gsize is unsigned, so it is nonsense to test against < 0
	{
		g_warning("Trying to create empty ring_buffer");
		return NULL;
	}

	// Create new struct
	l_rb_new = g_new0(t_ring_buffer, 1);
	g_assert(NULL != l_rb_new);

	// Create new queue
	l_rb_new->ring_queue = g_queue_new();
	g_assert(NULL != l_rb_new);

	// Fill fields
	l_rb_new->ring_size = p_buffer_size;

	return l_rb_new;
}

t_ring_buffer *ring_buffer_free(t_ring_buffer *p_buffer)
{
	DBG("ring_buffer_free has been called");

	if(NULL == p_buffer)
	{
		g_warning("Trying to free NULL ring buffer");
		return NULL;
	}

	// It's up to the user to free each element
	g_queue_free(p_buffer->ring_queue);
	g_free(p_buffer);

	return NULL;
}

gpointer ring_buffer_push(t_ring_buffer *p_buffer, gpointer p_value)
{
	DBG("ring_buffer_push has been called");
	gsize l_buffer_size = 0;
	gpointer l_oldest_value = NULL;

	if(NULL == p_buffer)
	{
		g_warning("Trying to fill NULL ring buffer");
		return NULL;
	}

	l_buffer_size = g_queue_get_length(p_buffer->ring_queue);

	if(p_buffer->ring_size == l_buffer_size)
	{
		DBG("Ring Buffer is full - losing oldest element");
		l_oldest_value = g_queue_pop_head(p_buffer->ring_queue);
	}

	DBG("Append new element - currently %"G_GSIZE_FORMAT" elements stored", l_buffer_size);
	g_queue_push_tail(p_buffer->ring_queue, p_value);

	// Return the lost element to the user in order to allow memory free
	return l_oldest_value;
}

gpointer ring_buffer_pop(t_ring_buffer *p_buffer)
{
	DBG("ring_buffer_pop has been called");
	gsize l_buffer_size = 0;
	gpointer l_newest_value = NULL;

	if(NULL == p_buffer)
	{
		g_warning("Trying to pop from NULL ring buffer");
		return NULL;
	}

	l_buffer_size = g_queue_get_length(p_buffer->ring_queue);

	if(0 == l_buffer_size)
	{
		DBG("Ring Buffer is empty");
		return NULL;
	}

	l_newest_value = g_queue_pop_tail(p_buffer->ring_queue);
	DBG("Remove newest element - currently %"G_GSIZE_FORMAT" elements stored", l_buffer_size - 1);

	return l_newest_value;
}

gsize ring_buffer_stored_elements(t_ring_buffer *p_buffer)
{
	DBG("ring_buffer_stored_elements has been called");

	if(NULL == p_buffer)
	{
		g_warning("Trying to retrieve size of NULL ring buffer");
		return 0;
	}

	return g_queue_get_length(p_buffer->ring_queue);
}
