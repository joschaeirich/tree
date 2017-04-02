#include "tree_window.h"

 Window *treeWindow;
 GBitmap *treeImage = NULL;
 BitmapLayer *treeImageLayer;
 int frame_no;
 const int NO_OF_FRAMES = 47;

 const int animation_images[] = {
        RESOURCE_ID_IMAGE_TREE_1,
     RESOURCE_ID_IMAGE_TREE_2,
     RESOURCE_ID_IMAGE_TREE_3,
     RESOURCE_ID_IMAGE_TREE_4,
     RESOURCE_ID_IMAGE_TREE_5,
     RESOURCE_ID_IMAGE_TREE_6,
     RESOURCE_ID_IMAGE_TREE_7,
     RESOURCE_ID_IMAGE_TREE_8,
     RESOURCE_ID_IMAGE_TREE_9,
        RESOURCE_ID_IMAGE_TREE_10,
     RESOURCE_ID_IMAGE_TREE_11,
     RESOURCE_ID_IMAGE_TREE_12,
     RESOURCE_ID_IMAGE_TREE_13,
     RESOURCE_ID_IMAGE_TREE_14,
     RESOURCE_ID_IMAGE_TREE_15,
     RESOURCE_ID_IMAGE_TREE_16,
     RESOURCE_ID_IMAGE_TREE_17,
     RESOURCE_ID_IMAGE_TREE_18,
     RESOURCE_ID_IMAGE_TREE_19,
        RESOURCE_ID_IMAGE_TREE_20,
     RESOURCE_ID_IMAGE_TREE_21,
     RESOURCE_ID_IMAGE_TREE_22,
     RESOURCE_ID_IMAGE_TREE_23,
     RESOURCE_ID_IMAGE_TREE_24,
     RESOURCE_ID_IMAGE_TREE_25,
     RESOURCE_ID_IMAGE_TREE_26,
     RESOURCE_ID_IMAGE_TREE_27,
     RESOURCE_ID_IMAGE_TREE_28,
     RESOURCE_ID_IMAGE_TREE_29,
        RESOURCE_ID_IMAGE_TREE_30,
     RESOURCE_ID_IMAGE_TREE_31,
     RESOURCE_ID_IMAGE_TREE_32,
     RESOURCE_ID_IMAGE_TREE_33,
     RESOURCE_ID_IMAGE_TREE_34,
     RESOURCE_ID_IMAGE_TREE_35,
     RESOURCE_ID_IMAGE_TREE_36,
     RESOURCE_ID_IMAGE_TREE_37,
     RESOURCE_ID_IMAGE_TREE_38,
     RESOURCE_ID_IMAGE_TREE_39,
        RESOURCE_ID_IMAGE_TREE_40,
     RESOURCE_ID_IMAGE_TREE_41,
     RESOURCE_ID_IMAGE_TREE_42,
     RESOURCE_ID_IMAGE_TREE_43,
     RESOURCE_ID_IMAGE_TREE_44,
     RESOURCE_ID_IMAGE_TREE_45,
     RESOURCE_ID_IMAGE_TREE_46,
     RESOURCE_ID_IMAGE_TREE_47

 };

static void load_sequence();

static void timer_handler(void *context) {
  if(frame_no <= NO_OF_FRAMES) {

  if(treeImage != NULL){
    gbitmap_destroy(treeImage);
    treeImage = NULL;
  }

  treeImage = gbitmap_create_with_resource(animation_images[frame_no]);
  bitmap_layer_set_bitmap(treeImageLayer, treeImage);
  layer_mark_dirty(bitmap_layer_get_layer(treeImageLayer));
  frame_no++;
  app_timer_register(45, timer_handler, NULL);
  }
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
