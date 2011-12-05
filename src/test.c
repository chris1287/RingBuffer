#include <glib.h>
#include "ringbuffer.h"

int main(int argc, const char *argv[])
{
	t_ring_buffer *r = NULL;
	int elem1 = 4;
	int elem2 = 6;
	int elem3 = 2;
	int elem4 = 3;
	gpointer oldelem = NULL;
	gpointer popelem = NULL;

	g_message("Test RingBuffer");
	
	r = ring_buffer_new(2);
	g_assert(NULL != r);

	oldelem = ring_buffer_push(r, &elem1);
	g_assert(NULL == oldelem);
	g_assert(1 == ring_buffer_stored_elements(r));

	oldelem = ring_buffer_push(r, &elem2);
	g_assert(NULL == oldelem);
	g_assert(2 == ring_buffer_stored_elements(r));
	
	oldelem = ring_buffer_push(r, &elem3);
	g_assert(NULL != oldelem && *((int *)oldelem) == elem1);
	g_assert(2 == ring_buffer_stored_elements(r));
	
	oldelem = ring_buffer_push(r, &elem4);
	g_assert(NULL != oldelem && *((int *)oldelem) == elem2);

	popelem = ring_buffer_pop(r);
	g_assert(NULL != popelem && *((int *)popelem) == elem4);

	popelem = ring_buffer_pop(r);
	g_assert(NULL != popelem && *((int *)popelem) == elem3);

	popelem = ring_buffer_pop(r);
	g_assert(NULL == popelem);
	g_assert(0 == ring_buffer_stored_elements(r));

	r = ring_buffer_free(r);
	g_assert(NULL == r);

	g_message("Test RingBuffer complete");

	return 0;
}
