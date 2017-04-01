#include "tree_window.h"

 Window *treeWindow;
 GBitmap *treeImage = NULL;
 BitmapLayer *treeImageLayer;
 int frame_no;
 const int NO_OF_FRAMES = 2;

 const int animation_images[] = {
  IMAGE_TREE_1,
  IMAGE_TREE_2
 };

static void load_sequence();

static void timer_handler(void *context) {
  if(frame_no == NO_OF_FRAMES - 1) {
    frame_no = 0;
  }

  if(treeImage != NULL){
    gbitmap_destroy(treeImage);
    treeImage = NULL;
  }

  treeImage = gbitmap_create_with_resource(animation_images[frame_no]);
  bitmap_layer_set_bitmap(treeImageLayer, treeImage);
  layer_mark_dirty(bitmap_layer_get_layer(treeImageLayer));
  frame_no++;
  app_time_register(80, timer_handler, NULL);
}

static void load_sequence() {
  frame_no = 0;
  app_timer_register(1, timer_handler, NULL);
}

/***********************************
* Load event of the tree window    *
***********************************/
void tree_window_load(Window *window)
{
  Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

  treeImageLayer = bitmap_layer_create(bounds);
  layer_add_child(window_layer, bitmap_layer_get_layer(treeImageLayer));
  APP_LOG(APP_LOG_LEVEL_DEBUG, "#5()");
  load_sequence();

}

/***********************************
* Unload event of the tree window  *
***********************************/
void tree_window_unload(Window *window)
{
  APP_LOG(APP_LOG_LEVEL_DEBUG, "#6()");
  gbitmap_destroy(treeImage);
  bitmap_layer_destroy(treeImageLayer);
}

/***********************************
* Initiates the tree window        *
***********************************/
void init_tree_window()
{
    treeWindow = window_create();
    APP_LOG(APP_LOG_LEVEL_DEBUG, "#7()");
    window_set_window_handlers(treeWindow, (WindowHandlers) { 
      .load = tree_window_load, 
      .unload = tree_window_unload });
  
}

/***********************************
* Deinit the tree window           *
***********************************/
void deinit_tree_window()
{
  window_destroy(treeWindow);
}

/***********************************
* Returns the window handle        *
***********************************/
Window *tree_window_get_window()
{
  return treeWindow;
}
