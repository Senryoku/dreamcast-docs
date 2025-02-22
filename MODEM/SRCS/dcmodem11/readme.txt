Changes
-------
v1.1
 - Changed the user accessable (non internal) function names to use a KOS
   style naming convention
 - Made some internal functions actually internal
 - Added modem_has_data
 - Added descriptions for all user accessable functions

Important
---------
- TMU interrupt 1 is modified and disabled during and after the modem
  detection sequence
- The detection sequence needs to have very precise timing. It's ok to have
  interrupt handlers enabled for the other TMUs but be aware that errors
  could result if too much of the CPU's time is consumed while in these
  interrupts.
- When dialing, it takes about 1 second for the modem to open the phone line
  and detect a dial tone. If there's no dial tone present then it will take
  1.5 seconds for the dialing procedure to exit. It takes about 1 or more
  additional seconds to dial the number that you gave the dialing procedure.
  Dialing times will, of course, vary depending how long the number you are
  dialing is. When you make the modem driver dial a number you should expect
  that it will cause your program to be interrupted for about 1.5 or more
  seconds.
- It is recommended that you always use the automatic bit rate (speed)
  detection as the parameter for the mode set procedure. If you set a specific
  speed there's a chance that the connection may not be successful if the
  remote computer that you are connecting to is configured to operate at a
  different bit rate than the one you have specified.
- You can only safely read and write data from the FIFO buffers 256 bytes at
  a time. Doing more than this usually seems to create some unwanted feedback
  on the other side.
- The read and write functions will not always read or write the number of
  bytes that you want them to! Check the return values. They tell you the
  number of bytes that were actually written/read.
      This is something that anyone who works with these communication devices
  (even working with high speed network connections) needs to deal with,
  because the operating environment for any such device is not always ideal.
- Don't use the read or write functions inside of the callback functions
  that are used when the modem asserts an IRQ.

Description of the modes of operation
-------------------------------------
The general connection routine: (This applys to ALL modes of operation!)
  1.) Set the mode of operation
      * If the mode is "remote mode" then make sure you dial a number before
        going to the next step.
  2.) Wait until modemIsConnecting returns zero. You can do other things while
      you're waiting, but don't try to access the modem until this happens.
  3.) When modemIsConnecting returns zero, check the return value of
      modemIsConnected. This will tell you if the modem has actually
      established a connection or if there was an error during the connection
      attempt. You can use modemGetLastError to get the error code if, at this
      point, modemIsConnected returns zero.
  4.) If modemIsConnected returns a non zero value (meaning that a connection
      has been established), then you can go on to transmit data, etc.

1.) Remote mode
2.) Direct mode -
    This mode assumes that you want to make a direct connection with another
    modem. You should plug your Dreamcast's modem into the "line" jack of
    the modem that you're connecting to.

    As soon as this mode is set, the line is opened and the driver waits until
    the start of a handshake signal signal has been detected. It will then
    attempt to connect automaticaly. The Dreamcast will always answer
    handshake signals not send them, this is mostly because it works out very
    well if you want to establish a direct connection between your Dreamcast
    and a computer.

3.) Answer mode

Functions and their return values
---------------------------------
int modem_init(void);
Description: Detects and gets the modem ready for use
Returns:     A non zero if a modem was found, or zero if there's no modem
             available.

void modem_shutdown(void);
Description: Shuts the modem down, deallocates memory, etc.
             Note: You do not need to call this function. It's called
                   automatically at exit!

int modem_set_mode(int mode, mspeed_t speed);
Description: Sets a mode of operation for the modem.
Arguments:   mode  - MODEM_MODE_REMOTE, MODEM_MODE_DIRECT, or
                     MODEM_MODE_ANSWER
             speed - Only use the MODEM_SPEED_* constants defined in modem.h!
Returns:     A non zero value if the mode was set, or zero if there was an
             error.

void modem_disconnect(void);
Description: Disconnects the modem if it's connected.

int modem_is_connecting(void);
Description: Determines if the modem is in the process of connecting to a
             remote modem.
Returns:     A non zero value if a connection is being established, or zero
             if a connection has been established or an error has occured.

int modem_is_connected(void);
Description: Determines if the modem has connected to a remote modem.
Returns:     A non zero value if a connection has been established, or zero
             if a connection has not been established.

unsigned long modem_get_connection_rate(void);
Description: Gets the connection speed in bits per second (bps)

int modem_read_data(unsigned char *data, int size);
Description: Reads data from the RX FIFO buffer.
Arguments:   data - A pointer to a location in memory where the data's to be
                    stored.
             size - The number of bytes to read from the RX FIFO buffer.
Returns:     The number of bytes that were actually read.

int modem_write_data(unsigned char *data, int size);
Description: Writes data to the TX FIFO buffer.
Arguments:   data - A pointer to a location in memory where the data that is
                    to be written is stored.
             size - The number of bytes to write.
Returns:     The number of bytes actually written.

int modem_has_data(void);
Description: Determines if there's any data in the RX FIFO buffer.
Returns:     A non zero value if there's data waiting to be read in the RX
             FIFO buffer, or zero if there's no data in the RX FIFO buffer.
