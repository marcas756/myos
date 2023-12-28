# myos

MyOs based on Contiki-Os concepts for memory constrained microcontrollers. Strictly C99.

## Library
- Circular singly linked list (abstract datatype)
- Circular doubly linked list (abstract datatype)
- Circular item buffer (ring buffer, queue)
- Buffer (byte buffer, item buffer)
- Fixed size blocks allocation (memory pool allocation)
- Binary constants 
- Bitarray (abstract datatype)
- Bit manipulation
- flexible debug output system

## Operating System
- Protothreads (slightly modified Contiki implementation)
- Processes and Events (inspired by Contiki, but reimplemented)
- Timestamp, base for all timer implementations
- Timer, base for all timer implementations
- Process Timer (ptimer) base class for ctimer and etimer
- Event Timer (delayed event delivery to any process), derived from ptimer
- Callback Timer (delayed function call), derived from ptimer
- Real Timer, high resolution free running hardware timer for timing measurements and real time operations

## User Interface
- User Interface LEDs
- User Interface Buttons
- Graphical User Interface

  For further information on MyOs consult :
  [MyOs Wiki](https://github.com/marcas756/myos/wiki)
  [MyOs Doxygen Documentation](tbd)

