#include <Arduino.h>
#include <SPI.h>

class Atmega328p
{
private:
    /* data */
public:
    Atmega328p();
    bool AllowProgram();
    bool EraseChip();
    bool IsBusy();
    
    uint16_t ReadFuseBit();
    uint8_t ReadLockBit();
    uint8_t* ReadSignature();
    uint8_t ReadExtFuse();
    uint8_t ReadCalibration();
    uint8_t ReadEeprom(uint16_t addr);
    uint16_t ReadFlash(uint16_t addr);

    void ApplyFlash(uint16_t addr);
    void WriteByteEeprom(uint16_t addr, uint8_t data);
    void WriteLockBit(uint8_t lockbit);
    void WriteExtFuse(uint8_t extbit);
    void WriteFuse(uint16_t fusebit);

    void SetExtAddr(uint8_t extAddr);
    void SetFlash(uint16_t addr,uint16_t data);

    ~Atmega328p();
};

