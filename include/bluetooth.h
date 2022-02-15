#ifndef bluetooth_h
#define bluetooth_h

#define LEN_COMMAND 32

#include "Arduino.h"

class Bluetooth {
		private:
			char string[LEN_COMMAND];
		public:
			void init(void);
			int dataAvailable(void);
			int isConnected(void);
			void send(char*);
			char* read(void);
};

static Bluetooth bt;
#endif
