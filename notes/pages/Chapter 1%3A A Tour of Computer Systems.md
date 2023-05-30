- 计算机系统漫游。
  :LOGBOOK:
  CLOCK: [2023-05-04 Thu 22:37:03]--[2023-05-04 Thu 22:37:08] =>  00:00:05
  :END:
  
  通过研究 `hello world` 程序的生命周期，介绍计算机系统的主要概念
- 1.1 Information Is Bits + Context
	- 系统中的所有信息--包括磁盘文件、内存中的程序、内存中存在的用户数据以及网络上传送的数据，都是又一串比特表示的。区分不同的数据对象的唯一方法是我们读到的这些数据对象的上下文。比如在不同的上下文中一个同样的字节序列可能表示一个整数、浮点数、字符串或者机器指令。
- 1.2 Programs Are Translated by Other Programs into Different Forms
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
		- gcc -Wall -Og -m64 hello.c #gcc
		  id:: 64760016-8846-4b98-80e1-b7e2e6fdc417
			- [[-Wall]] 报告所有警告
			- [[-Og]] 优化调试体验
			- [[-m64]] 忽略 Nvidia PTX 选项，但为了保留而向后兼容
- 1.3 It Pays to Understand How Compilations Systems Work
	- Optimizing program performance
	- Understanding link-time errors
	- Avoiding security holes
- 1.4 Processors Read and Interpret Instructions Stored in Memory
	- 1.4.1 Hardware Organization of a System
		- **Buses**. Buses carry bytes of information back and forth between the components. Buses are typically designed to transfer **fixed-size** chunks of bytes known as **words**.
		- **I/O Devices**. Input/output (I/O) devices are the system’s connection to the external world.
			- [[Chapter 6: The Memory Hierarchy]] has more to say about how I/O devices such as disks work.
			- In [[Chapter 10: System-Level I/O]] , you will learn how to use the Unix I/O interface to access devices from your application programs.
		- **Main Memory**. The main memory is a temporary storage device that holds both a program and the data it manipulates while the processor is executing the program.
			- [[Chapter 6: The Memory Hierarchy]] has more to say about how memory technologies such as DRAM chips work, and how they are combined to form main memory.
		- **Processor**. The central processing unit (CPU), or simply processor, is the engine that inter-prets (or executes) instructions stored in main memory.
		  id:: 6464ccc8-a92b-4f4c-bf06-6a0f91259d89
			- When we study machine code in [[Chapter 3: Machine-Level Representation of Programs]] , we will consider the abstraction provided by the machine’s instruction set architecture.
			- [[Chapter 4: Processor Architecture]] has more to say about how processors are actually implemented.
			- [[Chapter 5: Optimizing Program Performance]] describes a model of how modern processors work that enables predicting and optimizing the performance of machine-language programs.
	- 1.4.2 Running the hello Program
		- Type the characters `/.hello` at the keyboard, the shell program reads each one into a register and then stores it in memory.
		  id:: 6464d559-27dc-413b-a0a3-9662316efbe9
		  
		  Keyboard -> USB controller -> I/O bridge -> Bus interface -> Register file -> Bus interface -> I/O bridge -> Main memory
		- The shell then loads the executeable `hello` file by executing a sequence of instructions that copies the code and data in the `hello` object file from disk to main memory. The string of characters `hello, world\n` will eventually be printed out.
		  
		  Disk -> Disk controller -> I/O bridge -> Main memory
		- Once the code and data in the `hello` object file are loaded into memory, the processor begins executing the machine-language instructions in the hello program’s main routine. These instructions copy the bytes in the `hello, world\n` string from memory to the register file, and from there to the display device, where they are displayed on the screen.
		  
		  Main memory -> Bus interface -> Register file -> Bus interface -> I/O bridge -> Graphics adapter -> Display
- 1.5 Caches Matter
	- Application programmers are aware of cache memories can exploit them to improve the perfor-
	  mance of their programs by **an order of magnitude**. You will learn more about these important devices and how to exploit them in [[Chapter 6: The Memory Hierarchy]]
- 1.6 Storage Devices Form a Hierarchy
	- This notion of inserting a **smaller**, **faster** storage device (e.g., cache memory) between the processor and a **larger**, **slower** device (e.g., main memory) turns out to be a general idea.
	- memory hierarchy:
		- Regs
		- L1 cache(SRAM)
		- L2 cache(SRAM)
		- L3 cache(SRAM)
		- Main memory(DRAM)
		- Local secondary storage(lock disks)
		- Remote secondary storage(distributed file systems, Web servers)
- 1.7 The Operating System Manages the Hardware
	- The operating system has two primary purposes:
		- To protect the hardware from misuse by runaway applications
		- To provide applications with simple and uniform mechanisms for manipulating complicated and often wildly different low-level hardware devices
	- The operating system achieves both goals via the fundamental abstractions shown in: [[processes]] , [[virtual memory]] , and [[files]].
	- 1.7.1 [[processes]]
		- A process is the operating system’s abstraction for a running program. Multiple processes can run concurrently on the same system, and each process appears to have exclusive use of the hardware.
		- A single CPU can appear to execute multiple processes concurrently by having the processor switch among them. The operating system performs this interleaving with a mechanism known as [[context switching]] .
		- Implementing the process abstraction requires close cooperation between both the low-level hardware and the operating system software. We will explore how this works, and how applications can create and control their own processes, in [[Chapter 8: Exceptional Control Flow]] .
	- 1.7.2 Threads
		- A process can actually consist of multiple execution units, called threads, each running in the context of the process and sharing the same code and global data.
		- Multi-threading is also one way to make programs run faster when multiple processors are available, as we will discuss in [[1.9.2 Concurrency and Parallelism]] .
		- You will learn the basic concepts of concurrency, including how to write threaded programs, in [[Chapter 12: Concurrent Programming]] .
	- 1.7.3 [[virtual memory]]
		- Virtual memory is an abstraction that provides each process with the illusion that it has exclusive use of the main memory.
		- Each process has the same uniform view of memory, which is known as its **virtual address space**:
			- Program code and data. Code begins at the same *fixed address* for all processes, followed by data locations that correspond to global C variables. You will learn more about this part of the address space when we study linking and loading in [[Chapter 7: Linking]] .
			- Heap. The code and data areas are fixed in size once the process begins running,  the heap expands and contracts dynamically at run time.  We will study heaps in detail when we learn about managing virtual memory in [[Chapter 9: Virtual Memory]].
			- Shared libraries. Near the *middle* of the address space is an area that holds the code and data for shared libraries such as the **C standard library** and the **math library**. You will learn how they work when we study dynamic linking in [[Chapter 7: Linking]] .
			- Stack. At the *top* of the user’s virtual address space is the user stack that the compiler uses to implement function calls. Each time call a function, the stack grows. Each time return from a function, it contracts. You will learn how the compiler uses the stack in [[Chapter 3: Machine-Level Representation of Programs]] .
			- Kernel virtual memory. Application programs are *not allowed* to read or write the contents of this area or to directly call functions defined in the kernel code. Instead, they must invoke the kernel to perform these operations.
	- 1.7.4 [[files]]
		- A file is a sequence of bytes. Every I/O device, including disks, keyboards, displays, and even networks, is modeled as a file.
		- This simple and elegant notion of a file is nonetheless very powerful because it provides applications with a uniform view of all the varied I/O devices that might be contained in the system.
		- You will learn about Unix I/O in [[Chapter 10: System-Level I/O]] .
- 1.8 Systems Commuicate with Other Systems Using Networks
	- Modern systems are often linked to other systems by networks. From the point of view of an individual system, the network can be viewed as just another I/O device.
- 1.9 Important Themes
	- 1.9.1 Amdahl's Law
		- When we speed up one part of a system, the effect on the overall sys- tem performance depends on both how significant this part was and how much it sped up.
	- [[1.9.2 Concurrency and Parallelism]]
		- concurrency, the general concept of a system with multiple, simultaneous activities.
		- parallelish, the use of concurrency to make a system run faster.
		- We highlight three levels here, working from the highest to the lowest level in the *system hierarchy*:
			- Thread-Level Concurrency
			- Instruction-Level Parallelism
			- Single-Instruction, Multiple-Data(SIMD) Parallelism
	- 1.9.3 The Importance of Abstractions in Cimputer Systems
		- On the operating system, we have four abstractions:
			- files as an abstraction of I/O devices
			- virtual memory as an abstraction of program memory
			- processes as an abstraction of a running program
			- the virtual machine, providing an abstraction of the entire computer, including the operating system, the processor, and the programs