#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
	int pipefd[2];
	pid_t pid;
	char buf[256];
	pid= fork();
	if(pid == 0){
		//Child reads from pipe
		close(pipefd[1]);
		read(pipefd[0],buf,sizeof(buf));
		printf("Child received this %s \n",buf);
		close(pipefd[0]);
	}
	else{
		//Parent writes to the pipe
		close(pipefd[0]);
		const char * msg = "Hello from parent!\n";
		write(pipefd[1],msg,strlen(msg)+1);
		close(pipefd[1]);
		wait(NULL);
	}
	return 0;
}
