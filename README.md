# m5atom-relais
M5Atom based relais control that can be controlled by the M5Atom button or the serial port.
Relais is connected to GPIO 33.

## Serial interface

Open the serial port with 115200 baud

| Command          | Description                          |
| ---------------- | ------------------------------------ |
| relais:on        | Turn on the connected relais         |
| relais:off       | Turn off the connected relais        |
| relais:get       | Get the current relais state         |
| display:[VALUE]  | VALUE: 0-255, dim the M5Atom display |
