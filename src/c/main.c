#include <pebble.h>
#include "main.h"

static void init_windows() {
  init_tree_window(); 
}

static void deinit_windows(){
    deinit_tree_window();
}

static void init(){
  init_windows();
}

static void deinit() {
  deinit_windows();
}

int main(void) {
  init();
  window_stack_push(tree_window_get_window(), true);
  //window_stack_push(tree_window_get_window(), true);
  app_event_loop();

  deinit();
}