- 预处理阶段
- 预处理器（cpp）根据以字符 `#` 开头的命令，修改原始 C 程序。比如将 `hello.c` 中的第一行 `#include<stdio.h>` 替换成系统头文件 `stdio.h` 的内容。一般以 `.i` 文件作为文件拓展名
- command
	- `cpp hello.c > hello.i`
	-