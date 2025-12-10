# ESP32-Button
ESP32 with a single button for one action and 0 current draw when not in use


<img width="1225" height="830" alt="image" src="https://github.com/user-attachments/assets/6852d044-2685-4be1-bc45-77165970eb9c" />


I wanted to create a simple ESP32 PCB whose sole job was to send a single command over the Internet and then go completely dormant. Basically, the PCB, which is powered by 2x AA batteries, consumes 0 current when dormant (so not deep sleep) the button activates the power circuit to turn the ESP32 to run whatever code you want and then it shuts itself off.
The power design utilizes an boost circuit with an Enable pin that is pulled high by the button and then a GPIO on the ESP is used to keep it high until code execution is finished.

The use case I wanted it for was a simple Timesheet update for starting and finishing freelance work. The Google Sheets script is attached as well for those interested in this use case.
