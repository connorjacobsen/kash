#ifndef KSIGNAL_H_
#define KSIGNAL_H_


/**
 * Defines the class of functions that accept a single integer
 * and return nothing at all.  This function class is compatible
 * with the types of functions that can be installed to handle
 * signals.
 */
typedef void (*handler_t)(int);

/**
 * Installs the specified function to catch and handle any 
 * and all signals of the specified category.  The old handler
 * is returned.
 */
handler_t
install_signal_handler(int signum, handler_t handler);

#endif /* KSIGNAL_H_ */