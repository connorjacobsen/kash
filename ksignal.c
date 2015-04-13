#include <signal.h>
#include <assert.h>
#include "include/ksignal.h"

handler_t install_signal_handler(int signum, handler_t handler)
{
    struct sigaction action, old_action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask); // blocks sigs of type being handled
    action.sa_flags = SA_RESTART; // restart syscalls if possible
    int success = sigaction(signum, &action, &old_action);
    assert(success >= 0);
    return old_action.sa_handler;
}
