#ifndef CASIO_H
#define CASIO_H
#include "defs.h"

#define SDK_BLACK 0
#define SDK_WHITE 0xffff

#ifdef FX // FX monochrom
#define max_heap_size 128

#include "libfx.h"
#include <gint/kmalloc.h>
#include "syscalls.h"


// font sizes
#define C24 8 // 24 on 90
#define C18 8 // 18
#define C10 7 // 18
#define C6 2 // 6
#define C58 58

extern "C" {
  inline void os_wait_1ms(int ms){ Sleep(ms); }
  inline void Printmini(int x,int y,const char * s,int i){ PrintMini(x,y,(const unsigned char *)s,i);}
  inline void Printxy(int x,int y,const char * s,int i){ PrintXY(x,y,(const unsigned char*)s,i);}
}

#else // FXCG color
#define max_heap_size 2560
inline void  Cursor_SetFlashMode(int){}
#define Setup_GetEntry GetSetupSetting
#define _OPENMODE_READWRITE READWRITE
#define _OPENMODE_READ READ
#define MINI_REV 4
#define MINI_OVER 0
#define C24 24 // 24 on 90
#define C18 18 // 18
#define C10 18 // 18
#define C6 6 // 6
#define C58 58*3

#include <fxcg/display.h>
#include <fxcg/file.h>
#include <fxcg/keyboard.h>
#include <fxcg/system.h>
#include <fxcg/misc.h>
#include <fxcg/app.h>
#include <fxcg/serial.h>
extern "C" {
  void Printmini(int x,int y,const char * s,int i);
  inline void Printxy(int x,int y,const char * s,int i){
    PrintCXY(x*3, y*3, (char *) s, i?1:0, -1, SDK_BLACK, SDK_WHITE, 1,0);
  }
#include <fxcg/rtc.h>
  extern int execution_in_progress_py;
  extern volatile int ctrl_c_py;
  void set_abort_py();
  void clear_abort_py();
  inline void os_wait_1ms(int ms){ OS_InnerWait_ms(ms); }
}
#include <fxcg/heap.h>
#include <gint/kmalloc.h>

#endif

void statusflags();

extern "C" {
  
  inline bool waitforvblank(){ }
  bool back_key_pressed() ;
  inline bool os_set_angle_unit(int mode){ } // FIXME
  inline int os_get_angle_unit(){return 0;} // FIXME
  double millis(); //extern int time_shift;
  int file_exists(const char * filename);
  bool erase_file(const char * filename);
  const char * read_file(const char * filename);
  bool write_file(const char * filename,const char * s,size_t len);

#define MAX_NUMBER_OF_FILENAMES 255
  // int os_file_browser(const char ** filenames,int maxrecords,const char * extension,int storage);
  int filebrowser(char * filename,const char * extension,const char * title,int storage);
  inline int fileBrowser(char * filename,const char * extension,const char * title){ return filebrowser(filename,extension,title,2); /* flash storage */ }

  void sync_screen(); void clear_screen();
  void os_set_pixel(int x,int y,int c);
  void os_fill_rect(int x,int y,int w,int h,int c);
  inline void drawRectangle(int x,int y,int w,int h,int c){
    if (w>=0 && h>=0)
      os_fill_rect(x,y,w,h,c);
  }  
  int os_get_pixel(int x,int y);
  /* returns new x position */
  int os_draw_string(int x,int y,int c,int bg,const char * s,bool fake);
  inline int os_draw_string_(int x,int y,const char * s){ return os_draw_string(x,y,SDK_BLACK,SDK_WHITE,s,false);}
  int os_draw_string_small(int x,int y,int c,int bg,const char * s,bool fake);
  inline int os_draw_string_small_(int x,int y,const char * s){ return os_draw_string_small(x,y,SDK_BLACK,SDK_WHITE,s,false);}
  
  int os_draw_string_medium(int x,int y,int c,int bg,const char * s,bool fake);
  inline int os_draw_string_medium_(int x,int y,const char * s){ return os_draw_string_medium(x,y,SDK_BLACK,SDK_WHITE,s,false);}

  int getkey(int allow_suspend); // transformed
  int ck_getkey(int * keyptr); // Casio like  
  void enable_back_interrupt();
  void set_abort();
  void disable_back_interrupt();
  void clear_abort();
  bool isalphaactive();
  bool alphawasactive(int * key);
  void lock_alpha();
  void reset_kbd();
  extern int execution_in_progress ; // set to 1 during program execution
  extern volatile bool kbd_interrupted; extern int esc_flag;
  int GetKeyWait_OS(int* column, int* row, int type_of_waiting, int timeout_period, int menu, unsigned short* keycode);
  void OS_InnerWait_ms(int ms);
  void HourGlass();  

  void statuslinemsg(const char * msg);
  void statusline(int mode);
  bool iskeydown(int key);
  void get_time(int * heure,int * minute);
  void set_time(int heure,int minute);
  int handle_f5();

}  

#endif // CASIO_H
