## MQTT

### 课程目标

1. 了解MQTT协议
2. 安装并使用mosquitto

### 课程实验

使用mosquitto发布订阅消息

### 课堂引入

多个物联网设备进行网络通信的桥梁

### 简介

#### 什么是 MQTT？

MQTT是一种中间件，MQTT是一种通信协议。

MQTT（Message Queuing Telemetry  Transport）是一种轻量级、基于发布-订阅模式的消息传输协议，适用于资源受限的设备和低带宽、高延迟或不稳定的网络环境。它在物联网应用中广受欢迎，能够实现传感器、执行器和其它设备之间的高效通信。

> MQTT是基于TCP/IP协议族的，位于应用层。
>
> TCP/IP协议族的网络模型：
>
> https://blog.csdn.net/mzm1166/article/details/122868429
>
> 四层模型：数据链路、网络层、传输层、应用层
>
> 应用层： HTTP, HTTPS, FTP，SMTP , POP3, ssh MQTT
>
> 传输层:  TCP, DUP

> 网络层： IP 
>
> 数据链路层

#### 为什么 MQTT 是适用于物联网的最佳协议？



报文长度短，利用QoS  0  1   2级别，保证消息可靠性



MQTT 所具有的适用于物联网特定需求的特点和功能，使其成为物联网领域最佳的协议之一。它的主要特点包括：

- **轻量级：**物联网设备通常在处理能力、内存和能耗方面受到限制。MQTT 开销低、报文小的特点使其非常适合这些设备，因为它消耗更少的资源，即使在有限的能力下也能实现高效的通信。
- **可靠：**物联网网络常常面临高延迟或连接不稳定的情况。MQTT 支持多种 QoS （安全）等级、会话感知和持久连接，即使在困难的条件下也能保证消息的可靠传递，使其非常适合物联网应用。
- **安全通信：**安全对于物联网网络至关重要，因为其经常涉及敏感数据的传输。为确保数据在传输过程中的机密性，MQTT 提供传输层安全（TLS）和安全套接层（SSL）加密功能。此外，MQTT 还通过用户名/密码凭证或客户端证书提供身份验证和授权机制，以保护网络及其资源的访问。
- **双向通信：**MQTT 的发布-订阅模式为设备之间提供了无缝的双向通信方式。客户端既可以向主题发布消息，也可以订阅接收特定主题上的消息，从而实现了物联网生态系统中的高效数据交换，而无需直接将设备耦合在一起。这种模式也简化了新设备的集成，同时保证了系统易于扩展。
- **连续、有状态的会话：**MQTT 提供了客户端与 Broker  之间保持有状态会话的能力，这使得系统即使在断开连接后也能记住订阅和未传递的消息。此外，客户端还可以在建立连接时指定一个保活间隔，这会促使  Broker 定期检查连接状态。如果连接中断，Broker 会储存未传递的消息（根据 QoS  级别确定），并在客户端重新连接时尝试传递它们。这个特性保证了通信的可靠性，降低了因间断性连接而导致数据丢失的风险。
- **大规模物联网设备支持：**物联网系统往往涉及大量设备，需要一种能够处理大规模部署的协议。MQTT 的轻量级特性、低带宽消耗和对资源的高效利用使其成为大规模物联网应用的理想选择。通过采用发布-订阅模式，MQTT  实现了发送者和接收者的解耦，从而有效地减少了网络流量和资源使用。此外，协议对不同 QoS  等级的支持使得消息传递可以根据需求进行定制，确保在各种场景下获得最佳的性能表现。
- **语言支持：**物联网系统包含使用各种编程语言开发的设备和应用。MQTT 具有广泛的语言支持，使其能够轻松与多个平台和技术进行集成，从而实现了物联网生态系统中的无缝通信和互操作性。您可以阅读我们的 MQTT 客户端编程系列文章，学习如何在 PHP、Node.js、Python、Golang、Node.js 等编程语言中使用 MQTT。

#### MQTT 的工作原理

发布者--Broker--订阅者（多个

要了解 MQTT 的工作原理，首先需要掌握以下几个概念：MQTT 客户端、MQTT Broker、发布-订阅模式、主题、QoS。

**MQTT 客户端**

任何运行 MQTT 客户端库的应用或设备都是 MQTT 客户端。例如，使用 MQTT 的即时通讯应用是客户端，使用 MQTT 上报数据的各种传感器是客户端，各种 MQTT 测试工具也是客户端。

**MQTT Broker**

MQTT Broker 是负责处理客户端请求的关键组件，包括建立连接、断开连接、订阅和取消订阅等操作，同时还负责消息的转发。一个高效强大的 MQTT  Broker 能够轻松应对海量连接和百万级消息吞吐量，从而帮助物联网服务提供商专注于业务发展，快速构建可靠的 MQTT 应用。

**发布-订阅模式**

发布-订阅模式与客户端-服务器模式的不同之处在于，它将发送消息的客户端（发布者）和接收消息的客户端（订阅者）进行了解耦。发布者和订阅者之间无需建立直接连接，而是通过 MQTT Broker 来负责消息的路由和分发。

下图展示了 MQTT 发布/订阅过程。温度传感器作为客户端连接到 MQTT Broker，并通过发布操作将温度数据发布到一个特定主题（例如 `Temperature`）。MQTT Broker 接收到该消息后会负责将其转发给订阅了相应主题（`Temperature`）的订阅者客户端。



publish 发布

Temperature主题   Topic

subscribe 接收

中间的协议就是MQTT

任何一个设备都可以发布和订阅

![img](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/v2-be574ce8ec0e21e84ec29e1ac248543e_1440w.png)

**主题**

MQTT 协议根据主题来转发消息。主题通过 `/` 来区分层级，类似于 URL 路径，例如：



```text
chat/room/1
chat/room/2
chat/room/3

sensor/10/temperature
sensor/+/temperature
```

MQTT 主题支持以下两种通配符：`+` 和 `#`。

- `+`：表示单层通配符，例如 `a/+` 匹配 `a/x` 或 `a/y`。  
- `#`：表示多层通配符，例如 `a/#` 匹配 `a/x`、`a/b/c/d`。  
- \* : 一般用在最后，表示这个目录下所有的主题    sensor/#/*   

> **注意**：通配符主题只能用于订阅，不能用于发布。

**QoS**

MQTT 提供了三种服务质量（QoS），在不同网络环境下保证消息的可靠性。

- QoS 0：消息最多传送一次。如果当前客户端不可用，它将丢失这条消息。
- QoS 1：消息至少传送一次。（保证消息收到了，如果响应慢了，有可能再发一次，可能会导致消息重复发送和接收）
- QoS 2：消息只传送一次。（必须成功，比如扣钱）

#### MQTT 的工作流程

在了解了 MQTT 的基本组件之后，让我们来看看它的一般工作流程：

1. **客户端使用 TCP/IP 协议与 Broker 建立连接**，可以选择使用 TLS/SSL 加密来实现安全通信。客户端提供认证信息，并指定会话类型（Clean Session 或 Persistent Session）。
2. **客户端既可以向特定主题发布消息，也可以订阅主题以接收消息**。当客户端发布消息时，它会将消息发送给 MQTT Broker；而当客户端订阅消息时，它会接收与订阅主题相关的消息。
3. **MQTT Broker 接收发布的消息**，并将这些消息转发给订阅了对应主题的客户端。它根据 QoS 等级确保消息可靠传递，并根据会话类型为断开连接的客户端存储消息。

#### MQTT协议

参考官方文档

https://mqtt.p2hp.com/mqtt311#google_vignette

>MQTT常见的协议版本有3.11 3.1.1 5.0

### 常见MQTT服务器软件

> QoS 0：服务质量 0，最多传输一次。
> QoS 1：服务质量1，至少传输一次。
> QoS 2：服务质量2，仅仅传输一次。
> auth：验证，身份验证授权。
> bridge：桥接，服务器代理之间连接
> $SYS：主题过滤器通配符，订阅后能够接收到所有以此通配符开头的主题的消息。
> dynamic topics：动态主题
> cluster：集群
>
> 说明：✔表示支持，✘表示不支持，?表示未知，§表示支持但有限制，rm表示(roadmap)路线图规划中也就是计划支持。

| Server                          | QoS 0 | QoS 1 | QoS 2 | auth | bridge | $SYS | SSL  | dynamic topics | cluster | websockets | plugin system |
| ------------------------------- | ----- | ----- | ----- | ---- | ------ | ---- | ---- | -------------- | ------- | ---------- | ------------- |
| 2lemetry                        | ✔     | ✔     | ✔     | ✔    | ✔      | §    | ✔    | ✔              | ✔       | ✔          | ✘             |
| **Apache ActiveMQ**             | ✔     | ✔     | ✔     | ✔    | ✘      | ✘    | ✔    | ✔              | ✔       | ✔          | ✔             |
| Apache ActiveMQ Artemis         | ✔     | ✔     | ✔     | ✔    | ✘      | ✘    | ✔    | ✔              | ✔       | ✔          | ✔             |
| Bevywise IoT Platform           | ✔     | ✔     | ✔     | ✔    | rm     | ✔    | ✔    | ✔              | ✔       | ✔          | rm            |
| emitter                         | ✔     | §     | ✘     | ✔    | ✘      | ✘    | ✔    | ✔              | ✔       | ✔          | ✘             |
| **emqttd**                      | ✔     | ✔     | ✔     | ✔    | ✔      | ✔    | ✔    | ✔              | ✔       | ✔          | ✔             |
| flespi                          | ✔     | ✔     | ✔     | ✔    | ✘      | ✘    | ✔    | ✔              | ✔       | ✔          | ✘             |
| GnatMQ                          | ✔     | ✔     | ✔     | ✔    | ✘      | ✘    | ✘    | ✔              | ✘       | ✘          | ✘             |
| HBMQTT                          | ✔     | ✔     | ✔     | ✔    | ✘      | ✔    | ✔    | ✔              | ✘       | ✔          | ✔             |
| **HiveMQ**                      | ✔     | ✔     | ✔     | ✔    | ✔      | ✔    | ✔    | ✔              | ✔       | ✔          | ✔             |
| IBM MessageSight                | ✔     | ✔     | ✔     | ✔    | ✘      | ✔    | ✔    | ✔              | §       | ✔          | ✘             |
| JoramMQ                         | ✔     | ✔     | ✔     | ✔    | ✔      | ✔    | ✔    | ✔              | ✔       | ✔          | ✔             |
| Mongoose                        | ✔     | ✔     | ?     | ?    | ?      | ?    | ?    | ?              | ?       | ?          | ?             |
| moquette                        | ✔     | ✔     | ✔     | ✔    | ?      | ?    | ✔    | ?              | rm      | ✔          | ✘             |
| mosca                           | ✔     | ✔     | ✘     | ✔    | ?      | ?    | ?    | ?              | ✘       | ✔          | ✘             |
| **mosquitto**                   | ✔     | ✔     | ✔     | ✔    | ✔      | ✔    | ✔    | ✔              | §       | ✔          | ✔             |
| MQTT.js                         | ✔     | ✔     | ✔     | §    | ✘      | ✘    | ✔    | ✔              | ✘       | ✔          | ✘             |
| MqttWk                          | ✔     | ✔     | ✔     | ✔    | ✔      | ?    | ✔    | ✔              | ✔       | ✔          | ✘             |
| **RabbitMQ**                    | ✔     | ✔     | ✘     | ✔    | ✘      | ✘    | ✔    | ✔              | ?       | ?          | ?             |
| RSMB                            | ✔     | ✔     | ✔     | ✔    | ✔      | ✔    | ✘    | ✔              | ✘       | ✘          | ?             |
| Software AG Universal Messaging | ✔     | ✔     | ✔     | ✔    | ✘      | ✘    | ✔    | ✔              | ✔       | rm         | ✘             |
| Solace                          | ✔     | ✔     | ✘     | ✔    | §      | ✔    | ✔    | ✔              | ✔       | ✔          | ✘             |
| SwiftMQ                         | ✔     | ✔     | ✔     | ✔    | ✔      | ✘    | ✔    | ✔              | ✔       | ✘          | ✔             |
| Trafero Tstack                  | ✔     | ✔     | ✔     | ✔    | ✘      | ✘    | ✔    | ✔              | ✘       | ✘          | ✘             |
| VerneMQ                         | ✔     | ✔     | ✔     | ✔    | ✔      | ✔    | ✔    | ✔              | ✔       | ✔          | ✔             |
| WebSphere MQ                    | ✔     | ✔     | ✔     | ✔    | ✔      | ✔    | ✔    | ✔              | ?       | ?          | ?             |

### Mosquitto安装与使用



http://localhost:18083/

Mosquitto是一个实现了MQTT3.1协议的代理服务器，由MQTT协议创始人之一的Andy Stanford-Clark开发，它为我们提供了非常棒的轻量级数据交换的解决方案。

``` shell
# 安装 
# 安装完成之后，所有配置文件会被放置于/etc/mosquitto/目录下，其中最重要的就是Mosquitto的配置文件，即mosquitto.conf，以下是详细的配置参数说明。，表示连客户端带服务端一起安装，如果执行不成功，
#如果是阿里云 先sudo apt-get update
sudo apt-get install mosquitto mosquitto-clients

# 是否安装成功
which mosquitto
# 启动   -c 指定配置文件  -p 指定端口号，默认1883,不报错，就是没错
sudo mosquitto -c /etc/mosquitto/mosquitto.conf -p 1883
sudo mosquitto -p 1883
# 订阅主题   mqtt://127.0.0.1:1883
sudo mosquitto_sub -t "woniu"
# 发布消息
sudo mosquitto_pub -t "woniu" -m "helloworld"

```

![image-20231208150305168](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20231208150305168.png)

**其它参数**

关于长链接  ，SOCKET  或者webSOCKET

短连接：正常都是短链接

为了保证没挂：就加一个心跳机制

``` shell
# 订阅参数：
# -d 开启debug模式
# -v 打印详细信息日志
# -h 指定主机
# -p 指定端口
# 连接192.168.2.48的1883的服务，订阅了一个主题叫woniu，-d-v如果有任何消息都打印出来
sudo mosquitto_sub -d -v -t woniu -h 127.0.0.1 -p 1883 

# 订阅参数：
# -q 指定服务质量，默认Qos 0
sudo mosquitto_pub -d -t topic -h 192.168.2.48 -p 1883 -m hello -q 2
```

![image-20231208151624971](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20231208151624971.png)



* 三种安全等级，对应的不同的消息

 (QoS, Quality of Service) 

QoS 0：服务质量 0，最多传输一次,发送一次就不管了，有没有收到，不知道
QoS 1：服务质量1，至少传输一次。会多一次发布确认
QoS 2：服务质量2，仅仅传输一次。



![image-20240801045345972](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/zhangge/202408010453098.png)

````
这段日志记录了你使用 mosquitto_pub 工具向 MQTT 服务器发布消息的过程，分别以不同的服务质量等级（QoS）进行。以下是对每个 QoS 级别的日志的详细解释：

QoS 0
Client null sending CONNECT

客户端正在发送 CONNECT 消息，请求与 MQTT 服务器建立连接。
Client null received CONNACK (0)

客户端收到了 CONNACK 消息，表示连接确认，(0) 表示连接成功，没有错误。
Client null sending PUBLISH (d0, q0, r0, m1, 'woniu', ... (5 bytes))

客户端发送了一条 PUBLISH 消息，内容为 'hello'。参数说明：
d0: 消息的 DUP 标志为 0，表示这是第一次发送此消息。
q0: 消息的 QoS（服务质量）等级为 0，即“至多一次”。
r0: 保留标志为 0。
m1: 消息标识符为 1。
Client null sending DISCONNECT

客户端发送了 DISCONNECT 消息，表示它希望断开与 MQTT 服务器的连接。
总结: 在 QoS 0 下，消息发送后无需等待确认，消息可能会丢失，也不会重复发送。

QoS 1
Client null sending CONNECT

客户端正在发送 CONNECT 消息，请求与 MQTT 服务器建立连接。
Client null received CONNACK (0)

客户端收到了 CONNACK 消息，表示连接确认，(0) 表示连接成功，没有错误。
Client null sending PUBLISH (d0, q1, r0, m1, 'woniu', ... (5 bytes))

客户端发送了一条 PUBLISH 消息，内容为 'hello'。参数说明：
d0: 消息的 DUP 标志为 0。
q1: 消息的 QoS（服务质量）等级为 1，即“至少一次”。
r0: 保留标志为 0。
m1: 消息标识符为 1。
Client null received PUBACK (Mid: 1, RC:0)

客户端收到了 PUBACK 消息，表示服务器已接收到消息并确认。Mid: 1 表示消息标识符为 1，RC:0 表示处理结果为 0，通常表示成功。
Client null sending DISCONNECT

客户端发送了 DISCONNECT 消息，表示它希望断开与 MQTT 服务器的连接。
总结: 在 QoS 1 下，消息会得到服务器的确认，确保消息至少被传递一次，但可能会重复发送。

QoS 2
Client null sending CONNECT

客户端正在发送 CONNECT 消息，请求与 MQTT 服务器建立连接。
Client null received CONNACK (0)

客户端收到了 CONNACK 消息，表示连接确认，(0) 表示连接成功，没有错误。
Client null sending PUBLISH (d0, q2, r0, m1, 'woniu', ... (5 bytes))

客户端发送了一条 PUBLISH 消息，内容为 'hello'。参数说明：
d0: 消息的 DUP 标志为 0。
q2: 消息的 QoS（服务质量）等级为 2，即“仅一次”。
r0: 保留标志为 0。
m1: 消息标识符为 1。
Client null received PUBREC (Mid: 1)

客户端收到了 PUBREC 消息，表示服务器已接收到消息，并要求客户端发送 PUBREL 消息以完成确认。Mid: 1 表示消息标识符为 1。
Client null sending PUBREL (m1)

客户端发送了 PUBREL 消息，表示客户端已准备好接收服务器的消息确认。m1 表示消息标识符为 1。
Client null received PUBCOMP (Mid: 1, RC:0)

客户端收到了 PUBCOMP 消息，表示服务器已完成对消息的处理并确认。Mid: 1 表示消息标识符为 1，RC:0 表示处理结果为 0，通常表示成功。
Client null sending DISCONNECT

客户端发送了 DISCONNECT 消息，表示它希望断开与 MQTT 服务器的连接。
总结: 在 QoS 2 下，消息会得到服务器的确认，确保消息仅传递一次，避免重复。

这三种 QoS 等级的不同之处在于消息的传递保证和确认流程的复杂度。
````



![image-20240801044603418](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/zhangge/202408010446483.png)

````
Client null sending CONNECT

客户端正在发送 CONNECT 消息，请求与 MQTT 服务器建立连接。
Client null received CONNACK (0)

客户端收到了 CONNACK 消息，表示连接确认。(0) 表示连接成功，没有错误。
Client null sending SUBSCRIBE (Mid: 1, Topic: woniu, QoS: 0, Options: 0x00)

客户端发送了一条 SUBSCRIBE 消息，请求订阅主题 'woniu'。参数说明：
Mid: 1: 订阅请求的消息标识符为 1。
Topic: woniu: 订阅的主题是 'woniu'。
QoS: 0: 订阅的服务质量等级为 0，表示“至多一次”的传递保证。
Options: 0x00: 订阅选项，通常为 0。
Client null received SUBACK

客户端收到了 SUBACK 消息，表示服务器已处理订阅请求。
Subscribed (mid: 1): 0

客户端确认订阅已成功，mid: 1 表示订阅请求的消息标识符为 1。0 表示服务器同意订阅请求，并确认使用 QoS 0 服务质量等级。
````





#### 禁止匿名

``` shell
# 修改配置文件,文件的结尾 .xml  .json  .conf 可能都是配置文件
sudo vim /etc/mosquitto/mosquitto.conf 
# 文件最后添加：
# 禁匿名订阅和发布
allow_anonymous false
# 指定账号密码文件位置
password_file /etc/mosquitto/passwd.conf
保存退出:wq
# 设置账
cd /etc/mosquitto
touch passwd.conf
sudo mosquitto_passwd -b /etc/mosquitto/passwd.conf zg 12345678
#查询mosquitto的进程号
ps -ef | grep mosquitto
# kill 命令，杀了这个进程
kill -9 630

#重新启动程序
sudo mosquitto -d -c /etc/mosquitto/mosquitto.conf -p 1883


#如果想后台启动，也可以使用
nohup mosquitto -d -c /etc/mosquitto/mosquitto.conf -p 1883 &
```

![image-20231208152034177](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20231208152034177.png)

**添加账号密码**

```shell
sudo mosquitto_passwd -c /etc/mosquitto/passwd.conf zg
sudo mosquitto_passwd -b /etc/mosquitto/passwd.conf zg 12345678
```

![image-20231208152902453](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20231208152902453.png)

**使用账号密码**



```shell
# -u 用户名
# -P 密码
sudo mosquitto_sub -d -v -t topic -h 192.168.1.1 -p 1883 -u zg -P 12345678
```

![image-20231208153246243](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20231208153246243.png)

### 客户端下载



阿里云：购买SSL证书： 



https://mqttx.app/zh/downloads?os=windows

![image-20240801052849525](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/zhangge/202408010528693.png)





![image-20240801053008927](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/zhangge/202408010530230.png)



![image-20240801053054584](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/zhangge/202408010530748.png)



![image-20240801053137265](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/zhangge/202408010531406.png)



### 使用云服务器

要把mosquito运行在互联网上的服务器上，这样才可以使用ip地址或域名访问。

可以使用阿里云服务器或腾讯云服务器



### 使用云MQTT

#### 1、免费的MQTT

https://www.emqx.com/zh/mqtt/public-mqtt5-broker

#### 2、收费的云服务器

![image-20240801054415675](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/zhangge/202408010544985.png)



![image-20240801054500046](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/zhangge/202408010545559.png)





![image-20240801055246241](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/zhangge/202408010552398.png)





![image-20240801175722999](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/zhangge/202408011757263.png)







[巴法云免费MQTT](https://bemfa.com/)

![image-20231211120928179](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20231211120928179.png)

**新建主题**

![image-20231211121026210](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20231211121026210.png)

**命令连接**

![image-20231211121123340](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20231211121123340.png)

```shell
# -i指定客户端id   ----订阅
sudo mosquitto_sub -t topic -h bemfa.com -p 9501 -i f13f3242906a41df75f23cce575883af

# 发布
sudo mosquitto_pub -h bemfa.com -p 9501 -t topic -m 'hello woniu' -i f13f3242906a41df75f23cce575883af
```

![image-20231211121419494](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20231211121419494.png)

### 使用MQTT桌面客户端

[MQTTX下载](https://www.emqx.com/zh/products/mqttx)

![image-20231211122325461](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20231211122325461.png)

其中，1883：MQTT协议端口；8883: MQTT/SSL端口；8083: MQTT/WebSocket端口；8080: HTTP API端口；18083: Dashboard 管理控制台端口；

验证

执行完成之后，可在浏览器输入http://localhost:18083/ 来访问对应的管理后台。默认的登录用户名：admin，密码：public

虚拟机密码：woniu 123