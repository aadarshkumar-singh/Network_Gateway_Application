# Network Gateway Application developed using C++ 
## Objective
The goal of the project is to develop a network gateway application, which reads data from a port and sends it out
through another port. In between, the data is packaged according the port requirements.
  * For instance the receiver port is a UART (Packagesize 1) and the sender is a CAN(Packagesize 8)
  * The data is received bytewise (== packagesize 1) from the UART (in the rx_isr)
  * All bytes are stored in the UART port RX ringbuffer
  * The data is read out by the gateway transmit method and stored in the CAN port TX ringbuffer
  * The port TX isr reads out the data from the ringbuffer, creates packages (packagesize 8) and sends the packages to the hardware driver
##Addtional Requirements : 
The implementation shall be generic, i.e. any combination (set during runtime) of ports shall be supported
  * UART to CAN
  * CAN to UART
  * UART to UART
  * CAN to CAN
  * Any new additional port
