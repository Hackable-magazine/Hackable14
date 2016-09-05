#include <epd.h>

void setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  epd_init();
  epd_wakeup();
  epd_set_memory(MEM_NAND);
  //epd_set_memory(MEM_TF);
  epd_load_pic();
  //epd_screen_rotation(EPD_NORMAL);
}

void loop(void) {
  char flag = 0;
  
  //base_draw();

  //draw_text_demo();

  epd_set_color(BLACK, WHITE);

  epd_clear();
  epd_udpate();
  epd_clear();
  epd_disp_bitmap("HLOGO.BMP", 350, 165);
  epd_disp_bitmap("MOI4.BMP", 50, 165);
  
  epd_set_en_font(ASCII32);
  epd_disp_string("Hackable Magazine #14", 0, 0);

  epd_set_en_font(ASCII48);
  epd_disp_string("Hackable Magazine #14", 0, 32);

  epd_set_en_font(ASCII64);
  epd_disp_string("Hackable Magazine #14", 0, 80);
  epd_udpate();

  delay(3000);
  epd_clear();
  
  epd_enter_stopmode();

  while (1) {
    if(flag) {
      flag = 0;
      digitalWrite(LED_BUILTIN, LOW);
    } else {
      flag = 1;
      digitalWrite(LED_BUILTIN, HIGH);
    }
    delay(500);
  }
}


