#include <Arduino.h>
#include <Wire.h>

class eeprom
{
private:
    /* data */
public:
    eeprom(/* args */);
    void WriteByte(uint16_t addr,uint8_t data);
    bool WritePage(uint16_t addr,uint8_t* data);
    uint8_t ReadByte(uint16_t addr);
    uint8_t* ReadBytes(uint16_t addr, int size);
    ~eeprom();
};

eeprom::eeprom(/* args */)
{
}

eeprom::~eeprom()
{
}
