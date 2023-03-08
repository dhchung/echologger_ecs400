## Before you start

You need to change the mode into "Altimeter NMEA" using windows program.\
Also set Baudrate as 115200.

## Install

```bash
cd <your catkin workspace/src>
git clone git@github.com:dhchung/echologger_ecs400.git
cd <your catkin workspace> && catkin_make
```

## Run

```bash
rosrun echologger_ecs400 echologger_ecs400_node
```