from rpi_rf import RFDevice


def sendcode(code):
    print('sending code...')
    rfdevice = RFDevice(17)
    rfdevice.enable_tx()

    protocol = 1
    pulselength = 350

    rfdevice.tx_code(code, protocol, pulselength)
    rfdevice.cleanup()
    return
