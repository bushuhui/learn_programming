#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

#include <stdio.h>
#include <iostream>
#include <string>


#ifdef _WIN32
#include <windows.h>

STARTUPINFO sti = {0};
SECURITY_ATTRIBUTES sats = {0};
PROCESS_INFORMATION pi = {0};
HANDLE pipin_w, pipin_r, pipout_w, pipout_r;
BYTE buffer[2048];
DWORD writ, excode, read, available;


void ConnectToEngine(char* path)
{
    std::string exepath = path + ".exe";
    
    pipin_w = pipin_r = pipout_w = pipout_r = NULL;
    sats.nLength = sizeof(sats);
    sats.bInheritHandle = TRUE;
    sats.lpSecurityDescriptor = NULL;

    CreatePipe(&pipout_r, &pipout_w, &sats, 0);
    CreatePipe(&pipin_r, &pipin_w, &sats, 0);
         
    sti.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    sti.wShowWindow = SW_HIDE;
    sti.hStdInput = pipin_r;
    sti.hStdOutput = pipout_w;
    sti.hStdError = pipout_w;

    CreateProcess(NULL, exepath.c_str(), NULL, NULL, TRUE,0, NULL, NULL, &sti, &pi);
}


std::string getNextMove(std::string position)
{     
	std::string str;
	position = "position startpos moves "+position+"\ngo\n";	

	WriteFile(pipin_w, position.c_str(), position.length(),&writ, NULL);
    Sleep(500);
        
    PeekNamedPipe(pipout_r, buffer,sizeof(buffer), &read, &available, NULL);   
    do
    {   
        ZeroMemory(buffer, sizeof(buffer));
		if(!ReadFile(pipout_r, buffer, sizeof(buffer), &read, NULL) || !read) break; 
        buffer[read] = 0;	
		str+=(char*)buffer;
    }
    while(read >= sizeof(buffer));

	int n = str.find("bestmove");  
	if (n!=-1) return str.substr(n+9,4);
			 
    return "error";
}


void CloseConnection()
{
	WriteFile(pipin_w, "quit\n", 5,&writ, NULL);
    if(pipin_w != NULL) CloseHandle(pipin_w);
    if(pipin_r != NULL) CloseHandle(pipin_r);
    if(pipout_w != NULL) CloseHandle(pipout_w);
    if(pipout_r != NULL) CloseHandle(pipout_r);
    if(pi.hProcess != NULL) CloseHandle(pi.hProcess);
    if(pi.hThread != NULL) CloseHandle(pi.hThread);
}

#else // Linux

#include <unistd.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

pid_t pid = 0;
int inpipefd[2];
int outpipefd[2];

void ConnectToEngine(char* path)
{
    char cwd[PATH_MAX];
    char exepath[PATH_MAX];
    
    if( getcwd(cwd, sizeof(cwd)) == NULL ) 
    {
        printf("ERR: Faild to get current working directory!\n");
    }

    pipe(inpipefd);
    pipe(outpipefd);

    pid = fork();
    if (pid == 0)
    {
        // Child
        dup2(outpipefd[0], STDIN_FILENO);
        dup2(inpipefd[1], STDOUT_FILENO);
        dup2(inpipefd[1], STDERR_FILENO);

        //ask kernel to deliver SIGTERM in case the parent dies
        prctl(PR_SET_PDEATHSIG, SIGTERM);

        //replace tee with your process
        sprintf(exepath, "%s/%s", cwd, path);
        execl(exepath, path, (char*) NULL);

        // Nothing below this line should be executed by child process. If so,
        // it means that the execl function wasn't successfull, so lets exit:
        exit(0);
    }

    // The code below will be executed only by parent. You can write and read
    // from the child using pipefd descriptors, and you can send signals to
    // the process using its pid by kill() function. If the child process will
    // exit unexpectedly, the parent process will obtain SIGCHLD signal that
    // can be handled (e.g. you can respawn the child process).

    //close unused pipe ends
    close(outpipefd[0]);
    close(inpipefd[1]);
}


std::string getNextMove(std::string position)
{
    char buffer[2048];
	std::string str;
    
    // write our move to stockfish
	std::string str_pos = "position startpos moves " + 
                           position + "\ngo\n";
    //printf("move: %s\n", str_pos.c_str());
    
    write(outpipefd[1], str_pos.c_str(), str_pos.length());
    usleep(500000);
    
    // read results from stockfish
    do
    {
        int nread = read(inpipefd[0], buffer, sizeof(buffer));
        buffer[nread] = 0;
        str += buffer;
        
        if( nread < sizeof(buffer) ) break;
    } while(1);
        
    // get best move
	int n = str.find("bestmove");  
	if (n != -1) 
    {
        std::string str_res = str.substr(n+9, 4);
        //printf("res : %s\n", str_res.c_str());
        
        return str_res;
    }
    
    return "error";
}


void CloseConnection()
{
    int status;
    
    write(outpipefd[1], "quit\n", 5);
    usleep(500000);

    kill(pid, SIGKILL); //send SIGKILL signal to the child process
    waitpid(pid, &status, 0);
}


#endif // end of _WIN32

#endif // end of __CONNECTOR_H__
