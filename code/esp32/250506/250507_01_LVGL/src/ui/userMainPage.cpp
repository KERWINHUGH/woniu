#include "userMainPage.h"
#include "putPackagePage.h"
#include "getPackagePage.h"

void createMainPage(void)
{
        /*在整个屏幕上创建一个tabview，tab靠左，宽度是80px*/
        lv_obj_t * tabview;
        tabview = lv_tabview_create(lv_scr_act(), LV_DIR_LEFT, 80);
    
        lv_obj_set_style_bg_color(tabview, lv_palette_lighten(LV_PALETTE_PINK, 2), 0);
        //创建左边的tab btns
        lv_obj_t * tab_btns = lv_tabview_get_tab_btns(tabview);
        //设置tab btns的背景颜色
        lv_obj_set_style_bg_color(tab_btns, lv_palette_darken(LV_PALETTE_CYAN, 3), 0);
        //设置文字背景颜色
        lv_obj_set_style_text_color(tab_btns, lv_palette_lighten(LV_PALETTE_GREY, 5), 0);
        //设置边框样式
        lv_obj_set_style_border_side(tab_btns, LV_BORDER_SIDE_RIGHT, LV_PART_ITEMS | LV_STATE_CHECKED);
    
        /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
        lv_obj_t * tab1 = lv_tabview_add_tab(tabview, "ji\njian");
        lv_obj_t * tab2 = lv_tabview_add_tab(tabview, "qu\njian");
    
        lv_obj_set_style_bg_color(tab2, lv_palette_lighten(LV_PALETTE_AMBER, 3), 0);
        lv_obj_set_style_bg_opa(tab2, LV_OPA_COVER, 0);
    
        createPutPackagePage(tab1);
        // createGetPackagePage(tab2);
        //左边列不用滚动条
        lv_obj_clear_flag(lv_tabview_get_content(tabview), LV_OBJ_FLAG_SCROLLABLE);
}