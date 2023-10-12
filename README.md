# Intelligent_Traffic_Light_System

The Intelligent Traffic Light System is a sophisticated software solution that uses Python and C. The system's core functionality revolves around predicting traffic patterns by analyzing data collected from ultrasound sensors. The system effectively anticipates traffic density across various levels by employing a decision tree regressor model.

What it does
------------
- Traffic Signals are dumb. They just have a timer and they often need manual overrides depending on various traffic conditions.
- This is solved by using ultrasonic sensors (or inductive ground detection loops) at the junction of the traffic light.
- This allows us to detect different levels of traffic from each incoming road. Please refer to the below `How It Works` section to know more
- This data is timestamped and fed to a machine learning model. This model then predicts the traffic density from different sides of the junction and the traffic lights remain green for a longer or shorter time accordingly.
- This saves a lot of time spent on waiting for signals while the other side of the road doesn't need to be green for so much time.

How It Works
-------------
- A series of sensors is put on each incoming road, something similar to this:
![sensor-layout](https://cdn.discordapp.com/attachments/1080892669313699881/1142152738579415050/image.png)

- There are multiple sensors on each incoming road. If sensor 1 is blocked by a vehicle, that translates to traffic level 1. Sensor 2 = traffic level 2 and so on until sensor level n.
- This raw data is collected for a prototype on an Arduino and sent to Python through USB Serial along with a timestamp.
- Based on different traffic level predictions at different times of the day, we adjust the amount of time each side of the road gets a green signal. This prediction is done through ML algorithms explained below:

- Data from the ultrasound sensor which is in the form of levels is processed against the time of recording. A decision tree regressor model analyses this data to learn and predict traffic density levels. 
- This model also adapts to new data fed from the sensors. This allows us to override the predicted traffic level to the real time levels, in the case where traffic levels are unexpected.
- Safety Considerations: Pedestrian crossing times are considered in the signal light adjustments. We have also built in a failsafe if our sensors have failed. Additionally, varying vehicle types are accounted for in the optimisation process by using time buffers considering various scenarios like sudden spikes in traffic density from one side and so on.

## Maintainer

1. [Anurag Rao](https://github.com/anuragrao04)

[raoanu2004@gmail.com](mailto:raoanu2004@gmail.com)

2. [Shreya Gurram](https://github.com/bun137)

[gurram13775@gmail.com](mailto:gurram13775@gmail.com)


