#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H

#include <glib.h>

typedef struct _t_ring_buffer t_ring_buffer;

// Ring Buffer management functions
// TODO: complete documentation

/// \brief Create new Ring Buffer with given size
/// \param p_buffer_size size of the newly allocated RingBuffer
/// \return newly allocated Ring Buffer
t_ring_buffer *ring_buffer_new(gsize p_buffer_size);

/// \brief Free given RingBuffer.
/// It is up to the user to free every stored element, in order to avoid memory leaks.
/// \param p_buffer_size size of the newly allocated RingBuffer
/// \return newly allocated Ring Buffer
t_ring_buffer *ring_buffer_free(t_ring_buffer *p_buffer);
gpointer ring_buffer_pop(t_ring_buffer *p_buffer);
gpointer ring_buffer_push(t_ring_buffer *p_buffer, gpointer p_value);
gsize ring_buffer_stored_elements(t_ring_buffer *p_buffer);

#endif /* _RINGBUFFER_H */
