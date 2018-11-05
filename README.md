# Milestone 2: Closed Loop Systems
One of the bigger applications of Embedded Systems is the Closed Loop control system. Think about it, from cars to drones to amplifiers and more, this idea of a system being controlled by feedback is found practically everywhere. To begin to understand how these systems operate and what role your microcontroller plays, you will be asked to do three main tasks for this Milestone:
* ADC/DAC
* Open Loop System Characterization
* Closed Loop System Characterization

All of these parts are tightly integrated into the overall milestone project, so you will not be asked for a README for each part. Instead your project will just need ONE README that discusses what has been done as well as how to implement the code onto your board. Again, think of this like if you saw this project online and wanted to implement it. The README would talk about what it is quickly, what is the hardware required, and how to get it down to your boards. Your code still needs to be commented well.


## Grading
Your grade will be dependent not only on your code, commenting, and report, but also on the performance of the system during your testing. The Milestone Grade is broken down as:

* 30% App Note
* 30% Code and commenting
* 10% Room Temp to Hot
* 10% Hot to Warm
* 10% Warm to Hot
* 10% Disturbance Resilience

For the actual tests, your system will be graded on two main factors, stability and steady state performance. Each of the 10% portions will be broken up into 7% and 3% for the Steady State and Stability Respectively. All grades are given in the following form GroupOf2/GroupOf3 since larger groups will be expected to have better performance. The brackets for these grades are:

### Steady State (7%)
* 7 points: Steady state performance is within 3C/1.5C of the specified temperature
* 6 points: Steady State performance is within 5C/2.5C of the specified temperature
* 5 points: Steady State performance is within 7C/3.5C of the specified temperature
* 4 points: Steady State performance is within 9C/4.5C of the specified temperature
* 3 points: Steady State performance is within 11C/5.5C of the specified temperature
* 2 points: Steady State performance is above/below 11C/5.5C of the specified temperature
* 0 points: No steady state temperature was able to be recorded.

### Stability (3%)
* 3 points: The system shows little to no oscillations around 3C/1.5C of the specified temperature after the specified time for testing.
* 2 points: The system shows steady but small oscillations around 5C/2.5C of the operating point.
* 1 point: The system has heavy oscillation but is still stable. This may audible in the fan changing speed rapidly.
* 0 points: There is no stability or the system temperature can not be measured.


## System Performance
For testing, you will be asked to do a few scenarios where your system will try to stabilize around a specific temperature within a period of time. You will be asked to start with your system at room temperature and bring the regulator up to a specific temperature. While your system is approaching steady state, the main thing we are going to care about is the speed at which you approach it as well as the ability for your system to stay stable. After this first test, you will then be asked to bring your system back to a temperature warmer than room temperature and be analyzed again. Then your system will need to bring the chip up to a mildly hot temperature, stabilize, then we will introduce "disturbances" in your system to see how it reacts. These will include increasing/decreasing the voltage across the regulator, a heavier load for your regulator to drive, and adding an additional fan.

* Room Temp -> Medium/Hot
* Medium/Hot -> Slightly Warm
* Slightly Warm -> Medium/Hot
* Add Disturbances

In summary, the testing procedure will take about 20-30 minutes in total, so you MUST come to the lab period ready to demonstrate in a group setting. If you do not come ready, your team will be penalized and we will try to accommodate an additional testing time. If you can not show your system by that time, the portion of your grade depending on the system performance will become a zero. This doesn't mean you will get a zero for the milestone, but your grade will suffer.


## Deliverables
Along with your performance marked during testing, you will need to submit your code along with an App Note in your team repository. These team repositories will be kept private this time around in an attempt to allow each team to get creative. Feel free to utilize code from other labs you have done (which is actually the point of making you all do these labs in the first place) and look around and research what other people do for these types of systems.

In your app note and your repository, I expect you to have a section dedicated to the hardware used in the system and how it is connected. You will need to specify what sensors you are using, why use those sensors, and how you condition the signal before taking it into your microcontroller. As for the software side of things, your big focus in both App Note and code comments should be on the method in how to get information from your system, how to place the set point, and most importantly how your control algorithm works. This can not be stressed enough.

You will need to include a block diagram to show your system components and define the signals going between them and their relationship to each other. This really needs to stay "high level" and should look at the system components in terms of transfer functions. In your App Note, you need to include small portions of code exemplifying your algorithm and approach. As with Milestone 1, you need to really give us engineering analysis and decision making as to why you went with your algorithm and talk about what lead you to pick your specific implementation. Do we expect you to be Control Theory experts? No, but we do expect you to be able to take steps towards analyzing what is not desirable in your system and how to remedy it.
