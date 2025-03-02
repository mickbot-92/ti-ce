#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/lcd.h>

//#define DBG 1
#define MALLOC_MINSIZE 6 // minimal size (avoid blocks that are too small)

#define WITH_LCDMALLOC 1 // uses upper part of lcd for malloc
/* 
   attempt to include kmalloc from Lephe, but does not work
   changes B. Parisse to add heap from upper part of LCD 
   recompile toolchain from toolchain main directory
   make
   make install PREFIX=tmp
   check that tmp/lib/libc is fine then
   cd tmp/lib/libc
   cp allocator_standard.c.src arena_gint.c.src arena_osheap.c.src kmalloc.c.src ~/CEdev/lib/libc
   add arena_gint.c.src, arena_osheap.c.src and kmalloc.c.src 
   to app_tools/linker_script

   N.B.: assumes graphic mode is 8bpp and upper part is not used

   8bpp mode can be initialized with code like
   boot_ClearVRAM();

   // lcd_BacklightLevel=minBrightness;
   for (int r=0;r<4;r++){
   for (int g=0;g<8;g++){
   for (int b=0;b<4;b++){
   int R=r*255/3, G=g*255/7, B=b*255/3;
   int RGB=sdk_rgb(R,G,B);
   lcd_Palette[(r<<5)|(g<<2)|b]=RGB;//gfx_RGBTo1555(R,G,B);
   //dbg_printf("lcd_Palette[%i] R=%i/255 G=%i/255 B=%i/255 RGB565=%x\n",(r<<5)|(g<<2)|b,R,G,B,RGB);
   }
   }
   }

   //   UNDEFINDED      WTRMRK UN LCDVCMP LCDPWR BEPO BEBO BGR LCDDUAL LCDMONO8 LCDTFT LCDBW LCDBPP LCDEN

   // 0b000000000000000 0      00 00      1      0    0    1   0       0        1      0     011    1;
   lcd_Control = 0b100100100111; // 8bpp like graphx
   memset(ti8bpp_screen, 127, VIR_LCD_PIX_H * VIR_LCD_PIX_W);

*/

#ifdef WITH_LCDMALLOC
#include <debug.h>
#undef NDEBUG
unsigned freeslotpos(unsigned n){
  unsigned r=1;
  if ( (n<<8)==0 ){
    // bit15 to 0 are 0, position must be >=16
    // otherwise position is <16
    r+= 16;
    n>>=16;
  }
  if ( (n<<16)==0 ) {
    // bit7 to 0 are 0, position must be >=8
    // otherwise position is <8
    r+= 8; 
    n>>=8;
  }
  if ( (n<<20)==0 ) {
    r+= 4;
    n>>=4;
  }
  if ( (n<<22)==0 ) {
    r+= 2;
    n>>=2;
  }
  r -= n&1;
  //dbg_printf("freeslotpos n=%x r=%i\n",n,r);
  return r;
}

typedef struct char2_ {
  char c1,c2,c3,c4;
} char2; 
typedef struct char3_ {
  char c1,c2,c3,c4,c5,c6,c7,c8,c9,c10;
} char3 ; 
typedef struct char6_ {
  char c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16;
} char6; 
#endif // LCD_MALLOC

typedef struct __attribute__((packed)) block
{
  struct block *ptr;
  size_t size;
} __attribute__((packed)) block_t;


extern uint8_t __heapbot[];
extern uint8_t __heaptop[];
#ifdef WITH_LCDMALLOC
#define LCD_WIDTH_PX 320
#define LCD_HEIGHT_PX 240
// assumes that heap2_ptrend<=lcd_Ram
static uintptr_t heap2_ptr = (uintptr_t) __heapbot;
static uintptr_t heap2_ptrend = (uintptr_t) __heaptop;
#define NBITS_INT 24
#define ALLOC2 12*NBITS_INT
static unsigned int freeslot2[ALLOC2/NBITS_INT]={
  0xffffff, 0xffffff, 0xffffff, 0xffffff,
  0xffffff, 0xffffff, 0xffffff, 0xffffff,
  0xffffff, 0xffffff, 0xffffff, 0xffffff,
};
#define ALLOC3 12*NBITS_INT
static unsigned int freeslot3[ALLOC3/NBITS_INT]={
  0xffffff, 0xffffff, 0xffffff, 0xffffff,
  0xffffff, 0xffffff, 0xffffff, 0xffffff,
  0xffffff, 0xffffff, 0xffffff, 0xffffff,
};
#define ALLOC6 12*NBITS_INT
static unsigned int freeslot6[ALLOC6/NBITS_INT]={
  0xffffff, 0xffffff, 0xffffff, 0xffffff,
  0xffffff, 0xffffff, 0xffffff, 0xffffff,
  0xffffff, 0xffffff, 0xffffff, 0xffffff,
};
char2 * tab2=lcd_Ram+LCD_WIDTH_PX*LCD_HEIGHT_PX;
char3 * tab3=lcd_Ram+LCD_WIDTH_PX*LCD_HEIGHT_PX+ALLOC2*sizeof(char2);
char6 * tab6=lcd_Ram+LCD_WIDTH_PX*LCD_HEIGHT_PX+ALLOC2*sizeof(char2)+ALLOC3*sizeof(char3);
static uintptr_t heap_ptr = (uintptr_t) lcd_Ram+LCD_WIDTH_PX*LCD_HEIGHT_PX+ALLOC2*sizeof(char2)+ALLOC3*sizeof(char3)+ALLOC6*sizeof(char6);
static uintptr_t heap_ptrend = (uintptr_t) lcd_Ram+LCD_WIDTH_PX*LCD_HEIGHT_PX*2;

#else
static uintptr_t heap_ptr = (uintptr_t) __heapbot;
static uintptr_t heap_ptrend = (uintptr_t) __heaptop;
#endif
static block_t _alloc_base,_alloc2_base;
// these are 0 initialized, pointing to a chained list of free-ed pointers

  
void *_standard_malloc(size_t alloc_size){
  if (alloc_size==0)
    return NULL;
  if (alloc_size==0xffffff)
    return (heap_ptrend-heap_ptr)+(heap2_ptrend-heap2_ptr);
  if (alloc_size<=sizeof(char6)){
    int i,pos;
    if (tab2 && alloc_size<=sizeof(char2)){ 
      for (i=0;i<ALLOC2/NBITS_INT;){
	if (!(freeslot2[i] || freeslot2[i+1])){
	  i+=2;
	  continue;
	}
	if (freeslot2[i]){
        end2:
          pos=freeslotpos(freeslot2[i]);
	  freeslot2[i] &= ~(1<<pos);
#ifdef DBG          
          dbg_printf("allocfast2 %x %x\n",tab2,tab2+i*NBITS_INT+pos);
#endif
	  return (void *) (tab2+i*NBITS_INT+pos);
	}
	++i;
        goto end2;
      }
    }
    if (tab3 && alloc_size<=sizeof(char3)){ 
      for (i=0;i<ALLOC3/NBITS_INT;){
	if (!(freeslot3[i] || freeslot3[i+1])){
	  i+=2;
	  continue;
	}
	if (freeslot3[i]){
        end3:
          pos=freeslotpos(freeslot3[i]);
	  freeslot3[i] &= ~(1<<pos);
#ifdef DBG
          dbg_printf("allocfast3 %x %x\n",tab3,tab3+i*NBITS_INT+pos);
#endif
	  return (void *) (tab3+i*NBITS_INT+pos);
	}
	i++;
        goto end3;
      }
    }
    if (tab6 && alloc_size<=sizeof(char6)){ 
      for (i=0;i<ALLOC6/NBITS_INT;){
	if (!(freeslot6[i] || freeslot6[i+1])){
	  i+=2;
	  continue;
	}
	if (freeslot6[i]){
        end6:
          pos=freeslotpos(freeslot6[i]);
	  freeslot6[i] &= ~(1<<pos);
#ifdef DBG
          dbg_printf("allocfast6 %x %x\n",tab6,tab6+i*NBITS_INT+pos);
#endif
	  return (void *) (tab6+i*NBITS_INT+pos);
	}
	++i;
        goto end6;
      }
    }
  }
#ifdef DBG
  dbg_printf("malloc %i\n",alloc_size);
#endif
  block_t *q;
  block_t *r;

  /* add size of block header to real size */
  size_t size = alloc_size + sizeof(block_t);
  if (size < alloc_size)
    return NULL;
  //dbg_printf("alloc heap %x ptr=%x size=%i\n",&_alloc_base,_alloc_base.ptr,_alloc_base.size);

  for (block_t *p = &_alloc_base; (q = p->ptr); p = q){
    if (q->size >= size){
      if (q->size <= size + sizeof(block_t) + MALLOC_MINSIZE ){
#ifdef DBG
        dbg_printf("heap recycle full blocsize=%i size=%i\n",q->size,size);
#endif
        p->ptr = q->ptr;
      }
      else {
#ifdef DBG
        dbg_printf("heap recycle partial blocsize=%i size=%i\n",q->size,size);
#endif
        q->size -= size;
        q = (block_t*)(((uint8_t*)q) + q->size);
        q->size = size;
      }
      
      return q + 1;
    }
  }

  /* compute next heap pointer */
  if (heap_ptr+size<heap_ptr || heap_ptr+size>=(uintptr_t)heap_ptrend){
#ifdef WITH_LCDMALLOC
    // dbg_printf("alloc heap2 %x ptr=%x size=%i\n",&_alloc2_base,_alloc2_base.ptr,_alloc2_base.size);
    for (block_t *p = &_alloc2_base; (q = p->ptr); p = q){
      if (q->size >= size){
        if (q->size <= size + sizeof(block_t)){
#ifdef DBG
          dbg_printf("heap2 recycle full blocsize=%i size=%i\n",q->size,size);
#endif
          p->ptr = q->ptr;
        }
        else {
#ifdef DBG
          dbg_printf("heap2 recycle partial blocsize=%i size=%i\n",q->size,size);
#endif
          q->size -= size;
          q = (block_t*)(((uint8_t*)q) + q->size);
          q->size = size;
        }
        
        return q + 1;
      }
    }
    if (heap2_ptr+size<heap2_ptr || heap2_ptr+size>=(uintptr_t)heap2_ptrend){
      lcd_Control = 0b100100101101; // TI-OS default
      abort();
      return NULL;
    }
    r = (block_t*)heap2_ptr;
    if (size<MALLOC_MINSIZE)
      size=MALLOC_MINSIZE;
    r->size = size;
    heap2_ptr = heap2_ptr + size;
    return r + 1;
#else
    lcd_Control = 0b100100101101; // TI-OS default
    abort();
    return NULL;
#endif
  }
  
  r = (block_t*)heap_ptr;
  if (size<MALLOC_MINSIZE)
    size=MALLOC_MINSIZE;
  r->size = size;
  heap_ptr = heap_ptr + size;
  return r + 1;
}

void _standard_free(void *ptr){
  if (ptr!=NULL){
#ifdef DBG
    dbg_printf("free %x\n",ptr);
#endif
    if ( ((size_t)ptr >= (size_t) &tab2[0]) &&
	 ((size_t)ptr < (size_t) &tab2[ALLOC2]) ){
      int pos= ((size_t)ptr -((size_t) &tab2[0]))/sizeof(char2);
#ifdef DBG
      dbg_printf("deletefast2 %x pos=%i\n",ptr,pos);
#endif
      freeslot2[pos/NBITS_INT] |= (1 << (pos%NBITS_INT)); 
      return;
    }
    if ( ((size_t)ptr>=(size_t) &tab3[0] ) &&
	 ((size_t)ptr<(size_t) &tab3[ALLOC3] ) ){
      int pos= ((size_t)ptr -((size_t) &tab3[0]))/sizeof(char3);
#ifdef DBG
      dbg_printf("deletefast3 %x pos=%i\n",ptr,pos);
#endif
      freeslot3[pos/NBITS_INT] |= (1 << (pos%NBITS_INT)); 
      return;
    }
    if ( ((size_t)ptr>=(size_t) &tab6[0] ) &&
	 ((size_t)ptr<(size_t) &tab6[ALLOC6] ) ){
      int pos= ((size_t)ptr -((size_t) &tab6[0]))/sizeof(char6);
#ifdef DBG
      dbg_printf("deletefast6 %x pos=%i\n",ptr,pos);
#endif
      freeslot6[pos/NBITS_INT] |= (1 << (pos%NBITS_INT)); 
      return;
    }
    
    block_t *p;
    block_t *q;
    
    q = (block_t*)ptr - 1;
    
#ifdef WITH_LCDMALLOC
    p=(ptr<=heap2_ptrend?&_alloc2_base:&_alloc_base);
#else
    p=&_alloc_base;
#endif
    //dbg_printf("free ptr=%x heap_end=%x p=%x pptr=%x psize=%i\n",ptr,heap_ptrend,p,p->ptr,p->size);

    for (  ; p->ptr && p->ptr<q ; p=p->ptr)
      ;
    // p next pointer in the free-ed chaine list, p->ptr,
    // is 0 or is the first pointer >= q
    // (this means that p is before q)
    if ((uint8_t*)p->ptr == ((uint8_t*)q) + q->size){
      // concatenate q and p next pointer
      q->size += p->ptr->size;
      q->ptr = p->ptr->ptr;
#ifdef DBG
      dbg_printf("free concatenate blocsize=%i\n",q->size);
#endif
    }
    else { // insert in chained list: get q next cell from p next cell
      q->ptr = p->ptr;
#ifdef DBG
      dbg_printf("free add block blocsize=%i\n",q->size);
#endif
    }
    // check if we can concatenate p and q
    if (((uint8_t*)p) + p->size == (uint8_t*)q){
      // yes
      p->size += q->size;
      p->ptr = q->ptr;
    }
    else {
      // no, update next pointer for p
      p->ptr = q;
    }
  }
}

void *_standard_realloc(void *ptr, size_t size)
{
  block_t *h;
  void *p;

  if (ptr == NULL){
    return malloc(size);
  }
  if ( ( ((size_t)ptr >= (size_t) &tab2[0]) && ((size_t)ptr < (size_t) &tab2[ALLOC2]) ) ||
       ( ((size_t)ptr >= (size_t) &tab3[0]) && ((size_t)ptr < (size_t) &tab3[ALLOC2]) ) ||
       ( ((size_t)ptr >= (size_t) &tab6[0]) && ((size_t)ptr < (size_t) &tab6[ALLOC2]) )
       )
    ;
  else {
    h = (block_t*)((uint8_t*)ptr - sizeof(block_t));
  
    if (h->size >= (size + sizeof(block_t))){
      return ptr;
    }
  }
  
  if ((p = malloc(size))){
    memcpy(p, ptr, size);
    free(ptr);
  }
  
  return p;
}

