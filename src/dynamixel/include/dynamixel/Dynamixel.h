#ifndef DYNAMIXEL_H_
#define DYNAMIXEL_H_

typedef unsigned char byte;

#include <map>
#include <vector>
#include <string>
#include "SerialPort.h"
#include "Utils.h"

static const int BufferSize=1024;
byte buffer[BufferSize];
byte bufferIn[BufferSize];

class Dynamixel {
 public:
  Dynamixel();
  Dynamixel(byte id, SerialPort* port);

  void Configure();

  int SendReceiveCommand(std::string command, std::string address, 
			 std::vector<byte> data,
			 std::vector<byte>* outData);

  int getPosition();
  int setPosition(int position);
  
  int setSpeed(int speed);

  int setCCWAngleLimit(int limit);
  int setCWAngleLimit(int limit);

 private:

  byte _id;
  SerialPort* _port;
  int _recvWaitTimeMS; //=50

  int FormatCommand(byte command, byte address, std::vector<byte>, byte* buffer);

 protected:
  std::map<std::string, byte> Addresses;
  std::map<std::string, byte> Commands;
  std::map<std::string, int> ResponseLength;

};

class AX12 : Dynamixel {
 public:
  void Configure();

  static float posToAngle(short pos);
  static short angleToPos(float angle);

  int setCCWComplianceMargin(byte margin);
  int setCWComplianceMargin(byte margin);

  int setCCWComplianceSlope(byte slope);
  int setCWComplianceSlope(byte slope);
};

class MX28 : Dynamixel {
 public:
  void Configure();

  static float posToAngle(short pos);
  static short angleToPos(float angle);

  int setPGain(byte pGain);
  int setIGain(byte iGain);
  int setDGain(byte dGain);
};

#endif
