/*

X version of lock()/unlock() that uses XInitThreads and a pipe for awake().

This code is not normally used. Instead an gnui::RecursiveMutex is used,
see the code in ../lock.cxx.

We don't use this by default for 2 reasons:

1. Simple timing shows it to be abysimally slow, like 2x slower, probably
   due to overhead added to every Xlib call, because those morons thought
   they had to do such fine-scale locking.
2. It requires the Xdisplay to be open, making it impossible to make a
   program that works as a command-line version when DISPLAY is not set.
3. It may interfere with XInput processing. I took a guess at how to
   work around this but it is untested.

If you want this, edit config.h and set USE_X11_MULTITHREADING to 1.

*/

#include <gnui/x.h>
#include <unistd.h>
#include <fcntl.h>

extern void (*gnui_lock_function)();
extern void (*gnui_unlock_function)();
static void init_function();
static void (*init_or_lock_function)() = init_function;

static void lock_function() {XLockDisplay(gnui::xdisplay);}
static void unlock_function() {XUnlockDisplay(gnui::xdisplay);}

static void* thread_message_;
static void thread_awake_cb(int fd, void*) {
  while (read(fd, &thread_message_, sizeof(void*)) > 0);
}
static int thread_filedes[2];

static void init_function() {
  XInitThreads();
  gnui::open_display();
  // Init threads communication pipe to let threads awake FLTK from wait
  pipe(thread_filedes);
  fcntl(thread_filedes[0], F_SETFL, O_NONBLOCK);
  gnui::add_fd(thread_filedes[0], gnui::READ, thread_awake_cb);
  gnui_lock_function = init_or_lock_function = lock_function;
  gnui_unlock_function = unlock_function;
  lock_function();
}

void gnui::lock() {init_or_lock_function();}

void gnui::unlock() {gnui_unlock_function();}

void gnui::awake(void* msg) {
  write(thread_filedes[1], &msg, sizeof(void*));
}

void* gnui::thread_message() {
  void* r = thread_message_;
  thread_message_ = 0;
  return r;
}
