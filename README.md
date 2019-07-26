# EE3 FinalReport
This is the final project for my EE3 course.

## Assignment
Students were divided into groups of two then tasked with assembling and programming a small electric vehicle to follow a black line path as quickly as possible. A report was then written describing the implementation of the vehicle.

## Project Contents
* **pathFollower.ino**:  The primary program for the path following task. Uses a PID (Position Integral Derivative) controller to keep the car on the marked path.
* **schoolZone.in**: Extra Credit task of the project. Requires the car to slow down in the 'school zone' and use the shaft encoders to control the speed using a negative feedback loop.
  * **leftShaftEncoder.ino** and **rightShaftEncoder.ino**: These programs work with the schoolZone program by reporting the speed of their respective motor to the main program.
* **FinalReport.pdf**: This report outlines how the code was implemented and what design choices were made.

## Contributors
Kameron Carr (@kamalca) and Hien Ho (@hho065)

## Disclaimer
This project is posted to showcase my work. This project is not to be used for the purposes of cheating.
