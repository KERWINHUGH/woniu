# 修改makefile文件如下：
# 定义生成的可执行文件  
CFLAGS += -I/usr/local/include/cjson
LDFLAGS += -L/usr/local/lib -lcjson
 
all: thread  
  
normal:   
	@gcc $(n).c  -o $(n)
	@./$(n)
	@rm -f $(n)
    
thread:   
	@gcc -Wall -Wextra -Werror -pedantic -std=c11 $(CFLAGS) $(n).c operation.c sysOpera.c data.c json.c list.c  tcp_client.c -o $(n) -lsqlite3 -lpthread  $(LDFLAGS)                      
	@./$(n)
	@rm -f $(n)
# 清理生成的文件  
clean:  
	rm -f $(n)
