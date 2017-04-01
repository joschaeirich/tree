#include "tree_window.h"

 Window *treeWindow;
 GBitmap *treeImage = NULL;
 GBitmapSequence *treeSequence = NULL;
 BitmapLayer *treeImageLayer;

//static void load_sequence();

//static void timer_handler(void *context){
//  uint32_t next_delay;

//Advance to the next APNG frame
    
//  if (gbitmap_sequence_update_bitmap_next_frame(treeSequence, treeImage, &next_delay)){
//    bitmap_layer_set_bitmap(treeImageLayer,treeImage);
       
//    layer_mark_dirty(bitmap_layer_get_layer(treeImageLayer));
    
    // Timer for that delay
//    uint32_t first_delay_ms = 10;
       
 //   app_timer_register(next_delay, timer_handler, NULL);
    
//  }else {
//    // start again
       
//    load_sequence();
//  }
//}

/***********************************
* Any button single click handler  *
***********************************/
//void tree_single_click_handler(ClickRecognizerRef recognizer, void *context)
//{
//  APP_LOG(APP_LOG_LEVEL_INFO, "One button is pressed on tree_window. Exiting now!");
//  window_stack_pop_all(true);
//}

/***********************************
* CCP of the tree window           *
***********************************/
//void tree_click_config_provider(void *context){
//  window_single_click_subscribe(BUTTON_ID_UP, (ClickHandler)tree_single_click_handler);
//  window_single_click_subscribe(BUTTON_ID_DOWN, (ClickHandler)tree_single_click_handler);
//  window_single_click_subscribe(BUTTON_ID_BACK, (ClickHandler)tree_single_click_handler);
//  window_single_click_subscribe(BUTTON_ID_SELECT, (ClickHandler)tree_single_click_handler);
//}

static void load_sequence();

static void timer_handler(void *context) {
  uint32_t next_delay;

  // Advance to the next APNG frame
  if(gbitmap_sequence_update_bitmap_next_frame(treeSequence, treeImage, &next_delay)) {

    bitmap_layer_set_bitmap(treeImageLayer, treeImage);

    layer_mark_dirty(bitmap_layer_get_layer(treeImageLayer));

    // Timer for that delay

    app_timer_register(next_delay, timer_handler, NULL);
  } else {

    // Start again
      /*
      ** Docs say restart, but this does NOT restart after:
      gbitmap_sequence_update_bitmap_next_frame() results in error trace
[ERROR] tmap_sequence.c:219: APNG memory allocation failed
[ERROR] tmap_sequence.c:336: gbitmap_sequence failed to update bitmap

from https://github.com/pebble-hacks/gbitmap-sequence-example/blob/master/src/gbitmap-sequence.c
call load_sequence(); instead
    gbitmap_sequence_restart(s_sequence);
    */
      load_sequence();
  }

}


static void load_sequence() {
  // Free old data
  if(treeSequence) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "#1");
    gbitmap_sequence_destroy(treeSequence);
    treeSequence = NULL;
  }
  if(treeImage) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "#2");
    gbitmap_destroy(treeImage);
    treeImage = NULL;
  }

APP_LOG(APP_LOG_LEVEL_DEBUG, "#3");
  // Create sequence
  treeSequence = gbitmap_sequence_create_with_resource(RESOURCE_ID_IMAGE_TREE1_Black_White);

  // Create GBitmap
APP_LOG(APP_LOG_LEVEL_DEBUG, "#4");
  treeImage = gbitmap_create_blank(gbitmap_sequence_get_bitmap_size(treeSequence), GBitmapFormat8Bit);

  // Begin animation
  app_timer_register(1, timer_handler, NULL);
}





/***********************************
* Load event of the tree window    *
***********************************/
void tree_window_load(Window *window)
{
  Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);
  
  
  // treeWindow = window_create(); //apper second times
//#ifndef PBL_SDK_3
//  window_set_fullscreen(treeWindow, true);
//#endif

    
  //treeImage = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TREE1_Black_White);
  
  // Loads a png Image from ressources
  //treeImageLayer = bitmap_layer_create(GRect(0, 0, 100, 100));
  
  //bitmap_layer_set_bitmap(treeImageLayer, treeImage);
  //bitmap_layer_set_compositing_mode(treeImageLayer, GCompOpSet);
  //layer_add_child(window_layer, bitmap_layer_get_layer(treeImageLayer));

  // override back_button_manager
  //window_set_click_config_provider(window, (ClickConfigProvider) tree_click_config_provider);
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
