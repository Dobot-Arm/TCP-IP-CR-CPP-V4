---
typora-root-url: ./picture
---

1. English version of the README -> please [click here](./README-EN.md)

   Dobot   TCP-IP-CR-CPP-V4   二次开发api接口 （ [TCP-IP-CR-CPP-V4 README](https://github.com/Dobot-Arm/TCP-IP-CR-CPP-V4) ）

   

   # 1. 简介

   TCP-IP-CR-CPP-V4 是为 Dobot 公司旗下基于TCP/IP协议的C++的封装设计的软件开发套件。它基于 C++ 语言开发，遵循Dobot-TCP-IP控制通信协议，通过Socket与机器终端进行Tcp连接，  并为用户提供了易用的Api接口。 通过TCP-IP-CR-CPP-V4 ，用户可以快速地连接Dobot机器并进行二次开发,  实现对机器的控制与使用。

   

   ## 前置依赖

   * 电脑可用网线连接控制器的网口，然后设置固定 IP，与控制器 IP 在同一网段下。也可无线连接控制器。

     有线连接时连接LAN1：ip为192.168.5.1 , 有线连接时连接LAN2：ip为192.168.200.1,  无线连接：ip为192.168.9.1

   * Ubuntu 14.04/Ubuntu 16.04/Ubuntu 18.04, x86 和 ARM (Nvidia TX2) 

   * Windows 7/10, Visual Studio 2015 Update3/2017/2019

     * C++11 编译器

   * 此API接口与Demo适用于CR-V4系列的V4及以上控制器版本

   

   ##  版本和发布记录

   ###  当前版本v1.0.0.0

   |   版本   |  修改日期  |
   | :------: | :--------: |
   | v1.0.0.0 | 2023-11-20 |

   

   # 2. 技术支持

   在使用过程中如遇问题或者一些建议， 您可以通过以下方式获取dobot的技术支持 :

   * 发送邮件到futingxing@dobot-robots.com，详细描述您遇到的问题和使用场景
   * 发送邮件到 wuyongfeng@dobot-robots.com ，详细描述您遇到的问题和使用场景

   


   #    3. TCP-IP-CR-CPP-V4   控制协议

   由于基于TCP/IP的通讯具有成本低、可靠性高、实用性强、性能高等特点；许多工业自动化项目对支持TCP/IP协议控制机器人需求广泛，因此Dobot机器人将设计在TCP/IP协议的基础上，提供了丰富的接口用于与外部设备的交互；

   机器状态等级：

       1.报错状态为第一优先级，如机器人报错且未上使能，则状态返回为报错状态
       
       2.下电状态为第二优先级，如机器人未上电，未上使能，则状态返回未上电状态
       
       3.碰撞状态为第三优先级，如机器人处于碰撞，脚本暂停，则状态返回碰撞状态
       
       4.开抱闸状态为第四优先级，如机器人开抱闸，未使能状态，则状态返回开抱闸状态
       
       ​ 其余状态根据实际情况反馈。


   端口反馈信息：

       29999服务器端口通过一发一收的方式负责接收一些设置以及运动控制相关的指令
       
       30004服务器端口(以下简称实时反馈端口)每8ms反馈机器人的信息
       
       30005服务器端口每200ms反馈机器人的信息
       
       30006端口为可配置的反馈机器人信息端口(默认为每50ms反馈)
       
       取消30003端口

   有关协议更详细的信息请查阅**《越疆TCPIP控制协议文档6AXis-V4》**

   

# 4. 获取TCP-IP-CR-CPP-V4  

   1. 从GitHub 下载或者克隆Dobot  TCP-IP-CR-CPP-V4  二次开发api程序

      ```bash
      `git clone https://github.com/Dobot-Arm/TCP-IP-CR-CPP-V4 4.git
      ```

   2. 参考对应的 README.md 文档使用；

   

   # 5. 文件类的说明以及使用方法

   1. api目录包含了CR的相关功能封装的各个类，基于c++编写的。

  2. api/rapidjson是[腾讯的json](https://github.com/Tencent/rapidjson)解析库。

  3. api目录中的类说明：

        | Parameter       | Default Value                                       |
        | --------------- | --------------------------------------------------- |
        | BitConverter    | 封装了字节与基础类型的转换                          |
        | DescartesPoint  | 笛卡尔坐标结构体封装                                |
        | JointPoint      | 关节点坐标结构体封装                                |
        | FeedbackData    | 反馈数据结构体封装                                  |
        | ErrorInfoBean   | 错误信息封装                                        |
        | ErrorInfoHelper | 错误信息帮助类                                      |
        | DobotClient     | 基于tcp通信的接口类，封装了通信的基础业务           |
        | Dashboard       | 派生于DobotClient，实现了具体的机器人基本功能       |
        | DobotMov        | 派生于DobotClient，实现了具体的机器人运动功能       |
        | Feedback        | 派生于DobotClient，实现了具体的机器人反馈的具体业务 |
        |                 |                                                     |

  4. `alarm_controller.json`警告报警配置文件,`alarm_servo.json`伺服报警配置文件。

  

  **CDobotClient**  

   基于tcp通信的接口类，提供对机器的tcp连接，关闭，获取ip，端口等功能， 封装了通信的基础业务。

  ```c++
    class CDobotClient
    {
    public:
     }
  ```

  

  **Dashboard**  

  ​      派生于DobotClient，  能发送一些设置相关的控制指令给机器人。实现了具体的机器人基本功能。  

  ```c++
 class CDashboard : public CDobotClient
    {
    public:
     }
  ```



  **Feedback**

  派生于DobotClient，实现了具体的机器人反馈的具体业务，能实时反馈机器人的状态信息。

  ```c++
    class CFeedbackData
    {
    public:
    };
  ```

   **具体使用详情请查看代码示例PythonExample.py和Demo示例**



   # 6. 常见问题

   * Tcp连接问题：

     29999端口为单客户端连接  ，只允许一个客户端连接；

     30004  30005  30006端口可以多客户端同时连接；

     29999端口有机器人模式限制，开放前需要先将机器人设置为TCP模式，否则指令发送后无法响应并返回"Control Mode Is Not Tcp"，30004、30005、30006实时反馈端口无模式限制；

   * 要获取机器人的状态， 可监测RobotMode()返回值。

     1. 控制器启动阶段为初始化状态，返回1；

     2. 机器人状态不为0或1时，机器人初始化完成；

     3. 机器下电状态，返回3；

     4. 初始化完成但未上使能为未使能状态，返回4；

     5. 机器使能空闲状态，返回5，代表可正常接收运动指令；

     6. movj(运行相关指令)、脚本运行及其他队列指令统一为运行状态，返回7；

     7. movJog（点动）为单次运动状态，返回8；无上电状态；

        | 模式 | 描述                   | 备注                            |
        | ---- | ---------------------- | ------------------------------- |
        | 1    | ROBOT_MODE_INIT        | 初始化状态                      |
        | 2    | ROBOT_MODE_BRAKE_OPEN  | 抱闸松开                        |
        | 3    | ROBOT_MODE_POWEROFF    | 本体下电状态                    |
        | 4    | ROBOT_MODE_DISABLED    | 未使能(抱闸未松开)              |
        | 5    | ROBOT_MODE_ENABLE      | 使能(空闲)                      |
        | 6    | ROBOT_MODE_BACKDRIVE   | 拖拽                            |
        | 7    | ROBOT_MODE_RUNNING     | 运行状态（含脚本和TCP队列运行） |
        | 8    | ROBOT_MODE_SINGLE_MOVE | 单次运动状态(点动)              |
        | 9    | ROBOT_MODE_ERROR       | 错误状态                        |
        | 10   | ROBOT_MODE_PAUSE       | 暂停状态                        |
        | 11   | ROBOT_MODE_COLLISION   | 碰撞状态                        |

   * 不同机器状态响应指令

     ​    *错误状态可执行指令：ClearError()、GetErrorID()、EmergeStop()、RobotMode()，其余指令均拒绝指令，返回-2；

     ​	*急停状态可执行指令：ClearError()、GetErrorID()、EmergeStop()、RobotMode()，其余指令均拒绝指令，返回-3；

     ​	*下电状态可执行指令：ClearError()、GetErrorID()、EmergeStop()、RobotMode()，PowerOn()，其余指令均拒绝指令，返回-4；

     ​	*TCP指令除必要的影响到机器人状态的指令外（EnableRobot()、PowerOn()），其余均为立即返回指令，指令返回仅代表成功发送，不代表执行完成；

   * 坐标系问题

     进入TCP/IP模式默认会将用户/工具坐标系设置为0，0，退出TCP/IP模式自动恢复至上位机设置的用户/工具坐标系索引值；

     ​      全局坐标：User()、Tool()指令设置的是全局坐标系，设置后对所有指令均生效；

     ​      局部坐标：运动指令中带的user/tool可选参仅在当前运动指令生效，执行完当前指令后恢复至全局坐标系；

   * 算法允许的队列深度为64，可同时连续处理64条队列指令，若一直向端口发送队列指令而超出队列深度，端口不会断连，指令接口会返回-1，指令不会执行

   * 队列指令为立即返回指令，接口返回成功仅代表发送成功，不代表执行完毕。若判断执行完毕，则需要结合CommandID和RobotMode来综合判断

   * 伺服运行时间代表上使能后的累计时间，控制器开机时间代表控制器开机后的时间（正常上电），因此控制器开机时间总要大于伺服运行时间的

   * 碰撞状态不属于错误，GetErrorID()中没有碰撞的错误返回，可通过RobotMode()查询碰撞状态，返回11；ClearError()可清除碰撞状态

   * 发生碰撞后正常发送清错指令，清除碰撞状态即可重新运行，不需要重新上使能

   * 切换TCP/IP模式后会默认将速度/加速度/用户、工具坐标系参数设置为默认值，无需调用EnableRobot()指令进行默认参数设置

   * Tcp队列指令返回值仅表示指令参数和语法是否符合规范，不表示指令是否成功执行。TCP队列指令发送后即返回，返回0仅代表正常发送，不表示可成功执行。

   * Tcp指令参数类型/数量错误会直接报警，不会补0处理，指令不会下发至算法。

   * 触发急停信号后，机器人默认进行运动停止，若停止过程超过500ms还未停止运动，则执行下电动作；否则不进行下电；一般情况下机器人急停后不下电

   * 设置默认网关后，数值默认网关数据会保存，重启后数值不会更改

   * 上使能指令仅执行使能动作，无其余参数设置，不会清除运动学参数和坐标系参数。

   * Pause()、Continue()指令对脚本运行生效，运动指令（队列相关）也生效，调用Pause()指令后机器人进入暂停状态，算法队列暂停；可使用Continue()指令继续运行队列指令。MovJog(点动)指令属于单次运行状态，不可暂停和继续

   

   # 7. 示例

   * Dobot-Demo 实现Tcp对机器的控制等交互，分别对控制端口，反馈端口进行tcp连接，通过机器运动指令完成状态来进行下发指令，且对机器异常状态进行处理等功能。

     

1.  主线程：分别对机器控制端口，运动端口，反馈端口进行连接。给机器使能，MovL移动指令等动作

![](/main.png)

2.  反馈状态线程：实时反馈机器的状态信息

![](/feed.png)

3. 机器运动线程： 给机器下发运动指令

![](/move.png)

运动指令到位信号：

队列指令为立即返回指令，接口返回成功仅代表发送成功，不代表执行完毕。若判断执行完毕，则需要结合

* 当前CommandID大于下发运动队列指令的CommandID，则表示下发队列指令已完成。

* 当前CommandID等于下发运动指令的CommandID，且机器状态RobotMode指令返回值为5，则表示下发队列指令已完成。

  

4.  异常处理线程：对机器异常状态进行判断和处理动作

![](/exception.png)



   * 

     

   **Demo运行的操作步骤时序如下图所示 ：**

   1. 从GitHub 获取越疆Dobot  TCP-IP-CR-CPP-V4 二次开发Api程序

      ```bash
      `git clone https://github.com/Dobot-Arm/TCP-IP-CR-CPP-V4.git
      ```

   2. 通过LAN1网口-连接机器端，设置本机机器IP地址为192.168.5.X  网段

      控制面板>>网络>> Internet>>网络连接  

      ![](/netConnect.png)

      

      选择连接的以太网  >>  点击右键  >> 属性  >>   Internet协议版本(TCP/IP-V4)

      修改ip地址为192.168.5.X网段IP

      ![](/updateIP.png)

      

   3. 连接上位机DobotStudio Pro，连接机器，把机器模式切换至TCP/IP模式

      ![](Z:/dobot_home/v4/TCP-IP-CR-Python-V4/picture/checkTcpMode.png)




  1. 运行程序

     1. 从Dobot  GitHub 获取越疆Dobot  TCP-IP-CR-CPP 二次开发api程序

        ```bash
        `git clone https://github.com/Dobot-Arm/TCP-IP-CR-CPP-V4.git`
        ```

     &ensp;&ensp;&ensp;&ensp;

     2. 进入目录  TCP-IP-CR-CPP/CppDemo/  文件夹进行编译Demo程序

     ```bash
     cd  TCP-IP-CR-CPP-V4/CppDemo/
     bash compileDemo.sh
     ```

     

     3. 运行Demo程序

     ```bash
     bash runDemo.sh
     ```

     

     **常见问题：**

  ​     **问题一： 请确保机器处于Tcp/IP模式'**

  ​     **问题二： 确认Demo中 不同机型（CR）对应的笛卡尔坐标**

  

   **运行示例前请确保机器处于安全位置，防止机器发生不必要的碰撞**

   