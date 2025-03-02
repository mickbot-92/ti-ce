#if defined FX || defined FXCG

#include "casio.h"
#include "file.h"

void reset_kbd(){
#ifdef FXCG
  SetSetupSetting( (unsigned int)0x14,0);
#endif
}

int clip_ymin=0;
void os_fill_rect(int x, int y, int width, int height, int color){
  if (x<0){ width+=x; x=0;}
  if (y<clip_ymin){ height+=y-clip_ymin; y=clip_ymin;}
  if (width<=0 || height<=0) return;
  if (x+width>LCD_WIDTH_PX) width=LCD_WIDTH_PX-x;
  if (y+height>LCD_HEIGHT_PX) height=LCD_HEIGHT_PX-y;
  if (width<=0 || height<=0) return;
#ifdef FX
  DISPBOX d={x,y,x+width-1,y+height-1};
  Bdisp_AreaClr_VRAM(&d);
  if (color==SDK_BLACK) Bdisp_AreaReverseVRAM(x,y,x+width-1,y+height-1);
#else
  unsigned short* VRAM = (unsigned short*)GetVRAMAddress();
  VRAM+=(y*384)+x;
  while(height--){
    int i=width;
    while(i--){
      *VRAM++ = color;
    }
    VRAM+=384-width;
  }
#endif
}

void statusflags(){
#ifdef FX
  int pos=100;
#else
  int pos=300;
#endif
  char mode=Setup_GetEntry(0x14);
  if (mode==1)
    Printmini(pos,0," SHIFT  ",0);
  if (mode==4)
    Printmini(pos,0," ALPHA  ",0);
  if (mode==8)
    Printmini(pos,0," alpha  ",0);
  if (mode==(char) 0x84)
    Printmini(pos,0," ALOCK  ",0);
  if (mode==(char) 0x88)
    Printmini(100,0," alock  ",0);
}

void get_time(int * heure,int * minute){
  int t=RTC_GetTicks();
  t=t/128;
  t=(t+30)/60; // minutes;
  *minute=t%60;
  *heure=(t/60) %24;
}

void set_time(int heure,int minute){
  unsigned char time[7];
  time[0]=0x20;
  time[1]=0x18;
  time[2]=0x10;
  time[3]=0x1;
#if 1
  time[4]=(heure/10)*16+heure % 10;
  time[5]=(minute/10)*16+minute % 10;
#else
  time[4]=heure;//(heure/10)*16+heure % 10;
  time[5]=minute; //(minute/10)*16+minute % 10;
#endif
  time[6]=0x30;
  RTC_SetDateTime(time);
}

int handle_f5(){
  char keyflag = Setup_GetEntry(0x14);
  if (keyflag == 0x04 || keyflag == 0x08 || keyflag == (char)0x84 || keyflag == (char)0x88) {
    // ^only applies if some sort of alpha (not locked) is already on
    if (keyflag == 0x08 || keyflag == (char)0x88) { //if lowercase
      SetSetupSetting( (unsigned int)0x14, keyflag-0x04);
      return 1; //do not process the key, because otherwise we will leave alpha status
    } else {
      SetSetupSetting( (unsigned int)0x14, keyflag+0x04);
      return 1; //do not process the key, because otherwise we will leave alpha status
    }
  }
  if (keyflag==0) {
    SetSetupSetting( (unsigned int)0x14, (char)0x88);	
  }
  return 0;
}

int filebrowser(char * filename,const char * extension,const char * title,int storage){
  return casio_fileBrowser(filename,extension,title);
}

//#include "console.h"
int ck_getkey(int * keyptr){
  int keyflag=GetSetupSetting( (unsigned int)0x14);
#ifdef FX
  GetKey((unsigned int *)keyptr);
#else
  GetKey(keyptr);
#endif
  if (*keyptr>=KEY_CTRL_F1 && *keyptr<=KEY_CTRL_F6 && (keyflag & 1)){
    *keyptr += KEY_CTRL_F7-KEY_CTRL_F1;
    // confirm(print_INT_(keyflag).c_str(),print_INT_(*keyptr).c_str());
  }
  if (*keyptr>=KEY_CTRL_F1 && *keyptr<=KEY_CTRL_F6 && (keyflag & 0xc)){
    *keyptr += KEY_CTRL_F13-KEY_CTRL_F1;;
    // confirm(print_INT_(keyflag).c_str(),print_INT_(*keyptr).c_str());
  }
  return 1;
}

bool erase_file(const char * filename){
  unsigned short pFile[MAX_FILENAME_SIZE+1];
  // create file in data folder (assumes data folder already exists)
  Bfile_StrToName_ncpy(pFile, (const unsigned char *)filename, strlen(filename)+1);
  int hFile = Bfile_OpenFile_OS(pFile, _OPENMODE_READWRITE); // Get handle
  if (hFile>=0){
    Bfile_CloseFile_OS(hFile);
    Bfile_DeleteEntry(pFile);
    return true;
  }
  return false;
}  

void sync_screen(){
  Bdisp_PutDisp_DD();
}

void clear_screen(){
  Bdisp_AllClr_VRAM();
}

int os_get_pixel(int x0,int y0){
#if 1
  return Bdisp_GetPoint_VRAM(x0,y0);
#else
  unsigned short* VRAM = (unsigned short*)GetVRAMAddress();
  VRAM += (y0*LCD_WIDTH_PX + x0);
  return *VRAM;
#endif
}


#ifdef FX // Casio monochrom
int os_draw_string(int x,int y,int c,int bg,const char * s,bool fake){
  if (!fake) 
    PrintXY(x,y,(const unsigned char *) s,c==SDK_WHITE?1:0);
  return x+6*strlen(s);  
}

int os_draw_string_medium(int x,int y,int c,int bg,const char * s,bool fake){
  return os_draw_string(x,y,c,bg,s,fake);
}

int os_draw_string_small(int x,int y,int c,int bg,const char * s,bool fake){
  if (!fake) 
    return PrintMini(x,y,(const unsigned char *) s,c==SDK_WHITE?1:0);
  return x+4*strlen(s);  
}

void os_set_pixel(int x0, int y0,int color) {
  if (x0<0 || x0>=LCD_WIDTH_PX || y0<clip_ymin || y0>=LCD_HEIGHT_PX)
    return;
  Bdisp_SetPoint_VRAM(x0,y0,color==SDK_WHITE?0:1);
}

void statuslinemsg(const char * s){
  os_fill_rect(0,0,LCD_WIDTH_PX,7,SDK_WHITE);
  Printmini(0,0,s,0);
}

int execution_in_progress=0;
volatile bool kbd_interrupted=false; int esc_flag=0;

static void check_execution_abort() {
  if (execution_in_progress) {
    // HourGlass();
#if 0
    unsigned int key=0;
    int res = GetKeyWait(KEYWAIT_HALTOFF_TIMEROFF,0,1,&key);//PRGM_GetKey_();
    if (res==KEYREP_KEYEVENT){
      //cout << "timer " << key << " " << res << endl;
      cout << "Key pressed" << endl;
      esc_flag = 1;
    }
#else
    unsigned short key=0;
    int c=0,r=0;
    int res = getkeywait(&c,&r,KEYWAIT_HALTOFF_TIMEROFF,0,1,&key);//PRGM_GetKey_();
    if (res==KEYREP_KEYEVENT){
      // cout << "timer " << c << " " << r << endl;
      if (c==1 && r==1){
	//cout << "AC/ON" << endl;
	esc_flag = 1;
	kbd_interrupted=true;
      }
    }
#endif      
  }
}
  
static int aborttimer = 0;
void set_abort(){
  //cout << "set_abort " << endl;
  for (int i=1;i<=5;++i){
    aborttimer=SetTimer(i,300,check_execution_abort);
    if (aborttimer>0){
      //cout << "abort " << aborttimer << " " << i << endl;
      aborttimer=i;
      return;
    }
  }
  aborttimer=-1;
  // aborttimer = Timer_Install(0, check_execution_abort, 100);
  // if (aborttimer > 0) { Timer_Start(aborttimer); }  
}
  
void clear_abort(){
  //cout << "clr_abort " << aborttimer << endl;
  if (aborttimer > 0) {
    KillTimer(aborttimer);
    //Timer_Stop(aborttimer);
    //Timer_Deinstall(aborttimer);
  }
}
void OS_InnerWait_ms(int ms){
  Sleep(ms); 
}

void HourGlass(){
}

int GetKeyWait_OS(int* column, int* row, int type_of_waiting, int timeout_period, int menu, unsigned short* keycode){
  getkeywait(column,row,type_of_waiting,timeout_period,menu,keycode);
}

#endif // FX

#ifdef FXCG
int os_draw_string(int x,int y,int c,int bg,const char * s,bool fake){
  if (!fake)
    PrintCXY(x, y, s, 0, -1, c, bg, 1,0);
  return x+18*strlen(s);  
}

int os_draw_string_medium(int x,int y,int c,int bg,const char * s,bool fake){
  int X=x,Y=y;
  PrintMini(&X, &Y, (unsigned char *)s, 0, 0xFFFFFFFF, 0, 0, c, bg, fake?0:1, 0);
  return X;
}

int os_draw_string_small(int x,int y,int c,int bg,const char * s,bool fake){
  int X=x,Y=y;
  PrintMini(&X, &Y, (unsigned char *)s, 0, 0xFFFFFFFF, 0, 0, c, bg, fake?0:1, 0);
  return X;
}

void Printmini(int x,int y,const char * s,int i){
  int X=x,Y=y;
  PrintMini(&X, &Y, (unsigned char *)s, i?4:0, 0xFFFFFFFF, 0, 0, SDK_BLACK, SDK_WHITE, 1, 0);
}

void os_set_pixel(int x0, int y0,int color) {
  //if (x0>100 && x0<150 && y0>100 && y0<150) cout << x0 << " " << y0 << '\n';
  //drawRectangle(x0,y0,1,1,color);
  if (x0<0 || x0>=LCD_WIDTH_PX || y0<clip_ymin || y0>=LCD_HEIGHT_PX)
    return;
  unsigned short* VRAM = (unsigned short*)GetVRAMAddress(); 
  VRAM += (y0*LCD_WIDTH_PX + x0);
  *VRAM=color;//COLOR_RED; // color;
}

void statuslinemsg(const char * s){
  EnableStatusArea(0);
  DefineStatusAreaFlags(3, SAF_BATTERY | SAF_TEXT | SAF_GLYPH | SAF_ALPHA_SHIFT, 0, 0);
  DefineStatusMessage((char *)s, 0, 0, 0);
  DisplayStatusArea();
  return;
}

static int PRGM_GetKey_() {
  unsigned char buffer[12];
  PRGM_GetKey_OS( buffer );
  return ( ( buffer[1] & 0x0F) *10 + ( ( buffer[2] & 0xF0) >> 4 ));
}
  
int execution_in_progress = 0; // set to 1 during program execution

static void check_execution_abort() {
  if (execution_in_progress) {
    HourGlass();
    short unsigned int key = PRGM_GetKey_();
    if(key == KEY_PRGM_ACON){
      // if (!ctrl_c) cout << "ACON pressed\n";
      esc_flag = 1;
      ctrl_c=kbd_interrupted=interrupted=true;
    }
  }
}
  
static int aborttimer = 0;
void set_abort(){
  aborttimer = Timer_Install(0, check_execution_abort, 100);
  if (aborttimer > 0) { Timer_Start(aborttimer); }
}
  
void clear_abort(){
  if (aborttimer > 0) {
    Timer_Stop(aborttimer);
    Timer_Deinstall(aborttimer);
  }
}
    
#endif

#endif // FX || FXCG

