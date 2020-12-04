#include <lemon/util.h>

#include <stdio.h>

#include <vector>

int main(int argc, char** argv){
    std::vector<lemon_process_info_t> procs;
    Lemon::GetProcessList(procs);

    printf("Process:        PID:   Uptime:\n\n");
    for(lemon_process_info_t proc : procs){
        printf("%14s  %4lu  %lus\n", proc.name, proc.pid, proc.runningTime);
    }

    return 0;
}