/*
 * Client.h
 *
 *      Author: lucas
 */


#include <sys/neutrino.h>

#ifndef CLIENT_H_
#define CLIENT_H_

//namespace SC
//{
	class Client
	{
		#define NO_OF_MSGS 15
		#define MY_PULSE_CODE _PULSE_CODE_MINAVAIL

		const char* Attach_Point= "someReceiver";

		typedef struct _pulse header_t; // Fist header used by GNS and application

		public:
			void do_something();
			int sender();
			static void handle_QNX_pulse(header_t hdr, int rcvid);
			static void handle_appl_pulse(header_t hdr, int rcvid);
			static void handle_pulse(header_t hdr, int rcvid);
			static void handle_ONX_IO_msg(header_t hdr, int rcvid);
			static void handle_app_msg(header_t hdr, int rcvid);
			int receiver();
			int qnet_init(int argc,const char argv);
	};
//}

#endif /* CLIENT_H_ */
