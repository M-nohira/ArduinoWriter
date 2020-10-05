#include "../include/Atmega328p.h"

bool Atmega328p::AllowProgram()
{
    SPI.transfer(0xAC);
    uint8_t result = SPI.transfer(0x53);
    return  (result == 0x53)? true:false;
}

bool Atmega328p::EraseChip()
{
    SPI.transfer(0xAC);
    SPI.transfer(80);
    delay(15);  //min Delay = 10.5ms
    return true;
}

bool Atmega328p::IsBusy()
{
    SPI.transfer(0xF0);
    SPI.transfer(0x00);
    SPI.transfer(0x00);
    return (SPI.transfer(0x00) & 0b1 ) == 1 ? true: false;
}

uint16_t Atmega328p::ReadFuseBit()
{
    while (IsBusy()) delay(1);
    uint16_t result = 0x0000;   
    SPI.transfer(0x58);
    SPI.transfer(0x08);
    result += SPI.transfer(0x00) << 8;
    
    SPI.transfer(0x50);
    SPI.transfer(0x00);
    result += SPI.transfer(0x00);

    return result;
}

uint8_t Atmega328p::ReadLockBit()
{
    while (IsBusy()) delay(1);
    SPI.transfer(0x58);
    SPI.transfer(0x00);
    return SPI.transfer(0x00); 
}

uint8_t* Atmega328p::ReadSignature()
{
    while (IsBusy()) delay(1);
    uint8_t result[3];
    for(int itr = 0; itr < 3; itr++)
    {
        SPI.transfer(30);
        SPI.transfer(00);
        result[itr] = SPI.transfer(itr);
    }
    return result;
}

uint8_t Atmega328p::ReadExtFuse()
{
    while (IsBusy()) delay(1);
    SPI.transfer(0x50);
    SPI.transfer(0x08);
    return SPI.transfer(0x00);
}

uint8_t Atmega328p::ReadCalibration()
{
    while (IsBusy()) delay(1);
    SPI.transfer(0x38);
    SPI.transfer(0x00);
    return SPI.transfer(0x00);
}

uint8_t Atmega328p::ReadEeprom(uint16_t addr)
{
    while (IsBusy()) delay(1);
    SPI.transfer(0xA0);
    SPI.transfer(addr >> 8);
    return SPI.transfer(addr & 0xFF);
}

uint16_t Atmega328p::ReadFlash(uint16_t addr)
{
    while (IsBusy()) delay(1);
    uint16_t result;
    SPI.transfer(0x28);
    SPI.transfer(addr >> 8);
    result += SPI.transfer(addr & 0xFF) << 8;
    SPI.transfer(0x20);
    SPI.transfer(addr >> 8);
    result += SPI.transfer(addr & 0xFF) & 0xFF;
    return result;
}

void Atmega328p::ApplyFlash(uint16_t addr)
{
    while (IsBusy()) delay(1);
    SPI.transfer(0x4C);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr & 0xFF);
    SPI.transfer(0x00);

    delay(9); //min Delay = 4.5ms
}

void Atmega328p::WriteByteEeprom(uint16_t addr, uint8_t data)
{
    while (IsBusy()) delay(1);
    SPI.transfer(0xC0);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr & 0xFF);
    SPI.transfer(data);

    delay(7); //min Delay = 3.6ms
}

void Atmega328p::WriteLockBit(uint8_t lockbit)
{
    while (IsBusy()) delay(1);
    SPI.transfer(0xAC);
    SPI.transfer(0xE0);
    SPI.transfer(0x00);
    SPI.transfer(lockbit);

    delay(9); //min Delay = 4.5ms
}

void Atmega328p::WriteExtFuse(uint8_t extbit)
{
    while (IsBusy()) delay(1);
    SPI.transfer(0xAC);
    SPI.transfer(0xA4);
    SPI.transfer(0x00);
    SPI.transfer(extbit);

    delay(9); //min Delay = 4.5ms
}

void Atmega328p::WriteFuse(uint16_t fusebit)
{
    while (IsBusy()) delay(1);
    SPI.transfer(0xAC);
    SPI.transfer(0xA8);
    SPI.transfer(0x00);
    SPI.transfer(fusebit >> 8);

    delay(9); //min Delay = 4.5ms

    while (IsBusy()) delay(1);
    SPI.transfer(0xAC);
    SPI.transfer(0xA0);
    SPI.transfer(0x00);
    SPI.transfer(fusebit & 0xFF);

    delay(9); //min Delay = 4.5ms
}

void Atmega328p::SetExtAddr(uint8_t extAddr)
{
    while (IsBusy()) delay(1);
    SPI.transfer(0x4D);
    SPI.transfer(0x00);
    SPI.transfer(extAddr);
    SPI.transfer(0x00);
}

void Atmega328p::SetFlash(uint16_t addr, uint16_t data)
{
    while (IsBusy()) delay(1);
    SPI.transfer(0x48);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr & 0xFF);
    SPI.transfer(data >> 8);

    while (IsBusy()) delay(1);
    SPI.transfer(0x40);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr & 0xFF);
    SPI.transfer(data & 0xFF);
}

Atmega328p::Atmega328p(/* args */)
{
    SPI.begin();
    SPI.beginTransaction(SPISettings(4000000,MSBFIRST,SPI_MODE0));
}



Atmega328p::~Atmega328p()
{  
    SPI.endTransaction();
    SPI.end();
}