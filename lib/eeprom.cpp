#include "../include/eeprom.h"

#define cs 0x37

eeprom::eeprom()
{
    
}

///一バイト書き込む
void eeprom::WriteByte(uint16_t addr,uint8_t data)
{
    Wire.beginTransmission(cs);
    Wire.write(addr >> 8);          //High Byte
    Wire.write(addr & 0x00FF);      //LOW  Byte
    Wire.write(data);               //Data  
    Wire.endTransmission();
}

bool eeprom::WritePage(uint16_t addr,uint8_t* data)
{
    if(sizeof(data) > 128) return false;

    Wire.beginTransmission(cs);
    Wire.write(addr >> 8);
    Wire.write(addr & 0x00FF);
    for(int n = 0; n < sizeof(data); n++)
        Wire.write(data[n]);
    Wire.endTransmission();

    return true;
}

uint8_t eeprom::ReadByte(uint16_t addr)
{
    Wire.beginTransmission(cs);
    Wire.write(addr >> 8);
    Wire.write(addr & 0x00FF);
    Wire.requestFrom(addr,1);
    uint8_t result = Wire.read();
    Wire.endTransmission();
    return result;
}

uint8_t* eeprom::ReadBytes(uint16_t addr, int size)
{
    uint8_t result[size];
    int itr = 0;
    Wire.beginTransmission(cs);
    Wire.write(addr >> 8);
    Wire.write(addr & 0x00FF);
    Wire.requestFrom(addr, size);
    while (Wire.available())
    {
        result[itr] = Wire.read();
        itr++;
    }
    return   result;
}