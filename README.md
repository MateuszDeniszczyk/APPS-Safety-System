# APPS-Safety-System

  **APPS** - *"Accelerator Pedal Position Sensor"*
  
   Based on Formula Student rules, I built a physical Arduino prototype of the APPS safety logic.

   Rules:
- Pedal travel is defined as percentage of travel from fully released position to a fully applied
position where 0 % is fully released and 100 % is fully applied.
- At least two separate sensors must be used as APPSs. The sensors may share the housing.
- If an implausibility occurs between the values of the APPSs and persists for more than
100 ms, the power to the motor(s) must be immediately shut down completely.

## Step-by-Step Process

**1.** At the beginning I connected two potentiometers and programmed the measurement at a baud rate of 115200 to make sure that won't become a bottleneck, since our system will be checking positions at 10ms intervals. 

**2.** First rule says that pedal travel should be defined as a percentage value, so I converted ADC (*Analog to digital converter*) to percentages, by dividing the sensor value by 1023.0 and multiplying it by 100.0 

**3.** To prevent blocking or stalling the processor, I completely eliminated the `delay()` function in favor of a non-blocking architecture using `millis()`. This ensures the safety logic operates in real-time without introducing hazardous timing delays, allowing the system to meet the required 100ms fault reaction condition.

**4.** With a 100 Hz sampling frequency, I implemented conditional logic using `if` statements to evaluate sensor plausibility. If the implausibility persists continuously for more than 100ms, the system turns off the drive signal and illuminates the red safety fault LED (simulating a motor power shut-off).

**5.** I encountered an issue where sending data at 100 Hz froze the system. Because of that, I created a function that sends the readings to the Serial Monitor at 4 Hz instead.



  

