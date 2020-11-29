#define _GNU_SOURCE
#include <string.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <syscall.h>
static char child_stack[1048576];

/*TODO:
 * NETWORK ISOLATION +
 * FILESYSTEM ISOLATION +
 * PID ISOLATION +
 * Benchmark(sysbench)
 * cgroups
 * */



static int child_fn(void* arg) {
    
    printf("pid for child process: \n");
    system("echo $$");


//    mounting proc to isolate pids of parent from child
    system("mount -t proc proc /proc --make-private");
//    following command proves that child process cannot see parent's pids
    printf("Processes in child ns:\n");
    system("ps aux");


    system("ip link set veth1 up");
    system("ip addr add 10.1.1.1/24 dev veth1");

    //    sending packets to check to virtaul ethernet works
    system("ping -I veth1 10.1.1.2 -c 3");

//    printf("New NET namespace:\n\n");
//    system("ip link list");
//    printf("\n");

//    creating empty file
    system("dd if=/dev/zero of=image.img bs=1M count=100");
//    creating loop device from empty file
    system("losetup /dev/loop30 image.img");
//    making file system from file associated with loop device
    system("mkfs.ext4 image.img");
//    home directory for child process
    system("mkdir -p child_home2");
//    mounting loop device on folder
    system("mount -o loop /dev/loop30 child_home2");

//    creating file in child process that will not be visible to parent process
    system("touch child_home2/rand_file.txt");
    printf("View from children side:\n");
    system("ls child_home2/");


//    BENCHMARK
//    system("mkdir benchmarks");
//    system("sysbench cpu --cpu-max-prime=20000 run > benchmarks/cpu_benchmark.txt");
//    system("sysbench threads --num-threads=64 --thread-yields=100 --thread-locks=2 run >benchmarks/thread_benchmark.txt");
//    system("sysbench memory run > benchmarks/memory_benchmark.txt");
//    system("sysbench fileio --num-threads=16 --file-total-size=20G --file-test-mode=rndrw prepare");
//    system("sysbench fileio --num-threads=16 --file-total-size=20G --file-test-mode=rndrw run > benchmarks/fileio_benchmark.txt");
//    system("sysbench fileio --num-threads=16 --file-total-size=20G --file-test-mode=rndrw cleanup");




    // exiting from container
//    unmounting device from folder
    system("umount child_home2");
//    killing loop device
    system("losetup -d /dev/loop30");
//    unmounting proc folder back
    system("sudo -S umount /proc");


    sleep(5);
    return 0;
}

int main() {
    pid_t child_pid = clone(child_fn, child_stack+1048576, CLONE_NEWNS | CLONE_NEWNET | CLONE_NEWPID | SIGCHLD, NULL);
    char* cmd;

//    printf("pid for parent process: \n");
//    system("echo $$");


//    sprintf(str, "echo %d", child_pid);
//    system(str);
    printf("View from parent side:\n");
    system("ls child_home2");
    printf("\n");

//    Cgroups
//    system("mkdir /sys/fs/cgroup/cpu/test_group/");
//    system("mkdir /sys/fs/cgroup/memory/test_group/");
//
//    system("echo 400000 > /sys/fs/cgroup/cpu/test_group/cpu.cfs_quota_us");
//    system("echo 100000 > /sys/fs/cgroup/cpu/test_group/cpu.cfs_period_us");
//    system("echo 100MB > /sys/fs/cgroup/memory/test_group/memory.limit_in_bytes");
//    asprintf(&cmd,"echo %d > /sys/fs/cgroup/cpu/test_group/tasks",child_pid);
//    system(cmd);
//    asprintf(&cmd,"echo %d > /sys/fs/cgroup/memory/test_group/tasks",child_pid);
//    system(cmd);




//    creating virtual ethernet connection(veth0 <-> veth1)
    asprintf(&cmd,"ip link add name veth0 type veth peer name veth1 netns %d",child_pid);
    system(cmd);
    free(cmd);
//    activating and giving ip address
    system("ip link set veth0 up");
    system("ip addr add 10.1.1.2/24 dev veth0");

//    printf("\nOriginal NET namespace:\n\n");
//    system("ip link list");
//    printf("\n");




//    system("ip link del veth0");
//    system("ip link del veth1");

    waitpid(child_pid, NULL, 0);

//    system("rmdir /sys/fs/cgroup/cpu/test_group/");
//    system("rmdir /sys/fs/cgroup/memory/test_group/");

    return 0;
}