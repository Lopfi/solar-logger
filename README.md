# Solar Logger

This is a simple box with an ESP32 with a LC12S, build to replace a DataBox24G from All of Solar, which communicates with a solar inverter to collect data on power generation.

![pcb](https://github.com/user-attachments/assets/24637ad5-8ef4-46bf-b4c1-0602e10ca683)

All configuration is in `/firmware/include/config-example.h` just change the values to your needs and rename it to `config.h`.

For more information on how the hardware works and how I did the reverse engineering visit the hackaday project [here](https://hackaday.io/project/186606-solar-inverter-datalogger-improvements).

If anyone is interested in a the PCB with LC12S and ESP32 for easy communication with the panel and integration into any smarthome system feel free to contact me.
