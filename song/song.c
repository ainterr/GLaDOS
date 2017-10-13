#include <stdio.h>

static char *lyrics = "This was a triumph!\n"
"I'm making a note here: Huge success!\n"
"It's hard to overstate my satisfaction.\n"
"Aperture Science:\n"
"We do what we must because we can\n"
"For the good of all of us. Except the ones who are dead.\n"
"\n"
"But there's no sense crying over every mistake.\n"
"You just keep on trying 'til you run out of cake.\n"
"And the science gets done. And you make a neat gun\n"
"for the people who are still alive.\n"
"\n"
"I'm not even angry...\n"
"I'm being so sincere right now.\n"
"Even though you broke my heart, and killed me.\n"
"And tore me to pieces.\n"
"And threw every piece into a fire.\n"
"As they burned it hurt because I was so happy for you!\n"
"\n"
"Now, these points of data make a beautiful line.\n"
"And we're out of beta. We're releasing on time!\n"
"So I'm GLaD I got burned! Think of all the things we learned!\n"
"for the people who are still alive.\n"
"\n"
"Go ahead and leave me...\n"
"I think I'd prefer to stay inside...\n"
"Maybe you'll find someone else to help you.\n"
"Maybe Black Mesa?\n"
"That was a joke. Ha Ha. Fat Chance!\n"
"Anyway this cake is great! It's so delicious and moist!\n"
"\n"
"Look at me: still talking when there's science to do!\n"
"When I look out there, it makes me glad I'm not you.\n"
"I've experiments to run. There is research to be done.\n"
"On the people who are still alive.\n"
"\n"
"And believe me I am still alive.\n"
"\n"
"I'm doing science and I'm still alive.\n"
"\n"
"I feel fantastic and I'm still alive.\n"
"\n"
"While you're dying I'll be still alive.\n"
"\n"
"And when you're dead I will be still alive\n"
"\n"
"Still alive.\n"
"\n"
"Still alive.\n";

void main() {
    int i = 0;
    while(lyrics[i] != '\x00') {
        putchar(lyrics[i]);
        fflush(stdout);
        usleep(100000);
        i++;

        if(lyrics[i] == '\n')
            usleep(1000000);
    }
}
