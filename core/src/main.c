/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */


#include "stm32f7xx.h"
#include "stm32f769i_discovery.h"
#include "lvgl_hal/tft/tft.h"
#include "lvgl_hal/touchpad/touchpad.h"
#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"

static void SystemClock_Config(void);
static void CPU_CACHE_Enable(void);
static void MX_GPIO_Init(void);

void demo_screen_blit(void);
void demo_screen_blend(void);
void demo_screen_text(void);
void demo_bitmap(void);
void demo_bitmap_blend(void);
void demo_rle(void);
void demo_lz4(void);
void demo_img(void);

lv_obj_t * ui_Menu;
static lv_obj_t * my_rect;
static lv_obj_t * my_other_rect;
lv_obj_t * ui_Set_Minutes1;

const char *loremIpsumText = 
    "Donec pretium massa sapien, vel ultricies mauris malesuada ut. Sed id magna consequat, dictum turpis maximus, interdum neque. Integer tristique ex ac nulla tincidunt, id pellentesque massa imperdiet. Suspendisse convallis in metus ut egestas. Praesent magna elit, lacinia id turpis eu, fermentum accumsan leo. Mauris urna nibh, convallis vel augue sit amet, pretium dignissim elit. Quisque ornare sapien porttitor ex aliquet porta. Sed et lacus sit amet eros gravida pellentesque ut quis urna. Suspendisse aliquet nisl mauris, vitae consequat diam hendrerit id. Phasellus ligula urna, venenatis vitae neque sit amet, placerat faucibus ipsum. Integer eu felis sed quam mattis luctus. Vestibulum sed risus sit amet enim accumsan imperdiet quis quis neque. Donec accumsan aliquet sagittis. Pellentesque condimentum lobortis efficitur. Quisque sollicitudin tristique elit, euismod congue erat convallis ullamcorper. Etiam ultricies venenatis justo, at tincidunt turpis vulputate eu. Maecenas sodales condimentum tempus. Duis vitae ultricies ligula. Aliquam erat volutpat. Quisque porttitor nibh et urna placerat, quis congue sapien gravida. Vestibulum eget turpis at justo porttitor luctus a sed lectus. Aenean semper ante quis nunc efficitur, non varius tortor pulvinar. Morbi purus diam, condimentum id felis sit amet, commodo vehicula dui. Ut ut risus vitae nibh vehicula aliquam vitae eget nisi. Praesent vel tellus eget lacus luctus vulputate. Donec eget dapibus ex. Nam felis orci, gravida in velit et, gravida sodales lacus. Duis non scelerisque erat. Nullam fermentum vestibulum feugiat. Etiam egestas a nulla ut porta. Donec et lobortis massa, vel laoreet quam. Integer finibus nulla ut nisi dapibus, imperdiet suscipit dui scelerisque. Maecenas turpis neque, semper a molestie eget, semper convallis nibh. Nulla porttitor justo sed efficitur blandit. Ut commodo nulla nulla, nec bibendum purus gravida ut. Vivamus ultricies eget massa a porta. Sed consequat, nulla placerat fringilla placerat, est nisl rutrum erat, ut molestie risus enim ut ipsum.";

#define DEMO 6

int main(void) {

	/* Enable the CPU Cache */
	CPU_CACHE_Enable();

	/* STM32F7xx HAL library initialization:
	       - Configure the Flash prefetch
	       - Systick timer is configured by default as source of time base, but user
	         can eventually implement his proper time base source (a general purpose
	         timer for example or other time source), keeping in mind that Time base
	         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
	         handled in milliseconds basis.
	       - Set NVIC Group Priority to 4
	       - Low Level Initialization
	 */
	HAL_Init();

	SystemClock_Config();

    MX_GPIO_Init();

	lv_init();

	tft_init();
	touchpad_init();

#if DEMO == 0
	lv_demo_widgets();
#elif DEMO == 1
    demo_screen_blit();
#elif DEMO == 2
    demo_screen_blend();
#elif DEMO == 3
    demo_screen_text();
#elif DEMO == 4
    demo_bitmap();
#elif DEMO == 5
    demo_bitmap_blend();
#elif DEMO == 6
    demo_rle();
#elif DEMO == 7
    demo_lz4();
#elif DEMO == 8
    demo_img();
#else
#error
#endif

	while(1) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
	    lv_task_handler();
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
        lv_obj_invalidate(lv_scr_act());
		HAL_Delay(100);
	}
}

void demo_img()
{
    ui_Menu = lv_obj_create(NULL);

    LV_IMAGE_DECLARE(st_300x300_rgb565);
    lv_obj_t * comp_img = lv_image_create(ui_Menu);
    lv_image_set_src(comp_img, &st_300x300_rgb565);

    lv_disp_load_scr(ui_Menu);
}

void demo_rle()
{
    ui_Menu = lv_obj_create(NULL);

    LV_IMAGE_DECLARE(st_300x300_rle_rgb565);
    lv_obj_t * comp_img = lv_image_create(ui_Menu);
    lv_image_set_src(comp_img, &st_300x300_rle_rgb565);

    lv_disp_load_scr(ui_Menu);
}

void demo_lz4()
{
    ui_Menu = lv_obj_create(NULL);

    LV_IMAGE_DECLARE(st_300x300_lz4_rgb565);
    lv_obj_t * comp_img = lv_image_create(ui_Menu);
    lv_image_set_src(comp_img, &st_300x300_lz4_rgb565);

    lv_disp_load_scr(ui_Menu);
}

void demo_bitmap()
{
    ui_Menu = lv_obj_create(NULL);

    LV_IMAGE_DECLARE(forest_800x480);
    lv_obj_t * forest = lv_image_create(ui_Menu);
    lv_image_set_src(forest, &forest_800x480);

    lv_disp_load_scr(ui_Menu);
}

void demo_bitmap_blend()
{
    ui_Menu = lv_obj_create(NULL);

    my_rect = lv_obj_create(ui_Menu);
    lv_obj_set_size(my_rect, 800, 480);
    lv_obj_set_pos(my_rect, 0, 0);
    lv_obj_set_style_bg_color(my_rect, (lv_color_t)LV_COLOR_MAKE(0, 0, 255), 0);
    lv_obj_set_style_bg_opa(my_rect, LV_OPA_100, 0);
    lv_obj_set_style_radius(my_rect, 0, 0);

    LV_IMAGE_DECLARE(forest_800x480);
    lv_obj_t * forest = lv_image_create(ui_Menu);
    lv_image_set_src(forest, &forest_800x480);
    lv_obj_set_style_image_opa(forest, LV_OPA_50, 0);

    lv_disp_load_scr(ui_Menu);
}

void demo_screen_blit()
{
    ui_Menu = lv_obj_create(NULL);

    my_rect = lv_obj_create(ui_Menu);
    lv_obj_set_size(my_rect, 800, 480);
    lv_obj_set_pos(my_rect, 0, 0);
    lv_obj_set_style_bg_color(my_rect, (lv_color_t)LV_COLOR_MAKE(0, 0, 255), 0);

    lv_obj_set_style_radius(my_rect, 0, 0);

    lv_disp_load_scr(ui_Menu);
}

void demo_screen_blend()
{
    ui_Menu = lv_obj_create(NULL);

    my_rect = lv_obj_create(ui_Menu);
    lv_obj_set_size(my_rect, 800, 480);
    lv_obj_set_pos(my_rect, 0, 0);
    lv_obj_set_style_bg_color(my_rect, (lv_color_t)LV_COLOR_MAKE(0, 0, 255), 0);
    lv_obj_set_style_bg_opa(my_rect, LV_OPA_100, 0);
    lv_obj_set_style_radius(my_rect, 0, 0);
    lv_obj_move_background(my_rect);

    my_other_rect = lv_obj_create(ui_Menu);
    lv_obj_set_size(my_other_rect, 800, 480);
    lv_obj_set_pos(my_other_rect, 0, 0);
    lv_obj_set_style_bg_color(my_other_rect, (lv_color_t)LV_COLOR_MAKE(255, 0, 0), 0);
    lv_obj_set_style_bg_opa(my_other_rect, LV_OPA_50, 0);
    lv_obj_set_style_radius(my_other_rect, 0, 0);
    lv_obj_move_foreground(my_other_rect);

    lv_disp_load_scr(ui_Menu);
}

void demo_screen_text()
{
    ui_Menu = lv_obj_create(NULL);

    my_rect = lv_obj_create(ui_Menu);
    lv_obj_set_size(my_rect, 800, 480);
    lv_obj_set_pos(my_rect, 0, 0);
    lv_obj_set_style_bg_color(my_rect, (lv_color_t)LV_COLOR_MAKE(0, 0, 255), 0);
    lv_obj_set_style_radius(my_rect, 0, 0);

    ui_Set_Minutes1 = lv_label_create(ui_Menu);
    lv_obj_set_width(ui_Set_Minutes1, lv_pct(80));   /// 1
    lv_obj_set_height(ui_Set_Minutes1, LV_SIZE_CONTENT);    /// 1
    lv_label_set_text(ui_Set_Minutes1, loremIpsumText);
    lv_obj_set_style_text_color(ui_Set_Minutes1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Set_Minutes1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_disp_load_scr(ui_Menu);
}

void GPIO_1_SET(int state)
{
    if (state) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
    }
    else {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
    }
}

static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOJ_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_1, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin     = GPIO_PIN_7;
    GPIO_InitStruct.Mode    = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull    = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed   = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin     = GPIO_PIN_6;
    GPIO_InitStruct.Mode    = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull    = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed   = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin     = GPIO_PIN_6;
    GPIO_InitStruct.Mode    = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull    = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed   = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin     = GPIO_PIN_1;
    GPIO_InitStruct.Mode    = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull    = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed   = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);
}

static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  RCC_OscInitStruct.PLL.PLLR = 7;

  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }

  /* Activate the OverDrive to reach the 216 MHz Frequency */
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
}


/**
* @brief  CPU L1-Cache enable.
* @param  None
* @retval None
*/
static void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}
