---

typora-root-url: ./picture
---

1. Chinese version of the README -> please [click here](./README.md)
  
   Dobot   TCP-IP-CR-CPP-V4   secondary development API interface ([TCP-IP-CR-CPP-V4 README](https://github.com/Dobot-Arm/TCP-IP-CR-CPP-V4))
   
   # 1\. Introduction
   
   **TCP-IP-CR-CPP-V4** is a software development kit designed by Dobot based on the C language of TCP/IP protocol. It is developed based on C language, follows the Dobot-TCP-IP control communication protocol, connects to the device terminal via Socket, and provides users with an easy-to-use API interface. Through TCP-IP-CR-CPP-V4, users can quickly connect to the Dobot device and carry out secondary development to control and use the device.
   
   ## Pre-dependency
   
   * You can connect your computer to the network interface of the controller with a network cable, and then set the fixed IP to be in the same network segment as the controller IP. You can also connect your computer to the controller via wireless connection.
     
     When connected to LAN1 via wired connection: IP: 192.168.5.1; When connected to LAN2 via wired connection: IP: 192.168.200.1; Wireless connection: IP: 192.168.9.1
   
   * Ubuntu 14.04/Ubuntu 16.04/Ubuntu 18.04, x86 and ARM (Nvidia TX2)
   
   * Windows 7/10, Visual Studio 2015 Update3/2017/2019
     
     * C++11 compiler
   
   * This API interface and Demo are applicable to V4 and above controller version of CR-V4 series
   
   ## Version and Release
   
   ### Current version V1.0.0.0
   
   | Version| Date|
   |:----------:|:----------:|
   | V1.0.0.0| 2024-03-07|

   # 2\. Technical support
   
   If you have any questions or suggestions, you can contact Dobot's technical support:
   
   * Send an email to futingxing@dobot-robots.com with a detailed description of the problem you are experiencing and the scenario in which you are using it.
   * Send an email to wuyongfeng@dobot-robots.com with a detailed description of the problem you are experiencing and the scenario in which you are using it.
   
   # 3\. TCP-IP-CR-CPP-V4 control protocol
   
   As the communication based on TCP/IP has high reliability, strong practicability and high performance with low cost, many industrial automation projects have a wide demand for controlling robots based on TCP/IP protocol. Dobot robots, designed on the basis of TCP/IP protocol, provide rich interfaces for interaction with external devices.
   
   Robot status:
   
       1. Error status is the first priority. If the robot reports an error and is not enabled, it returns the error status.
       
       2. Power-off status is the second priority. If the robot is not powered on and not enabled, it returns the power-off status.
       
       3. Collision status is the third priority. If the robot is in a collision and the script is paused, it returns the collision status.
       
       4. Brake-ON status is the fourth priority. If the brake of the robot is switched on but the robot is not enabled, it returns the brake-ON status.
       
       The other statuses are fed back according to the actual situation.
   
   Port feedback:
   
       Port 29999 is responsible for receiving the commands related to settings and motion control by sending and receiving.
       
       Port 30004 (hereinafter referred to as the real-time feedback port) feeds back robot information every 8ms.
       
       Port 30005 feeds back robot information every 200ms.
       
       Port 30006 is a configurable port to feed back robot information (feed back every 50ms by default).
       
       Cancel port 30003.
   
   For more details, see **Dobot TCP_IP Remote Control Interface Guide**.

# 4\. Obtaining TCP-IP-CR-CPP-V4

1. Obtain the secondary development API program of Dobot  TCP-IP-CR-CPP-V4 from GitHub.
  
   ```bash
   `git clone https://github.com/Dobot-Arm/TCP-IP-CR-CPP-V4 4.git
   ```

2. Refer to the corresponding README.md file for use.

# 5\. File and class descriptions

1. The API directory contains various classes that encapsulate the related functions of CR, which are written based on C++.

2. [api/rapidjson](https://github.com/Tencent/rapidjson) is Tencent’s open source json parsing library.

3. Class descriptions in the API directory:
  
   | Parameter| Default Value|
   |----------|----------|
   | BitConverter| Encapsulates the conversion of bytes to underlying types|
   | DescartesPoint| Encapsulation of Cartesian coordinate structure|
   | JointPoint| Encapsulation of joint point coordinate structure|
   | FeedbackData| Encapsulation of feedback data structure|
   | ErrorInfoBean| Encapsulation of error message|
   | ErrorInfoHelper| Error message helper class|
   | DobotClient| Interface class based on TCP communication, encapsulates the basic business of communication|
   | Dashboard| Derived from DobotClient, it implements the specific basic functions of the robot|
   | DobotMov| Derived from DobotClient, it implements the specific motion functions of the robot|
   | Feedback| Derived from DobotClient, it implements the specific feedback services of the robot|
   | | |


4. `alarm_controller.json`: Warning alarm profile, `alarm_servo.json`: Servo alarm profile.

**CDobotClient**

Interface class based on TCP communication, encapsulates the basic business of communication.

```c++
  class CDobotClient
  {
  public:
   }
```

**Dashboard**

Derived from DobotClient, it can deliver some settings-related commands to the robot. It implements the specific basic functions of the robot.

```c++
class CDashboard : public CDobotClient
  {
  public:
   }
```

**Feedback**

Derived from DobotClient, it implements the specific feedback services of the robot can can provide real-time feedback on robot status information.

```c++
  class CFeedbackData
  {
  public:
  };
```

**For details, see the PythonExample.py and the Demo example.**

# 6\. Common problem

* TCP connection:
  
  Port 29999 can be connected by one client at a time;
  
  Ports 30004 30005 30006 can be connected by multiple clients at the same time;
  
  Port 29999 has mode restriction. Before opening, you need to set the robot to TCP mode, otherwise it cannot respond and return “Control Mode Is Not Tcp” after the command is delivered. There is no mode restriction for real-time feedback ports 30004, 30005, 30006.

* To obtain the robot status, you can monitor the return value of RobotMode().
  
  1. When the controller is in initializing status, it returns 1;
  
  2. When the robot status is not 0 or 1, the robot initialization is completed;
  
  3. When the robot is in power-off status, it returns 3;
  
  4. When the robot is initialized but not enabled, it returns 4;
  
  5. When the robot is enabled but idle, it returns 5, indicating that it can receive motion commands normally;
  
  6. movj, script, and other queue commands are running status and return 7;
  
  7. movJog is a single motion status, it return 8; no power-on status.
    
     | Mode| Description| Note|
     |----------|----------|----------|
     | 1| ROBOT_MODE_INIT| Initialized status|
     | 2| ROBOT_MODE_BRAKE_OPEN| Brake switched on|
     | 3| ROBOT_MODE_POWEROFF| Power-off status|
     | 4| ROBOT_MODE_DISABLED| Disabled (no brake switched on)|
     | 5| ROBOT_MODE_ENABLE| Enabled (idle)|
     | 6| ROBOT_MODE_BACKDRIVE| Drag|
     | 7| ROBOT_MODE_RUNNING| Running status (script, TCP queue)|
     | 8| ROBOT_MODE_SINGLE_MOVE| Single motion status (jog)|
     | 9| ROBOT_MODE_ERROR| Error status|
     | 10| ROBOT_MODE_PAUSE| Pause status|
     | 11| ROBOT_MODE_COLLISION| Collision status|


* Commands for different status
  
  ​    *Commands can be executed for error status: ClearError(), GetErrorID(), EmergeStop(), RobotMode(), the rest are rejected commands and return -2;
  
  ​    *Commands can be executed for emergency stop status: ClearError(), GetErrorID(), EmergeStop(), RobotMode(), the rest are rejected commands and return -3;
  
  ​    *Commands can be executed for power-off status: ClearError(), GetErrorID(), EmergeStop(), RobotMode(), PowerOn(), the rest are rejected commands and return -4;
  
  ​	*TCP commands are all immediate return commands except EnableRobot() and PowerOn(). The return of the command only represents successful delivering, not completion of execution.

* Coordinate system
  
  After entering TCP/IP mode, the system sets the user/tool coordinate system to 0 by default. It automatically restores the value of the user/tool coordinate system after exiting TCP/IP mode.
  
  ​      Global coordinates: the coordinates set by User() and Tool() commands are the global coordinates, which takes effect for all commands after setting;
  
  ​      Local coordinates: the optional parameters (user/tool) in the motion command are only effective in the current motion command, and will be restored to the global coordinates after the execution of the current command.

* The algorithm allows a queue depth of 64, 64 queued commands can be processed continuously at the same time. If the queued commands sent to the port exceed the queue depth, the port will not be disconnected, and the command interface will return -1 and the command will not be executed.

* The queue command is an immediate return command. The successful return of the interface only means that it was delivered successfully, it does not mean that the execution is completed. If it is judged that the execution is completed, it needs to be combined with CommandID and RobotMode to make a comprehensive judgment.

* The servo run time represents the accumulated time after the robot is enabled, and the controller power-on time represents the time after the controller is powered on, so the controller power-on time is always greater than the servo run time.

* The collision status is not an error, there is no collision error returned in GetErrorID(). You can query the collision status by RobotMode(), which returns 11. You can clear the collision status by ClearError().

* After a collision, you can deliver an error clearing command to clear the collision status, and the robot can be run again without re-enabling.

* After switching to TCP/IP mode, the speed/acceleration/user/tool coordinate system parameters will be set to the default values, so there is no need to call the EnableRobot() command to set the default parameters.

* The return value of the TCP queue command only indicates whether the parameters and syntax of the command conform to the specification, it does not indicate whether the command is successfully executed or not. The TCP queue command returns when it is delivered, and the return of 0 only means that it is delivered successfully, not that it can be executed successfully.

* If an error occurs in parameter type/number of the TCP command , the system will alarm directly and will not give a 0 to handle it, and the command will not be delivered to the algorithm.

* After triggering the emergency stop signal, the robot stops running by default. If it does not stop after 500ms, it will be powered off. If it stops, it will not be powered off. In general, the robot will not be powered off after an emergency stop.

* After setting the default gateway, the default gateway data will be saved and the value will not be changed after a restart.

* The Enable command only executes the enable action without other parameter settings. It will not clear the kinematic parameters and coordinate system parameters.

* The Pause() and Continue() commands are effective for script, and the motion commands (queue-related) are also effective. The robot enters the pause status and the algorithmic queue pauses after calling the Pause() command. You can continue to run the queue commands using the Continue() command. The MovJog command cannot be paused or continued.

# 7\. Example

* Dobot-Demo realizes TCP control of the robot and other interactions. It connects to the control port and feedback port of the robot respectively. It delivers motion commands to robot, and handles the abnormal status of the robot, etc.

1. Main thread: Connect to the control port, motion port, and feedback port of the robot respectively. Enable the robot.

![](/main_en.png)

2. Feedback status thread: Real-time feedback of robot status information.

![](/feed_en.png)

3. Robot motion thread: Deliver motion commands to robot

![](/move_en.png)

Arrival signal

The queue command is an immediate return command. The successful return of the interface only means that it was delivered successfully, it does not mean that the execution is completed. If it is judged that the execution is completed, it needs to be combined with

* If the current CommandID is greater than the CommandID that delivered, it means the delivered queue command is completed.

* If the current CommandID is equal to the CommandID that delivered, and RobotMode command returns a value of 5, it means the delivered queue command is completed.

4. Exception handling thread: Judge and handle the abnormal status of the robot

![](/exception_en.png)

*

**Steps to run the Demo:**

1. Obtain the secondary development API program of Dobot TCP-IP-CR-CPP-V4 from GitHub.
  
   ```bash
   `git clone https://github.com/Dobot-Arm/TCP-IP-CR-CPP-V4.git
   ```

2. Connect to the robot via LAN1 interface, and set the local IP address to 192.168.5.X
  
   Control Panel >> Network and Internet >> Network Connections
   
   ![](/netConnect_en.png)
   
   Select the connected Ethernet >> Right click >> Properties >> Internet Protocol Version (TCP/IP-V4)
   
   Modify the IP address to 192.168.5.X
   
   ![](/updateIP_en.png)

3. Open the DobotStudio Pro, connect to the robot, and set the robot mode to **TCP**.
  
   ![](./checkTcpMode_en.png)

4. Run program
  
   1. Obtain the secondary development API program of Dobot TCP-IP-CR-CPP from Dobot GitHub.
     
      ```bash
      `git clone https://github.com/Dobot-Arm/TCP-IP-CR-CPP-V4.git`
      ```
   
       
   
   2. Enter the directory TCP-IP-CR-CPP/CppDemo/ folder to compile the Demo program
   
   ```bash
   cd  TCP-IP-CR-CPP-V4/CppDemo/
   bash compileDemo.sh
   ```
   
   3. Run the Demo
   
   ```bash
   bash runDemo.sh
   ```
   
   **Common problem**

**Problem 1: Make sure the robot is in TCP/IP mode**

**Problem 2: Confirm the Cartesian coordinates of the different models (CR) in the Demo**

**Make sure the robot is in a safe position before running the Demo to prevent unnecessary collisions.**