#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H

#include <glib.h>

/// \brief The Buffer Ring main object
typedef struct _t_ring_buffer t_ring_buffer;

// Ring Buffer management functions

/// \brief Create new Ring Buffer with given size.
/// \param p_buffer_size size of the newly allocated RingBuffer
/// \return newly allocated Ring Buffer
t_ring_buffer *ring_buffer_new(gsize p_buffer_size);

/// \brief Free given RingBuffer.
/// It is up to the user to free every stored element, in order to avoid memory leaks.
/// \param p_buffer the Ring Buffer
/// \return newly allocated Ring Buffer
t_ring_buffer *ring_buffer_free(t_ring_buffer *p_buffer);

/// \brief Get the last item from the given Ring Buffer.
/// \param p_buffer the Ring Buffer
/// \return The last inserted item, or NULL if p_buffer is epmty
gpointer ring_buffer_pop(t_ring_buffer *p_buffer);

/// \brief Append to the given Ring Buffer the given element.
/// The oldest element will be lost if p_buffer is full.
/// \param p_buffer the Ring Buffer
/// \param p_value the value to be appended
/// \return The oldest item of p_buffer if p_buffer is full, or NULL
gpointer ring_buffer_push(t_ring_buffer *p_buffer, gpointer p_value);

/// \brief Get the number of items stored in p_buffer
/// \param p_buffer the Ring Buffer
gsize ring_buffer_stored_elements(t_ring_buffer *p_buffer);

#endif /* _RINGBUFFER_H */
