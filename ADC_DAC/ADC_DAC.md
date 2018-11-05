# ADC-DAC: Getting a sense of the world around you
So far, you have had really only looked at what your microcontroller has inside of it and how to get internal peripherals to behave with one another. Now it is time to start thinking about how the microcontroller can see the world. In previous labs, you have brought your controller from the mouth of the stork (or from the package from TI), fed it electrons, got it to say its first words, and helped it make its first steps. You have spent many sleepless night consoling your quadruplets when they threw tantrums, sometimes making you question your commitment to become a Junior ECE; but now it is time to send your little prodigies to kindergarten to make you proud. They will learn all about the world around them, not just the binary conditions of your dreary lifestyle.

## Temperature Sensors
At the heart of this project is the feedback loop which will provide your microcontroller with knowledge of how the system is currently behaving. To do this, you need to use a sensor which converts a physical phenomena into an electrical phenomena. The reason I don't say signal is because only some sensors produce a voltage or current. Some work on the resistance of the device, others on the inductance or capacitance of the material. Your goal is to make these sensors talk to your microncontroller, and this is done through the process of signal conditioning.

## Signal Conditioning - Thermistor
If you want to use a thermistor, you will need to build a circuit to convert a change in resistance to a change in voltage. You will also need to pick the correct values of resistances and gain to ensure that you have the maximum resolution in your signal. This sensor is also non-linear, so you need to look at the differences between linearization and utilizing the Stein-Hart Hart equation to determine the temperature.

## Signal Conditioning - PTAT
Since the PTAT provides you with a voltage which is proportional to the temperature, very little signal conditioning is needed in order to work with this device. You should be able to quickly develop code which can read from this sensor and output the temperature over UART.

## Displaying Temperature
You will need to take the temperature that you sense and not only use it in your control scheme, but also output to the user (me, the one testing it) over UART. This means that you will need to convert your measurement into ASCII so that a program like RealTerm can interpret what your system is saying. For this you do not have to worry about decimal places, so you could round up or just take the whole number.
