#ifndef ESLOV_HANDLER_H_
#define ESLOV_HANDLER_H_

#include "Arduino.h"
#include "Wire.h"

#define ESLOV_MAX_LENGTH      255
#define ESLOV_DEFAULT_ADDRESS 0x55

enum EslovOpcode {
  ESLOV_DFU_INTERNAL_OPCODE,
  ESLOV_DFU_EXTERNAL_OPCODE,
  ESLOV_SENSOR_CONFIG_OPCODE,
  ESLOV_SENSOR_STATE_OPCODE
};

enum EslovState {
  ESLOV_AVAILABLE_SENSOR_STATE = 0x00,
  ESLOV_READ_SENSOR_STATE = 0x01
};

class EslovHandler {
  public:
    EslovHandler();
    virtual ~EslovHandler();

    void begin();

    static void onReceive(int length);
    static void onRequest();

  private:
    void receiveEvent(int length);
    void requestEvent();

    void dump();

    int _rxIndex;
    uint8_t _rxBuffer[ESLOV_MAX_LENGTH];

    EslovState _state;
};

extern EslovHandler eslovHandler;

#endif
