# Linux PROC 

The linux file-system stores information about the processes of the OS in `/proc/`
and in `/etc/`

For example:  
- We can access information about the OS by using `cat /etc/os-release`
- We can check the meminfo by running `cat /proc/meminfo`
- We can check uptime by running `cat /proc/uptime`
- We can check processes by running `cat /proc/stat`
- We can check the kernel version by running `cat /etc/kernel`
- We can check the `proc/stat` for CPU info
    - there is essentially an aggregated clock tick on the first cpu key
    - these are called jiffies
    - these jiffies are based on the total system uptime
    - this is not a good measure of current time utilization
    - you may need to measure the current utilization versus the last second in order to get a better sense of "true" cpu utilization
- more information on cpu utilization:

    ```text
    The very first "cpu" line aggregates the numbers in all of the other "cpuN" lines. These numbers identify the amount of time the CPU has spent performing different kinds of work. Time units are in USER_HZ (typically hundredths of a second). The meanings of the columns are as follows, from left to right:

    user: normal processes executing in user mode
    nice: niced processes executing in user mode
    system: processes executing in kernel mode
    idle: twiddling thumbs
    iowait: In a word, iowait stands for waiting for I/O to complete. But there are several problems:
    Cpu will not wait for I/O to complete, iowait is the time that a task is waiting for I/O to complete. When cpu goes into idle state for outstanding task io, another task will be scheduled on this CPU.
    In a multi-core CPU, the task waiting for I/O to complete is not running on any CPU, so the iowait of each CPU is difficult to calculate.
    The value of iowait field in /proc/stat will decrease in certain conditions. So, the iowait is not reliable by reading from /proc/stat.
    irq: servicing interrupts
    softirq: servicing softirqs
    steal: involuntary wait
    guest: running a normal guest
    guest_nice: running a niced guest
    ```


