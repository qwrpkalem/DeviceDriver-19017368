#include <stdexcept>
#include "device_driver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice *hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int beforeread = (int)(m_hardware->read(address));
    int prevread = beforeread;


    for (int i = 0; i < 4; i++) {
        beforeread = (int)(m_hardware->read(address));
        if (prevread != beforeread) {
            prevread = -1;
        }
    }

    // Need to read fivetimes
    if (prevread == -1) {
        throw std::runtime_error("Read resut not same error.");
    }

    return prevread;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}
