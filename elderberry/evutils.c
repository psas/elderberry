/* todo: append
 * DO NOT EDIT THIS FILE
 * to autogenerated output
 */


#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <ev.h>

static void modules_initialize(int argc, char *argv[], char *envp[], struct ev_loop * loop){

}

static void stop_cb(struct ev_loop *loop, ev_signal *w, int revents){
	ev_break(loop, EVBREAK_ALL);
}

int main(int argc, char *argv[], char *envp[]){
	printf(
	"\n ELDERBERRY FRAMEWORK V1.0 -- Copyright (C) 2013\n"
	" : Ron Astin, Clark Wachsmuth, Chris Glasser\n"
	" : Josef Mihalits, Jordan Hewitt, Michael Hooper\n"
	"\n"
	"----------------------------------------------------------------\n"
	" This program comes with ABSOLUTELY NO WARRANTY;\n for details please"
	" visit http://www.gnu.org/licenses/gpl.html.\n"
	"\n"
	" This is free software, and you are welcome to redistribute it\n"
	" under certain conditions; For details, please visit\n"
	" http://www.gnu.org/licenses/gpl.html.\n"
	"----------------------------------------------------------------\n"
	"\n"
	"\n"
	);

	int major = ev_version_major();
	int minor = ev_version_minor();
	if(!(major != EV_VERSION_MAJOR && minor >= EV_VERSION_MINOR)){
		errx(EXIT_FAILURE,
		     "Fatal: libev version mismatch. Expected %d.%d but got %d.%d",
		     EV_VERSION_MAJOR, EV_VERSION_MINOR, major, minor);
	}
	if(!ev_recommended_backends()){
		errx(EXIT_FAILURE, "Fatal: libev recommended backend not available");
	}

	struct ev_loop * loop;
	loop = ev_default_loop(0);
	if(!loop){
		errx(EXIT_FAILURE, "Fatal: could not initialize libev loop");
	}

	ev_signal stop;
	ev_signal_init(&stop, stop_cb, SIGINT);
	ev_signal_start(loop, &stop);
	modules_initialize(argc, argv, envp, loop)
	ev_run(loop, 0);

	return EXIT_SUCCESS;
}