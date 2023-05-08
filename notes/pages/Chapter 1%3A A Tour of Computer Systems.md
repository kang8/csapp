- 计算机系统漫游。
  :LOGBOOK:
  CLOCK: [2023-05-04 Thu 22:37:03]--[2023-05-04 Thu 22:37:08] =>  00:00:05
  :END:
  
  通过研究 `hello world` 程序的生命周期，介绍计算机系统的主要概念
- 一个 C 语言的源程序，通过编译器驱动程序转换成可执行目标文件（executable object pro）分为四步：
  id:: 6453c8c1-8e38-4ad0-972f-ff4464b1dd3e
	- [[Preprocessing]]
	- [[Compilation]]
	- [[Assembly]]
	- [[Linking]]
	- hello.c 文件和编译命令：
		- ```c
		  #include <stdio.h>
		  
		  int main()
		  {
		    printf("hello, world");
		    return 0;
		  }
		  ```
		- gcc -Wall -Og -m64 hello.c
			- [[-Wall]] 报告所有警告
			- [[-Og]] 优化调试体验
			- [[-m64]] 忽略 Nvidia PTX 选项，但为了保留而向后兼容