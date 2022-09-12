/*
 * Copyright 2022 wtcat 
 */
#include <SDL2/SDL.h>
#include "lvgl.h"
#include "lvgl/demos/lv_demos.h"
#include "lv_drivers/sdl/sdl.h"
#include "mtrace.h"

#include <stdio.h>

#define SCREEN_HOR_RES     480
#define SCREEN_VER_RES     320

static void lv_driver_setup(void) {
    static lv_disp_drv_t dpd;
    static lv_disp_draw_buf_t bd;
    static lv_color_t front_buffer[SCREEN_HOR_RES * SCREEN_VER_RES];
    static lv_color_t background_buffer[SCREEN_HOR_RES * SCREEN_VER_RES];

    sdl_init();
    lv_disp_draw_buf_init(&bd, front_buffer, background_buffer,
        SCREEN_HOR_RES * SCREEN_VER_RES);
    lv_disp_drv_init(&dpd);
    dpd.hor_res = SCREEN_HOR_RES;
    dpd.ver_res = SCREEN_VER_RES;
    dpd.flush_cb = sdl_display_flush;
    dpd.draw_buf = &bd;
    dpd.full_refresh = 1;
    lv_disp_drv_register(&dpd);
}

static void lv_input_setup(void) {
    static lv_indev_drv_t input;
    lv_indev_t* input_mouse;

    /*Register a mouse input device*/
    lv_indev_drv_init(&input);
    input.type = LV_INDEV_TYPE_POINTER;
    input.read_cb = sdl_mouse_read;
    input_mouse = lv_indev_drv_register(&input);

    /*Set cursor. For simplicity set a HOME symbol now.*/
    lv_obj_t* mouse_cursor = lv_img_create(lv_scr_act());
    lv_img_set_src(mouse_cursor, LV_SYMBOL_HOME);
    lv_indev_set_cursor(input_mouse, mouse_cursor);
}

extern "C" void _lvgl_mem_init(void);
int main(int argc, char* argv[]) {
    _ui_mem_init();
    lv_init();
    lv_driver_setup();
    lv_input_setup();
    lv_demo_music();
    while (true) {
        lv_task_handler();
        SDL_Delay(10);
    }
    lv_deinit();
    return 0;
}
