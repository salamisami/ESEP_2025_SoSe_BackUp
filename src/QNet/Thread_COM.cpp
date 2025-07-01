#include "Thread_COM.h"
#include <iostream>
using namespace Thread_COM;

//================================================= contructors & destructors =================================================

Sender::Sender(const char* name) {
    receiver_coid = name_open(name,NAME_FLAG_ATTACH_GLOBAL);
    if (receiver_coid < 0) {
        switch (errno) {
            case EINTR:
                std::cerr << "Error: name_open() operation interrupted by signal" << std::endl;
                // Consider retrying the operation if appropriate for your application
                break;
            case EINVAL:
                std::cerr << "Error: Invalid arguments passed to name_open()" << std::endl;
                // Check the 'name' parameter and flags
                break;
            case ELOOP:
                std::cerr << "Error: Too many symbolic links or prefixes in name path" << std::endl;
                // Simplify the path or check for cyclic symbolic links
                break;
            case EMFILE:
                std::cerr << "Error: Process file descriptor limit reached" << std::endl;
                // Close unused file descriptors or increase the limit
                break;
            case ENAMETOOLONG:
                std::cerr << "Error: Name string exceeds maximum allowed length" << std::endl;
                // Use a shorter name or check PATH_MAX
                break;
            case ENFILE:
                std::cerr << "Error: System file table is full" << std::endl;
                // Wait and retry later or report system resource issue
                break;
            case ENOENT:
                std::cerr << "Error: Name '" << name << "' does not exist" << std::endl;
                // Verify the name exists or handle missing resource
                break;
            default:
                std::cerr << "Error: Unknown error in name_open(): " << strerror(errno) << std::endl;
                break;
        }
	}
    else {
                std::cout << "Success: Name '" << name << "' connected" << std::endl;
                // Verify the name exists or handle missing resource
    }
}
Sender::~Sender(){
    name_close(receiver_coid);
}

void Sender::send_event(int8_t event_code, int event_value, int priority) {
    MsgSendPulse(receiver_coid, priority, event_code, event_value);
}

int Sender::getcoid(){
    return receiver_coid;
}

Receiver::Receiver(const char* name) {
    gns_name = name;

    std::string str_gns_name(gns_name);

    attach = name_attach(NULL, gns_name, NAME_FLAG_ATTACH_GLOBAL);
    if(attach == NULL) {
        printf("%s: ", gns_name);
        perror(" name_open on Dispatcher failed");
        exit(-1);
    }

    if(str_gns_name.compare(FBM_N_DISPATCHER) == 0) {
        return;
    }

}

Receiver::~Receiver(){
    name_detach(attach, 0);
}




void Receiver::handle_QNX_IO_msg(_pulse* msg, int rcvid) {
    switch(msg->code) {
        case _PULSE_CODE_DISCONNECT:
            printf("%s _PULSE_CODE_DISCONNECT\n", gns_name);
            /* A client disconnected all its connections (called
            * name_close() for each name_open() of our name) or
            * terminated. */
            ConnectDetach(msg->scoid);
            break;
        case _PULSE_CODE_UNBLOCK:
            printf("%s received _PULSE_CODE_UNBLOCK\n", gns_name);
            /* REPLY blocked client wants to unblock (was hit by
            * a signal or timed out). It's up to you if you
            * reply now or later. */
            break;
        case 12:
        	printf("%s Sending EOK, connect\n", gns_name);
            MsgReply(rcvid, EOK, NULL, 0);
            break;
        default:
            /* A pulse sent by the kernel like
            * _PULSE_CODE_COIDDEATH or _PULSE_CODE_THREADDEATH
            * from the kernel? */
            printf("%s received some other QNX pulse msg code: %d\n", gns_name, msg->code);
            break;
    }
}

void Receiver::handle_app_msg(_pulse* msg, int rcvid) {
    printf("%s: Unexpected message type 0x%04X\n", gns_name, msg->type);
    MsgError(rcvid, EPERM);
}

void Receiver::handle_QNX_pulse(_pulse* msg, int rcvid) {
    switch(msg->code) {
        case _PULSE_CODE_DISCONNECT:
            printf("%s _PULSE_CODE_DISCONNECT\n", gns_name);
            /* A client disconnected all its connections (called
            * name_close() for each name_open() of our name) or
            * terminated. */
            ConnectDetach(msg->scoid);
            break;
        case _PULSE_CODE_UNBLOCK:
            printf("%s received _PULSE_CODE_UNBLOCK\n", gns_name);
            /* REPLY blocked client wants to unblock (was hit by
            * a signal or timed out). It's up to you if you
            * reply now or later. */
            break;
        default:
            /* A pulse sent by the kernel like
            * _PULSE_CODE_COIDDEATH or _PULSE_CODE_THREADDEATH
            * from the kernel? */
            printf("%s received some other QNX pulse msg code: %d.\n", gns_name, msg->code);
            break;
    }
}

//===================================================== public functions =====================================================


int Receiver::receive_event(_pulse* event) {
    int rcvid = MsgReceive(attach->chid, event, sizeof(_pulse), NULL);
    if(rcvid == -1) {
        printf("%s: ", gns_name);
        perror(" MsgReceived failed");
        return -1; //return MsgReceived failed
    }
    if(rcvid == 0) {
        if((_PULSE_CODE_MINAVAIL <= event->code) && (event->code <= _PULSE_CODE_MAXAVAIL)) {
            return 0; //return Event received
        } else {
            handle_QNX_pulse(event, rcvid);
            return 1;
        }
    }
    if((_IO_BASE <= event->type) && (event->type <= _IO_MAX)) {
        // Some QNX IO msg generated by gns was received
        handle_QNX_IO_msg(event, rcvid);
        return 1;
    }
    handle_app_msg(event, rcvid);
    return -1;
}

int Receiver::getchid(){
    return attach->chid;
}
