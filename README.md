# Architecture design
![image](https://user-images.githubusercontent.com/65532421/157684876-e5e55fb3-e4f0-4f8c-ad62-3a18fc721598.png)

* Network Delegate Class
  * async tcp/ip commuication base on event-driven
  * For POSIX, NetworkEngine is made by boost/asio
* Content Logic Delegate Class
  * main thread
* DB Delegate Class
  * async
