#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;

struct u24 {
  unsigned char a,b,c;
};

unsigned getu24(const unsigned char * ptr){
  u24 * u=(u24 *)ptr;
  unsigned res=u->c;
  res *= 256;
  res += u->b;
  res *= 256;
  res += u->a;
  return res;
}

unsigned getu24big(const unsigned char * ptr){
  unsigned res=*ptr;
  res *= 256;
  res += ptr[1];
  res *= 256;
  res += ptr[2];
  return res;
}

void setu24(unsigned char * ptr,unsigned i){
  *ptr = i%256;
  ptr[1] = (i/256)%256;
  ptr[2] = (i/65536);
}

void setu24big(unsigned char * ptr,unsigned i){
  ptr[2] = i%256;
  ptr[1] = (i/256)%256;
  *ptr = (i/65536);
}

int main(int argc,char **argv){
  if (argc<2){
    printf("syntax: %s  bin_filename\n",argv[0]);
    return -1;
  }
  FILE * f=fopen(argv[1],"rb");
  if (!f){
    printf("File not found\n");
    return -2;
  }
  vector<unsigned char> buf; buf.reserve(3*1024*1024);
  for (;;){
    unsigned char c=fgetc(f);
    if (feof(f))
      break;
    buf.push_back(c);
  }
  fclose(f);
  char tmp[32]={'_',0};
  strcat(tmp,argv[1]);
  f=0;
  f=fopen(tmp,"wb");
  if (!f){
    printf("Unable to write %s\n",tmp);
    return -3;
  }
  unsigned decal=getu24big(&buf[0xfd]);
  unsigned codestart=getu24(&buf[0x112]);
  unsigned datastart=getu24(&buf[0x115]);
  unsigned database=0xd1787c; //???
  unsigned relocbase=0x3afffd-decal+codestart-0x104;
  printf("codestart=0x%x datastart=0x%x relocbase=0x%x\n",codestart,datastart,relocbase);
  // reloc computation loop
  for (int pos=0x12a;pos<codestart+0x100;pos+=6){
    unsigned relocoffset=getu24(&buf[pos]);
    unsigned relocvalue=getu24(&buf[pos+3]);
    bool data=relocvalue & 0x800000;
    relocvalue &=0x3fffff;
#if 0
    if (data)
      printf("data reloc pos=0x%x relocoffset=0x%x relocvalue=0x%x write=0x%x at 0x%x\n",pos,relocoffset,relocvalue,relocvalue+database,relocoffset+0x100+codestart);;
    else
      printf("code reloc pos=0x%x relocoffset=0x%x relocvalue=0x%x write=0x%x at 0x%x\n",pos,relocoffset,relocvalue,relocvalue+relocbase,relocoffset+0x100+codestart);
#endif
    setu24(&buf[relocoffset+0x100+codestart],relocvalue+(data?database:relocbase));
  }
  // delete reloc section
  buf.erase(buf.begin()+0x12a,buf.begin()+codestart+0x100);
  // set new sizes
  unsigned delta=codestart-0x2a;
  setu24(&buf[0x112],0x2a); // new code section
  setu24(&buf[0x115],getu24(&buf[0x115])-delta); // data section
  setu24(&buf[0x11b],getu24(&buf[0x11b])-delta); // entry point, should be 0x2a
  setu24(&buf[0x124],getu24(&buf[0x124])-delta); // data section
  setu24big(&buf[3],getu24big(&buf[3])-delta); // 1st length field
  setu24big(&buf[0xfd],getu24big(&buf[0xfd])-delta); // 2nd length field
  fwrite(&buf[0],1,buf.size(),f);
  fclose(f);
  printf("Wrote file %s, saved bytes %i\n",tmp,delta);
  printf("Now run\n  python3 make_8ek.py %s DEMO.8ek DEMO\nand cp the 8ek app to destination. For the installer\n",tmp);
  printf("python3 make_segments.py %s bin\n",tmp);
}
