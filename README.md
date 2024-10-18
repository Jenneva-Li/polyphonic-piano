# Polyphonic Piano



https://github.com/user-attachments/assets/d40ac370-c9ee-4f6b-87b4-035d13a49bd4



## Introduction[![](https://raw.githubusercontent.com/aregtech/areg-sdk/master/docs/img/pin.svg)](#introduction)

This polyphonic piano is essentially a push-button circuit that includes a switch, an LED (light-emitting diode), and a few resistors. This straightforward push-button circuit enables the Arduino to read the button's status while also controlling the LED's illumination through software. When the button is pressed, the LED lights up automatically and turns off when the button is released. The design of the circuit wiring is credited to <a href="https://www.hackster.io/">hackster.io</a>.</p>

This project was completed before I began university and any circuits courses, making it an excellent introductory project. It provided me with a foundational understanding of programming in Arduino and introduced me to the fundamentals of working with a breadboard. I learned to create and troubleshoot basic electronic systems, laying a solid groundwork for more advanced studies in electronics and programming. This early experience not only enhanced my technical skills but also sparked my interest in pursuing further projects in the field of electronics and firmware.
<p align="center">
  <img src="https://github.com/user-attachments/assets/8005d956-e1ff-4828-9437-f1dc701df08b" alt="full-view" width="500px">
</p>



---

## Design[![](https://raw.githubusercontent.com/aregtech/areg-sdk/master/docs/img/pin.svg)](#design)
The hardware for this project consists of four main components:
* Passive buzzer
* Illuminated key circuit (repeated five times for each button)
* A potentiometer (used as a tuning control)
* LCD display (indicate to the user what is the next note to play and detect when the user presses the button)

Libraries used for the software component of this project:
* DZLOnline TheSynth library (used to output sound through pin 11)
* Mozzi library (optional)

If the Mozzi library is used, the audio output will come from pin 9 instead. To avoid switching the output pin connected to the buzzer, the circuit shown above is wired so that only one pin, either pin 11 or pin 9, will be connected to the buzzer via a 100-ohm resistor. The other pin will be set up as an input and will not affect the sound.

<p align="center">
  <img src="https://github.com/user-attachments/assets/6f02592a-71c0-4762-a508-33cb2d618ba7" alt="schematic" width="800px">
</p>



---
<div align="right">[ <a href="#introduction">↑ Back to top ↑</a> ]</div>
