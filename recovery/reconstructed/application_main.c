/* Whole-control-flow C semantic recovery of 0x0800A708..0x0800B0C6.
 * Generated from verified Thumb operands by tools/lift_application_main.py.
 * Explicit register names and address labels are intentional; this is NOT the
 * lost original source or a production-ready high-level firmware main.
 * No opaque opcode interpreter, bytecode execution, or TODO branch bodies.
 * Literal pools and the Keil switch8 table are data, excluded from instructions.
 */
#include "application_main.h"
#define NZ 0xC0000000u
#define CV 0x30000000u
static uint32_t nz(AppMainState*s,uint32_t x){s->apsr=(s->apsr&~NZ)|(x&0x80000000u)|(x?0:0x40000000u);return x;}
static uint32_t add(AppMainState*s,uint32_t a,uint32_t b){uint32_t r=a+b;s->apsr=(s->apsr&~CV)|((uint64_t)a+b>0xffffffffu?0x20000000u:0)|((~(a^b)&(a^r)&0x80000000u)?0x10000000u:0);return nz(s,r);}
static uint32_t sub(AppMainState*s,uint32_t a,uint32_t b){uint32_t r=a-b;s->apsr=(s->apsr&~CV)|(a>=b?0x20000000u:0)|(((a^b)&(a^r)&0x80000000u)?0x10000000u:0);return nz(s,r);}
static uint32_t lsl(AppMainState*s,uint32_t a,unsigned n){uint32_t r;if(!n)return nz(s,a);s->apsr=(s->apsr&~0x20000000u)|((n<=32&&((a>>(32-n))&1u))?0x20000000u:0);r=n<32?a<<n:0;return nz(s,r);}
static uint32_t lsr(AppMainState*s,uint32_t a,unsigned n){uint32_t r;if(!n)return nz(s,a);s->apsr=(s->apsr&~0x20000000u)|((n<=32&&((a>>(n-1))&1u))?0x20000000u:0);r=n<32?a>>n:0;return nz(s,r);}
static uint32_t read_mem(AppMainState*s,uint32_t a,unsigned n){const uint8_t*p=0;uint32_t v=0;if(a>=0x08000000u&&a-0x08000000u<=0x10000u-n)p=s->flash+(a-0x08000000u);else if(a>=0x20000000u&&s->sram_size>=n&&a-0x20000000u<=s->sram_size-n)p=s->sram+(a-0x20000000u);else if(s->io_read)return s->io_read(s->user,a,n);else{s->fault=-1;s->fault_address=a;return 0;}for(unsigned i=0;i<n;i++)v|=(uint32_t)p[i]<<(8*i);return v;}
static void write_mem(AppMainState*s,uint32_t a,unsigned n,uint32_t v){uint8_t*p=0;if(a>=0x20000000u&&s->sram_size>=n&&a-0x20000000u<=s->sram_size-n)p=s->sram+(a-0x20000000u);else if(s->io_write){s->io_write(s->user,a,n,v);return;}else{s->fault=-1;s->fault_address=a;return;}for(unsigned i=0;i<n;i++)p[i]=(uint8_t)(v>>(8*i));}
#define STEP(a) do{s->pc=(a);s->r[15]=(a)+4u;if(s->fault)return s->fault;if(!budget--)return 0;++s->main_instruction_count;}while(0)
#define C ((s->apsr>>29)&1u)
#define Z ((s->apsr>>30)&1u)
int recovered_application_main_run(AppMainState *s,uint32_t budget)
{
    uint32_t temp;
    goto dispatch;
dispatch:
    switch(s->pc) {

    case 0x0800a708u: goto L_0800a708;
    case 0x0800a70au: goto L_0800a70a;
    case 0x0800a70cu: goto L_0800a70c;
    case 0x0800a70eu: goto L_0800a70e;
    case 0x0800a710u: goto L_0800a710;
    case 0x0800a712u: goto L_0800a712;
    case 0x0800a714u: goto L_0800a714;
    case 0x0800a716u: goto L_0800a716;
    case 0x0800a718u: goto L_0800a718;
    case 0x0800a71au: goto L_0800a71a;
    case 0x0800a71cu: goto L_0800a71c;
    case 0x0800a71eu: goto L_0800a71e;
    case 0x0800a720u: goto L_0800a720;
    case 0x0800a722u: goto L_0800a722;
    case 0x0800a724u: goto L_0800a724;
    case 0x0800a726u: goto L_0800a726;
    case 0x0800a728u: goto L_0800a728;
    case 0x0800a72au: goto L_0800a72a;
    case 0x0800a72cu: goto L_0800a72c;
    case 0x0800a72eu: goto L_0800a72e;
    case 0x0800a730u: goto L_0800a730;
    case 0x0800a732u: goto L_0800a732;
    case 0x0800a734u: goto L_0800a734;
    case 0x0800a736u: goto L_0800a736;
    case 0x0800a738u: goto L_0800a738;
    case 0x0800a73au: goto L_0800a73a;
    case 0x0800a73cu: goto L_0800a73c;
    case 0x0800a73eu: goto L_0800a73e;
    case 0x0800a740u: goto L_0800a740;
    case 0x0800a742u: goto L_0800a742;
    case 0x0800a746u: goto L_0800a746;
    case 0x0800a74au: goto L_0800a74a;
    case 0x0800a74eu: goto L_0800a74e;
    case 0x0800a752u: goto L_0800a752;
    case 0x0800a756u: goto L_0800a756;
    case 0x0800a75au: goto L_0800a75a;
    case 0x0800a75eu: goto L_0800a75e;
    case 0x0800a762u: goto L_0800a762;
    case 0x0800a766u: goto L_0800a766;
    case 0x0800a76au: goto L_0800a76a;
    case 0x0800a76cu: goto L_0800a76c;
    case 0x0800a770u: goto L_0800a770;
    case 0x0800a772u: goto L_0800a772;
    case 0x0800a774u: goto L_0800a774;
    case 0x0800a776u: goto L_0800a776;
    case 0x0800a778u: goto L_0800a778;
    case 0x0800a77au: goto L_0800a77a;
    case 0x0800a77cu: goto L_0800a77c;
    case 0x0800a780u: goto L_0800a780;
    case 0x0800a782u: goto L_0800a782;
    case 0x0800a784u: goto L_0800a784;
    case 0x0800a786u: goto L_0800a786;
    case 0x0800a788u: goto L_0800a788;
    case 0x0800a78au: goto L_0800a78a;
    case 0x0800a78eu: goto L_0800a78e;
    case 0x0800a790u: goto L_0800a790;
    case 0x0800a792u: goto L_0800a792;
    case 0x0800a794u: goto L_0800a794;
    case 0x0800a798u: goto L_0800a798;
    case 0x0800a79cu: goto L_0800a79c;
    case 0x0800a7a0u: goto L_0800a7a0;
    case 0x0800a7a4u: goto L_0800a7a4;
    case 0x0800a7a6u: goto L_0800a7a6;
    case 0x0800a7aau: goto L_0800a7aa;
    case 0x0800a7aeu: goto L_0800a7ae;
    case 0x0800a7b0u: goto L_0800a7b0;
    case 0x0800a7b4u: goto L_0800a7b4;
    case 0x0800a7b8u: goto L_0800a7b8;
    case 0x0800a7bau: goto L_0800a7ba;
    case 0x0800a7beu: goto L_0800a7be;
    case 0x0800a7c2u: goto L_0800a7c2;
    case 0x0800a7c6u: goto L_0800a7c6;
    case 0x0800a7c8u: goto L_0800a7c8;
    case 0x0800a7cau: goto L_0800a7ca;
    case 0x0800a7ccu: goto L_0800a7cc;
    case 0x0800a7ceu: goto L_0800a7ce;
    case 0x0800a7d0u: goto L_0800a7d0;
    case 0x0800a7d2u: goto L_0800a7d2;
    case 0x0800a7d4u: goto L_0800a7d4;
    case 0x0800a7d6u: goto L_0800a7d6;
    case 0x0800a7dau: goto L_0800a7da;
    case 0x0800a7deu: goto L_0800a7de;
    case 0x0800a7e0u: goto L_0800a7e0;
    case 0x0800a7e2u: goto L_0800a7e2;
    case 0x0800a7e4u: goto L_0800a7e4;
    case 0x0800a7e6u: goto L_0800a7e6;
    case 0x0800a7e8u: goto L_0800a7e8;
    case 0x0800a7eau: goto L_0800a7ea;
    case 0x0800a7ecu: goto L_0800a7ec;
    case 0x0800a7eeu: goto L_0800a7ee;
    case 0x0800a7f0u: goto L_0800a7f0;
    case 0x0800a7f2u: goto L_0800a7f2;
    case 0x0800a7f4u: goto L_0800a7f4;
    case 0x0800a7f6u: goto L_0800a7f6;
    case 0x0800a7f8u: goto L_0800a7f8;
    case 0x0800a7fau: goto L_0800a7fa;
    case 0x0800a7fcu: goto L_0800a7fc;
    case 0x0800a7feu: goto L_0800a7fe;
    case 0x0800a800u: goto L_0800a800;
    case 0x0800a802u: goto L_0800a802;
    case 0x0800a804u: goto L_0800a804;
    case 0x0800a806u: goto L_0800a806;
    case 0x0800a808u: goto L_0800a808;
    case 0x0800a80au: goto L_0800a80a;
    case 0x0800a80cu: goto L_0800a80c;
    case 0x0800a80eu: goto L_0800a80e;
    case 0x0800a810u: goto L_0800a810;
    case 0x0800a812u: goto L_0800a812;
    case 0x0800a814u: goto L_0800a814;
    case 0x0800a816u: goto L_0800a816;
    case 0x0800a818u: goto L_0800a818;
    case 0x0800a81au: goto L_0800a81a;
    case 0x0800a81cu: goto L_0800a81c;
    case 0x0800a820u: goto L_0800a820;
    case 0x0800a822u: goto L_0800a822;
    case 0x0800a824u: goto L_0800a824;
    case 0x0800a826u: goto L_0800a826;
    case 0x0800a828u: goto L_0800a828;
    case 0x0800a82au: goto L_0800a82a;
    case 0x0800a82cu: goto L_0800a82c;
    case 0x0800a82eu: goto L_0800a82e;
    case 0x0800a830u: goto L_0800a830;
    case 0x0800a832u: goto L_0800a832;
    case 0x0800a834u: goto L_0800a834;
    case 0x0800a836u: goto L_0800a836;
    case 0x0800a838u: goto L_0800a838;
    case 0x0800a83au: goto L_0800a83a;
    case 0x0800a83cu: goto L_0800a83c;
    case 0x0800a83eu: goto L_0800a83e;
    case 0x0800a840u: goto L_0800a840;
    case 0x0800a842u: goto L_0800a842;
    case 0x0800a844u: goto L_0800a844;
    case 0x0800a848u: goto L_0800a848;
    case 0x0800a84au: goto L_0800a84a;
    case 0x0800a84cu: goto L_0800a84c;
    case 0x0800a84eu: goto L_0800a84e;
    case 0x0800a850u: goto L_0800a850;
    case 0x0800a852u: goto L_0800a852;
    case 0x0800a854u: goto L_0800a854;
    case 0x0800a858u: goto L_0800a858;
    case 0x0800a85au: goto L_0800a85a;
    case 0x0800a85cu: goto L_0800a85c;
    case 0x0800a85eu: goto L_0800a85e;
    case 0x0800a860u: goto L_0800a860;
    case 0x0800a864u: goto L_0800a864;
    case 0x0800a866u: goto L_0800a866;
    case 0x0800a868u: goto L_0800a868;
    case 0x0800a86au: goto L_0800a86a;
    case 0x0800a86cu: goto L_0800a86c;
    case 0x0800a86eu: goto L_0800a86e;
    case 0x0800a870u: goto L_0800a870;
    case 0x0800a872u: goto L_0800a872;
    case 0x0800a874u: goto L_0800a874;
    case 0x0800a878u: goto L_0800a878;
    case 0x0800a87au: goto L_0800a87a;
    case 0x0800a87cu: goto L_0800a87c;
    case 0x0800a87eu: goto L_0800a87e;
    case 0x0800a882u: goto L_0800a882;
    case 0x0800a884u: goto L_0800a884;
    case 0x0800a886u: goto L_0800a886;
    case 0x0800a888u: goto L_0800a888;
    case 0x0800a88au: goto L_0800a88a;
    case 0x0800a8e2u: goto L_0800a8e2;
    case 0x0800a8e4u: goto L_0800a8e4;
    case 0x0800a8e6u: goto L_0800a8e6;
    case 0x0800a8e8u: goto L_0800a8e8;
    case 0x0800a8eau: goto L_0800a8ea;
    case 0x0800a8eeu: goto L_0800a8ee;
    case 0x0800a8f0u: goto L_0800a8f0;
    case 0x0800a8f2u: goto L_0800a8f2;
    case 0x0800a8f4u: goto L_0800a8f4;
    case 0x0800a8f6u: goto L_0800a8f6;
    case 0x0800a8f8u: goto L_0800a8f8;
    case 0x0800a8fau: goto L_0800a8fa;
    case 0x0800a8fcu: goto L_0800a8fc;
    case 0x0800a8feu: goto L_0800a8fe;
    case 0x0800a902u: goto L_0800a902;
    case 0x0800a904u: goto L_0800a904;
    case 0x0800a908u: goto L_0800a908;
    case 0x0800a90au: goto L_0800a90a;
    case 0x0800a90cu: goto L_0800a90c;
    case 0x0800a90eu: goto L_0800a90e;
    case 0x0800a912u: goto L_0800a912;
    case 0x0800a914u: goto L_0800a914;
    case 0x0800a916u: goto L_0800a916;
    case 0x0800a918u: goto L_0800a918;
    case 0x0800a91au: goto L_0800a91a;
    case 0x0800a91cu: goto L_0800a91c;
    case 0x0800a91eu: goto L_0800a91e;
    case 0x0800a920u: goto L_0800a920;
    case 0x0800a922u: goto L_0800a922;
    case 0x0800a924u: goto L_0800a924;
    case 0x0800a926u: goto L_0800a926;
    case 0x0800a928u: goto L_0800a928;
    case 0x0800a92au: goto L_0800a92a;
    case 0x0800a92cu: goto L_0800a92c;
    case 0x0800a930u: goto L_0800a930;
    case 0x0800a932u: goto L_0800a932;
    case 0x0800a934u: goto L_0800a934;
    case 0x0800a936u: goto L_0800a936;
    case 0x0800a938u: goto L_0800a938;
    case 0x0800a93au: goto L_0800a93a;
    case 0x0800a93cu: goto L_0800a93c;
    case 0x0800a93eu: goto L_0800a93e;
    case 0x0800a940u: goto L_0800a940;
    case 0x0800a942u: goto L_0800a942;
    case 0x0800a944u: goto L_0800a944;
    case 0x0800a946u: goto L_0800a946;
    case 0x0800a948u: goto L_0800a948;
    case 0x0800a94au: goto L_0800a94a;
    case 0x0800a94cu: goto L_0800a94c;
    case 0x0800a94eu: goto L_0800a94e;
    case 0x0800a950u: goto L_0800a950;
    case 0x0800a952u: goto L_0800a952;
    case 0x0800a954u: goto L_0800a954;
    case 0x0800a956u: goto L_0800a956;
    case 0x0800a95au: goto L_0800a95a;
    case 0x0800a95cu: goto L_0800a95c;
    case 0x0800a95eu: goto L_0800a95e;
    case 0x0800a960u: goto L_0800a960;
    case 0x0800a962u: goto L_0800a962;
    case 0x0800a964u: goto L_0800a964;
    case 0x0800a966u: goto L_0800a966;
    case 0x0800a96au: goto L_0800a96a;
    case 0x0800a96cu: goto L_0800a96c;
    case 0x0800a96eu: goto L_0800a96e;
    case 0x0800a970u: goto L_0800a970;
    case 0x0800a972u: goto L_0800a972;
    case 0x0800a974u: goto L_0800a974;
    case 0x0800a976u: goto L_0800a976;
    case 0x0800a978u: goto L_0800a978;
    case 0x0800a97au: goto L_0800a97a;
    case 0x0800a97cu: goto L_0800a97c;
    case 0x0800a97eu: goto L_0800a97e;
    case 0x0800a980u: goto L_0800a980;
    case 0x0800a982u: goto L_0800a982;
    case 0x0800a984u: goto L_0800a984;
    case 0x0800a986u: goto L_0800a986;
    case 0x0800a988u: goto L_0800a988;
    case 0x0800a98au: goto L_0800a98a;
    case 0x0800a98cu: goto L_0800a98c;
    case 0x0800a98eu: goto L_0800a98e;
    case 0x0800a990u: goto L_0800a990;
    case 0x0800a992u: goto L_0800a992;
    case 0x0800a994u: goto L_0800a994;
    case 0x0800a996u: goto L_0800a996;
    case 0x0800a998u: goto L_0800a998;
    case 0x0800a99au: goto L_0800a99a;
    case 0x0800a99cu: goto L_0800a99c;
    case 0x0800a99eu: goto L_0800a99e;
    case 0x0800a9a0u: goto L_0800a9a0;
    case 0x0800a9a2u: goto L_0800a9a2;
    case 0x0800a9a4u: goto L_0800a9a4;
    case 0x0800a9a6u: goto L_0800a9a6;
    case 0x0800a9a8u: goto L_0800a9a8;
    case 0x0800a9aau: goto L_0800a9aa;
    case 0x0800a9acu: goto L_0800a9ac;
    case 0x0800a9aeu: goto L_0800a9ae;
    case 0x0800a9b0u: goto L_0800a9b0;
    case 0x0800a9b2u: goto L_0800a9b2;
    case 0x0800a9b4u: goto L_0800a9b4;
    case 0x0800a9b8u: goto L_0800a9b8;
    case 0x0800a9bau: goto L_0800a9ba;
    case 0x0800a9bcu: goto L_0800a9bc;
    case 0x0800a9beu: goto L_0800a9be;
    case 0x0800a9c0u: goto L_0800a9c0;
    case 0x0800a9c2u: goto L_0800a9c2;
    case 0x0800a9c4u: goto L_0800a9c4;
    case 0x0800a9c6u: goto L_0800a9c6;
    case 0x0800a9c8u: goto L_0800a9c8;
    case 0x0800a9cau: goto L_0800a9ca;
    case 0x0800a9ceu: goto L_0800a9ce;
    case 0x0800a9d0u: goto L_0800a9d0;
    case 0x0800a9d2u: goto L_0800a9d2;
    case 0x0800a9d4u: goto L_0800a9d4;
    case 0x0800a9d6u: goto L_0800a9d6;
    case 0x0800a9d8u: goto L_0800a9d8;
    case 0x0800a9dau: goto L_0800a9da;
    case 0x0800a9dcu: goto L_0800a9dc;
    case 0x0800a9deu: goto L_0800a9de;
    case 0x0800a9e0u: goto L_0800a9e0;
    case 0x0800a9e2u: goto L_0800a9e2;
    case 0x0800a9e4u: goto L_0800a9e4;
    case 0x0800a9e6u: goto L_0800a9e6;
    case 0x0800a9e8u: goto L_0800a9e8;
    case 0x0800a9eau: goto L_0800a9ea;
    case 0x0800a9ecu: goto L_0800a9ec;
    case 0x0800a9eeu: goto L_0800a9ee;
    case 0x0800a9f0u: goto L_0800a9f0;
    case 0x0800a9f2u: goto L_0800a9f2;
    case 0x0800a9f4u: goto L_0800a9f4;
    case 0x0800a9f6u: goto L_0800a9f6;
    case 0x0800a9f8u: goto L_0800a9f8;
    case 0x0800a9fau: goto L_0800a9fa;
    case 0x0800a9fcu: goto L_0800a9fc;
    case 0x0800a9feu: goto L_0800a9fe;
    case 0x0800aa00u: goto L_0800aa00;
    case 0x0800aa02u: goto L_0800aa02;
    case 0x0800aa04u: goto L_0800aa04;
    case 0x0800aa06u: goto L_0800aa06;
    case 0x0800aa0au: goto L_0800aa0a;
    case 0x0800aa0cu: goto L_0800aa0c;
    case 0x0800aa0eu: goto L_0800aa0e;
    case 0x0800aa10u: goto L_0800aa10;
    case 0x0800aa14u: goto L_0800aa14;
    case 0x0800aa16u: goto L_0800aa16;
    case 0x0800aa18u: goto L_0800aa18;
    case 0x0800aa1au: goto L_0800aa1a;
    case 0x0800aa1cu: goto L_0800aa1c;
    case 0x0800aa1eu: goto L_0800aa1e;
    case 0x0800aa20u: goto L_0800aa20;
    case 0x0800aa22u: goto L_0800aa22;
    case 0x0800aa24u: goto L_0800aa24;
    case 0x0800aa26u: goto L_0800aa26;
    case 0x0800aa28u: goto L_0800aa28;
    case 0x0800aa2au: goto L_0800aa2a;
    case 0x0800aa2cu: goto L_0800aa2c;
    case 0x0800aa2eu: goto L_0800aa2e;
    case 0x0800aa30u: goto L_0800aa30;
    case 0x0800aa32u: goto L_0800aa32;
    case 0x0800aa34u: goto L_0800aa34;
    case 0x0800aa36u: goto L_0800aa36;
    case 0x0800aa38u: goto L_0800aa38;
    case 0x0800aa3au: goto L_0800aa3a;
    case 0x0800aa3cu: goto L_0800aa3c;
    case 0x0800aa3eu: goto L_0800aa3e;
    case 0x0800aa40u: goto L_0800aa40;
    case 0x0800aa42u: goto L_0800aa42;
    case 0x0800aa44u: goto L_0800aa44;
    case 0x0800aa46u: goto L_0800aa46;
    case 0x0800aa48u: goto L_0800aa48;
    case 0x0800aa4au: goto L_0800aa4a;
    case 0x0800aa4cu: goto L_0800aa4c;
    case 0x0800aa4eu: goto L_0800aa4e;
    case 0x0800aa50u: goto L_0800aa50;
    case 0x0800aa52u: goto L_0800aa52;
    case 0x0800aa54u: goto L_0800aa54;
    case 0x0800aa56u: goto L_0800aa56;
    case 0x0800aa58u: goto L_0800aa58;
    case 0x0800aa5au: goto L_0800aa5a;
    case 0x0800aa5cu: goto L_0800aa5c;
    case 0x0800aa5eu: goto L_0800aa5e;
    case 0x0800aa60u: goto L_0800aa60;
    case 0x0800aa62u: goto L_0800aa62;
    case 0x0800aa64u: goto L_0800aa64;
    case 0x0800aa66u: goto L_0800aa66;
    case 0x0800aa6au: goto L_0800aa6a;
    case 0x0800aa6cu: goto L_0800aa6c;
    case 0x0800aa6eu: goto L_0800aa6e;
    case 0x0800aa70u: goto L_0800aa70;
    case 0x0800aa72u: goto L_0800aa72;
    case 0x0800aa74u: goto L_0800aa74;
    case 0x0800aa76u: goto L_0800aa76;
    case 0x0800aa78u: goto L_0800aa78;
    case 0x0800aa7au: goto L_0800aa7a;
    case 0x0800aa7cu: goto L_0800aa7c;
    case 0x0800aa7eu: goto L_0800aa7e;
    case 0x0800aa80u: goto L_0800aa80;
    case 0x0800aa82u: goto L_0800aa82;
    case 0x0800aa84u: goto L_0800aa84;
    case 0x0800aa86u: goto L_0800aa86;
    case 0x0800aa88u: goto L_0800aa88;
    case 0x0800aa8cu: goto L_0800aa8c;
    case 0x0800aa8eu: goto L_0800aa8e;
    case 0x0800aa90u: goto L_0800aa90;
    case 0x0800aa92u: goto L_0800aa92;
    case 0x0800aa94u: goto L_0800aa94;
    case 0x0800aa96u: goto L_0800aa96;
    case 0x0800aa98u: goto L_0800aa98;
    case 0x0800aa9au: goto L_0800aa9a;
    case 0x0800aa9cu: goto L_0800aa9c;
    case 0x0800aa9eu: goto L_0800aa9e;
    case 0x0800aaa0u: goto L_0800aaa0;
    case 0x0800aaa2u: goto L_0800aaa2;
    case 0x0800aaa4u: goto L_0800aaa4;
    case 0x0800aaa6u: goto L_0800aaa6;
    case 0x0800aaa8u: goto L_0800aaa8;
    case 0x0800aaaau: goto L_0800aaaa;
    case 0x0800aaacu: goto L_0800aaac;
    case 0x0800aaaeu: goto L_0800aaae;
    case 0x0800aab0u: goto L_0800aab0;
    case 0x0800aab2u: goto L_0800aab2;
    case 0x0800aab4u: goto L_0800aab4;
    case 0x0800aab6u: goto L_0800aab6;
    case 0x0800aab8u: goto L_0800aab8;
    case 0x0800aabau: goto L_0800aaba;
    case 0x0800aabcu: goto L_0800aabc;
    case 0x0800aabeu: goto L_0800aabe;
    case 0x0800aac0u: goto L_0800aac0;
    case 0x0800aac2u: goto L_0800aac2;
    case 0x0800aac4u: goto L_0800aac4;
    case 0x0800aac6u: goto L_0800aac6;
    case 0x0800aac8u: goto L_0800aac8;
    case 0x0800aacau: goto L_0800aaca;
    case 0x0800aaccu: goto L_0800aacc;
    case 0x0800aaceu: goto L_0800aace;
    case 0x0800aad0u: goto L_0800aad0;
    case 0x0800aad2u: goto L_0800aad2;
    case 0x0800aad4u: goto L_0800aad4;
    case 0x0800aad6u: goto L_0800aad6;
    case 0x0800aad8u: goto L_0800aad8;
    case 0x0800aadau: goto L_0800aada;
    case 0x0800aadcu: goto L_0800aadc;
    case 0x0800aadeu: goto L_0800aade;
    case 0x0800aae0u: goto L_0800aae0;
    case 0x0800aae2u: goto L_0800aae2;
    case 0x0800aae4u: goto L_0800aae4;
    case 0x0800aae6u: goto L_0800aae6;
    case 0x0800aae8u: goto L_0800aae8;
    case 0x0800aaeau: goto L_0800aaea;
    case 0x0800aaecu: goto L_0800aaec;
    case 0x0800aaeeu: goto L_0800aaee;
    case 0x0800aaf0u: goto L_0800aaf0;
    case 0x0800aaf2u: goto L_0800aaf2;
    case 0x0800aaf4u: goto L_0800aaf4;
    case 0x0800aaf6u: goto L_0800aaf6;
    case 0x0800aaf8u: goto L_0800aaf8;
    case 0x0800aafau: goto L_0800aafa;
    case 0x0800aafcu: goto L_0800aafc;
    case 0x0800aafeu: goto L_0800aafe;
    case 0x0800ab00u: goto L_0800ab00;
    case 0x0800ab02u: goto L_0800ab02;
    case 0x0800ab58u: goto L_0800ab58;
    case 0x0800ab5au: goto L_0800ab5a;
    case 0x0800ab5cu: goto L_0800ab5c;
    case 0x0800ab5eu: goto L_0800ab5e;
    case 0x0800ab60u: goto L_0800ab60;
    case 0x0800ab62u: goto L_0800ab62;
    case 0x0800ab64u: goto L_0800ab64;
    case 0x0800ab66u: goto L_0800ab66;
    case 0x0800ab68u: goto L_0800ab68;
    case 0x0800ab6au: goto L_0800ab6a;
    case 0x0800ab6cu: goto L_0800ab6c;
    case 0x0800ab6eu: goto L_0800ab6e;
    case 0x0800ab70u: goto L_0800ab70;
    case 0x0800ab72u: goto L_0800ab72;
    case 0x0800ab74u: goto L_0800ab74;
    case 0x0800ab78u: goto L_0800ab78;
    case 0x0800ab7au: goto L_0800ab7a;
    case 0x0800ab7cu: goto L_0800ab7c;
    case 0x0800ab7eu: goto L_0800ab7e;
    case 0x0800ab80u: goto L_0800ab80;
    case 0x0800ab82u: goto L_0800ab82;
    case 0x0800ab84u: goto L_0800ab84;
    case 0x0800ab88u: goto L_0800ab88;
    case 0x0800ab8au: goto L_0800ab8a;
    case 0x0800ab8cu: goto L_0800ab8c;
    case 0x0800ab8eu: goto L_0800ab8e;
    case 0x0800ab90u: goto L_0800ab90;
    case 0x0800ab92u: goto L_0800ab92;
    case 0x0800ab94u: goto L_0800ab94;
    case 0x0800ab98u: goto L_0800ab98;
    case 0x0800ab9au: goto L_0800ab9a;
    case 0x0800ab9cu: goto L_0800ab9c;
    case 0x0800ab9eu: goto L_0800ab9e;
    case 0x0800aba0u: goto L_0800aba0;
    case 0x0800aba2u: goto L_0800aba2;
    case 0x0800aba4u: goto L_0800aba4;
    case 0x0800aba6u: goto L_0800aba6;
    case 0x0800aba8u: goto L_0800aba8;
    case 0x0800abaau: goto L_0800abaa;
    case 0x0800abacu: goto L_0800abac;
    case 0x0800abaeu: goto L_0800abae;
    case 0x0800abb0u: goto L_0800abb0;
    case 0x0800abb2u: goto L_0800abb2;
    case 0x0800abb6u: goto L_0800abb6;
    case 0x0800abb8u: goto L_0800abb8;
    case 0x0800abbau: goto L_0800abba;
    case 0x0800abbcu: goto L_0800abbc;
    case 0x0800abbeu: goto L_0800abbe;
    case 0x0800abc0u: goto L_0800abc0;
    case 0x0800abc2u: goto L_0800abc2;
    case 0x0800abc4u: goto L_0800abc4;
    case 0x0800abc6u: goto L_0800abc6;
    case 0x0800abc8u: goto L_0800abc8;
    case 0x0800abcau: goto L_0800abca;
    case 0x0800abceu: goto L_0800abce;
    case 0x0800abd0u: goto L_0800abd0;
    case 0x0800abd2u: goto L_0800abd2;
    case 0x0800abd4u: goto L_0800abd4;
    case 0x0800abd6u: goto L_0800abd6;
    case 0x0800abd8u: goto L_0800abd8;
    case 0x0800abdau: goto L_0800abda;
    case 0x0800abdcu: goto L_0800abdc;
    case 0x0800abdeu: goto L_0800abde;
    case 0x0800abe0u: goto L_0800abe0;
    case 0x0800abe2u: goto L_0800abe2;
    case 0x0800abe4u: goto L_0800abe4;
    case 0x0800abe6u: goto L_0800abe6;
    case 0x0800abe8u: goto L_0800abe8;
    case 0x0800abeau: goto L_0800abea;
    case 0x0800abecu: goto L_0800abec;
    case 0x0800abeeu: goto L_0800abee;
    case 0x0800abf0u: goto L_0800abf0;
    case 0x0800abf2u: goto L_0800abf2;
    case 0x0800abf4u: goto L_0800abf4;
    case 0x0800abf6u: goto L_0800abf6;
    case 0x0800abf8u: goto L_0800abf8;
    case 0x0800abfcu: goto L_0800abfc;
    case 0x0800abfeu: goto L_0800abfe;
    case 0x0800ac00u: goto L_0800ac00;
    case 0x0800ac02u: goto L_0800ac02;
    case 0x0800ac04u: goto L_0800ac04;
    case 0x0800ac06u: goto L_0800ac06;
    case 0x0800ac08u: goto L_0800ac08;
    case 0x0800ac0au: goto L_0800ac0a;
    case 0x0800ac0cu: goto L_0800ac0c;
    case 0x0800ac0eu: goto L_0800ac0e;
    case 0x0800ac10u: goto L_0800ac10;
    case 0x0800ac12u: goto L_0800ac12;
    case 0x0800ac14u: goto L_0800ac14;
    case 0x0800ac16u: goto L_0800ac16;
    case 0x0800ac18u: goto L_0800ac18;
    case 0x0800ac1au: goto L_0800ac1a;
    case 0x0800ac1cu: goto L_0800ac1c;
    case 0x0800ac1eu: goto L_0800ac1e;
    case 0x0800ac20u: goto L_0800ac20;
    case 0x0800ac22u: goto L_0800ac22;
    case 0x0800ac24u: goto L_0800ac24;
    case 0x0800ac26u: goto L_0800ac26;
    case 0x0800ac28u: goto L_0800ac28;
    case 0x0800ac2au: goto L_0800ac2a;
    case 0x0800ac2cu: goto L_0800ac2c;
    case 0x0800ac2eu: goto L_0800ac2e;
    case 0x0800ac30u: goto L_0800ac30;
    case 0x0800ac32u: goto L_0800ac32;
    case 0x0800ac34u: goto L_0800ac34;
    case 0x0800ac36u: goto L_0800ac36;
    case 0x0800ac38u: goto L_0800ac38;
    case 0x0800ac3au: goto L_0800ac3a;
    case 0x0800ac3eu: goto L_0800ac3e;
    case 0x0800ac40u: goto L_0800ac40;
    case 0x0800ac42u: goto L_0800ac42;
    case 0x0800ac44u: goto L_0800ac44;
    case 0x0800ac46u: goto L_0800ac46;
    case 0x0800ac48u: goto L_0800ac48;
    case 0x0800ac4au: goto L_0800ac4a;
    case 0x0800ac4cu: goto L_0800ac4c;
    case 0x0800ac4eu: goto L_0800ac4e;
    case 0x0800ac50u: goto L_0800ac50;
    case 0x0800ac52u: goto L_0800ac52;
    case 0x0800ac54u: goto L_0800ac54;
    case 0x0800ac56u: goto L_0800ac56;
    case 0x0800ac5au: goto L_0800ac5a;
    case 0x0800ac5cu: goto L_0800ac5c;
    case 0x0800ac5eu: goto L_0800ac5e;
    case 0x0800ac60u: goto L_0800ac60;
    case 0x0800ac62u: goto L_0800ac62;
    case 0x0800ac64u: goto L_0800ac64;
    case 0x0800ac66u: goto L_0800ac66;
    case 0x0800ac68u: goto L_0800ac68;
    case 0x0800ac6au: goto L_0800ac6a;
    case 0x0800ac6cu: goto L_0800ac6c;
    case 0x0800ac6eu: goto L_0800ac6e;
    case 0x0800ac70u: goto L_0800ac70;
    case 0x0800ac72u: goto L_0800ac72;
    case 0x0800ac74u: goto L_0800ac74;
    case 0x0800ac76u: goto L_0800ac76;
    case 0x0800ac78u: goto L_0800ac78;
    case 0x0800ac7au: goto L_0800ac7a;
    case 0x0800ac7cu: goto L_0800ac7c;
    case 0x0800ac7eu: goto L_0800ac7e;
    case 0x0800ac80u: goto L_0800ac80;
    case 0x0800ac82u: goto L_0800ac82;
    case 0x0800ac84u: goto L_0800ac84;
    case 0x0800ac86u: goto L_0800ac86;
    case 0x0800ac88u: goto L_0800ac88;
    case 0x0800ac8au: goto L_0800ac8a;
    case 0x0800ac8cu: goto L_0800ac8c;
    case 0x0800ac8eu: goto L_0800ac8e;
    case 0x0800ac92u: goto L_0800ac92;
    case 0x0800ac94u: goto L_0800ac94;
    case 0x0800ac96u: goto L_0800ac96;
    case 0x0800ac98u: goto L_0800ac98;
    case 0x0800ac9au: goto L_0800ac9a;
    case 0x0800ac9cu: goto L_0800ac9c;
    case 0x0800ac9eu: goto L_0800ac9e;
    case 0x0800aca0u: goto L_0800aca0;
    case 0x0800aca2u: goto L_0800aca2;
    case 0x0800aca4u: goto L_0800aca4;
    case 0x0800aca6u: goto L_0800aca6;
    case 0x0800aca8u: goto L_0800aca8;
    case 0x0800acacu: goto L_0800acac;
    case 0x0800acaeu: goto L_0800acae;
    case 0x0800acb0u: goto L_0800acb0;
    case 0x0800acb2u: goto L_0800acb2;
    case 0x0800acb6u: goto L_0800acb6;
    case 0x0800acb8u: goto L_0800acb8;
    case 0x0800acbau: goto L_0800acba;
    case 0x0800acbcu: goto L_0800acbc;
    case 0x0800acbeu: goto L_0800acbe;
    case 0x0800acc0u: goto L_0800acc0;
    case 0x0800acc2u: goto L_0800acc2;
    case 0x0800acc4u: goto L_0800acc4;
    case 0x0800acc6u: goto L_0800acc6;
    case 0x0800acc8u: goto L_0800acc8;
    case 0x0800accau: goto L_0800acca;
    case 0x0800acccu: goto L_0800accc;
    case 0x0800acceu: goto L_0800acce;
    case 0x0800acd0u: goto L_0800acd0;
    case 0x0800acd2u: goto L_0800acd2;
    case 0x0800acd4u: goto L_0800acd4;
    case 0x0800acd6u: goto L_0800acd6;
    case 0x0800acd8u: goto L_0800acd8;
    case 0x0800acdau: goto L_0800acda;
    case 0x0800acdeu: goto L_0800acde;
    case 0x0800ace0u: goto L_0800ace0;
    case 0x0800ace2u: goto L_0800ace2;
    case 0x0800ace4u: goto L_0800ace4;
    case 0x0800ace6u: goto L_0800ace6;
    case 0x0800ace8u: goto L_0800ace8;
    case 0x0800aceau: goto L_0800acea;
    case 0x0800acecu: goto L_0800acec;
    case 0x0800acf0u: goto L_0800acf0;
    case 0x0800acf2u: goto L_0800acf2;
    case 0x0800acf4u: goto L_0800acf4;
    case 0x0800acf6u: goto L_0800acf6;
    case 0x0800acf8u: goto L_0800acf8;
    case 0x0800acfau: goto L_0800acfa;
    case 0x0800acfcu: goto L_0800acfc;
    case 0x0800acfeu: goto L_0800acfe;
    case 0x0800ad00u: goto L_0800ad00;
    case 0x0800ad02u: goto L_0800ad02;
    case 0x0800ad06u: goto L_0800ad06;
    case 0x0800ad08u: goto L_0800ad08;
    case 0x0800ad0au: goto L_0800ad0a;
    case 0x0800ad0cu: goto L_0800ad0c;
    case 0x0800ad0eu: goto L_0800ad0e;
    case 0x0800ad12u: goto L_0800ad12;
    case 0x0800ad14u: goto L_0800ad14;
    case 0x0800ad16u: goto L_0800ad16;
    case 0x0800ad18u: goto L_0800ad18;
    case 0x0800ad1au: goto L_0800ad1a;
    case 0x0800ad1cu: goto L_0800ad1c;
    case 0x0800ad1eu: goto L_0800ad1e;
    case 0x0800ad20u: goto L_0800ad20;
    case 0x0800ad22u: goto L_0800ad22;
    case 0x0800ad24u: goto L_0800ad24;
    case 0x0800ad26u: goto L_0800ad26;
    case 0x0800ad28u: goto L_0800ad28;
    case 0x0800ad2au: goto L_0800ad2a;
    case 0x0800ad2cu: goto L_0800ad2c;
    case 0x0800ad2eu: goto L_0800ad2e;
    case 0x0800ad30u: goto L_0800ad30;
    case 0x0800ad32u: goto L_0800ad32;
    case 0x0800ad34u: goto L_0800ad34;
    case 0x0800ad36u: goto L_0800ad36;
    case 0x0800ad3au: goto L_0800ad3a;
    case 0x0800ad3cu: goto L_0800ad3c;
    case 0x0800ad3eu: goto L_0800ad3e;
    case 0x0800ad40u: goto L_0800ad40;
    case 0x0800ad44u: goto L_0800ad44;
    case 0x0800ad46u: goto L_0800ad46;
    case 0x0800ad48u: goto L_0800ad48;
    case 0x0800ad4cu: goto L_0800ad4c;
    case 0x0800ad4eu: goto L_0800ad4e;
    case 0x0800ad50u: goto L_0800ad50;
    case 0x0800ad54u: goto L_0800ad54;
    case 0x0800ad56u: goto L_0800ad56;
    case 0x0800ad58u: goto L_0800ad58;
    case 0x0800ad5au: goto L_0800ad5a;
    case 0x0800ad5cu: goto L_0800ad5c;
    case 0x0800ad5eu: goto L_0800ad5e;
    case 0x0800ad60u: goto L_0800ad60;
    case 0x0800ad62u: goto L_0800ad62;
    case 0x0800ad64u: goto L_0800ad64;
    case 0x0800ad66u: goto L_0800ad66;
    case 0x0800ad6au: goto L_0800ad6a;
    case 0x0800ad6cu: goto L_0800ad6c;
    case 0x0800ad6eu: goto L_0800ad6e;
    case 0x0800ad72u: goto L_0800ad72;
    case 0x0800ad74u: goto L_0800ad74;
    case 0x0800ad76u: goto L_0800ad76;
    case 0x0800ad78u: goto L_0800ad78;
    case 0x0800ad7au: goto L_0800ad7a;
    case 0x0800ad7cu: goto L_0800ad7c;
    case 0x0800ad80u: goto L_0800ad80;
    case 0x0800ad82u: goto L_0800ad82;
    case 0x0800ad84u: goto L_0800ad84;
    case 0x0800ad86u: goto L_0800ad86;
    case 0x0800ad8au: goto L_0800ad8a;
    case 0x0800ad8cu: goto L_0800ad8c;
    case 0x0800ad8eu: goto L_0800ad8e;
    case 0x0800ad90u: goto L_0800ad90;
    case 0x0800ad92u: goto L_0800ad92;
    case 0x0800ad94u: goto L_0800ad94;
    case 0x0800ad96u: goto L_0800ad96;
    case 0x0800ad98u: goto L_0800ad98;
    case 0x0800ad9cu: goto L_0800ad9c;
    case 0x0800ad9eu: goto L_0800ad9e;
    case 0x0800ada0u: goto L_0800ada0;
    case 0x0800ada2u: goto L_0800ada2;
    case 0x0800ada4u: goto L_0800ada4;
    case 0x0800ada6u: goto L_0800ada6;
    case 0x0800ada8u: goto L_0800ada8;
    case 0x0800adaau: goto L_0800adaa;
    case 0x0800adacu: goto L_0800adac;
    case 0x0800adaeu: goto L_0800adae;
    case 0x0800adb0u: goto L_0800adb0;
    case 0x0800adb2u: goto L_0800adb2;
    case 0x0800adb4u: goto L_0800adb4;
    case 0x0800adb6u: goto L_0800adb6;
    case 0x0800adb8u: goto L_0800adb8;
    case 0x0800adbau: goto L_0800adba;
    case 0x0800adbcu: goto L_0800adbc;
    case 0x0800adbeu: goto L_0800adbe;
    case 0x0800adc2u: goto L_0800adc2;
    case 0x0800adc4u: goto L_0800adc4;
    case 0x0800adc6u: goto L_0800adc6;
    case 0x0800adcau: goto L_0800adca;
    case 0x0800adccu: goto L_0800adcc;
    case 0x0800adceu: goto L_0800adce;
    case 0x0800add0u: goto L_0800add0;
    case 0x0800add2u: goto L_0800add2;
    case 0x0800add4u: goto L_0800add4;
    case 0x0800add6u: goto L_0800add6;
    case 0x0800add8u: goto L_0800add8;
    case 0x0800addau: goto L_0800adda;
    case 0x0800addcu: goto L_0800addc;
    case 0x0800addeu: goto L_0800adde;
    case 0x0800ade0u: goto L_0800ade0;
    case 0x0800ade2u: goto L_0800ade2;
    case 0x0800ade4u: goto L_0800ade4;
    case 0x0800ade6u: goto L_0800ade6;
    case 0x0800ade8u: goto L_0800ade8;
    case 0x0800adeau: goto L_0800adea;
    case 0x0800adecu: goto L_0800adec;
    case 0x0800adeeu: goto L_0800adee;
    case 0x0800adf0u: goto L_0800adf0;
    case 0x0800adf2u: goto L_0800adf2;
    case 0x0800adf4u: goto L_0800adf4;
    case 0x0800adf6u: goto L_0800adf6;
    case 0x0800adf8u: goto L_0800adf8;
    case 0x0800adfau: goto L_0800adfa;
    case 0x0800adfcu: goto L_0800adfc;
    case 0x0800adfeu: goto L_0800adfe;
    case 0x0800ae00u: goto L_0800ae00;
    case 0x0800ae02u: goto L_0800ae02;
    case 0x0800ae04u: goto L_0800ae04;
    case 0x0800ae06u: goto L_0800ae06;
    case 0x0800ae08u: goto L_0800ae08;
    case 0x0800ae0au: goto L_0800ae0a;
    case 0x0800ae0cu: goto L_0800ae0c;
    case 0x0800ae0eu: goto L_0800ae0e;
    case 0x0800ae10u: goto L_0800ae10;
    case 0x0800ae12u: goto L_0800ae12;
    case 0x0800ae14u: goto L_0800ae14;
    case 0x0800ae16u: goto L_0800ae16;
    case 0x0800ae18u: goto L_0800ae18;
    case 0x0800ae1au: goto L_0800ae1a;
    case 0x0800ae1cu: goto L_0800ae1c;
    case 0x0800ae1eu: goto L_0800ae1e;
    case 0x0800ae20u: goto L_0800ae20;
    case 0x0800ae22u: goto L_0800ae22;
    case 0x0800ae24u: goto L_0800ae24;
    case 0x0800ae26u: goto L_0800ae26;
    case 0x0800ae28u: goto L_0800ae28;
    case 0x0800ae2au: goto L_0800ae2a;
    case 0x0800ae2cu: goto L_0800ae2c;
    case 0x0800ae2eu: goto L_0800ae2e;
    case 0x0800ae30u: goto L_0800ae30;
    case 0x0800ae32u: goto L_0800ae32;
    case 0x0800ae34u: goto L_0800ae34;
    case 0x0800ae36u: goto L_0800ae36;
    case 0x0800ae38u: goto L_0800ae38;
    case 0x0800ae3au: goto L_0800ae3a;
    case 0x0800ae3cu: goto L_0800ae3c;
    case 0x0800ae3eu: goto L_0800ae3e;
    case 0x0800ae40u: goto L_0800ae40;
    case 0x0800ae42u: goto L_0800ae42;
    case 0x0800ae44u: goto L_0800ae44;
    case 0x0800ae46u: goto L_0800ae46;
    case 0x0800ae48u: goto L_0800ae48;
    case 0x0800ae4au: goto L_0800ae4a;
    case 0x0800ae4cu: goto L_0800ae4c;
    case 0x0800ae4eu: goto L_0800ae4e;
    case 0x0800ae50u: goto L_0800ae50;
    case 0x0800ae52u: goto L_0800ae52;
    case 0x0800ae54u: goto L_0800ae54;
    case 0x0800ae56u: goto L_0800ae56;
    case 0x0800ae58u: goto L_0800ae58;
    case 0x0800ae5au: goto L_0800ae5a;
    case 0x0800ae5cu: goto L_0800ae5c;
    case 0x0800ae5eu: goto L_0800ae5e;
    case 0x0800ae60u: goto L_0800ae60;
    case 0x0800ae62u: goto L_0800ae62;
    case 0x0800ae64u: goto L_0800ae64;
    case 0x0800ae66u: goto L_0800ae66;
    case 0x0800ae68u: goto L_0800ae68;
    case 0x0800ae6au: goto L_0800ae6a;
    case 0x0800ae6cu: goto L_0800ae6c;
    case 0x0800ae6eu: goto L_0800ae6e;
    case 0x0800ae70u: goto L_0800ae70;
    case 0x0800ae72u: goto L_0800ae72;
    case 0x0800ae74u: goto L_0800ae74;
    case 0x0800ae76u: goto L_0800ae76;
    case 0x0800ae78u: goto L_0800ae78;
    case 0x0800ae7au: goto L_0800ae7a;
    case 0x0800ae7cu: goto L_0800ae7c;
    case 0x0800ae7eu: goto L_0800ae7e;
    case 0x0800ae80u: goto L_0800ae80;
    case 0x0800ae82u: goto L_0800ae82;
    case 0x0800ae84u: goto L_0800ae84;
    case 0x0800ae86u: goto L_0800ae86;
    case 0x0800ae88u: goto L_0800ae88;
    case 0x0800ae8au: goto L_0800ae8a;
    case 0x0800ae8cu: goto L_0800ae8c;
    case 0x0800ae8eu: goto L_0800ae8e;
    case 0x0800ae90u: goto L_0800ae90;
    case 0x0800ae92u: goto L_0800ae92;
    case 0x0800ae94u: goto L_0800ae94;
    case 0x0800ae96u: goto L_0800ae96;
    case 0x0800ae98u: goto L_0800ae98;
    case 0x0800ae9au: goto L_0800ae9a;
    case 0x0800ae9cu: goto L_0800ae9c;
    case 0x0800ae9eu: goto L_0800ae9e;
    case 0x0800aea0u: goto L_0800aea0;
    case 0x0800aea2u: goto L_0800aea2;
    case 0x0800aea4u: goto L_0800aea4;
    case 0x0800aea6u: goto L_0800aea6;
    case 0x0800aea8u: goto L_0800aea8;
    case 0x0800aeaau: goto L_0800aeaa;
    case 0x0800aeacu: goto L_0800aeac;
    case 0x0800aeaeu: goto L_0800aeae;
    case 0x0800aeb0u: goto L_0800aeb0;
    case 0x0800aeb2u: goto L_0800aeb2;
    case 0x0800aeb4u: goto L_0800aeb4;
    case 0x0800aeb6u: goto L_0800aeb6;
    case 0x0800aeb8u: goto L_0800aeb8;
    case 0x0800aebau: goto L_0800aeba;
    case 0x0800aebcu: goto L_0800aebc;
    case 0x0800aebeu: goto L_0800aebe;
    case 0x0800aec0u: goto L_0800aec0;
    case 0x0800aec2u: goto L_0800aec2;
    case 0x0800aec4u: goto L_0800aec4;
    case 0x0800aec6u: goto L_0800aec6;
    case 0x0800aec8u: goto L_0800aec8;
    case 0x0800aecau: goto L_0800aeca;
    case 0x0800aeccu: goto L_0800aecc;
    case 0x0800aeceu: goto L_0800aece;
    case 0x0800aed0u: goto L_0800aed0;
    case 0x0800aed2u: goto L_0800aed2;
    case 0x0800aed4u: goto L_0800aed4;
    case 0x0800aed6u: goto L_0800aed6;
    case 0x0800aed8u: goto L_0800aed8;
    case 0x0800aedau: goto L_0800aeda;
    case 0x0800aedcu: goto L_0800aedc;
    case 0x0800aedeu: goto L_0800aede;
    case 0x0800aee0u: goto L_0800aee0;
    case 0x0800aee2u: goto L_0800aee2;
    case 0x0800aee4u: goto L_0800aee4;
    case 0x0800aee6u: goto L_0800aee6;
    case 0x0800aee8u: goto L_0800aee8;
    case 0x0800aeeau: goto L_0800aeea;
    case 0x0800aeecu: goto L_0800aeec;
    case 0x0800aeeeu: goto L_0800aeee;
    case 0x0800aef0u: goto L_0800aef0;
    case 0x0800aef2u: goto L_0800aef2;
    case 0x0800aef4u: goto L_0800aef4;
    case 0x0800aef6u: goto L_0800aef6;
    case 0x0800aef8u: goto L_0800aef8;
    case 0x0800aefau: goto L_0800aefa;
    case 0x0800aefcu: goto L_0800aefc;
    case 0x0800aefeu: goto L_0800aefe;
    case 0x0800af00u: goto L_0800af00;
    case 0x0800af02u: goto L_0800af02;
    case 0x0800af04u: goto L_0800af04;
    case 0x0800af06u: goto L_0800af06;
    case 0x0800af0au: goto L_0800af0a;
    case 0x0800af0cu: goto L_0800af0c;
    case 0x0800af10u: goto L_0800af10;
    case 0x0800af12u: goto L_0800af12;
    case 0x0800af14u: goto L_0800af14;
    case 0x0800af16u: goto L_0800af16;
    case 0x0800af18u: goto L_0800af18;
    case 0x0800af1au: goto L_0800af1a;
    case 0x0800af1eu: goto L_0800af1e;
    case 0x0800af20u: goto L_0800af20;
    case 0x0800af22u: goto L_0800af22;
    case 0x0800af24u: goto L_0800af24;
    case 0x0800af26u: goto L_0800af26;
    case 0x0800af28u: goto L_0800af28;
    case 0x0800af2au: goto L_0800af2a;
    case 0x0800af2cu: goto L_0800af2c;
    case 0x0800af2eu: goto L_0800af2e;
    case 0x0800af30u: goto L_0800af30;
    case 0x0800af32u: goto L_0800af32;
    case 0x0800af34u: goto L_0800af34;
    case 0x0800af36u: goto L_0800af36;
    case 0x0800af38u: goto L_0800af38;
    case 0x0800af3au: goto L_0800af3a;
    case 0x0800af3cu: goto L_0800af3c;
    case 0x0800af3eu: goto L_0800af3e;
    case 0x0800af42u: goto L_0800af42;
    case 0x0800af44u: goto L_0800af44;
    case 0x0800af46u: goto L_0800af46;
    case 0x0800af48u: goto L_0800af48;
    case 0x0800af4au: goto L_0800af4a;
    case 0x0800af4cu: goto L_0800af4c;
    case 0x0800af50u: goto L_0800af50;
    case 0x0800af52u: goto L_0800af52;
    case 0x0800af54u: goto L_0800af54;
    case 0x0800af58u: goto L_0800af58;
    case 0x0800af5au: goto L_0800af5a;
    case 0x0800af5cu: goto L_0800af5c;
    case 0x0800af5eu: goto L_0800af5e;
    case 0x0800af62u: goto L_0800af62;
    case 0x0800af64u: goto L_0800af64;
    case 0x0800af66u: goto L_0800af66;
    case 0x0800af68u: goto L_0800af68;
    case 0x0800af6au: goto L_0800af6a;
    case 0x0800af6cu: goto L_0800af6c;
    case 0x0800af6eu: goto L_0800af6e;
    case 0x0800af70u: goto L_0800af70;
    case 0x0800af72u: goto L_0800af72;
    case 0x0800af74u: goto L_0800af74;
    case 0x0800af76u: goto L_0800af76;
    case 0x0800af78u: goto L_0800af78;
    case 0x0800af7au: goto L_0800af7a;
    case 0x0800af7cu: goto L_0800af7c;
    case 0x0800af80u: goto L_0800af80;
    case 0x0800af82u: goto L_0800af82;
    case 0x0800af84u: goto L_0800af84;
    case 0x0800af86u: goto L_0800af86;
    case 0x0800af8au: goto L_0800af8a;
    case 0x0800af8cu: goto L_0800af8c;
    case 0x0800af8eu: goto L_0800af8e;
    case 0x0800af90u: goto L_0800af90;
    case 0x0800af92u: goto L_0800af92;
    case 0x0800af94u: goto L_0800af94;
    case 0x0800af96u: goto L_0800af96;
    case 0x0800af98u: goto L_0800af98;
    case 0x0800af9au: goto L_0800af9a;
    case 0x0800af9cu: goto L_0800af9c;
    case 0x0800af9eu: goto L_0800af9e;
    case 0x0800afa0u: goto L_0800afa0;
    case 0x0800afa4u: goto L_0800afa4;
    case 0x0800afa6u: goto L_0800afa6;
    case 0x0800afa8u: goto L_0800afa8;
    case 0x0800afaau: goto L_0800afaa;
    case 0x0800afacu: goto L_0800afac;
    case 0x0800afaeu: goto L_0800afae;
    case 0x0800afb0u: goto L_0800afb0;
    case 0x0800afb4u: goto L_0800afb4;
    case 0x0800afb6u: goto L_0800afb6;
    case 0x0800afb8u: goto L_0800afb8;
    case 0x0800afbau: goto L_0800afba;
    case 0x0800afbcu: goto L_0800afbc;
    case 0x0800afbeu: goto L_0800afbe;
    case 0x0800afc0u: goto L_0800afc0;
    case 0x0800afc2u: goto L_0800afc2;
    case 0x0800afc6u: goto L_0800afc6;
    case 0x0800afdcu: goto L_0800afdc;
    case 0x0800afdeu: goto L_0800afde;
    case 0x0800afe2u: goto L_0800afe2;
    case 0x0800afe4u: goto L_0800afe4;
    case 0x0800afe6u: goto L_0800afe6;
    case 0x0800afeau: goto L_0800afea;
    case 0x0800afecu: goto L_0800afec;
    case 0x0800aff0u: goto L_0800aff0;
    case 0x0800aff2u: goto L_0800aff2;
    case 0x0800aff4u: goto L_0800aff4;
    case 0x0800aff6u: goto L_0800aff6;
    case 0x0800aff8u: goto L_0800aff8;
    case 0x0800affau: goto L_0800affa;
    case 0x0800affeu: goto L_0800affe;
    case 0x0800b000u: goto L_0800b000;
    case 0x0800b002u: goto L_0800b002;
    case 0x0800b004u: goto L_0800b004;
    case 0x0800b006u: goto L_0800b006;
    case 0x0800b008u: goto L_0800b008;
    case 0x0800b00cu: goto L_0800b00c;
    case 0x0800b00eu: goto L_0800b00e;
    case 0x0800b010u: goto L_0800b010;
    case 0x0800b012u: goto L_0800b012;
    case 0x0800b014u: goto L_0800b014;
    case 0x0800b016u: goto L_0800b016;
    case 0x0800b018u: goto L_0800b018;
    case 0x0800b01au: goto L_0800b01a;
    case 0x0800b01cu: goto L_0800b01c;
    case 0x0800b01eu: goto L_0800b01e;
    case 0x0800b020u: goto L_0800b020;
    case 0x0800b022u: goto L_0800b022;
    case 0x0800b024u: goto L_0800b024;
    case 0x0800b026u: goto L_0800b026;
    case 0x0800b028u: goto L_0800b028;
    case 0x0800b02au: goto L_0800b02a;
    case 0x0800b02cu: goto L_0800b02c;
    case 0x0800b030u: goto L_0800b030;
    case 0x0800b032u: goto L_0800b032;
    case 0x0800b034u: goto L_0800b034;
    case 0x0800b036u: goto L_0800b036;
    case 0x0800b038u: goto L_0800b038;
    case 0x0800b03au: goto L_0800b03a;
    case 0x0800b03cu: goto L_0800b03c;
    case 0x0800b03eu: goto L_0800b03e;
    case 0x0800b040u: goto L_0800b040;
    case 0x0800b042u: goto L_0800b042;
    case 0x0800b044u: goto L_0800b044;
    case 0x0800b046u: goto L_0800b046;
    case 0x0800b04au: goto L_0800b04a;
    case 0x0800b04cu: goto L_0800b04c;
    case 0x0800b04eu: goto L_0800b04e;
    case 0x0800b050u: goto L_0800b050;
    case 0x0800b052u: goto L_0800b052;
    case 0x0800b054u: goto L_0800b054;
    case 0x0800b056u: goto L_0800b056;
    case 0x0800b058u: goto L_0800b058;
    case 0x0800b05au: goto L_0800b05a;
    case 0x0800b05cu: goto L_0800b05c;
    case 0x0800b05eu: goto L_0800b05e;
    case 0x0800b060u: goto L_0800b060;
    case 0x0800b062u: goto L_0800b062;
    case 0x0800b064u: goto L_0800b064;
    case 0x0800b068u: goto L_0800b068;
    case 0x0800b06au: goto L_0800b06a;
    case 0x0800b06cu: goto L_0800b06c;
    case 0x0800b06eu: goto L_0800b06e;
    case 0x0800b070u: goto L_0800b070;
    case 0x0800b072u: goto L_0800b072;
    case 0x0800b074u: goto L_0800b074;
    case 0x0800b076u: goto L_0800b076;
    case 0x0800b078u: goto L_0800b078;
    case 0x0800b07cu: goto L_0800b07c;
    case 0x0800b07eu: goto L_0800b07e;
    case 0x0800b080u: goto L_0800b080;
    case 0x0800b082u: goto L_0800b082;
    case 0x0800b084u: goto L_0800b084;
    case 0x0800b086u: goto L_0800b086;
    case 0x0800b08au: goto L_0800b08a;
    case 0x0800b08cu: goto L_0800b08c;
    case 0x0800b08eu: goto L_0800b08e;
    case 0x0800b090u: goto L_0800b090;
    case 0x0800b092u: goto L_0800b092;
    case 0x0800b094u: goto L_0800b094;
    case 0x0800b096u: goto L_0800b096;
    case 0x0800b098u: goto L_0800b098;
    case 0x0800b09au: goto L_0800b09a;
    case 0x0800b09cu: goto L_0800b09c;
    case 0x0800b09eu: goto L_0800b09e;
    case 0x0800b0a0u: goto L_0800b0a0;
    case 0x0800b0a2u: goto L_0800b0a2;
    case 0x0800b0a4u: goto L_0800b0a4;
    case 0x0800b0a6u: goto L_0800b0a6;
    case 0x0800b0aau: goto L_0800b0aa;
    case 0x0800b0acu: goto L_0800b0ac;
    case 0x0800b0b0u: goto L_0800b0b0;
    case 0x0800b0b4u: goto L_0800b0b4;
    case 0x0800b0b8u: goto L_0800b0b8;
    case 0x0800b0bcu: goto L_0800b0bc;
    case 0x0800b0beu: goto L_0800b0be;
    case 0x0800b0c0u: goto L_0800b0c0;
    case 0x0800b0c4u: goto L_0800b0c4;
    default: s->fault=-1;s->fault_address=s->pc;return -1;
    }

    /* Startup: vector remap and peripheral initialization */
L_0800a708: STEP(0x0800a708u); /* ldr r3, [pc, #0x3f8] */
    s->r[3]=read_mem(s,(0x800a70cu + 0x3f8u),4);
    goto L_0800a70a;
L_0800a70a: STEP(0x0800a70au); /* ldr r2, [pc, #0x3fc] */
    s->r[2]=read_mem(s,(0x800a70cu + 0x3fcu),4);
    goto L_0800a70c;
L_0800a70c: STEP(0x0800a70cu); /* sub sp, #0x50 */
    s->r[13]=(s->r[13])-(0x50u);
    goto L_0800a70e;
L_0800a70e: STEP(0x0800a70eu); /* movs r0, #0 */
    s->r[0]=nz(s,0x0u);
    goto L_0800a710;
L_0800a710: STEP(0x0800a710u); /* lsls r1, r0, #2 */
    s->r[1]=lsl(s,s->r[0],0x2u);
    goto L_0800a712;
L_0800a712: STEP(0x0800a712u); /* adds r4, r1, r3 */
    s->r[4]=add(s,s->r[1],s->r[3]);
    goto L_0800a714;
L_0800a714: STEP(0x0800a714u); /* ldr r4, [r4] */
    s->r[4]=read_mem(s,(s->r[4]),4);
    goto L_0800a716;
L_0800a716: STEP(0x0800a716u); /* str r4, [r2, r1] */
    write_mem(s,(s->r[2] + s->r[1]),4,s->r[4]);
    goto L_0800a718;
L_0800a718: STEP(0x0800a718u); /* adds r0, r0, #1 */
    s->r[0]=add(s,s->r[0],0x1u);
    goto L_0800a71a;
L_0800a71a: STEP(0x0800a71au); /* uxtb r0, r0 */
    s->r[0]=(uint8_t)(s->r[0]);
    goto L_0800a71c;
L_0800a71c: STEP(0x0800a71cu); /* cmp r0, #0x2d */
    (void)sub(s,s->r[0],0x2du);
    goto L_0800a71e;
L_0800a71e: STEP(0x0800a71eu); /* blo #0x800a710 */
    if(!C)goto L_0800a710;
    goto L_0800a720;
L_0800a720: STEP(0x0800a720u); /* ldr r0, [pc, #0x3e8] */
    s->r[0]=read_mem(s,(0x800a724u + 0x3e8u),4);
    goto L_0800a722;
L_0800a722: STEP(0x0800a722u); /* ldr r1, [r0, #0x18] */
    s->r[1]=read_mem(s,(s->r[0] + 0x18u),4);
    goto L_0800a724;
L_0800a724: STEP(0x0800a724u); /* movs r2, #1 */
    s->r[2]=nz(s,0x1u);
    goto L_0800a726;
L_0800a726: STEP(0x0800a726u); /* orrs r1, r2 */
    s->r[1]=nz(s,(s->r[1])|(s->r[2]));
    goto L_0800a728;
L_0800a728: STEP(0x0800a728u); /* str r1, [r0, #0x18] */
    write_mem(s,(s->r[0] + 0x18u),4,s->r[1]);
    goto L_0800a72a;
L_0800a72a: STEP(0x0800a72au); /* ldr r0, [r0, #0x18] */
    s->r[0]=read_mem(s,(s->r[0] + 0x18u),4);
    goto L_0800a72c;
L_0800a72c: STEP(0x0800a72cu); /* ands r0, r2 */
    s->r[0]=nz(s,(s->r[0])&(s->r[2]));
    goto L_0800a72e;
L_0800a72e: STEP(0x0800a72eu); /* str r0, [sp] */
    write_mem(s,(s->r[13]),4,s->r[0]);
    goto L_0800a730;
L_0800a730: STEP(0x0800a730u); /* ldr r0, [pc, #0x3dc] */
    s->r[0]=read_mem(s,(0x800a734u + 0x3dcu),4);
    goto L_0800a732;
L_0800a732: STEP(0x0800a732u); /* ldr r1, [r0] */
    s->r[1]=read_mem(s,(s->r[0]),4);
    goto L_0800a734;
L_0800a734: STEP(0x0800a734u); /* lsrs r1, r1, #2 */
    s->r[1]=lsr(s,s->r[1],0x2u);
    goto L_0800a736;
L_0800a736: STEP(0x0800a736u); /* lsls r1, r1, #2 */
    s->r[1]=lsl(s,s->r[1],0x2u);
    goto L_0800a738;
L_0800a738: STEP(0x0800a738u); /* str r1, [r0] */
    write_mem(s,(s->r[0]),4,s->r[1]);
    goto L_0800a73a;
L_0800a73a: STEP(0x0800a73au); /* ldr r1, [r0] */
    s->r[1]=read_mem(s,(s->r[0]),4);
    goto L_0800a73c;
L_0800a73c: STEP(0x0800a73cu); /* movs r2, #3 */
    s->r[2]=nz(s,0x3u);
    goto L_0800a73e;
L_0800a73e: STEP(0x0800a73eu); /* orrs r1, r2 */
    s->r[1]=nz(s,(s->r[1])|(s->r[2]));
    goto L_0800a740;
L_0800a740: STEP(0x0800a740u); /* str r1, [r0] */
    write_mem(s,(s->r[0]),4,s->r[1]);
    goto L_0800a742;
L_0800a742: STEP(0x0800a742u); /* bl #0x8006340 */
    s->r[14]=0x0800a747u;
    if(!s->call){s->fault=-2;s->fault_address=0x08006340u;return -2;}
    s->r[15]=0x08006340u;
    temp=(uint32_t)s->call(s->user,0x08006340u,s);
    if(temp){s->pc=0x0800a746u;return 1;}
    goto L_0800a746;
L_0800a746: STEP(0x0800a746u); /* bl #0x800848a */
    s->r[14]=0x0800a74bu;
    if(!s->call){s->fault=-2;s->fault_address=0x0800848au;return -2;}
    s->r[15]=0x0800848au;
    temp=(uint32_t)s->call(s->user,0x0800848au,s);
    if(temp){s->pc=0x0800a74au;return 1;}
    goto L_0800a74a;
L_0800a74a: STEP(0x0800a74au); /* bl #0x8007de8 */
    s->r[14]=0x0800a74fu;
    if(!s->call){s->fault=-2;s->fault_address=0x08007de8u;return -2;}
    s->r[15]=0x08007de8u;
    temp=(uint32_t)s->call(s->user,0x08007de8u,s);
    if(temp){s->pc=0x0800a74eu;return 1;}
    goto L_0800a74e;
L_0800a74e: STEP(0x0800a74eu); /* bl #0x8007db0 */
    s->r[14]=0x0800a753u;
    if(!s->call){s->fault=-2;s->fault_address=0x08007db0u;return -2;}
    s->r[15]=0x08007db0u;
    temp=(uint32_t)s->call(s->user,0x08007db0u,s);
    if(temp){s->pc=0x0800a752u;return 1;}
    goto L_0800a752;
L_0800a752: STEP(0x0800a752u); /* bl #0x8007fc4 */
    s->r[14]=0x0800a757u;
    if(!s->call){s->fault=-2;s->fault_address=0x08007fc4u;return -2;}
    s->r[15]=0x08007fc4u;
    temp=(uint32_t)s->call(s->user,0x08007fc4u,s);
    if(temp){s->pc=0x0800a756u;return 1;}
    goto L_0800a756;
L_0800a756: STEP(0x0800a756u); /* bl #0x8008034 */
    s->r[14]=0x0800a75bu;
    if(!s->call){s->fault=-2;s->fault_address=0x08008034u;return -2;}
    s->r[15]=0x08008034u;
    temp=(uint32_t)s->call(s->user,0x08008034u,s);
    if(temp){s->pc=0x0800a75au;return 1;}
    goto L_0800a75a;
L_0800a75a: STEP(0x0800a75au); /* bl #0x800806c */
    s->r[14]=0x0800a75fu;
    if(!s->call){s->fault=-2;s->fault_address=0x0800806cu;return -2;}
    s->r[15]=0x0800806cu;
    temp=(uint32_t)s->call(s->user,0x0800806cu,s);
    if(temp){s->pc=0x0800a75eu;return 1;}
    goto L_0800a75e;
L_0800a75e: STEP(0x0800a75eu); /* bl #0x8007f38 */
    s->r[14]=0x0800a763u;
    if(!s->call){s->fault=-2;s->fault_address=0x08007f38u;return -2;}
    s->r[15]=0x08007f38u;
    temp=(uint32_t)s->call(s->user,0x08007f38u,s);
    if(temp){s->pc=0x0800a762u;return 1;}
    goto L_0800a762;
L_0800a762: STEP(0x0800a762u); /* bl #0x8007f90 */
    s->r[14]=0x0800a767u;
    if(!s->call){s->fault=-2;s->fault_address=0x08007f90u;return -2;}
    s->r[15]=0x08007f90u;
    temp=(uint32_t)s->call(s->user,0x08007f90u,s);
    if(temp){s->pc=0x0800a766u;return 1;}
    goto L_0800a766;
L_0800a766: STEP(0x0800a766u); /* bl #0x8007d44 */
    s->r[14]=0x0800a76bu;
    if(!s->call){s->fault=-2;s->fault_address=0x08007d44u;return -2;}
    s->r[15]=0x08007d44u;
    temp=(uint32_t)s->call(s->user,0x08007d44u,s);
    if(temp){s->pc=0x0800a76au;return 1;}
    goto L_0800a76a;
L_0800a76a: STEP(0x0800a76au); /* ldr r0, [pc, #0x3a8] */
    s->r[0]=read_mem(s,(0x800a76cu + 0x3a8u),4);
    goto L_0800a76c;
L_0800a76c: STEP(0x0800a76cu); /* bl #0x8005450 */
    s->r[14]=0x0800a771u;
    if(!s->call){s->fault=-2;s->fault_address=0x08005450u;return -2;}
    s->r[15]=0x08005450u;
    temp=(uint32_t)s->call(s->user,0x08005450u,s);
    if(temp){s->pc=0x0800a770u;return 1;}
    goto L_0800a770;
L_0800a770: STEP(0x0800a770u); /* ldr r1, [pc, #0x3a4] */
    s->r[1]=read_mem(s,(0x800a774u + 0x3a4u),4);
    goto L_0800a772;
L_0800a772: STEP(0x0800a772u); /* movs r0, #1 */
    s->r[0]=nz(s,0x1u);
    goto L_0800a774;
L_0800a774: STEP(0x0800a774u); /* ldr r1, [r1] */
    s->r[1]=read_mem(s,(s->r[1]),4);
    goto L_0800a776;
L_0800a776: STEP(0x0800a776u); /* mvns r0, r0 */
    s->r[0]=nz(s,~(s->r[0]));
    goto L_0800a778;
L_0800a778: STEP(0x0800a778u); /* str r0, [r1, #0x10] */
    write_mem(s,(s->r[1] + 0x10u),4,s->r[0]);
    goto L_0800a77a;
L_0800a77a: STEP(0x0800a77au); /* ldr r0, [pc, #0x39c] */
    s->r[0]=read_mem(s,(0x800a77cu + 0x39cu),4);
    goto L_0800a77c;
L_0800a77c: STEP(0x0800a77cu); /* bl #0x8006b2c */
    s->r[14]=0x0800a781u;
    if(!s->call){s->fault=-2;s->fault_address=0x08006b2cu;return -2;}
    s->r[15]=0x08006b2cu;
    temp=(uint32_t)s->call(s->user,0x08006b2cu,s);
    if(temp){s->pc=0x0800a780u;return 1;}
    goto L_0800a780;
L_0800a780: STEP(0x0800a780u); /* movs r4, #1 */
    s->r[4]=nz(s,0x1u);
    goto L_0800a782;
L_0800a782: STEP(0x0800a782u); /* lsls r4, r4, #9 */
    s->r[4]=lsl(s,s->r[4],0x9u);
    goto L_0800a784;
L_0800a784: STEP(0x0800a784u); /* mov r2, r4 */
    s->r[2]=s->r[4];
    goto L_0800a786;
L_0800a786: STEP(0x0800a786u); /* ldr r1, [pc, #0x394] */
    s->r[1]=read_mem(s,(0x800a788u + 0x394u),4);
    goto L_0800a788;
L_0800a788: STEP(0x0800a788u); /* ldr r0, [pc, #0x394] */
    s->r[0]=read_mem(s,(0x800a78cu + 0x394u),4);
    goto L_0800a78a;
L_0800a78a: STEP(0x0800a78au); /* bl #0x8006dca */
    s->r[14]=0x0800a78fu;
    if(!s->call){s->fault=-2;s->fault_address=0x08006dcau;return -2;}
    s->r[15]=0x08006dcau;
    temp=(uint32_t)s->call(s->user,0x08006dcau,s);
    if(temp){s->pc=0x0800a78eu;return 1;}
    goto L_0800a78e;
L_0800a78e: STEP(0x0800a78eu); /* mov r2, r4 */
    s->r[2]=s->r[4];
    goto L_0800a790;
L_0800a790: STEP(0x0800a790u); /* ldr r1, [pc, #0x390] */
    s->r[1]=read_mem(s,(0x800a794u + 0x390u),4);
    goto L_0800a792;
L_0800a792: STEP(0x0800a792u); /* ldr r0, [pc, #0x394] */
    s->r[0]=read_mem(s,(0x800a794u + 0x394u),4);
    goto L_0800a794;
L_0800a794: STEP(0x0800a794u); /* bl #0x8006dca */
    s->r[14]=0x0800a799u;
    if(!s->call){s->fault=-2;s->fault_address=0x08006dcau;return -2;}
    s->r[15]=0x08006dcau;
    temp=(uint32_t)s->call(s->user,0x08006dcau,s);
    if(temp){s->pc=0x0800a798u;return 1;}
    goto L_0800a798;
L_0800a798: STEP(0x0800a798u); /* bl #0x8004920 */
    s->r[14]=0x0800a79du;
    if(!s->call){s->fault=-2;s->fault_address=0x08004920u;return -2;}
    s->r[15]=0x08004920u;
    temp=(uint32_t)s->call(s->user,0x08004920u,s);
    if(temp){s->pc=0x0800a79cu;return 1;}
    goto L_0800a79c;
L_0800a79c: STEP(0x0800a79cu); /* bl #0x8008728 */
    s->r[14]=0x0800a7a1u;
    if(!s->call){s->fault=-2;s->fault_address=0x08008728u;return -2;}
    s->r[15]=0x08008728u;
    temp=(uint32_t)s->call(s->user,0x08008728u,s);
    if(temp){s->pc=0x0800a7a0u;return 1;}
    goto L_0800a7a0;
L_0800a7a0: STEP(0x0800a7a0u); /* bl #0x800c298 */
    s->r[14]=0x0800a7a5u;
    if(!s->call){s->fault=-2;s->fault_address=0x0800c298u;return -2;}
    s->r[15]=0x0800c298u;
    temp=(uint32_t)s->call(s->user,0x0800c298u,s);
    if(temp){s->pc=0x0800a7a4u;return 1;}
    goto L_0800a7a4;
L_0800a7a4: STEP(0x0800a7a4u); /* movs r0, #0x64 */
    s->r[0]=nz(s,0x64u);
    goto L_0800a7a6;
L_0800a7a6: STEP(0x0800a7a6u); /* bl #0x8005a28 */
    s->r[14]=0x0800a7abu;
    if(!s->call){s->fault=-2;s->fault_address=0x08005a28u;return -2;}
    s->r[15]=0x08005a28u;
    temp=(uint32_t)s->call(s->user,0x08005a28u,s);
    if(temp){s->pc=0x0800a7aau;return 1;}
    goto L_0800a7aa;
L_0800a7aa: STEP(0x0800a7aau); /* bl #0x800cda4 */
    s->r[14]=0x0800a7afu;
    if(!s->call){s->fault=-2;s->fault_address=0x0800cda4u;return -2;}
    s->r[15]=0x0800cda4u;
    temp=(uint32_t)s->call(s->user,0x0800cda4u,s);
    if(temp){s->pc=0x0800a7aeu;return 1;}
    goto L_0800a7ae;
L_0800a7ae: STEP(0x0800a7aeu); /* movs r0, #0xd */
    s->r[0]=nz(s,0xdu);
    goto L_0800a7b0;
L_0800a7b0: STEP(0x0800a7b0u); /* bl #0x800cdb8 */
    s->r[14]=0x0800a7b5u;
    if(!s->call){s->fault=-2;s->fault_address=0x0800cdb8u;return -2;}
    s->r[15]=0x0800cdb8u;
    temp=(uint32_t)s->call(s->user,0x0800cdb8u,s);
    if(temp){s->pc=0x0800a7b4u;return 1;}
    goto L_0800a7b4;
L_0800a7b4: STEP(0x0800a7b4u); /* bl #0x8009d84 */
    s->r[14]=0x0800a7b9u;
    if(!s->call){s->fault=-2;s->fault_address=0x08009d84u;return -2;}
    s->r[15]=0x08009d84u;
    temp=(uint32_t)s->call(s->user,0x08009d84u,s);
    if(temp){s->pc=0x0800a7b8u;return 1;}
    goto L_0800a7b8;
L_0800a7b8: STEP(0x0800a7b8u); /* movs r0, #1 */
    s->r[0]=nz(s,0x1u);
    goto L_0800a7ba;
L_0800a7ba: STEP(0x0800a7bau); /* bl #0x800890c */
    s->r[14]=0x0800a7bfu;
    if(!s->call){s->fault=-2;s->fault_address=0x0800890cu;return -2;}
    s->r[15]=0x0800890cu;
    temp=(uint32_t)s->call(s->user,0x0800890cu,s);
    if(temp){s->pc=0x0800a7beu;return 1;}
    goto L_0800a7be;
L_0800a7be: STEP(0x0800a7beu); /* bl #0x80087b8 */
    s->r[14]=0x0800a7c3u;
    if(!s->call){s->fault=-2;s->fault_address=0x080087b8u;return -2;}
    s->r[15]=0x080087b8u;
    temp=(uint32_t)s->call(s->user,0x080087b8u,s);
    if(temp){s->pc=0x0800a7c2u;return 1;}
    goto L_0800a7c2;
L_0800a7c2: STEP(0x0800a7c2u); /* bl #0x800a6cc */
    s->r[14]=0x0800a7c7u;
    if(!s->call){s->fault=-2;s->fault_address=0x0800a6ccu;return -2;}
    s->r[15]=0x0800a6ccu;
    temp=(uint32_t)s->call(s->user,0x0800a6ccu,s);
    if(temp){s->pc=0x0800a7c6u;return 1;}
    goto L_0800a7c6;
L_0800a7c6: STEP(0x0800a7c6u); /* str r0, [sp, #0x1c] */
    write_mem(s,(s->r[13] + 0x1cu),4,s->r[0]);
    goto L_0800a7c8;
L_0800a7c8: STEP(0x0800a7c8u); /* ldr r0, [pc, #0x360] */
    s->r[0]=read_mem(s,(0x800a7ccu + 0x360u),4);
    goto L_0800a7ca;
L_0800a7ca: STEP(0x0800a7cau); /* str r0, [sp, #0x34] */
    write_mem(s,(s->r[13] + 0x34u),4,s->r[0]);
    goto L_0800a7cc;
L_0800a7cc: STEP(0x0800a7ccu); /* ldr r0, [pc, #0x360] */
    s->r[0]=read_mem(s,(0x800a7d0u + 0x360u),4);
    goto L_0800a7ce;
L_0800a7ce: STEP(0x0800a7ceu); /* str r0, [sp, #0x2c] */
    write_mem(s,(s->r[13] + 0x2cu),4,s->r[0]);
    goto L_0800a7d0;
L_0800a7d0: STEP(0x0800a7d0u); /* ldr r0, [pc, #0x360] */
    s->r[0]=read_mem(s,(0x800a7d4u + 0x360u),4);
    goto L_0800a7d2;
L_0800a7d2: STEP(0x0800a7d2u); /* str r0, [sp, #0x30] */
    write_mem(s,(s->r[13] + 0x30u),4,s->r[0]);
    goto L_0800a7d4;

    /* Main loop entry: watchdog, time delta */
L_0800a7d4: STEP(0x0800a7d4u); /* ldr r0, [pc, #0x360] */
    s->r[0]=read_mem(s,(0x800a7d8u + 0x360u),4);
    goto L_0800a7d6;
L_0800a7d6: STEP(0x0800a7d6u); /* bl #0x8006320 */
    s->r[14]=0x0800a7dbu;
    if(!s->call){s->fault=-2;s->fault_address=0x08006320u;return -2;}
    s->r[15]=0x08006320u;
    temp=(uint32_t)s->call(s->user,0x08006320u,s);
    if(temp){s->pc=0x0800a7dau;return 1;}
    goto L_0800a7da;
L_0800a7da: STEP(0x0800a7dau); /* bl #0x800a6cc */
    s->r[14]=0x0800a7dfu;
    if(!s->call){s->fault=-2;s->fault_address=0x0800a6ccu;return -2;}
    s->r[15]=0x0800a6ccu;
    temp=(uint32_t)s->call(s->user,0x0800a6ccu,s);
    if(temp){s->pc=0x0800a7deu;return 1;}
    goto L_0800a7de;
L_0800a7de: STEP(0x0800a7deu); /* ldr r1, [sp, #0x1c] */
    s->r[1]=read_mem(s,(s->r[13] + 0x1cu),4);
    goto L_0800a7e0;
L_0800a7e0: STEP(0x0800a7e0u); /* cmp r0, r1 */
    (void)sub(s,s->r[0],s->r[1]);
    goto L_0800a7e2;
L_0800a7e2: STEP(0x0800a7e2u); /* bhs #0x800a7ec */
    if(C)goto L_0800a7ec;
    goto L_0800a7e4;
L_0800a7e4: STEP(0x0800a7e4u); /* movs r1, #1 */
    s->r[1]=nz(s,0x1u);
    goto L_0800a7e6;
L_0800a7e6: STEP(0x0800a7e6u); /* str r1, [sp, #8] */
    write_mem(s,(s->r[13] + 0x8u),4,s->r[1]);
    goto L_0800a7e8;
L_0800a7e8: STEP(0x0800a7e8u); /* str r0, [sp, #0x1c] */
    write_mem(s,(s->r[13] + 0x1cu),4,s->r[0]);
    goto L_0800a7ea;
L_0800a7ea: STEP(0x0800a7eau); /* b #0x800a7f8 */
    goto L_0800a7f8;
L_0800a7ec: STEP(0x0800a7ecu); /* subs r1, r0, r1 */
    s->r[1]=sub(s,s->r[0],s->r[1]);
    goto L_0800a7ee;
L_0800a7ee: STEP(0x0800a7eeu); /* lsls r1, r1, #0x10 */
    s->r[1]=lsl(s,s->r[1],0x10u);
    goto L_0800a7f0;
L_0800a7f0: STEP(0x0800a7f0u); /* lsrs r1, r1, #0x10 */
    s->r[1]=lsr(s,s->r[1],0x10u);
    goto L_0800a7f2;
L_0800a7f2: STEP(0x0800a7f2u); /* str r1, [sp, #8] */
    write_mem(s,(s->r[13] + 0x8u),4,s->r[1]);
    goto L_0800a7f4;
L_0800a7f4: STEP(0x0800a7f4u); /* str r0, [sp, #0x1c] */
    write_mem(s,(s->r[13] + 0x1cu),4,s->r[0]);
    goto L_0800a7f6;
L_0800a7f6: STEP(0x0800a7f6u); /* beq #0x800a8f4 */
    if(Z)goto L_0800a8f4;
    goto L_0800a7f8;
L_0800a7f8: STEP(0x0800a7f8u); /* movs r4, #0 */
    s->r[4]=nz(s,0x0u);
    goto L_0800a7fa;

    /* Scan 93 software timer slots */
L_0800a7fa: STEP(0x0800a7fau); /* ldr r5, [pc, #0x340] */
    s->r[5]=read_mem(s,(0x800a7fcu + 0x340u),4);
    goto L_0800a7fc;
L_0800a7fc: STEP(0x0800a7fcu); /* lsls r6, r4, #1 */
    s->r[6]=lsl(s,s->r[4],0x1u);
    goto L_0800a7fe;
L_0800a7fe: STEP(0x0800a7feu); /* ldrh r0, [r5, r6] */
    s->r[0]=read_mem(s,(s->r[5] + s->r[6]),2);
    goto L_0800a800;
L_0800a800: STEP(0x0800a800u); /* cmp r0, #0 */
    (void)sub(s,s->r[0],0x0u);
    goto L_0800a802;
L_0800a802: STEP(0x0800a802u); /* beq #0x800a848 */
    if(Z)goto L_0800a848;
    goto L_0800a804;
L_0800a804: STEP(0x0800a804u); /* ldr r1, [sp, #8] */
    s->r[1]=read_mem(s,(s->r[13] + 0x8u),4);
    goto L_0800a806;
L_0800a806: STEP(0x0800a806u); /* cmp r0, r1 */
    (void)sub(s,s->r[0],s->r[1]);
    goto L_0800a808;
L_0800a808: STEP(0x0800a808u); /* bls #0x800a884 */
    if(!C||Z)goto L_0800a884;
    goto L_0800a80a;
L_0800a80a: STEP(0x0800a80au); /* subs r0, r0, r1 */
    s->r[0]=sub(s,s->r[0],s->r[1]);
    goto L_0800a80c;
L_0800a80c: STEP(0x0800a80cu); /* mov r1, r4 */
    s->r[1]=s->r[4];
    goto L_0800a80e;
L_0800a80e: STEP(0x0800a80eu); /* uxth r0, r0 */
    s->r[0]=(uint16_t)(s->r[0]);
    goto L_0800a810;
L_0800a810: STEP(0x0800a810u); /* subs r1, #0x21 */
    s->r[1]=sub(s,s->r[1],0x21u);
    goto L_0800a812;
L_0800a812: STEP(0x0800a812u); /* strh r0, [r5, r6] */
    write_mem(s,(s->r[5] + s->r[6]),2,s->r[0]);
    goto L_0800a814;
L_0800a814: STEP(0x0800a814u); /* cmp r1, #9 */
    (void)sub(s,s->r[1],0x9u);
    goto L_0800a816;
L_0800a816: STEP(0x0800a816u); /* bhi #0x800a84a */
    if(C&&!Z)goto L_0800a84a;
    goto L_0800a818;
L_0800a818: STEP(0x0800a818u); /* uxth r6, r1 */
    s->r[6]=(uint16_t)(s->r[1]);
    goto L_0800a81a;
L_0800a81a: STEP(0x0800a81au); /* movs r1, #0xa */
    s->r[1]=nz(s,0xau);
    goto L_0800a81c;
L_0800a81c: STEP(0x0800a81cu); /* bl #0x80040e8 */
    s->r[14]=0x0800a821u;
    if(!s->call){s->fault=-2;s->fault_address=0x080040e8u;return -2;}
    s->r[15]=0x080040e8u;
    temp=(uint32_t)s->call(s->user,0x080040e8u,s);
    if(temp){s->pc=0x0800a820u;return 1;}
    goto L_0800a820;
L_0800a820: STEP(0x0800a820u); /* cmp r1, #0 */
    (void)sub(s,s->r[1],0x0u);
    goto L_0800a822;
L_0800a822: STEP(0x0800a822u); /* bne #0x800a848 */
    if(!Z)goto L_0800a848;
    goto L_0800a824;
L_0800a824: STEP(0x0800a824u); /* lsls r0, r6, #1 */
    s->r[0]=lsl(s,s->r[6],0x1u);
    goto L_0800a826;
L_0800a826: STEP(0x0800a826u); /* adds r0, r0, r5 */
    s->r[0]=add(s,s->r[0],s->r[5]);
    goto L_0800a828;
L_0800a828: STEP(0x0800a828u); /* movs r1, #0x1e */
    s->r[1]=nz(s,0x1eu);
    goto L_0800a82a;
L_0800a82a: STEP(0x0800a82au); /* adds r0, #0x40 */
    s->r[0]=add(s,s->r[0],0x40u);
    goto L_0800a82c;
L_0800a82c: STEP(0x0800a82cu); /* strh r1, [r0, #0x1a] */
    write_mem(s,(s->r[0] + 0x1au),2,s->r[1]);
    goto L_0800a82e;
L_0800a82e: STEP(0x0800a82eu); /* mov r0, r6 */
    s->r[0]=s->r[6];
    goto L_0800a830;
L_0800a830: STEP(0x0800a830u); /* movs r1, #0x34 */
    s->r[1]=nz(s,0x34u);
    goto L_0800a832;
L_0800a832: STEP(0x0800a832u); /* muls r0, r1, r0 */
    s->r[0]=nz(s,(s->r[1])*(s->r[0]));
    goto L_0800a834;
L_0800a834: STEP(0x0800a834u); /* ldr r1, [pc, #0x308] */
    s->r[1]=read_mem(s,(0x800a838u + 0x308u),4);
    goto L_0800a836;
L_0800a836: STEP(0x0800a836u); /* movs r2, #0 */
    s->r[2]=nz(s,0x0u);
    goto L_0800a838;
L_0800a838: STEP(0x0800a838u); /* adds r0, r0, r1 */
    s->r[0]=add(s,s->r[0],s->r[1]);
    goto L_0800a83a;
L_0800a83a: STEP(0x0800a83au); /* strh r2, [r0, #4] */
    write_mem(s,(s->r[0] + 0x4u),2,s->r[2]);
    goto L_0800a83c;
L_0800a83c: STEP(0x0800a83cu); /* movs r1, #2 */
    s->r[1]=nz(s,0x2u);
    goto L_0800a83e;
L_0800a83e: STEP(0x0800a83eu); /* strb r1, [r0, #0x16] */
    write_mem(s,(s->r[0] + 0x16u),1,s->r[1]);
    goto L_0800a840;
L_0800a840: STEP(0x0800a840u); /* uxtb r0, r6 */
    s->r[0]=(uint8_t)(s->r[6]);
    goto L_0800a842;
L_0800a842: STEP(0x0800a842u); /* movs r1, #1 */
    s->r[1]=nz(s,0x1u);
    goto L_0800a844;
L_0800a844: STEP(0x0800a844u); /* bl #0x800c85c */
    s->r[14]=0x0800a849u;
    if(!s->call){s->fault=-2;s->fault_address=0x0800c85cu;return -2;}
    s->r[15]=0x0800c85cu;
    temp=(uint32_t)s->call(s->user,0x0800c85cu,s);
    if(temp){s->pc=0x0800a848u;return 1;}
    goto L_0800a848;
L_0800a848: STEP(0x0800a848u); /* b #0x800ac5a */
    goto L_0800ac5a;
L_0800a84a: STEP(0x0800a84au); /* mov r0, r4 */
    s->r[0]=s->r[4];
    goto L_0800a84c;
L_0800a84c: STEP(0x0800a84cu); /* subs r0, #0x2d */
    s->r[0]=sub(s,s->r[0],0x2du);
    goto L_0800a84e;
L_0800a84e: STEP(0x0800a84eu); /* cmp r0, #9 */
    (void)sub(s,s->r[0],0x9u);
    goto L_0800a850;
L_0800a850: STEP(0x0800a850u); /* bhi #0x800a86c */
    if(C&&!Z)goto L_0800a86c;
    goto L_0800a852;
L_0800a852: STEP(0x0800a852u); /* uxtb r0, r0 */
    s->r[0]=(uint8_t)(s->r[0]);
    goto L_0800a854;
L_0800a854: STEP(0x0800a854u); /* bl #0x800a018 */
    s->r[14]=0x0800a859u;
    if(!s->call){s->fault=-2;s->fault_address=0x0800a018u;return -2;}
    s->r[15]=0x0800a018u;
    temp=(uint32_t)s->call(s->user,0x0800a018u,s);
    if(temp){s->pc=0x0800a858u;return 1;}
    goto L_0800a858;
L_0800a858: STEP(0x0800a858u); /* cmp r0, #1 */
    (void)sub(s,s->r[0],0x1u);
    goto L_0800a85a;
L_0800a85a: STEP(0x0800a85au); /* bne #0x800a848 */
    if(!Z)goto L_0800a848;
    goto L_0800a85c;
L_0800a85c: STEP(0x0800a85cu); /* ldrh r0, [r5, r6] */
    s->r[0]=read_mem(s,(s->r[5] + s->r[6]),2);
    goto L_0800a85e;
L_0800a85e: STEP(0x0800a85eu); /* movs r1, #5 */
    s->r[1]=nz(s,0x5u);
    goto L_0800a860;
L_0800a860: STEP(0x0800a860u); /* bl #0x80040e8 */
    s->r[14]=0x0800a865u;
    if(!s->call){s->fault=-2;s->fault_address=0x080040e8u;return -2;}
    s->r[15]=0x080040e8u;
    temp=(uint32_t)s->call(s->user,0x080040e8u,s);
    if(temp){s->pc=0x0800a864u;return 1;}
    goto L_0800a864;
L_0800a864: STEP(0x0800a864u); /* cmp r1, #0 */
    (void)sub(s,s->r[1],0x0u);
    goto L_0800a866;
L_0800a866: STEP(0x0800a866u); /* bne #0x800a848 */
    if(!Z)goto L_0800a848;
    goto L_0800a868;
L_0800a868: STEP(0x0800a868u); /* movs r0, #0x33 */
    s->r[0]=nz(s,0x33u);
    goto L_0800a86a;
L_0800a86a: STEP(0x0800a86au); /* b #0x800a87e */
    goto L_0800a87e;
L_0800a86c: STEP(0x0800a86cu); /* cmp r4, #4 */
    (void)sub(s,s->r[4],0x4u);
    goto L_0800a86e;
L_0800a86e: STEP(0x0800a86eu); /* bne #0x800a848 */
    if(!Z)goto L_0800a848;
    goto L_0800a870;
L_0800a870: STEP(0x0800a870u); /* ldrh r0, [r5, #8] */
    s->r[0]=read_mem(s,(s->r[5] + 0x8u),2);
    goto L_0800a872;
L_0800a872: STEP(0x0800a872u); /* movs r1, #5 */
    s->r[1]=nz(s,0x5u);
    goto L_0800a874;
L_0800a874: STEP(0x0800a874u); /* bl #0x80040e8 */
    s->r[14]=0x0800a879u;
    if(!s->call){s->fault=-2;s->fault_address=0x080040e8u;return -2;}
    s->r[15]=0x080040e8u;
    temp=(uint32_t)s->call(s->user,0x080040e8u,s);
    if(temp){s->pc=0x0800a878u;return 1;}
    goto L_0800a878;
L_0800a878: STEP(0x0800a878u); /* cmp r1, #0 */
    (void)sub(s,s->r[1],0x0u);
    goto L_0800a87a;
L_0800a87a: STEP(0x0800a87au); /* bne #0x800a848 */
    if(!Z)goto L_0800a848;
    goto L_0800a87c;
L_0800a87c: STEP(0x0800a87cu); /* movs r0, #0x34 */
    s->r[0]=nz(s,0x34u);
    goto L_0800a87e;
L_0800a87e: STEP(0x0800a87eu); /* bl #0x800cdb8 */
    s->r[14]=0x0800a883u;
    if(!s->call){s->fault=-2;s->fault_address=0x0800cdb8u;return -2;}
    s->r[15]=0x0800cdb8u;
    temp=(uint32_t)s->call(s->user,0x0800cdb8u,s);
    if(temp){s->pc=0x0800a882u;return 1;}
    goto L_0800a882;
L_0800a882: STEP(0x0800a882u); /* b #0x800ac5a */
    goto L_0800ac5a;
L_0800a884: STEP(0x0800a884u); /* movs r0, #0 */
    s->r[0]=nz(s,0x0u);
    goto L_0800a886;
L_0800a886: STEP(0x0800a886u); /* strh r0, [r5, r6] */
    write_mem(s,(s->r[5] + s->r[6]),2,s->r[0]);
    goto L_0800a888;

    /* Keil switch8 timer expiry dispatch */
L_0800a888: STEP(0x0800a888u); /* movs r3, r4 */
    s->r[3]=nz(s,s->r[4]);
    goto L_0800a88a;
L_0800a88a: STEP(0x0800a88au); /* bl #0x80095d2 */
    s->r[14]=0x0800a88fu;
    /* Inline exact switch8 helper; preserve its stack writes and NZCV. */
    write_mem(s,s->r[13]-8u,4,s->r[4]);write_mem(s,s->r[13]-4u,4,s->r[5]);
    (void)sub(s,s->r[3],81u);temp=s->r[3]<81u?s->r[3]:81u;
    s->r[3]=read_mem(s,0x0800a88fu+temp,1);
    s->r[3]=lsl(s,s->r[3],1);
    s->r[3]=add(s,0x0800a88fu,s->r[3]);
    s->pc=s->r[3]&~1u;goto dispatch;
L_0800a8e2: STEP(0x0800a8e2u); /* ldr r6, [pc, #0x24c] */
    s->r[6]=read_mem(s,(0x800a8e4u + 0x24cu),4);
    goto L_0800a8e4;
L_0800a8e4: STEP(0x0800a8e4u); /* movs r0, #1 */
    s->r[0]=nz(s,0x1u);
    goto L_0800a8e6;
L_0800a8e6: STEP(0x0800a8e6u); /* subs r6, #0x60 */
    s->r[6]=sub(s,s->r[6],0x60u);
    goto L_0800a8e8;
L_0800a8e8: STEP(0x0800a8e8u); /* strb r0, [r6] */
    write_mem(s,(s->r[6]),1,s->r[0]);
    goto L_0800a8ea;
L_0800a8ea: STEP(0x0800a8eau); /* bl #0x800a644 */
    s->r[14]=0x0800a8efu;
    if(!s->call){s->fault=-2;s->fault_address=0x0800a644u;return -2;}
    s->r[15]=0x0800a644u;
    temp=(uint32_t)s->call(s->user,0x0800a644u,s);
    if(temp){s->pc=0x0800a8eeu;return 1;}
    goto L_0800a8ee;
L_0800a8ee: STEP(0x0800a8eeu); /* mov r0, r6 */
    s->r[0]=s->r[6];
    goto L_0800a8f0;
L_0800a8f0: STEP(0x0800a8f0u); /* adds r0, #0x40 */
    s->r[0]=add(s,s->r[0],0x40u);
    goto L_0800a8f2;
L_0800a8f2: STEP(0x0800a8f2u); /* b #0x800a8f6 */
    goto L_0800a8f6;
L_0800a8f4: STEP(0x0800a8f4u); /* b #0x800af3a */
    goto L_0800af3a;
L_0800a8f6: STEP(0x0800a8f6u); /* ldrh r0, [r0, #0x28] */
    s->r[0]=read_mem(s,(s->r[0] + 0x28u),2);
    goto L_0800a8f8;
L_0800a8f8: STEP(0x0800a8f8u); /* cmp r0, #0 */
    (void)sub(s,s->r[0],0x0u);
    goto L_0800a8fa;
L_0800a8fa: STEP(0x0800a8fau); /* beq #0x800a902 */
    if(Z)goto L_0800a902;
    goto L_0800a8fc;
L_0800a8fc: STEP(0x0800a8fcu); /* movs r0, #1 */
    s->r[0]=nz(s,0x1u);
    goto L_0800a8fe;
L_0800a8fe: STEP(0x0800a8feu); /* bl #0x800cc64 */
    s->r[14]=0x0800a903u;
    if(!s->call){s->fault=-2;s->fault_address=0x0800cc64u;return -2;}
    s->r[15]=0x0800cc64u;
    temp=(uint32_t)s->call(s->user,0x0800cc64u,s);
    if(temp){s->pc=0x0800a902u;return 1;}
    goto L_0800a902;
L_0800a902: STEP(0x0800a902u); /* movs r0, #0x26 */
    s->r[0]=nz(s,0x26u);
    goto L_0800a904;
L_0800a904: STEP(0x0800a904u); /* bl #0x800cdb8 */
    s->r[14]=0x0800a909u;
    if(!s->call){s->fault=-2;s->fault_address=0x0800cdb8u;return -2;}
    s->r[15]=0x0800cdb8u;
    temp=(uint32_t)s->call(s->user,0x0800cdb8u,s);
    if(temp){s->pc=0x0800a908u;return 1;}
    goto L_0800a908;
L_0800a908: STEP(0x0800a908u); /* movs r0, #0 */
    s->r[0]=nz(s,0x0u);
    goto L_0800a90a;
L_0800a90a: STEP(0x0800a90au); /* strh r0, [r5] */
    write_mem(s,(s->r[5]),2,s->r[0]);
    goto L_0800a90c;
L_0800a90c: STEP(0x0800a90cu); /* ldrb r0, [r6, #1] */
    s->r[0]=read_mem(s,(s->r[6] + 0x1u),1);
    goto L_0800a90e;
L_0800a90e: STEP(0x0800a90eu); /* bl #0x800a488 */
    s->r[14]=0x0800a913u;
    if(!s->call){s->fault=-2;s->fault_address=0x0800a488u;return -2;}
    s->r[15]=0x0800a488u;
    temp=(uint32_t)s->call(s->user,0x0800a488u,s);
    if(temp){s->pc=0x0800a912u;return 1;}
    goto L_0800a912;
L_0800a912: STEP(0x0800a912u); /* b #0x800ac5a */
    goto L_0800ac5a;
L_0800a914: STEP(0x0800a914u); /* ldr r6, [pc, #0x228] */
    s->r[6]=read_mem(s,(0x800a918u + 0x228u),4);
    goto L_0800a916;
L_0800a916: STEP(0x0800a916u); /* movs r5, #0 */
    s->r[5]=nz(s,0x0u);
    goto L_0800a918;
L_0800a918: STEP(0x0800a918u); /* movs r0, #0x34 */
    s->r[0]=nz(s,0x34u);
    goto L_0800a91a;
L_0800a91a: STEP(0x0800a91au); /* muls r0, r5, r0 */
    s->r[0]=nz(s,(s->r[5])*(s->r[0]));
    goto L_0800a91c;
L_0800a91c: STEP(0x0800a91cu); /* adds r0, r0, r6 */
    s->r[0]=add(s,s->r[0],s->r[6]);
    goto L_0800a91e;
L_0800a91e: STEP(0x0800a91eu); /* ldrb r1, [r0, #0x16] */
    s->r[1]=read_mem(s,(s->r[0] + 0x16u),1);
    goto L_0800a920;
L_0800a920: STEP(0x0800a920u); /* cmp r1, #1 */
    (void)sub(s,s->r[1],0x1u);
    goto L_0800a922;
L_0800a922: STEP(0x0800a922u); /* bne #0x800a930 */
    if(!Z)goto L_0800a930;
    goto L_0800a924;
L_0800a924: STEP(0x0800a924u); /* ldrb r0, [r0, #0x17] */
    s->r[0]=read_mem(s,(s->r[0] + 0x17u),1);
    goto L_0800a926;
L_0800a926: STEP(0x0800a926u); /* cmp r0, #1 */
    (void)sub(s,s->r[0],0x1u);
    goto L_0800a928;
L_0800a928: STEP(0x0800a928u); /* bne #0x800a930 */
    if(!Z)goto L_0800a930;
    goto L_0800a92a;
L_0800a92a: STEP(0x0800a92au); /* uxtb r0, r5 */
    s->r[0]=(uint8_t)(s->r[5]);
    goto L_0800a92c;
L_0800a92c: STEP(0x0800a92cu); /* bl #0x8004b10 */
    s->r[14]=0x0800a931u;
    if(!s->call){s->fault=-2;s->fault_address=0x08004b10u;return -2;}
    s->r[15]=0x08004b10u;
    temp=(uint32_t)s->call(s->user,0x08004b10u,s);
    if(temp){s->pc=0x0800a930u;return 1;}
    goto L_0800a930;
L_0800a930: STEP(0x0800a930u); /* adds r5, r5, #1 */
    s->r[5]=add(s,s->r[5],0x1u);
    goto L_0800a932;
L_0800a932: STEP(0x0800a932u); /* uxth r5, r5 */
    s->r[5]=(uint16_t)(s->r[5]);
    goto L_0800a934;
L_0800a934: STEP(0x0800a934u); /* cmp r5, #0xc */
    (void)sub(s,s->r[5],0xcu);
    goto L_0800a936;
L_0800a936: STEP(0x0800a936u); /* blo #0x800a918 */
    if(!C)goto L_0800a918;
    goto L_0800a938;
L_0800a938: STEP(0x0800a938u); /* ldr r5, [pc, #0x1f4] */
    s->r[5]=read_mem(s,(0x800a93cu + 0x1f4u),4);
    goto L_0800a93a;
L_0800a93a: STEP(0x0800a93au); /* subs r5, #0x60 */
    s->r[5]=sub(s,s->r[5],0x60u);
    goto L_0800a93c;
L_0800a93c: STEP(0x0800a93cu); /* ldrb r0, [r5] */
    s->r[0]=read_mem(s,(s->r[5]),1);
    goto L_0800a93e;
L_0800a93e: STEP(0x0800a93eu); /* cmp r0, #3 */
    (void)sub(s,s->r[0],0x3u);
    goto L_0800a940;
L_0800a940: STEP(0x0800a940u); /* beq #0x800a950 */
    if(Z)goto L_0800a950;
    goto L_0800a942;
L_0800a942: STEP(0x0800a942u); /* cmp r0, #4 */
    (void)sub(s,s->r[0],0x4u);
    goto L_0800a944;
L_0800a944: STEP(0x0800a944u); /* beq #0x800a956 */
    if(Z)goto L_0800a956;
    goto L_0800a946;
L_0800a946: STEP(0x0800a946u); /* ldr r0, [sp, #0x2c] */
    s->r[0]=read_mem(s,(s->r[13] + 0x2cu),4);
    goto L_0800a948;
L_0800a948: STEP(0x0800a948u); /* ldrb r0, [r0, #0xc] */
    s->r[0]=read_mem(s,(s->r[0] + 0xcu),1);
    goto L_0800a94a;
L_0800a94a: STEP(0x0800a94au); /* cmp r0, #4 */
    (void)sub(s,s->r[0],0x4u);
    goto L_0800a94c;
L_0800a94c: STEP(0x0800a94cu); /* beq #0x800a956 */
    if(Z)goto L_0800a956;
    goto L_0800a94e;
L_0800a94e: STEP(0x0800a94eu); /* b #0x800a95a */
    goto L_0800a95a;
L_0800a950: STEP(0x0800a950u); /* ldrh r0, [r5, #0x30] */
    s->r[0]=read_mem(s,(s->r[5] + 0x30u),2);
    goto L_0800a952;
L_0800a952: STEP(0x0800a952u); /* cmp r0, #0 */
    (void)sub(s,s->r[0],0x0u);
    goto L_0800a954;
L_0800a954: STEP(0x0800a954u); /* bne #0x800a946 */
    if(!Z)goto L_0800a946;
    goto L_0800a956;
L_0800a956: STEP(0x0800a956u); /* bl #0x800a65c */
    s->r[14]=0x0800a95bu;
    if(!s->call){s->fault=-2;s->fault_address=0x0800a65cu;return -2;}
    s->r[15]=0x0800a65cu;
    temp=(uint32_t)s->call(s->user,0x0800a65cu,s);
    if(temp){s->pc=0x0800a95au;return 1;}
    goto L_0800a95a;
L_0800a95a: STEP(0x0800a95au); /* ldr r1, [pc, #0x1e8] */
    s->r[1]=read_mem(s,(0x800a95cu + 0x1e8u),4);
    goto L_0800a95c;
L_0800a95c: STEP(0x0800a95cu); /* movs r0, #0 */
    s->r[0]=nz(s,0x0u);
    goto L_0800a95e;
L_0800a95e: STEP(0x0800a95eu); /* strb r0, [r1, #1] */
    write_mem(s,(s->r[1] + 0x1u),1,s->r[0]);
    goto L_0800a960;
L_0800a960: STEP(0x0800a960u); /* movs r0, #1 */
    s->r[0]=nz(s,0x1u);
    goto L_0800a962;
L_0800a962: STEP(0x0800a962u); /* strb r0, [r5] */
    write_mem(s,(s->r[5]),1,s->r[0]);
    goto L_0800a964;
L_0800a964: STEP(0x0800a964u); /* b #0x800ac5a */
    goto L_0800ac5a;
L_0800a966: STEP(0x0800a966u); /* bl #0x800a644 */
    s->r[14]=0x0800a96bu;
    if(!s->call){s->fault=-2;s->fault_address=0x0800a644u;return -2;}
    s->r[15]=0x0800a644u;
    temp=(uint32_t)s->call(s->user,0x0800a644u,s);
    if(temp){s->pc=0x0800a96au;return 1;}
    goto L_0800a96a;
L_0800a96a: STEP(0x0800a96au); /* b #0x800ac5a */
    goto L_0800ac5a;
L_0800a96c: STEP(0x0800a96cu); /* ldr r1, [pc, #0x1c0] */
    s->r[1]=read_mem(s,(0x800a970u + 0x1c0u),4);
    goto L_0800a96e;
L_0800a96e: STEP(0x0800a96eu); /* movs r0, #0 */
    s->r[0]=nz(s,0x0u);
    goto L_0800a970;
L_0800a970: STEP(0x0800a970u); /* subs r1, #0x60 */
    s->r[1]=sub(s,s->r[1],0x60u);
    goto L_0800a972;
L_0800a972: STEP(0x0800a972u); /* strh r0, [r1, #0x2e] */
    write_mem(s,(s->r[1] + 0x2eu),2,s->r[0]);
    goto L_0800a974;
L_0800a974: STEP(0x0800a974u); /* strh r0, [r1, #0x32] */
    write_mem(s,(s->r[1] + 0x32u),2,s->r[0]);
    goto L_0800a976;
L_0800a976: STEP(0x0800a976u); /* strh r0, [r1, #0x30] */
    write_mem(s,(s->r[1] + 0x30u),2,s->r[0]);
    goto L_0800a978;
L_0800a978: STEP(0x0800a978u); /* str r0, [r1, #0x48] */
    write_mem(s,(s->r[1] + 0x48u),4,s->r[0]);
    goto L_0800a97a;
L_0800a97a: STEP(0x0800a97au); /* strh r0, [r1, #0x34] */
    write_mem(s,(s->r[1] + 0x34u),2,s->r[0]);
    goto L_0800a97c;
L_0800a97c: STEP(0x0800a97cu); /* ldr r1, [sp, #0x2c] */
    s->r[1]=read_mem(s,(s->r[13] + 0x2cu),4);
    goto L_0800a97e;
L_0800a97e: STEP(0x0800a97eu); /* strb r0, [r1, #0xc] */
    write_mem(s,(s->r[1] + 0xcu),1,s->r[0]);
    goto L_0800a980;
L_0800a980: STEP(0x0800a980u); /* b #0x800ac5a */
    goto L_0800ac5a;
L_0800a982: STEP(0x0800a982u); /* ldr r0, [pc, #0x1ac] */
    s->r[0]=read_mem(s,(0x800a984u + 0x1acu),4);
    goto L_0800a984;
L_0800a984: STEP(0x0800a984u); /* subs r0, #0x60 */
    s->r[0]=sub(s,s->r[0],0x60u);
    goto L_0800a986;
L_0800a986: STEP(0x0800a986u); /* ldrh r0, [r0, #0x24] */
    s->r[0]=read_mem(s,(s->r[0] + 0x24u),2);
    goto L_0800a988;
L_0800a988: STEP(0x0800a988u); /* cmp r0, #3 */
    (void)sub(s,s->r[0],0x3u);
    goto L_0800a98a;
L_0800a98a: STEP(0x0800a98au); /* bne #0x800a912 */
    if(!Z)goto L_0800a912;
    goto L_0800a98c;
L_0800a98c: STEP(0x0800a98cu); /* ldr r6, [pc, #0x1b8] */
    s->r[6]=read_mem(s,(0x800a990u + 0x1b8u),4);
    goto L_0800a98e;
L_0800a98e: STEP(0x0800a98eu); /* ldrb r0, [r6] */
    s->r[0]=read_mem(s,(s->r[6]),1);
    goto L_0800a990;
L_0800a990: STEP(0x0800a990u); /* cmp r0, #0 */
    (void)sub(s,s->r[0],0x0u);
    goto L_0800a992;
L_0800a992: STEP(0x0800a992u); /* beq #0x800a912 */
    if(Z)goto L_0800a912;
    goto L_0800a994;
L_0800a994: STEP(0x0800a994u); /* subs r0, r0, #1 */
    s->r[0]=sub(s,s->r[0],0x1u);
    goto L_0800a996;
L_0800a996: STEP(0x0800a996u); /* strb r0, [r6] */
    write_mem(s,(s->r[6]),1,s->r[0]);
    goto L_0800a998;
L_0800a998: STEP(0x0800a998u); /* ldr r0, [pc, #0x1b0] */
    s->r[0]=read_mem(s,(0x800a99cu + 0x1b0u),4);
    goto L_0800a99a;
L_0800a99a: STEP(0x0800a99au); /* ldrb r0, [r0] */
    s->r[0]=read_mem(s,(s->r[0]),1);
    goto L_0800a99c;
L_0800a99c: STEP(0x0800a99cu); /* cmp r0, #0x2c */
    (void)sub(s,s->r[0],0x2cu);
    goto L_0800a99e;
L_0800a99e: STEP(0x0800a99eu); /* beq #0x800a9a6 */
    if(Z)goto L_0800a9a6;
    goto L_0800a9a0;
L_0800a9a0: STEP(0x0800a9a0u); /* cmp r0, #0x2d */
    (void)sub(s,s->r[0],0x2du);
    goto L_0800a9a2;
L_0800a9a2: STEP(0x0800a9a2u); /* beq #0x800a9ba */
    if(Z)goto L_0800a9ba;
    goto L_0800a9a4;
L_0800a9a4: STEP(0x0800a9a4u); /* b #0x800a9ce */
    goto L_0800a9ce;
L_0800a9a6: STEP(0x0800a9a6u); /* ldr r0, [pc, #0x1a8] */
    s->r[0]=read_mem(s,(0x800a9a8u + 0x1a8u),4);
    goto L_0800a9a8;
L_0800a9a8: STEP(0x0800a9a8u); /* movs r3, #0 */
    s->r[3]=nz(s,0x0u);
    goto L_0800a9aa;
L_0800a9aa: STEP(0x0800a9aau); /* ldr r0, [r0] */
    s->r[0]=read_mem(s,(s->r[0]),4);
    goto L_0800a9ac;
L_0800a9ac: STEP(0x0800a9acu); /* str r0, [sp] */
    write_mem(s,(s->r[13]),4,s->r[0]);
    goto L_0800a9ae;
L_0800a9ae: STEP(0x0800a9aeu); /* mov r2, r3 */
    s->r[2]=s->r[3];
    goto L_0800a9b0;
L_0800a9b0: STEP(0x0800a9b0u); /* mov r1, r3 */
    s->r[1]=s->r[3];
    goto L_0800a9b2;
L_0800a9b2: STEP(0x0800a9b2u); /* mov r0, r3 */
    s->r[0]=s->r[3];
    goto L_0800a9b4;
L_0800a9b4: STEP(0x0800a9b4u); /* bl #0x800bb7c */
    s->r[14]=0x0800a9b9u;
    if(!s->call){s->fault=-2;s->fault_address=0x0800bb7cu;return -2;}
    s->r[15]=0x0800bb7cu;
    temp=(uint32_t)s->call(s->user,0x0800bb7cu,s);
    if(temp){s->pc=0x0800a9b8u;return 1;}
    goto L_0800a9b8;
L_0800a9b8: STEP(0x0800a9b8u); /* b #0x800a9ce */
    goto L_0800a9ce;
L_0800a9ba: STEP(0x0800a9bau); /* ldr r0, [pc, #0x194] */
    s->r[0]=read_mem(s,(0x800a9bcu + 0x194u),4);
    goto L_0800a9bc;
L_0800a9bc: STEP(0x0800a9bcu); /* ldr r1, [r0] */
    s->r[1]=read_mem(s,(s->r[0]),4);
    goto L_0800a9be;
L_0800a9be: STEP(0x0800a9beu); /* movs r0, #0 */
    s->r[0]=nz(s,0x0u);
    goto L_0800a9c0;
L_0800a9c0: STEP(0x0800a9c0u); /* str r1, [sp, #4] */
    write_mem(s,(s->r[13] + 0x4u),4,s->r[1]);
    goto L_0800a9c2;
L_0800a9c2: STEP(0x0800a9c2u); /* mov r3, r0 */
    s->r[3]=s->r[0];
    goto L_0800a9c4;
L_0800a9c4: STEP(0x0800a9c4u); /* mov r2, r0 */
    s->r[2]=s->r[0];
    goto L_0800a9c6;
L_0800a9c6: STEP(0x0800a9c6u); /* str r0, [sp] */
    write_mem(s,(s->r[13]),4,s->r[0]);
    goto L_0800a9c8;
L_0800a9c8: STEP(0x0800a9c8u); /* mov r1, r0 */
    s->r[1]=s->r[0];
    goto L_0800a9ca;
L_0800a9ca: STEP(0x0800a9cau); /* bl #0x800bab4 */
    s->r[14]=0x0800a9cfu;
    if(!s->call){s->fault=-2;s->fault_address=0x0800bab4u;return -2;}
    s->r[15]=0x0800bab4u;
    temp=(uint32_t)s->call(s->user,0x0800bab4u,s);
    if(temp){s->pc=0x0800a9ceu;return 1;}
    goto L_0800a9ce;
L_0800a9ce: STEP(0x0800a9ceu); /* ldrb r0, [r6] */
    s->r[0]=read_mem(s,(s->r[6]),1);
    goto L_0800a9d0;
L_0800a9d0: STEP(0x0800a9d0u); /* cmp r0, #0 */
    (void)sub(s,s->r[0],0x0u);
    goto L_0800a9d2;
L_0800a9d2: STEP(0x0800a9d2u); /* beq #0x800a912 */
    if(Z)goto L_0800a912;
    goto L_0800a9d4;
L_0800a9d4: STEP(0x0800a9d4u); /* movs r0, #0x14 */
    s->r[0]=nz(s,0x14u);
    goto L_0800a9d6;
L_0800a9d6: STEP(0x0800a9d6u); /* strh r0, [r5, #0xa] */
    write_mem(s,(s->r[5] + 0xau),2,s->r[0]);
    goto L_0800a9d8;
L_0800a9d8: STEP(0x0800a9d8u); /* b #0x800ac5a */
    goto L_0800ac5a;
L_0800a9da: STEP(0x0800a9dau); /* ldr r0, [pc, #0x154] */
    s->r[0]=read_mem(s,(0x800a9dcu + 0x154u),4);
    goto L_0800a9dc;
L_0800a9dc: STEP(0x0800a9dcu); /* subs r0, #0x60 */
    s->r[0]=sub(s,s->r[0],0x60u);
    goto L_0800a9de;
L_0800a9de: STEP(0x0800a9deu); /* ldrb r1, [r0] */
    s->r[1]=read_mem(s,(s->r[0]),1);
    goto L_0800a9e0;
L_0800a9e0: STEP(0x0800a9e0u); /* cmp r1, #5 */
    (void)sub(s,s->r[1],0x5u);
    goto L_0800a9e2;
L_0800a9e2: STEP(0x0800a9e2u); /* bne #0x800a912 */
    if(!Z)goto L_0800a912;
    goto L_0800a9e4;
L_0800a9e4: STEP(0x0800a9e4u); /* movs r1, #0 */
    s->r[1]=nz(s,0x0u);
    goto L_0800a9e6;
L_0800a9e6: STEP(0x0800a9e6u); /* str r1, [r0, #0x48] */
    write_mem(s,(s->r[0] + 0x48u),4,s->r[1]);
    goto L_0800a9e8;
L_0800a9e8: STEP(0x0800a9e8u); /* ldr r2, [sp, #0x2c] */
    s->r[2]=read_mem(s,(s->r[13] + 0x2cu),4);
    goto L_0800a9ea;
L_0800a9ea: STEP(0x0800a9eau); /* strb r1, [r2, #0xc] */
    write_mem(s,(s->r[2] + 0xcu),1,s->r[1]);
    goto L_0800a9ec;
L_0800a9ec: STEP(0x0800a9ecu); /* movs r1, #1 */
    s->r[1]=nz(s,0x1u);
    goto L_0800a9ee;
L_0800a9ee: STEP(0x0800a9eeu); /* strb r1, [r0] */
    write_mem(s,(s->r[0]),1,s->r[1]);
    goto L_0800a9f0;
L_0800a9f0: STEP(0x0800a9f0u); /* b #0x800a966 */
    goto L_0800a966;
L_0800a9f2: STEP(0x0800a9f2u); /* ldr r0, [pc, #0x13c] */
    s->r[0]=read_mem(s,(0x800a9f4u + 0x13cu),4);
    goto L_0800a9f4;
L_0800a9f4: STEP(0x0800a9f4u); /* subs r0, #0x60 */
    s->r[0]=sub(s,s->r[0],0x60u);
    goto L_0800a9f6;
L_0800a9f6: STEP(0x0800a9f6u); /* ldrh r0, [r0, #0x24] */
    s->r[0]=read_mem(s,(s->r[0] + 0x24u),2);
    goto L_0800a9f8;
L_0800a9f8: STEP(0x0800a9f8u); /* cmp r0, #3 */
    (void)sub(s,s->r[0],0x3u);
    goto L_0800a9fa;
L_0800a9fa: STEP(0x0800a9fau); /* beq #0x800aa02 */
    if(Z)goto L_0800aa02;
    goto L_0800a9fc;
L_0800a9fc: STEP(0x0800a9fcu); /* cmp r0, #0 */
    (void)sub(s,s->r[0],0x0u);
    goto L_0800a9fe;
L_0800a9fe: STEP(0x0800a9feu); /* beq #0x800aa0c */
    if(Z)goto L_0800aa0c;
    goto L_0800aa00;
L_0800aa00: STEP(0x0800aa00u); /* b #0x800aa14 */
    goto L_0800aa14;
L_0800aa02: STEP(0x0800aa02u); /* ldr r0, [pc, #0x150] */
    s->r[0]=read_mem(s,(0x800aa04u + 0x150u),4);
    goto L_0800aa04;
L_0800aa04: STEP(0x0800aa04u); /* ldrb r0, [r0] */
    s->r[0]=read_mem(s,(s->r[0]),1);
    goto L_0800aa06;
L_0800aa06: STEP(0x0800aa06u); /* bl #0x800b960 */
    s->r[14]=0x0800aa0bu;
    if(!s->call){s->fault=-2;s->fault_address=0x0800b960u;return -2;}
    s->r[15]=0x0800b960u;
    temp=(uint32_t)s->call(s->user,0x0800b960u,s);
    if(temp){s->pc=0x0800aa0au;return 1;}
    goto L_0800aa0a;
L_0800aa0a: STEP(0x0800aa0au); /* b #0x800aa14 */
    goto L_0800aa14;
L_0800aa0c: STEP(0x0800aa0cu); /* ldr r0, [pc, #0x144] */
    s->r[0]=read_mem(s,(0x800aa10u + 0x144u),4);
    goto L_0800aa0e;
L_0800aa0e: STEP(0x0800aa0eu); /* ldrb r0, [r0] */
    s->r[0]=read_mem(s,(s->r[0]),1);
    goto L_0800aa10;
L_0800aa10: STEP(0x0800aa10u); /* bl #0x800b87c */
    s->r[14]=0x0800aa15u;
    if(!s->call){s->fault=-2;s->fault_address=0x0800b87cu;return -2;}
    s->r[15]=0x0800b87cu;
    temp=(uint32_t)s->call(s->user,0x0800b87cu,s);
    if(temp){s->pc=0x0800aa14u;return 1;}
    goto L_0800aa14;
L_0800aa14: STEP(0x0800aa14u); /* ldr r0, [pc, #0x13c] */
    s->r[0]=read_mem(s,(0x800aa18u + 0x13cu),4);
    goto L_0800aa16;
L_0800aa16: STEP(0x0800aa16u); /* movs r1, #1 */
    s->r[1]=nz(s,0x1u);
    goto L_0800aa18;
L_0800aa18: STEP(0x0800aa18u); /* ldrb r2, [r0] */
    s->r[2]=read_mem(s,(s->r[0]),1);
    goto L_0800aa1a;
L_0800aa1a: STEP(0x0800aa1au); /* bics r1, r2 */
    s->r[1]=nz(s,(s->r[1])&~(s->r[2]));
    goto L_0800aa1c;
L_0800aa1c: STEP(0x0800aa1cu); /* b #0x800aa2a */
    goto L_0800aa2a;
L_0800aa1e: STEP(0x0800aa1eu); /* ldr r0, [pc, #0x110] */
    s->r[0]=read_mem(s,(0x800aa20u + 0x110u),4);
    goto L_0800aa20;
L_0800aa20: STEP(0x0800aa20u); /* subs r0, #0x60 */
    s->r[0]=sub(s,s->r[0],0x60u);
    goto L_0800aa22;
L_0800aa22: STEP(0x0800aa22u); /* ldrb r1, [r0] */
    s->r[1]=read_mem(s,(s->r[0]),1);
    goto L_0800aa24;
L_0800aa24: STEP(0x0800aa24u); /* cmp r1, #0x21 */
    (void)sub(s,s->r[1],0x21u);
    goto L_0800aa26;
L_0800aa26: STEP(0x0800aa26u); /* bne #0x800a964 */
    if(!Z)goto L_0800a964;
    goto L_0800aa28;
L_0800aa28: STEP(0x0800aa28u); /* movs r1, #1 */
    s->r[1]=nz(s,0x1u);
    goto L_0800aa2a;
L_0800aa2a: STEP(0x0800aa2au); /* strb r1, [r0] */
    write_mem(s,(s->r[0]),1,s->r[1]);
    goto L_0800aa2c;
L_0800aa2c: STEP(0x0800aa2cu); /* b #0x800ac5a */
    goto L_0800ac5a;
L_0800aa2e: STEP(0x0800aa2eu); /* ldr r0, [pc, #0x100] */
    s->r[0]=read_mem(s,(0x800aa30u + 0x100u),4);
    goto L_0800aa30;
L_0800aa30: STEP(0x0800aa30u); /* subs r0, #0x60 */
    s->r[0]=sub(s,s->r[0],0x60u);
    goto L_0800aa32;
L_0800aa32: STEP(0x0800aa32u); /* ldrh r0, [r0, #0x22] */
    s->r[0]=read_mem(s,(s->r[0] + 0x22u),2);
    goto L_0800aa34;
L_0800aa34: STEP(0x0800aa34u); /* cmp r0, #0 */
    (void)sub(s,s->r[0],0x0u);
    goto L_0800aa36;
L_0800aa36: STEP(0x0800aa36u); /* beq #0x800aa3a */
    if(Z)goto L_0800aa3a;
    goto L_0800aa38;
L_0800aa38: STEP(0x0800aa38u); /* movs r0, #2 */
    s->r[0]=nz(s,0x2u);
    goto L_0800aa3a;
L_0800aa3a: STEP(0x0800aa3au); /* movs r1, #0x34 */
    s->r[1]=nz(s,0x34u);
    goto L_0800aa3c;
L_0800aa3c: STEP(0x0800aa3cu); /* ldr r2, [pc, #0x100] */
    s->r[2]=read_mem(s,(0x800aa40u + 0x100u),4);
    goto L_0800aa3e;
L_0800aa3e: STEP(0x0800aa3eu); /* muls r1, r4, r1 */
    s->r[1]=nz(s,(s->r[4])*(s->r[1]));
    goto L_0800aa40;
L_0800aa40: STEP(0x0800aa40u); /* adds r1, r1, r2 */
    s->r[1]=add(s,s->r[1],s->r[2]);
    goto L_0800aa42;
L_0800aa42: STEP(0x0800aa42u); /* subs r1, #0xff */
    s->r[1]=sub(s,s->r[1],0xffu);
    goto L_0800aa44;
L_0800aa44: STEP(0x0800aa44u); /* subs r1, #0xc1 */
    s->r[1]=sub(s,s->r[1],0xc1u);
    goto L_0800aa46;
L_0800aa46: STEP(0x0800aa46u); /* strb r0, [r1, #0x19] */
    write_mem(s,(s->r[1] + 0x19u),1,s->r[0]);
    goto L_0800aa48;
L_0800aa48: STEP(0x0800aa48u); /* b #0x800ac5a */
    goto L_0800ac5a;
L_0800aa4a: STEP(0x0800aa4au); /* mov r0, r4 */
    s->r[0]=s->r[4];
    goto L_0800aa4c;
L_0800aa4c: STEP(0x0800aa4cu); /* subs r0, #0x15 */
    s->r[0]=sub(s,s->r[0],0x15u);
    goto L_0800aa4e;
L_0800aa4e: STEP(0x0800aa4eu); /* uxth r7, r0 */
    s->r[7]=(uint16_t)(s->r[0]);
    goto L_0800aa50;
L_0800aa50: STEP(0x0800aa50u); /* movs r0, #0x34 */
    s->r[0]=nz(s,0x34u);
    goto L_0800aa52;
L_0800aa52: STEP(0x0800aa52u); /* str r7, [sp, #4] */
    write_mem(s,(s->r[13] + 0x4u),4,s->r[7]);
    goto L_0800aa54;
L_0800aa54: STEP(0x0800aa54u); /* ldr r6, [pc, #0xe8] */
    s->r[6]=read_mem(s,(0x800aa58u + 0xe8u),4);
    goto L_0800aa56;
L_0800aa56: STEP(0x0800aa56u); /* muls r7, r0, r7 */
    s->r[7]=nz(s,(s->r[0])*(s->r[7]));
    goto L_0800aa58;
L_0800aa58: STEP(0x0800aa58u); /* adds r0, r7, r6 */
    s->r[0]=add(s,s->r[7],s->r[6]);
    goto L_0800aa5a;
L_0800aa5a: STEP(0x0800aa5au); /* str r0, [sp, #0x18] */
    write_mem(s,(s->r[13] + 0x18u),4,s->r[0]);
    goto L_0800aa5c;
L_0800aa5c: STEP(0x0800aa5cu); /* adds r0, #0x20 */
    s->r[0]=add(s,s->r[0],0x20u);
    goto L_0800aa5e;
L_0800aa5e: STEP(0x0800aa5eu); /* str r0, [sp, #0x20] */
    write_mem(s,(s->r[13] + 0x20u),4,s->r[0]);
    goto L_0800aa60;
L_0800aa60: STEP(0x0800aa60u); /* ldrb r0, [r0, #0xc] */
    s->r[0]=read_mem(s,(s->r[0] + 0xcu),1);
    goto L_0800aa62;
L_0800aa62: STEP(0x0800aa62u); /* cmp r0, #1 */
    (void)sub(s,s->r[0],0x1u);
    goto L_0800aa64;
L_0800aa64: STEP(0x0800aa64u); /* beq #0x800aa76 */
    if(Z)goto L_0800aa76;
    goto L_0800aa66;
L_0800aa66: STEP(0x0800aa66u); /* bl #0x800a068 */
    s->r[14]=0x0800aa6bu;
    if(!s->call){s->fault=-2;s->fault_address=0x0800a068u;return -2;}
    s->r[15]=0x0800a068u;
    temp=(uint32_t)s->call(s->user,0x0800a068u,s);
    if(temp){s->pc=0x0800aa6au;return 1;}
    goto L_0800aa6a;
L_0800aa6a: STEP(0x0800aa6au); /* cmp r0, #1 */
    (void)sub(s,s->r[0],0x1u);
    goto L_0800aa6c;
L_0800aa6c: STEP(0x0800aa6cu); /* beq #0x800aa8e */
    if(Z)goto L_0800aa8e;
    goto L_0800aa6e;
L_0800aa6e: STEP(0x0800aa6eu); /* b #0x800aa96 */
    goto L_0800aa96;
L_0800aa70: STEP(0x0800aa70u); /* b #0x800ac34 */
    goto L_0800ac34;
L_0800aa72: STEP(0x0800aa72u); /* b #0x800ac4e */
    goto L_0800ac4e;
L_0800aa74: STEP(0x0800aa74u); /* b #0x800ac2a */
    goto L_0800ac2a;
L_0800aa76: STEP(0x0800aa76u); /* ldr r0, [sp, #0x18] */
    s->r[0]=read_mem(s,(s->r[13] + 0x18u),4);
    goto L_0800aa78;
L_0800aa78: STEP(0x0800aa78u); /* ldrh r1, [r0, #4] */
    s->r[1]=read_mem(s,(s->r[0] + 0x4u),2);
    goto L_0800aa7a;
L_0800aa7a: STEP(0x0800aa7au); /* ldr r0, [pc, #0xb4] */
    s->r[0]=read_mem(s,(0x800aa7cu + 0xb4u),4);
    goto L_0800aa7c;
L_0800aa7c: STEP(0x0800aa7cu); /* subs r0, #0x60 */
    s->r[0]=sub(s,s->r[0],0x60u);
    goto L_0800aa7e;
L_0800aa7e: STEP(0x0800aa7eu); /* ldrh r0, [r0, #0x12] */
    s->r[0]=read_mem(s,(s->r[0] + 0x12u),2);
    goto L_0800aa80;
L_0800aa80: STEP(0x0800aa80u); /* cmp r1, r0 */
    (void)sub(s,s->r[1],s->r[0]);
    goto L_0800aa82;
L_0800aa82: STEP(0x0800aa82u); /* blo #0x800aa8c */
    if(!C)goto L_0800aa8c;
    goto L_0800aa84;
L_0800aa84: STEP(0x0800aa84u); /* ldr r0, [sp, #4] */
    s->r[0]=read_mem(s,(s->r[13] + 0x4u),4);
    goto L_0800aa86;
L_0800aa86: STEP(0x0800aa86u); /* uxtb r0, r0 */
    s->r[0]=(uint8_t)(s->r[0]);
    goto L_0800aa88;
L_0800aa88: STEP(0x0800aa88u); /* bl #0x8008224 */
    s->r[14]=0x0800aa8du;
    if(!s->call){s->fault=-2;s->fault_address=0x08008224u;return -2;}
    s->r[15]=0x08008224u;
    temp=(uint32_t)s->call(s->user,0x08008224u,s);
    if(temp){s->pc=0x0800aa8cu;return 1;}
    goto L_0800aa8c;
L_0800aa8c: STEP(0x0800aa8cu); /* b #0x800ac5a */
    goto L_0800ac5a;
L_0800aa8e: STEP(0x0800aa8eu); /* ldr r0, [sp, #0x20] */
    s->r[0]=read_mem(s,(s->r[13] + 0x20u),4);
    goto L_0800aa90;
L_0800aa90: STEP(0x0800aa90u); /* ldrb r0, [r0, #0xc] */
    s->r[0]=read_mem(s,(s->r[0] + 0xcu),1);
    goto L_0800aa92;
L_0800aa92: STEP(0x0800aa92u); /* cmp r0, #0 */
    (void)sub(s,s->r[0],0x0u);
    goto L_0800aa94;
L_0800aa94: STEP(0x0800aa94u); /* beq #0x800aaa4 */
    if(Z)goto L_0800aaa4;
    goto L_0800aa96;
L_0800aa96: STEP(0x0800aa96u); /* ldr r0, [sp, #0x20] */
    s->r[0]=read_mem(s,(s->r[13] + 0x20u),4);
    goto L_0800aa98;
L_0800aa98: STEP(0x0800aa98u); /* ldrb r0, [r0, #0xc] */
    s->r[0]=read_mem(s,(s->r[0] + 0xcu),1);
    goto L_0800aa9a;
L_0800aa9a: STEP(0x0800aa9au); /* cmp r0, #2 */
    (void)sub(s,s->r[0],0x2u);
    goto L_0800aa9c;
L_0800aa9c: STEP(0x0800aa9cu); /* beq #0x800ab9c */
    if(Z)goto L_0800ab9c;
    goto L_0800aa9e;
L_0800aa9e: STEP(0x0800aa9eu); /* cmp r0, #3 */
    (void)sub(s,s->r[0],0x3u);
    goto L_0800aaa0;
L_0800aaa0: STEP(0x0800aaa0u); /* beq #0x800ab9e */
    if(Z)goto L_0800ab9e;
    goto L_0800aaa2;
L_0800aaa2: STEP(0x0800aaa2u); /* b #0x800ac5a */
    goto L_0800ac5a;
L_0800aaa4: STEP(0x0800aaa4u); /* ldr r1, [sp, #0x18] */
    s->r[1]=read_mem(s,(s->r[13] + 0x18u),4);
    goto L_0800aaa6;
L_0800aaa6: STEP(0x0800aaa6u); /* ldr r0, [sp, #0x18] */
    s->r[0]=read_mem(s,(s->r[13] + 0x18u),4);
    goto L_0800aaa8;
L_0800aaa8: STEP(0x0800aaa8u); /* ldrb r1, [r1, #0x15] */
    s->r[1]=read_mem(s,(s->r[1] + 0x15u),1);
    goto L_0800aaaa;
L_0800aaaa: STEP(0x0800aaaau); /* ldrh r0, [r0, #4] */
    s->r[0]=read_mem(s,(s->r[0] + 0x4u),2);
    goto L_0800aaac;
L_0800aaac: STEP(0x0800aaacu); /* lsls r2, r1, #1 */
    s->r[2]=lsl(s,s->r[1],0x1u);
    goto L_0800aaae;
L_0800aaae: STEP(0x0800aaaeu); /* ldr r1, [pc, #0x80] */
    s->r[1]=read_mem(s,(0x800aab0u + 0x80u),4);
    goto L_0800aab0;
L_0800aab0: STEP(0x0800aab0u); /* subs r1, #0x60 */
    s->r[1]=sub(s,s->r[1],0x60u);
    goto L_0800aab2;
L_0800aab2: STEP(0x0800aab2u); /* adds r2, r2, r1 */
    s->r[2]=add(s,s->r[2],s->r[1]);
    goto L_0800aab4;
L_0800aab4: STEP(0x0800aab4u); /* ldrh r2, [r2, #0xc] */
    s->r[2]=read_mem(s,(s->r[2] + 0xcu),2);
    goto L_0800aab6;
L_0800aab6: STEP(0x0800aab6u); /* cmp r0, r2 */
    (void)sub(s,s->r[0],s->r[2]);
    goto L_0800aab8;
L_0800aab8: STEP(0x0800aab8u); /* blo #0x800aba0 */
    if(!C)goto L_0800aba0;
    goto L_0800aaba;
L_0800aaba: STEP(0x0800aabau); /* ldrh r2, [r1, #0xc] */
    s->r[2]=read_mem(s,(s->r[1] + 0xcu),2);
    goto L_0800aabc;
L_0800aabc: STEP(0x0800aabcu); /* cmp r0, r2 */
    (void)sub(s,s->r[0],s->r[2]);
    goto L_0800aabe;
L_0800aabe: STEP(0x0800aabeu); /* blo #0x800aaca */
    if(!C)goto L_0800aaca;
    goto L_0800aac0;
L_0800aac0: STEP(0x0800aac0u); /* ldrh r2, [r1, #0xe] */
    s->r[2]=read_mem(s,(s->r[1] + 0xeu),2);
    goto L_0800aac2;
L_0800aac2: STEP(0x0800aac2u); /* cmp r0, r2 */
    (void)sub(s,s->r[0],s->r[2]);
    goto L_0800aac4;
L_0800aac4: STEP(0x0800aac4u); /* bhs #0x800aaca */
    if(C)goto L_0800aaca;
    goto L_0800aac6;
L_0800aac6: STEP(0x0800aac6u); /* movs r0, #1 */
    s->r[0]=nz(s,0x1u);
    goto L_0800aac8;
L_0800aac8: STEP(0x0800aac8u); /* b #0x800aae8 */
    goto L_0800aae8;
L_0800aaca: STEP(0x0800aacau); /* ldrh r2, [r1, #0xe] */
    s->r[2]=read_mem(s,(s->r[1] + 0xeu),2);
    goto L_0800aacc;
L_0800aacc: STEP(0x0800aaccu); /* cmp r0, r2 */
    (void)sub(s,s->r[0],s->r[2]);
    goto L_0800aace;
L_0800aace: STEP(0x0800aaceu); /* blo #0x800aada */
    if(!C)goto L_0800aada;
    goto L_0800aad0;
L_0800aad0: STEP(0x0800aad0u); /* ldrh r2, [r1, #0x10] */
    s->r[2]=read_mem(s,(s->r[1] + 0x10u),2);
    goto L_0800aad2;
L_0800aad2: STEP(0x0800aad2u); /* cmp r0, r2 */
    (void)sub(s,s->r[0],s->r[2]);
    goto L_0800aad4;
L_0800aad4: STEP(0x0800aad4u); /* bhs #0x800aada */
    if(C)goto L_0800aada;
    goto L_0800aad6;
L_0800aad6: STEP(0x0800aad6u); /* movs r0, #2 */
    s->r[0]=nz(s,0x2u);
    goto L_0800aad8;
L_0800aad8: STEP(0x0800aad8u); /* b #0x800aae8 */
    goto L_0800aae8;
L_0800aada: STEP(0x0800aadau); /* ldrh r2, [r1, #0x10] */
    s->r[2]=read_mem(s,(s->r[1] + 0x10u),2);
    goto L_0800aadc;
L_0800aadc: STEP(0x0800aadcu); /* cmp r0, r2 */
    (void)sub(s,s->r[0],s->r[2]);
    goto L_0800aade;
L_0800aade: STEP(0x0800aadeu); /* blo #0x800aaec */
    if(!C)goto L_0800aaec;
    goto L_0800aae0;
L_0800aae0: STEP(0x0800aae0u); /* ldrh r2, [r1, #0x12] */
    s->r[2]=read_mem(s,(s->r[1] + 0x12u),2);
    goto L_0800aae2;
L_0800aae2: STEP(0x0800aae2u); /* cmp r0, r2 */
    (void)sub(s,s->r[0],s->r[2]);
    goto L_0800aae4;
L_0800aae4: STEP(0x0800aae4u); /* bhs #0x800aaec */
    if(C)goto L_0800aaec;
    goto L_0800aae6;
L_0800aae6: STEP(0x0800aae6u); /* movs r0, #3 */
    s->r[0]=nz(s,0x3u);
    goto L_0800aae8;
L_0800aae8: STEP(0x0800aae8u); /* ldr r2, [sp, #0x18] */
    s->r[2]=read_mem(s,(s->r[13] + 0x18u),4);
    goto L_0800aaea;
L_0800aaea: STEP(0x0800aaeau); /* strb r0, [r2, #0x15] */
    write_mem(s,(s->r[2] + 0x15u),1,s->r[0]);
    goto L_0800aaec;
L_0800aaec: STEP(0x0800aaecu); /* ldr r0, [sp, #0x18] */
    s->r[0]=read_mem(s,(s->r[13] + 0x18u),4);
    goto L_0800aaee;
L_0800aaee: STEP(0x0800aaeeu); /* ldrb r0, [r0, #0x15] */
    s->r[0]=read_mem(s,(s->r[0] + 0x15u),1);
    goto L_0800aaf0;
L_0800aaf0: STEP(0x0800aaf0u); /* subs r0, r0, #1 */
    s->r[0]=sub(s,s->r[0],0x1u);
    goto L_0800aaf2;
L_0800aaf2: STEP(0x0800aaf2u); /* uxth r5, r0 */
    s->r[5]=(uint16_t)(s->r[0]);
    goto L_0800aaf4;
L_0800aaf4: STEP(0x0800aaf4u); /* ldr r0, [sp, #0x18] */
    s->r[0]=read_mem(s,(s->r[13] + 0x18u),4);
    goto L_0800aaf6;
L_0800aaf6: STEP(0x0800aaf6u); /* lsls r2, r5, #1 */
    s->r[2]=lsl(s,s->r[5],0x1u);
    goto L_0800aaf8;
L_0800aaf8: STEP(0x0800aaf8u); /* ldrh r0, [r0, #4] */
    s->r[0]=read_mem(s,(s->r[0] + 0x4u),2);
    goto L_0800aafa;
L_0800aafa: STEP(0x0800aafau); /* adds r2, r2, r1 */
    s->r[2]=add(s,s->r[2],s->r[1]);
    goto L_0800aafc;
L_0800aafc: STEP(0x0800aafcu); /* str r2, [sp, #0xc] */
    write_mem(s,(s->r[13] + 0xcu),4,s->r[2]);
    goto L_0800aafe;
L_0800aafe: STEP(0x0800aafeu); /* ldrh r2, [r2, #0xc] */
    s->r[2]=read_mem(s,(s->r[2] + 0xcu),2);
    goto L_0800ab00;
L_0800ab00: STEP(0x0800ab00u); /* cmp r0, r2 */
    (void)sub(s,s->r[0],s->r[2]);
    goto L_0800ab02;
L_0800ab02: STEP(0x0800ab02u); /* b #0x800ab58 */
    goto L_0800ab58;
L_0800ab58: STEP(0x0800ab58u); /* blo #0x800ac5a */
    if(!C)goto L_0800ac5a;
    goto L_0800ab5a;
L_0800ab5a: STEP(0x0800ab5au); /* cmp r5, #3 */
    (void)sub(s,s->r[5],0x3u);
    goto L_0800ab5c;
L_0800ab5c: STEP(0x0800ab5cu); /* bhs #0x800ac5a */
    if(C)goto L_0800ac5a;
    goto L_0800ab5e;
L_0800ab5e: STEP(0x0800ab5eu); /* ldr r0, [sp, #0x20] */
    s->r[0]=read_mem(s,(s->r[13] + 0x20u),4);
    goto L_0800ab60;
L_0800ab60: STEP(0x0800ab60u); /* ldrb r0, [r0, #0x11] */
    s->r[0]=read_mem(s,(s->r[0] + 0x11u),1);
    goto L_0800ab62;
L_0800ab62: STEP(0x0800ab62u); /* cmp r0, #1 */
    (void)sub(s,s->r[0],0x1u);
    goto L_0800ab64;
L_0800ab64: STEP(0x0800ab64u); /* bne #0x800ab90 */
    if(!Z)goto L_0800ab90;
    goto L_0800ab66;
L_0800ab66: STEP(0x0800ab66u); /* ldr r0, [sp, #0x3c] */
    s->r[0]=read_mem(s,(s->r[13] + 0x3cu),4);
    goto L_0800ab68;
L_0800ab68: STEP(0x0800ab68u); /* lsls r0, r0, #1 */
    s->r[0]=lsl(s,s->r[0],0x1u);
    goto L_0800ab6a;
L_0800ab6a: STEP(0x0800ab6au); /* adds r0, r0, r1 */
    s->r[0]=add(s,s->r[0],s->r[1]);
    goto L_0800ab6c;
L_0800ab6c: STEP(0x0800ab6cu); /* ldrh r0, [r0, #0x14] */
    s->r[0]=read_mem(s,(s->r[0] + 0x14u),2);
    goto L_0800ab6e;
L_0800ab6e: STEP(0x0800ab6eu); /* str r0, [sp] */
    write_mem(s,(s->r[13]),4,s->r[0]);
    goto L_0800ab70;
L_0800ab70: STEP(0x0800ab70u); /* ldr r0, [r6, r7] */
    s->r[0]=read_mem(s,(s->r[6] + s->r[7]),4);
    goto L_0800ab72;
L_0800ab72: STEP(0x0800ab72u); /* ldr r1, [sp] */
    s->r[1]=read_mem(s,(s->r[13]),4);
    goto L_0800ab74;
L_0800ab74: STEP(0x0800ab74u); /* bl #0x80040e8 */
    s->r[14]=0x0800ab79u;
    if(!s->call){s->fault=-2;s->fault_address=0x080040e8u;return -2;}
    s->r[15]=0x080040e8u;
    temp=(uint32_t)s->call(s->user,0x080040e8u,s);
    if(temp){s->pc=0x0800ab78u;return 1;}
    goto L_0800ab78;
L_0800ab78: STEP(0x0800ab78u); /* movs r1, #0x64 */
    s->r[1]=nz(s,0x64u);
    goto L_0800ab7a;
L_0800ab7a: STEP(0x0800ab7au); /* muls r0, r1, r0 */
    s->r[0]=nz(s,(s->r[1])*(s->r[0]));
    goto L_0800ab7c;
L_0800ab7c: STEP(0x0800ab7cu); /* str r0, [r6, r7] */
    write_mem(s,(s->r[6] + s->r[7]),4,s->r[0]);
    goto L_0800ab7e;
L_0800ab7e: STEP(0x0800ab7eu); /* ldr r0, [sp, #0x18] */
    s->r[0]=read_mem(s,(s->r[13] + 0x18u),4);
    goto L_0800ab80;
L_0800ab80: STEP(0x0800ab80u); /* ldr r1, [sp] */
    s->r[1]=read_mem(s,(s->r[13]),4);
    goto L_0800ab82;
L_0800ab82: STEP(0x0800ab82u); /* ldr r0, [r0, #0x24] */
    s->r[0]=read_mem(s,(s->r[0] + 0x24u),4);
    goto L_0800ab84;
L_0800ab84: STEP(0x0800ab84u); /* bl #0x80040e8 */
    s->r[14]=0x0800ab89u;
    if(!s->call){s->fault=-2;s->fault_address=0x080040e8u;return -2;}
    s->r[15]=0x080040e8u;
    temp=(uint32_t)s->call(s->user,0x080040e8u,s);
    if(temp){s->pc=0x0800ab88u;return 1;}
    goto L_0800ab88;
L_0800ab88: STEP(0x0800ab88u); /* movs r1, #0x64 */
    s->r[1]=nz(s,0x64u);
    goto L_0800ab8a;
L_0800ab8a: STEP(0x0800ab8au); /* muls r0, r1, r0 */
    s->r[0]=nz(s,(s->r[1])*(s->r[0]));
    goto L_0800ab8c;
L_0800ab8c: STEP(0x0800ab8cu); /* ldr r1, [sp, #0x18] */
    s->r[1]=read_mem(s,(s->r[13] + 0x18u),4);
    goto L_0800ab8e;
L_0800ab8e: STEP(0x0800ab8eu); /* str r0, [r1, #0x24] */
    write_mem(s,(s->r[1] + 0x24u),4,s->r[0]);
    goto L_0800ab90;
L_0800ab90: STEP(0x0800ab90u); /* ldr r0, [r6, r7] */
    s->r[0]=read_mem(s,(s->r[6] + s->r[7]),4);
    goto L_0800ab92;
L_0800ab92: STEP(0x0800ab92u); /* movs r1, #0x64 */
    s->r[1]=nz(s,0x64u);
    goto L_0800ab94;
L_0800ab94: STEP(0x0800ab94u); /* bl #0x80040e8 */
    s->r[14]=0x0800ab99u;
    if(!s->call){s->fault=-2;s->fault_address=0x080040e8u;return -2;}
    s->r[15]=0x080040e8u;
    temp=(uint32_t)s->call(s->user,0x080040e8u,s);
    if(temp){s->pc=0x0800ab98u;return 1;}
    goto L_0800ab98;
L_0800ab98: STEP(0x0800ab98u); /* ldr r1, [sp, #0xc] */
    s->r[1]=read_mem(s,(s->r[13] + 0xcu),4);
    goto L_0800ab9a;
L_0800ab9a: STEP(0x0800ab9au); /* b #0x800aba2 */
    goto L_0800aba2;
L_0800ab9c: STEP(0x0800ab9cu); /* b #0x800abd0 */
    goto L_0800abd0;
L_0800ab9e: STEP(0x0800ab9eu); /* b #0x800ac08 */
    goto L_0800ac08;
L_0800aba0: STEP(0x0800aba0u); /* b #0x800ac06 */
    goto L_0800ac06;
L_0800aba2: STEP(0x0800aba2u); /* ldrh r1, [r1, #0x14] */
    s->r[1]=read_mem(s,(s->r[1] + 0x14u),2);
    goto L_0800aba4;
L_0800aba4: STEP(0x0800aba4u); /* str r1, [sp, #0xc] */
    write_mem(s,(s->r[13] + 0xcu),4,s->r[1]);
    goto L_0800aba6;
L_0800aba6: STEP(0x0800aba6u); /* muls r0, r1, r0 */
    s->r[0]=nz(s,(s->r[1])*(s->r[0]));
    goto L_0800aba8;
L_0800aba8: STEP(0x0800aba8u); /* adds r0, #0x3c */
    s->r[0]=add(s,s->r[0],0x3cu);
    goto L_0800abaa;
L_0800abaa: STEP(0x0800abaau); /* str r0, [r6, r7] */
    write_mem(s,(s->r[6] + s->r[7]),4,s->r[0]);
    goto L_0800abac;
L_0800abac: STEP(0x0800abacu); /* ldr r0, [sp, #0x18] */
    s->r[0]=read_mem(s,(s->r[13] + 0x18u),4);
    goto L_0800abae;
L_0800abae: STEP(0x0800abaeu); /* movs r1, #0x64 */
    s->r[1]=nz(s,0x64u);
    goto L_0800abb0;
L_0800abb0: STEP(0x0800abb0u); /* ldr r0, [r0, #0x24] */
    s->r[0]=read_mem(s,(s->r[0] + 0x24u),4);
    goto L_0800abb2;
L_0800abb2: STEP(0x0800abb2u); /* bl #0x80040e8 */
    s->r[14]=0x0800abb7u;
    if(!s->call){s->fault=-2;s->fault_address=0x080040e8u;return -2;}
    s->r[15]=0x080040e8u;
    temp=(uint32_t)s->call(s->user,0x080040e8u,s);
    if(temp){s->pc=0x0800abb6u;return 1;}
    goto L_0800abb6;
L_0800abb6: STEP(0x0800abb6u); /* ldr r1, [sp, #0xc] */
    s->r[1]=read_mem(s,(s->r[13] + 0xcu),4);
    goto L_0800abb8;
L_0800abb8: STEP(0x0800abb8u); /* muls r0, r1, r0 */
    s->r[0]=nz(s,(s->r[1])*(s->r[0]));
    goto L_0800abba;
L_0800abba: STEP(0x0800abbau); /* ldr r1, [sp, #0x18] */
    s->r[1]=read_mem(s,(s->r[13] + 0x18u),4);
    goto L_0800abbc;
L_0800abbc: STEP(0x0800abbcu); /* str r0, [r1, #0x24] */
    write_mem(s,(s->r[1] + 0x24u),4,s->r[0]);
    goto L_0800abbe;
L_0800abbe: STEP(0x0800abbeu); /* ldr r1, [sp, #0x20] */
    s->r[1]=read_mem(s,(s->r[13] + 0x20u),4);
    goto L_0800abc0;
L_0800abc0: STEP(0x0800abc0u); /* movs r0, #1 */
    s->r[0]=nz(s,0x1u);
    goto L_0800abc2;
L_0800abc2: STEP(0x0800abc2u); /* str r5, [sp, #0x3c] */
    write_mem(s,(s->r[13] + 0x3cu),4,s->r[5]);
    goto L_0800abc4;
L_0800abc4: STEP(0x0800abc4u); /* strb r0, [r1, #0x11] */
    write_mem(s,(s->r[1] + 0x11u),1,s->r[0]);
    goto L_0800abc6;
L_0800abc6: STEP(0x0800abc6u); /* ldr r0, [sp, #4] */
    s->r[0]=read_mem(s,(s->r[13] + 0x4u),4);
    goto L_0800abc8;
L_0800abc8: STEP(0x0800abc8u); /* uxtb r0, r0 */
    s->r[0]=(uint8_t)(s->r[0]);
    goto L_0800abca;
L_0800abca: STEP(0x0800abcau); /* bl #0x800a5b0 */
    s->r[14]=0x0800abcfu;
    if(!s->call){s->fault=-2;s->fault_address=0x0800a5b0u;return -2;}
    s->r[15]=0x0800a5b0u;
    temp=(uint32_t)s->call(s->user,0x0800a5b0u,s);
    if(temp){s->pc=0x0800abceu;return 1;}
    goto L_0800abce;
L_0800abce: STEP(0x0800abceu); /* b #0x800ac5a */
    goto L_0800ac5a;
L_0800abd0: STEP(0x0800abd0u); /* ldr r0, [sp, #0x18] */
    s->r[0]=read_mem(s,(s->r[13] + 0x18u),4);
    goto L_0800abd2;
L_0800abd2: STEP(0x0800abd2u); /* ldrh r1, [r0, #4] */
    s->r[1]=read_mem(s,(s->r[0] + 0x4u),2);
    goto L_0800abd4;
L_0800abd4: STEP(0x0800abd4u); /* ldr r0, [pc, #0x3f0] */
    s->r[0]=read_mem(s,(0x800abd8u + 0x3f0u),4);
    goto L_0800abd6;
L_0800abd6: STEP(0x0800abd6u); /* ldrh r2, [r0, #0x28] */
    s->r[2]=read_mem(s,(s->r[0] + 0x28u),2);
    goto L_0800abd8;
L_0800abd8: STEP(0x0800abd8u); /* cmp r1, r2 */
    (void)sub(s,s->r[1],s->r[2]);
    goto L_0800abda;
L_0800abda: STEP(0x0800abdau); /* bhs #0x800ac5a */
    if(C)goto L_0800ac5a;
    goto L_0800abdc;
L_0800abdc: STEP(0x0800abdcu); /* ldrh r2, [r0, #0x26] */
    s->r[2]=read_mem(s,(s->r[0] + 0x26u),2);
    goto L_0800abde;
L_0800abde: STEP(0x0800abdeu); /* ldr r0, [sp, #4] */
    s->r[0]=read_mem(s,(s->r[13] + 0x4u),4);
    goto L_0800abe0;
L_0800abe0: STEP(0x0800abe0u); /* movs r1, #0x5a */
    s->r[1]=nz(s,0x5au);
    goto L_0800abe2;
L_0800abe2: STEP(0x0800abe2u); /* lsls r0, r0, #1 */
    s->r[0]=lsl(s,s->r[0],0x1u);
    goto L_0800abe4;
L_0800abe4: STEP(0x0800abe4u); /* adds r0, r0, r5 */
    s->r[0]=add(s,s->r[0],s->r[5]);
    goto L_0800abe6;
L_0800abe6: STEP(0x0800abe6u); /* ldrh r1, [r1, r0] */
    s->r[1]=read_mem(s,(s->r[1] + s->r[0]),2);
    goto L_0800abe8;
L_0800abe8: STEP(0x0800abe8u); /* adds r0, #0x80 */
    s->r[0]=add(s,s->r[0],0x80u);
    goto L_0800abea;
L_0800abea: STEP(0x0800abeau); /* adds r1, r2, r1 */
    s->r[1]=add(s,s->r[2],s->r[1]);
    goto L_0800abec;
L_0800abec: STEP(0x0800abecu); /* strh r1, [r0, #0xa] */
    write_mem(s,(s->r[0] + 0xau),2,s->r[1]);
    goto L_0800abee;
L_0800abee: STEP(0x0800abeeu); /* ldr r0, [sp, #0x20] */
    s->r[0]=read_mem(s,(s->r[13] + 0x20u),4);
    goto L_0800abf0;
L_0800abf0: STEP(0x0800abf0u); /* ldrb r0, [r0, #0x13] */
    s->r[0]=read_mem(s,(s->r[0] + 0x13u),1);
    goto L_0800abf2;
L_0800abf2: STEP(0x0800abf2u); /* cmp r0, #4 */
    (void)sub(s,s->r[0],0x4u);
    goto L_0800abf4;
L_0800abf4: STEP(0x0800abf4u); /* bhs #0x800ac5a */
    if(C)goto L_0800ac5a;
    goto L_0800abf6;
L_0800abf6: STEP(0x0800abf6u); /* movs r0, #3 */
    s->r[0]=nz(s,0x3u);
    goto L_0800abf8;
L_0800abf8: STEP(0x0800abf8u); /* bl #0x800cdb8 */
    s->r[14]=0x0800abfdu;
    if(!s->call){s->fault=-2;s->fault_address=0x0800cdb8u;return -2;}
    s->r[15]=0x0800cdb8u;
    temp=(uint32_t)s->call(s->user,0x0800cdb8u,s);
    if(temp){s->pc=0x0800abfcu;return 1;}
    goto L_0800abfc;
L_0800abfc: STEP(0x0800abfcu); /* ldr r0, [sp, #0x20] */
    s->r[0]=read_mem(s,(s->r[13] + 0x20u),4);
    goto L_0800abfe;
L_0800abfe: STEP(0x0800abfeu); /* ldr r1, [sp, #0x20] */
    s->r[1]=read_mem(s,(s->r[13] + 0x20u),4);
    goto L_0800ac00;
L_0800ac00: STEP(0x0800ac00u); /* ldrb r0, [r0, #0x13] */
    s->r[0]=read_mem(s,(s->r[0] + 0x13u),1);
    goto L_0800ac02;
L_0800ac02: STEP(0x0800ac02u); /* adds r0, r0, #1 */
    s->r[0]=add(s,s->r[0],0x1u);
    goto L_0800ac04;
L_0800ac04: STEP(0x0800ac04u); /* strb r0, [r1, #0x13] */
    write_mem(s,(s->r[1] + 0x13u),1,s->r[0]);
    goto L_0800ac06;
L_0800ac06: STEP(0x0800ac06u); /* b #0x800ac5a */
    goto L_0800ac5a;
L_0800ac08: STEP(0x0800ac08u); /* ldr r0, [sp, #0x18] */
    s->r[0]=read_mem(s,(s->r[13] + 0x18u),4);
    goto L_0800ac0a;
L_0800ac0a: STEP(0x0800ac0au); /* ldrb r0, [r0, #0x16] */
    s->r[0]=read_mem(s,(s->r[0] + 0x16u),1);
    goto L_0800ac0c;
L_0800ac0c: STEP(0x0800ac0cu); /* cmp r0, #2 */
    (void)sub(s,s->r[0],0x2u);
    goto L_0800ac0e;
L_0800ac0e: STEP(0x0800ac0eu); /* bne #0x800ac5a */
    if(!Z)goto L_0800ac5a;
    goto L_0800ac10;
L_0800ac10: STEP(0x0800ac10u); /* ldr r0, [sp, #0x18] */
    s->r[0]=read_mem(s,(s->r[13] + 0x18u),4);
    goto L_0800ac12;
L_0800ac12: STEP(0x0800ac12u); /* ldrh r1, [r0, #4] */
    s->r[1]=read_mem(s,(s->r[0] + 0x4u),2);
    goto L_0800ac14;
L_0800ac14: STEP(0x0800ac14u); /* ldr r0, [pc, #0x3b0] */
    s->r[0]=read_mem(s,(0x800ac18u + 0x3b0u),4);
    goto L_0800ac16;
L_0800ac16: STEP(0x0800ac16u); /* ldrh r0, [r0, #0x12] */
    s->r[0]=read_mem(s,(s->r[0] + 0x12u),2);
    goto L_0800ac18;
L_0800ac18: STEP(0x0800ac18u); /* cmp r1, r0 */
    (void)sub(s,s->r[1],s->r[0]);
    goto L_0800ac1a;
L_0800ac1a: STEP(0x0800ac1au); /* bhs #0x800ac5a */
    if(C)goto L_0800ac5a;
    goto L_0800ac1c;
L_0800ac1c: STEP(0x0800ac1cu); /* ldr r1, [sp, #4] */
    s->r[1]=read_mem(s,(s->r[13] + 0x4u),4);
    goto L_0800ac1e;
L_0800ac1e: STEP(0x0800ac1eu); /* movs r0, #0 */
    s->r[0]=nz(s,0x0u);
    goto L_0800ac20;
L_0800ac20: STEP(0x0800ac20u); /* lsls r1, r1, #1 */
    s->r[1]=lsl(s,s->r[1],0x1u);
    goto L_0800ac22;
L_0800ac22: STEP(0x0800ac22u); /* adds r1, r1, r5 */
    s->r[1]=add(s,s->r[1],s->r[5]);
    goto L_0800ac24;
L_0800ac24: STEP(0x0800ac24u); /* adds r1, #0x40 */
    s->r[1]=add(s,s->r[1],0x40u);
    goto L_0800ac26;
L_0800ac26: STEP(0x0800ac26u); /* strh r0, [r1, #2] */
    write_mem(s,(s->r[1] + 0x2u),2,s->r[0]);
    goto L_0800ac28;
L_0800ac28: STEP(0x0800ac28u); /* b #0x800ac5a */
    goto L_0800ac5a;
L_0800ac2a: STEP(0x0800ac2au); /* mov r0, r4 */
    s->r[0]=s->r[4];
    goto L_0800ac2c;
L_0800ac2c: STEP(0x0800ac2cu); /* subs r0, #0x21 */
    s->r[0]=sub(s,s->r[0],0x21u);
    goto L_0800ac2e;
L_0800ac2e: STEP(0x0800ac2eu); /* uxtb r0, r0 */
    s->r[0]=(uint8_t)(s->r[0]);
    goto L_0800ac30;
L_0800ac30: STEP(0x0800ac30u); /* movs r1, #3 */
    s->r[1]=nz(s,0x3u);
    goto L_0800ac32;
L_0800ac32: STEP(0x0800ac32u); /* b #0x800ac56 */
    goto L_0800ac56;
L_0800ac34: STEP(0x0800ac34u); /* mov r5, r4 */
    s->r[5]=s->r[4];
    goto L_0800ac36;
L_0800ac36: STEP(0x0800ac36u); /* subs r5, #0x45 */
    s->r[5]=sub(s,s->r[5],0x45u);
    goto L_0800ac38;
L_0800ac38: STEP(0x0800ac38u); /* uxtb r0, r5 */
    s->r[0]=(uint8_t)(s->r[5]);
    goto L_0800ac3a;
L_0800ac3a: STEP(0x0800ac3au); /* bl #0x800a128 */
    s->r[14]=0x0800ac3fu;
    if(!s->call){s->fault=-2;s->fault_address=0x0800a128u;return -2;}
    s->r[15]=0x0800a128u;
    temp=(uint32_t)s->call(s->user,0x0800a128u,s);
    if(temp){s->pc=0x0800ac3eu;return 1;}
    goto L_0800ac3e;
L_0800ac3e: STEP(0x0800ac3eu); /* cmp r0, #0 */
    (void)sub(s,s->r[0],0x0u);
    goto L_0800ac40;
L_0800ac40: STEP(0x0800ac40u); /* beq #0x800ac48 */
    if(Z)goto L_0800ac48;
    goto L_0800ac42;
L_0800ac42: STEP(0x0800ac42u); /* uxtb r0, r5 */
    s->r[0]=(uint8_t)(s->r[5]);
    goto L_0800ac44;
L_0800ac44: STEP(0x0800ac44u); /* movs r1, #0xb */
    s->r[1]=nz(s,0xbu);
    goto L_0800ac46;
L_0800ac46: STEP(0x0800ac46u); /* b #0x800ac56 */
    goto L_0800ac56;
L_0800ac48: STEP(0x0800ac48u); /* uxtb r0, r5 */
    s->r[0]=(uint8_t)(s->r[5]);
    goto L_0800ac4a;
L_0800ac4a: STEP(0x0800ac4au); /* movs r1, #1 */
    s->r[1]=nz(s,0x1u);
    goto L_0800ac4c;
L_0800ac4c: STEP(0x0800ac4cu); /* b #0x800ac56 */
    goto L_0800ac56;
L_0800ac4e: STEP(0x0800ac4eu); /* mov r0, r4 */
    s->r[0]=s->r[4];
    goto L_0800ac50;
L_0800ac50: STEP(0x0800ac50u); /* subs r0, #0x39 */
    s->r[0]=sub(s,s->r[0],0x39u);
    goto L_0800ac52;
L_0800ac52: STEP(0x0800ac52u); /* uxtb r0, r0 */
    s->r[0]=(uint8_t)(s->r[0]);
    goto L_0800ac54;
L_0800ac54: STEP(0x0800ac54u); /* movs r1, #2 */
    s->r[1]=nz(s,0x2u);
    goto L_0800ac56;
L_0800ac56: STEP(0x0800ac56u); /* bl #0x8009e30 */
    s->r[14]=0x0800ac5bu;
    if(!s->call){s->fault=-2;s->fault_address=0x08009e30u;return -2;}
    s->r[15]=0x08009e30u;
    temp=(uint32_t)s->call(s->user,0x08009e30u,s);
    if(temp){s->pc=0x0800ac5au;return 1;}
    goto L_0800ac5a;
L_0800ac5a: STEP(0x0800ac5au); /* adds r4, r4, #1 */
    s->r[4]=add(s,s->r[4],0x1u);
    goto L_0800ac5c;
L_0800ac5c: STEP(0x0800ac5cu); /* uxth r4, r4 */
    s->r[4]=(uint16_t)(s->r[4]);
    goto L_0800ac5e;
L_0800ac5e: STEP(0x0800ac5eu); /* cmp r4, #0x5d */
    (void)sub(s,s->r[4],0x5du);
    goto L_0800ac60;
L_0800ac60: STEP(0x0800ac60u); /* bhs #0x800ac64 */
    if(C)goto L_0800ac64;
    goto L_0800ac62;
L_0800ac62: STEP(0x0800ac62u); /* b #0x800a7fa */
    goto L_0800a7fa;

    /* Global mode processing */
L_0800ac64: STEP(0x0800ac64u); /* ldr r5, [pc, #0x360] */
    s->r[5]=read_mem(s,(0x800ac68u + 0x360u),4);
    goto L_0800ac66;
L_0800ac66: STEP(0x0800ac66u); /* ldrh r0, [r5, #0x24] */
    s->r[0]=read_mem(s,(s->r[5] + 0x24u),2);
    goto L_0800ac68;
L_0800ac68: STEP(0x0800ac68u); /* cmp r0, #2 */
    (void)sub(s,s->r[0],0x2u);
    goto L_0800ac6a;
L_0800ac6a: STEP(0x0800ac6au); /* bne #0x800ac92 */
    if(!Z)goto L_0800ac92;
    goto L_0800ac6c;
L_0800ac6c: STEP(0x0800ac6cu); /* ldrh r1, [r5, #0x2e] */
    s->r[1]=read_mem(s,(s->r[5] + 0x2eu),2);
    goto L_0800ac6e;
L_0800ac6e: STEP(0x0800ac6eu); /* ldrh r0, [r5, #0x30] */
    s->r[0]=read_mem(s,(s->r[5] + 0x30u),2);
    goto L_0800ac70;
L_0800ac70: STEP(0x0800ac70u); /* cmn r1, r0 */
    (void)add(s,s->r[1],s->r[0]);
    goto L_0800ac72;
L_0800ac72: STEP(0x0800ac72u); /* beq #0x800ac92 */
    if(Z)goto L_0800ac92;
    goto L_0800ac74;
L_0800ac74: STEP(0x0800ac74u); /* ldrb r0, [r5, #1] */
    s->r[0]=read_mem(s,(s->r[5] + 0x1u),1);
    goto L_0800ac76;
L_0800ac76: STEP(0x0800ac76u); /* cmp r0, #0xc */
    (void)sub(s,s->r[0],0xcu);
    goto L_0800ac78;
L_0800ac78: STEP(0x0800ac78u); /* bhs #0x800ac92 */
    if(C)goto L_0800ac92;
    goto L_0800ac7a;
L_0800ac7a: STEP(0x0800ac7au); /* ldrh r1, [r5, #0x22] */
    s->r[1]=read_mem(s,(s->r[5] + 0x22u),2);
    goto L_0800ac7c;
L_0800ac7c: STEP(0x0800ac7cu); /* cmp r1, #0 */
    (void)sub(s,s->r[1],0x0u);
    goto L_0800ac7e;
L_0800ac7e: STEP(0x0800ac7eu); /* beq #0x800ac82 */
    if(Z)goto L_0800ac82;
    goto L_0800ac80;
L_0800ac80: STEP(0x0800ac80u); /* movs r1, #2 */
    s->r[1]=nz(s,0x2u);
    goto L_0800ac82;
L_0800ac82: STEP(0x0800ac82u); /* movs r2, #0x34 */
    s->r[2]=nz(s,0x34u);
    goto L_0800ac84;
L_0800ac84: STEP(0x0800ac84u); /* ldr r3, [pc, #0x344] */
    s->r[3]=read_mem(s,(0x800ac88u + 0x344u),4);
    goto L_0800ac86;
L_0800ac86: STEP(0x0800ac86u); /* muls r2, r0, r2 */
    s->r[2]=nz(s,(s->r[0])*(s->r[2]));
    goto L_0800ac88;
L_0800ac88: STEP(0x0800ac88u); /* adds r2, r2, r3 */
    s->r[2]=add(s,s->r[2],s->r[3]);
    goto L_0800ac8a;
L_0800ac8a: STEP(0x0800ac8au); /* adds r2, #0x20 */
    s->r[2]=add(s,s->r[2],0x20u);
    goto L_0800ac8c;
L_0800ac8c: STEP(0x0800ac8cu); /* strb r1, [r2, #0xd] */
    write_mem(s,(s->r[2] + 0xdu),1,s->r[1]);
    goto L_0800ac8e;
L_0800ac8e: STEP(0x0800ac8eu); /* bl #0x8004b10 */
    s->r[14]=0x0800ac93u;
    if(!s->call){s->fault=-2;s->fault_address=0x08004b10u;return -2;}
    s->r[15]=0x08004b10u;
    temp=(uint32_t)s->call(s->user,0x08004b10u,s);
    if(temp){s->pc=0x0800ac92u;return 1;}
    goto L_0800ac92;
L_0800ac92: STEP(0x0800ac92u); /* ldr r0, [pc, #0x33c] */
    s->r[0]=read_mem(s,(0x800ac94u + 0x33cu),4);
    goto L_0800ac94;
L_0800ac94: STEP(0x0800ac94u); /* ldrh r0, [r0, #0xe] */
    s->r[0]=read_mem(s,(s->r[0] + 0xeu),2);
    goto L_0800ac96;
L_0800ac96: STEP(0x0800ac96u); /* cmp r0, #0 */
    (void)sub(s,s->r[0],0x0u);
    goto L_0800ac98;
L_0800ac98: STEP(0x0800ac98u); /* bne #0x800aca0 */
    if(!Z)goto L_0800aca0;
    goto L_0800ac9a;
L_0800ac9a: STEP(0x0800ac9au); /* ldr r0, [pc, #0x334] */
    s->r[0]=read_mem(s,(0x800ac9cu + 0x334u),4);
    goto L_0800ac9c;
L_0800ac9c: STEP(0x0800ac9cu); /* movs r1, #0x96 */
    s->r[1]=nz(s,0x96u);
    goto L_0800ac9e;
L_0800ac9e: STEP(0x0800ac9eu); /* strh r1, [r0, #0xe] */
    write_mem(s,(s->r[0] + 0xeu),2,s->r[1]);
    goto L_0800aca0;
L_0800aca0: STEP(0x0800aca0u); /* ldr r0, [sp, #0x2c] */
    s->r[0]=read_mem(s,(s->r[13] + 0x2cu),4);
    goto L_0800aca2;
L_0800aca2: STEP(0x0800aca2u); /* ldrb r0, [r0, #0x16] */
    s->r[0]=read_mem(s,(s->r[0] + 0x16u),1);
    goto L_0800aca4;
L_0800aca4: STEP(0x0800aca4u); /* cmp r0, #0 */
    (void)sub(s,s->r[0],0x0u);
    goto L_0800aca6;
L_0800aca6: STEP(0x0800aca6u); /* beq #0x800acac */
    if(Z)goto L_0800acac;
    goto L_0800aca8;
L_0800aca8: STEP(0x0800aca8u); /* bl #0x800cc80 */
    s->r[14]=0x0800acadu;
    if(!s->call){s->fault=-2;s->fault_address=0x0800cc80u;return -2;}
    s->r[15]=0x0800cc80u;
    temp=(uint32_t)s->call(s->user,0x0800cc80u,s);
    if(temp){s->pc=0x0800acacu;return 1;}
    goto L_0800acac;
L_0800acac: STEP(0x0800acacu); /* movs r4, #0 */
    s->r[4]=nz(s,0x0u);
    goto L_0800acae;
L_0800acae: STEP(0x0800acaeu); /* movs r1, #0x96 */
    s->r[1]=nz(s,0x96u);
    goto L_0800acb0;
L_0800acb0: STEP(0x0800acb0u); /* ldr r0, [sp, #0x1c] */
    s->r[0]=read_mem(s,(s->r[13] + 0x1cu),4);
    goto L_0800acb2;
L_0800acb2: STEP(0x0800acb2u); /* bl #0x80040e8 */
    s->r[14]=0x0800acb7u;
    if(!s->call){s->fault=-2;s->fault_address=0x080040e8u;return -2;}
    s->r[15]=0x080040e8u;
    temp=(uint32_t)s->call(s->user,0x080040e8u,s);
    if(temp){s->pc=0x0800acb6u;return 1;}
    goto L_0800acb6;
L_0800acb6: STEP(0x0800acb6u); /* str r1, [sp, #0x40] */
    write_mem(s,(s->r[13] + 0x40u),4,s->r[1]);
    goto L_0800acb8;

    /* Twelve channel state updates */
L_0800acb8: STEP(0x0800acb8u); /* mov r0, r4 */
    s->r[0]=s->r[4];
    goto L_0800acba;
L_0800acba: STEP(0x0800acbau); /* movs r1, #0x34 */
    s->r[1]=nz(s,0x34u);
    goto L_0800acbc;
L_0800acbc: STEP(0x0800acbcu); /* muls r0, r1, r0 */
    s->r[0]=nz(s,(s->r[1])*(s->r[0]));
    goto L_0800acbe;
L_0800acbe: STEP(0x0800acbeu); /* ldr r1, [pc, #0x30c] */
    s->r[1]=read_mem(s,(0x800acc0u + 0x30cu),4);
    goto L_0800acc0;
L_0800acc0: STEP(0x0800acc0u); /* str r0, [sp, #0x18] */
    write_mem(s,(s->r[13] + 0x18u),4,s->r[0]);
    goto L_0800acc2;
L_0800acc2: STEP(0x0800acc2u); /* adds r5, r0, r1 */
    s->r[5]=add(s,s->r[0],s->r[1]);
    goto L_0800acc4;
L_0800acc4: STEP(0x0800acc4u); /* ldr r7, [r1, r0] */
    s->r[7]=read_mem(s,(s->r[1] + s->r[0]),4);
    goto L_0800acc6;
L_0800acc6: STEP(0x0800acc6u); /* mov r0, r5 */
    s->r[0]=s->r[5];
    goto L_0800acc8;
L_0800acc8: STEP(0x0800acc8u); /* ldrh r6, [r5, #4] */
    s->r[6]=read_mem(s,(s->r[5] + 0x4u),2);
    goto L_0800acca;
L_0800acca: STEP(0x0800accau); /* adds r0, #0x20 */
    s->r[0]=add(s,s->r[0],0x20u);
    goto L_0800accc;
L_0800accc: STEP(0x0800acccu); /* str r0, [sp, #0x20] */
    write_mem(s,(s->r[13] + 0x20u),4,s->r[0]);
    goto L_0800acce;
L_0800acce: STEP(0x0800acceu); /* ldrb r1, [r0, #0xc] */
    s->r[1]=read_mem(s,(s->r[0] + 0xcu),1);
    goto L_0800acd0;
L_0800acd0: STEP(0x0800acd0u); /* str r1, [sp, #0x38] */
    write_mem(s,(s->r[13] + 0x38u),4,s->r[1]);
    goto L_0800acd2;
L_0800acd2: STEP(0x0800acd2u); /* ldrb r0, [r0, #0xe] */
    s->r[0]=read_mem(s,(s->r[0] + 0xeu),1);
    goto L_0800acd4;
L_0800acd4: STEP(0x0800acd4u); /* cmp r0, #1 */
    (void)sub(s,s->r[0],0x1u);
    goto L_0800acd6;
L_0800acd6: STEP(0x0800acd6u); /* bne #0x800ace4 */
    if(!Z)goto L_0800ace4;
    goto L_0800acd8;
L_0800acd8: STEP(0x0800acd8u); /* uxtb r0, r4 */
    s->r[0]=(uint8_t)(s->r[4]);
    goto L_0800acda;
L_0800acda: STEP(0x0800acdau); /* bl #0x800a5b0 */
    s->r[14]=0x0800acdfu;
    if(!s->call){s->fault=-2;s->fault_address=0x0800a5b0u;return -2;}
    s->r[15]=0x0800a5b0u;
    temp=(uint32_t)s->call(s->user,0x0800a5b0u,s);
    if(temp){s->pc=0x0800acdeu;return 1;}
    goto L_0800acde;
L_0800acde: STEP(0x0800acdeu); /* ldr r1, [sp, #0x20] */
    s->r[1]=read_mem(s,(s->r[13] + 0x20u),4);
    goto L_0800ace0;
L_0800ace0: STEP(0x0800ace0u); /* movs r0, #0 */
    s->r[0]=nz(s,0x0u);
    goto L_0800ace2;
L_0800ace2: STEP(0x0800ace2u); /* strb r0, [r1, #0xe] */
    write_mem(s,(s->r[1] + 0xeu),1,s->r[0]);
    goto L_0800ace4;
L_0800ace4: STEP(0x0800ace4u); /* ldr r1, [sp, #0x40] */
    s->r[1]=read_mem(s,(s->r[13] + 0x40u),4);
    goto L_0800ace6;
L_0800ace6: STEP(0x0800ace6u); /* cmp r1, #0 */
    (void)sub(s,s->r[1],0x0u);
    goto L_0800ace8;
L_0800ace8: STEP(0x0800ace8u); /* bne #0x800acf0 */
    if(!Z)goto L_0800acf0;
    goto L_0800acea;
L_0800acea: STEP(0x0800aceau); /* uxtb r0, r4 */
    s->r[0]=(uint8_t)(s->r[4]);
    goto L_0800acec;
L_0800acec: STEP(0x0800acecu); /* bl #0x800a24c */
    s->r[14]=0x0800acf1u;
    if(!s->call){s->fault=-2;s->fault_address=0x0800a24cu;return -2;}
    s->r[15]=0x0800a24cu;
    temp=(uint32_t)s->call(s->user,0x0800a24cu,s);
    if(temp){s->pc=0x0800acf0u;return 1;}
    goto L_0800acf0;
L_0800acf0: STEP(0x0800acf0u); /* ldr r0, [pc, #0x2d4] */
    s->r[0]=read_mem(s,(0x800acf4u + 0x2d4u),4);
    goto L_0800acf2;
L_0800acf2: STEP(0x0800acf2u); /* ldrb r0, [r0] */
    s->r[0]=read_mem(s,(s->r[0]),1);
    goto L_0800acf4;
L_0800acf4: STEP(0x0800acf4u); /* cmp r0, #0x20 */
    (void)sub(s,s->r[0],0x20u);
    goto L_0800acf6;
L_0800acf6: STEP(0x0800acf6u); /* bne #0x800ad08 */
    if(!Z)goto L_0800ad08;
    goto L_0800acf8;
L_0800acf8: STEP(0x0800acf8u); /* ldr r0, [pc, #0x2cc] */
    s->r[0]=read_mem(s,(0x800acfcu + 0x2ccu),4);
    goto L_0800acfa;
L_0800acfa: STEP(0x0800acfau); /* ldrb r0, [r0, #1] */
    s->r[0]=read_mem(s,(s->r[0] + 0x1u),1);
    goto L_0800acfc;
L_0800acfc: STEP(0x0800acfcu); /* cmp r0, r4 */
    (void)sub(s,s->r[0],s->r[4]);
    goto L_0800acfe;
L_0800acfe: STEP(0x0800acfeu); /* bne #0x800ad08 */
    if(!Z)goto L_0800ad08;
    goto L_0800ad00;
L_0800ad00: STEP(0x0800ad00u); /* uxtb r0, r4 */
    s->r[0]=(uint8_t)(s->r[4]);
    goto L_0800ad02;
L_0800ad02: STEP(0x0800ad02u); /* bl #0x8008278 */
    s->r[14]=0x0800ad07u;
    if(!s->call){s->fault=-2;s->fault_address=0x08008278u;return -2;}
    s->r[15]=0x08008278u;
    temp=(uint32_t)s->call(s->user,0x08008278u,s);
    if(temp){s->pc=0x0800ad06u;return 1;}
    goto L_0800ad06;
L_0800ad06: STEP(0x0800ad06u); /* uxth r6, r0 */
    s->r[6]=(uint16_t)(s->r[0]);
    goto L_0800ad08;
L_0800ad08: STEP(0x0800ad08u); /* cmp r7, #0 */
    (void)sub(s,s->r[7],0x0u);
    goto L_0800ad0a;
L_0800ad0a: STEP(0x0800ad0au); /* beq #0x800ae08 */
    if(Z)goto L_0800ae08;
    goto L_0800ad0c;
L_0800ad0c: STEP(0x0800ad0cu); /* uxtb r0, r4 */
    s->r[0]=(uint8_t)(s->r[4]);
    goto L_0800ad0e;
L_0800ad0e: STEP(0x0800ad0eu); /* bl #0x8008278 */
    s->r[14]=0x0800ad13u;
    if(!s->call){s->fault=-2;s->fault_address=0x08008278u;return -2;}
    s->r[15]=0x08008278u;
    temp=(uint32_t)s->call(s->user,0x08008278u,s);
    if(temp){s->pc=0x0800ad12u;return 1;}
    goto L_0800ad12;
L_0800ad12: STEP(0x0800ad12u); /* uxth r6, r0 */
    s->r[6]=(uint16_t)(s->r[0]);
    goto L_0800ad14;
L_0800ad14: STEP(0x0800ad14u); /* ldr r1, [sp, #0x20] */
    s->r[1]=read_mem(s,(s->r[13] + 0x20u),4);
    goto L_0800ad16;
L_0800ad16: STEP(0x0800ad16u); /* ldr r0, [sp, #8] */
    s->r[0]=read_mem(s,(s->r[13] + 0x8u),4);
    goto L_0800ad18;
L_0800ad18: STEP(0x0800ad18u); /* ldrb r1, [r1, #0xf] */
    s->r[1]=read_mem(s,(s->r[1] + 0xfu),1);
    goto L_0800ad1a;
L_0800ad1a: STEP(0x0800ad1au); /* muls r0, r6, r0 */
    s->r[0]=nz(s,(s->r[6])*(s->r[0]));
    goto L_0800ad1c;
L_0800ad1c: STEP(0x0800ad1cu); /* cmp r1, #0 */
    (void)sub(s,s->r[1],0x0u);
    goto L_0800ad1e;
L_0800ad1e: STEP(0x0800ad1eu); /* ldr r1, [r5, #8] */
    s->r[1]=read_mem(s,(s->r[5] + 0x8u),4);
    goto L_0800ad20;
L_0800ad20: STEP(0x0800ad20u); /* beq #0x800ad26 */
    if(Z)goto L_0800ad26;
    goto L_0800ad22;
L_0800ad22: STEP(0x0800ad22u); /* adds r0, r1, r0 */
    s->r[0]=add(s,s->r[1],s->r[0]);
    goto L_0800ad24;
L_0800ad24: STEP(0x0800ad24u); /* b #0x800ad30 */
    goto L_0800ad30;
L_0800ad26: STEP(0x0800ad26u); /* cmp r1, r0 */
    (void)sub(s,s->r[1],s->r[0]);
    goto L_0800ad28;
L_0800ad28: STEP(0x0800ad28u); /* bhs #0x800ad2e */
    if(C)goto L_0800ad2e;
    goto L_0800ad2a;
L_0800ad2a: STEP(0x0800ad2au); /* movs r0, #0 */
    s->r[0]=nz(s,0x0u);
    goto L_0800ad2c;
L_0800ad2c: STEP(0x0800ad2cu); /* b #0x800ad30 */
    goto L_0800ad30;
L_0800ad2e: STEP(0x0800ad2eu); /* subs r0, r1, r0 */
    s->r[0]=sub(s,s->r[1],s->r[0]);
    goto L_0800ad30;
L_0800ad30: STEP(0x0800ad30u); /* str r0, [r5, #8] */
    write_mem(s,(s->r[5] + 0x8u),4,s->r[0]);
    goto L_0800ad32;
L_0800ad32: STEP(0x0800ad32u); /* movs r1, #3 */
    s->r[1]=nz(s,0x3u);
    goto L_0800ad34;
L_0800ad34: STEP(0x0800ad34u); /* mov r0, r7 */
    s->r[0]=s->r[7];
    goto L_0800ad36;
L_0800ad36: STEP(0x0800ad36u); /* bl #0x80040e8 */
    s->r[14]=0x0800ad3bu;
    if(!s->call){s->fault=-2;s->fault_address=0x080040e8u;return -2;}
    s->r[15]=0x080040e8u;
    temp=(uint32_t)s->call(s->user,0x080040e8u,s);
    if(temp){s->pc=0x0800ad3au;return 1;}
    goto L_0800ad3a;
L_0800ad3a: STEP(0x0800ad3au); /* cmp r1, #0 */
    (void)sub(s,s->r[1],0x0u);
    goto L_0800ad3c;
L_0800ad3c: STEP(0x0800ad3cu); /* bne #0x800ad4e */
    if(!Z)goto L_0800ad4e;
    goto L_0800ad3e;
L_0800ad3e: STEP(0x0800ad3eu); /* uxtb r0, r4 */
    s->r[0]=(uint8_t)(s->r[4]);
    goto L_0800ad40;
L_0800ad40: STEP(0x0800ad40u); /* bl #0x8009468 */
    s->r[14]=0x0800ad45u;
    if(!s->call){s->fault=-2;s->fault_address=0x08009468u;return -2;}
    s->r[15]=0x08009468u;
    temp=(uint32_t)s->call(s->user,0x08009468u,s);
    if(temp){s->pc=0x0800ad44u;return 1;}
    goto L_0800ad44;
L_0800ad44: STEP(0x0800ad44u); /* strh r0, [r5, #0x10] */
    write_mem(s,(s->r[5] + 0x10u),2,s->r[0]);
    goto L_0800ad46;
L_0800ad46: STEP(0x0800ad46u); /* uxtb r0, r4 */
    s->r[0]=(uint8_t)(s->r[4]);
    goto L_0800ad48;
L_0800ad48: STEP(0x0800ad48u); /* bl #0x8007840 */
    s->r[14]=0x0800ad4du;
    if(!s->call){s->fault=-2;s->fault_address=0x08007840u;return -2;}
    s->r[15]=0x08007840u;
    temp=(uint32_t)s->call(s->user,0x08007840u,s);
    if(temp){s->pc=0x0800ad4cu;return 1;}
    goto L_0800ad4c;
L_0800ad4c: STEP(0x0800ad4cu); /* strh r0, [r5, #0x12] */
    write_mem(s,(s->r[5] + 0x12u),2,s->r[0]);
    goto L_0800ad4e;
L_0800ad4e: STEP(0x0800ad4eu); /* uxtb r0, r4 */
    s->r[0]=(uint8_t)(s->r[4]);
    goto L_0800ad50;
L_0800ad50: STEP(0x0800ad50u); /* bl #0x8009fec */
    s->r[14]=0x0800ad55u;
    if(!s->call){s->fault=-2;s->fault_address=0x08009fecu;return -2;}
    s->r[15]=0x08009fecu;
    temp=(uint32_t)s->call(s->user,0x08009fecu,s);
    if(temp){s->pc=0x0800ad54u;return 1;}
    goto L_0800ad54;
L_0800ad54: STEP(0x0800ad54u); /* cmp r0, #0 */
    (void)sub(s,s->r[0],0x0u);
    goto L_0800ad56;
L_0800ad56: STEP(0x0800ad56u); /* beq #0x800ae36 */
    if(Z)goto L_0800ae36;
    goto L_0800ad58;
L_0800ad58: STEP(0x0800ad58u); /* ldr r0, [sp, #8] */
    s->r[0]=read_mem(s,(s->r[13] + 0x8u),4);
    goto L_0800ad5a;
L_0800ad5a: STEP(0x0800ad5au); /* cmp r7, r0 */
    (void)sub(s,s->r[7],s->r[0]);
    goto L_0800ad5c;
L_0800ad5c: STEP(0x0800ad5cu); /* bls #0x800ae36 */
    if(!C||Z)goto L_0800ae36;
    goto L_0800ad5e;
L_0800ad5e: STEP(0x0800ad5eu); /* ldr r0, [r5, #8] */
    s->r[0]=read_mem(s,(s->r[5] + 0x8u),4);
    goto L_0800ad60;
L_0800ad60: STEP(0x0800ad60u); /* cmp r0, #0 */
    (void)sub(s,s->r[0],0x0u);
    goto L_0800ad62;
L_0800ad62: STEP(0x0800ad62u); /* beq #0x800ad6c */
    if(Z)goto L_0800ad6c;
    goto L_0800ad64;
L_0800ad64: STEP(0x0800ad64u); /* ldr r1, [pc, #0x26c] */
    s->r[1]=read_mem(s,(0x800ad68u + 0x26cu),4);
    goto L_0800ad66;
L_0800ad66: STEP(0x0800ad66u); /* bl #0x80040e8 */
    s->r[14]=0x0800ad6bu;
    if(!s->call){s->fault=-2;s->fault_address=0x080040e8u;return -2;}
    s->r[15]=0x080040e8u;
    temp=(uint32_t)s->call(s->user,0x080040e8u,s);
    if(temp){s->pc=0x0800ad6au;return 1;}
    goto L_0800ad6a;
L_0800ad6a: STEP(0x0800ad6au); /* strh r0, [r5, #6] */
    write_mem(s,(s->r[5] + 0x6u),2,s->r[0]);
    goto L_0800ad6c;
L_0800ad6c: STEP(0x0800ad6cu); /* uxtb r0, r4 */
    s->r[0]=(uint8_t)(s->r[4]);
    goto L_0800ad6e;
L_0800ad6e: STEP(0x0800ad6eu); /* bl #0x800a090 */
    s->r[14]=0x0800ad73u;
    if(!s->call){s->fault=-2;s->fault_address=0x0800a090u;return -2;}
    s->r[15]=0x0800a090u;
    temp=(uint32_t)s->call(s->user,0x0800a090u,s);
    if(temp){s->pc=0x0800ad72u;return 1;}
    goto L_0800ad72;
L_0800ad72: STEP(0x0800ad72u); /* strh r0, [r5, #0xe] */
    write_mem(s,(s->r[5] + 0xeu),2,s->r[0]);
    goto L_0800ad74;
L_0800ad74: STEP(0x0800ad74u); /* ldr r0, [sp, #8] */
    s->r[0]=read_mem(s,(s->r[13] + 0x8u),4);
    goto L_0800ad76;
L_0800ad76: STEP(0x0800ad76u); /* movs r1, #0x3c */
    s->r[1]=nz(s,0x3cu);
    goto L_0800ad78;
L_0800ad78: STEP(0x0800ad78u); /* subs r7, r7, r0 */
    s->r[7]=sub(s,s->r[7],s->r[0]);
    goto L_0800ad7a;
L_0800ad7a: STEP(0x0800ad7au); /* mov r0, r7 */
    s->r[0]=s->r[7];
    goto L_0800ad7c;
L_0800ad7c: STEP(0x0800ad7cu); /* bl #0x80040e8 */
    s->r[14]=0x0800ad81u;
    if(!s->call){s->fault=-2;s->fault_address=0x080040e8u;return -2;}
    s->r[15]=0x080040e8u;
    temp=(uint32_t)s->call(s->user,0x080040e8u,s);
    if(temp){s->pc=0x0800ad80u;return 1;}
    goto L_0800ad80;
L_0800ad80: STEP(0x0800ad80u); /* cmp r1, #0 */
    (void)sub(s,s->r[1],0x0u);
    goto L_0800ad82;
L_0800ad82: STEP(0x0800ad82u); /* bne #0x800ad8a */
    if(!Z)goto L_0800ad8a;
    goto L_0800ad84;
L_0800ad84: STEP(0x0800ad84u); /* uxtb r0, r4 */
    s->r[0]=(uint8_t)(s->r[4]);
    goto L_0800ad86;
L_0800ad86: STEP(0x0800ad86u); /* bl #0x800a5b0 */
    s->r[14]=0x0800ad8bu;
    if(!s->call){s->fault=-2;s->fault_address=0x0800a5b0u;return -2;}
    s->r[15]=0x0800a5b0u;
    temp=(uint32_t)s->call(s->user,0x0800a5b0u,s);
    if(temp){s->pc=0x0800ad8au;return 1;}
    goto L_0800ad8a;
L_0800ad8a: STEP(0x0800ad8au); /* ldr r0, [pc, #0x23c] */
    s->r[0]=read_mem(s,(0x800ad8cu + 0x23cu),4);
    goto L_0800ad8c;
L_0800ad8c: STEP(0x0800ad8cu); /* ldrh r0, [r0, #0x12] */
    s->r[0]=read_mem(s,(s->r[0] + 0x12u),2);
    goto L_0800ad8e;
L_0800ad8e: STEP(0x0800ad8eu); /* lsls r1, r0, #1 */
    s->r[1]=lsl(s,s->r[0],0x1u);
    goto L_0800ad90;
L_0800ad90: STEP(0x0800ad90u); /* adds r1, r0, r1 */
    s->r[1]=add(s,s->r[0],s->r[1]);
    goto L_0800ad92;
L_0800ad92: STEP(0x0800ad92u); /* cmp r1, r6 */
    (void)sub(s,s->r[1],s->r[6]);
    goto L_0800ad94;
L_0800ad94: STEP(0x0800ad94u); /* bhi #0x800ad9e */
    if(C&&!Z)goto L_0800ad9e;
    goto L_0800ad96;
L_0800ad96: STEP(0x0800ad96u); /* uxtb r0, r4 */
    s->r[0]=(uint8_t)(s->r[4]);
    goto L_0800ad98;
L_0800ad98: STEP(0x0800ad98u); /* bl #0x8008224 */
    s->r[14]=0x0800ad9du;
    if(!s->call){s->fault=-2;s->fault_address=0x08008224u;return -2;}
    s->r[15]=0x08008224u;
    temp=(uint32_t)s->call(s->user,0x08008224u,s);
    if(temp){s->pc=0x0800ad9cu;return 1;}
    goto L_0800ad9c;
L_0800ad9c: STEP(0x0800ad9cu); /* b #0x800adf6 */
    goto L_0800adf6;
L_0800ad9e: STEP(0x0800ad9eu); /* cmp r0, r6 */
    (void)sub(s,s->r[0],s->r[6]);
    goto L_0800ada0;
L_0800ada0: STEP(0x0800ada0u); /* bhi #0x800adc6 */
    if(C&&!Z)goto L_0800adc6;
    goto L_0800ada2;
L_0800ada2: STEP(0x0800ada2u); /* ldr r0, [pc, #0x22c] */
    s->r[0]=read_mem(s,(0x800ada4u + 0x22cu),4);
    goto L_0800ada4;
L_0800ada4: STEP(0x0800ada4u); /* lsls r1, r4, #1 */
    s->r[1]=lsl(s,s->r[4],0x1u);
    goto L_0800ada6;
L_0800ada6: STEP(0x0800ada6u); /* adds r0, r1, r0 */
    s->r[0]=add(s,s->r[1],s->r[0]);
    goto L_0800ada8;
L_0800ada8: STEP(0x0800ada8u); /* ldrh r1, [r0, #0x2a] */
    s->r[1]=read_mem(s,(s->r[0] + 0x2au),2);
    goto L_0800adaa;
L_0800adaa: STEP(0x0800adaau); /* cmp r1, #0 */
    (void)sub(s,s->r[1],0x0u);
    goto L_0800adac;
L_0800adac: STEP(0x0800adacu); /* beq #0x800adb4 */
    if(Z)goto L_0800adb4;
    goto L_0800adae;
L_0800adae: STEP(0x0800adaeu); /* ldr r1, [sp, #0x38] */
    s->r[1]=read_mem(s,(s->r[13] + 0x38u),4);
    goto L_0800adb0;
L_0800adb0: STEP(0x0800adb0u); /* cmp r1, #1 */
    (void)sub(s,s->r[1],0x1u);
    goto L_0800adb2;
L_0800adb2: STEP(0x0800adb2u); /* beq #0x800adf6 */
    if(Z)goto L_0800adf6;
    goto L_0800adb4;
L_0800adb4: STEP(0x0800adb4u); /* movs r1, #2 */
    s->r[1]=nz(s,0x2u);
    goto L_0800adb6;
L_0800adb6: STEP(0x0800adb6u); /* strh r1, [r0, #0x2a] */
    write_mem(s,(s->r[0] + 0x2au),2,s->r[1]);
    goto L_0800adb8;
L_0800adb8: STEP(0x0800adb8u); /* movs r0, #1 */
    s->r[0]=nz(s,0x1u);
    goto L_0800adba;
L_0800adba: STEP(0x0800adbau); /* str r0, [sp, #0x38] */
    write_mem(s,(s->r[13] + 0x38u),4,s->r[0]);
    goto L_0800adbc;
L_0800adbc: STEP(0x0800adbcu); /* mov r0, r6 */
    s->r[0]=s->r[6];
    goto L_0800adbe;
L_0800adbe: STEP(0x0800adbeu); /* bl #0x8009fa4 */
    s->r[14]=0x0800adc3u;
    if(!s->call){s->fault=-2;s->fault_address=0x08009fa4u;return -2;}
    s->r[15]=0x08009fa4u;
    temp=(uint32_t)s->call(s->user,0x08009fa4u,s);
    if(temp){s->pc=0x0800adc2u;return 1;}
    goto L_0800adc2;
L_0800adc2: STEP(0x0800adc2u); /* strb r0, [r5, #0x14] */
    write_mem(s,(s->r[5] + 0x14u),1,s->r[0]);
    goto L_0800adc4;
L_0800adc4: STEP(0x0800adc4u); /* b #0x800adf6 */
    goto L_0800adf6;
L_0800adc6: STEP(0x0800adc6u); /* bl #0x800a068 */
    s->r[14]=0x0800adcbu;
    if(!s->call){s->fault=-2;s->fault_address=0x0800a068u;return -2;}
    s->r[15]=0x0800a068u;
    temp=(uint32_t)s->call(s->user,0x0800a068u,s);
    if(temp){s->pc=0x0800adcau;return 1;}
    goto L_0800adca;
L_0800adca: STEP(0x0800adcau); /* cmp r0, #1 */
    (void)sub(s,s->r[0],0x1u);
    goto L_0800adcc;
L_0800adcc: STEP(0x0800adccu); /* bne #0x800adf6 */
    if(!Z)goto L_0800adf6;
    goto L_0800adce;
L_0800adce: STEP(0x0800adceu); /* ldrb r0, [r5, #0x15] */
    s->r[0]=read_mem(s,(s->r[5] + 0x15u),1);
    goto L_0800add0;
L_0800add0: STEP(0x0800add0u); /* lsls r1, r0, #1 */
    s->r[1]=lsl(s,s->r[0],0x1u);
    goto L_0800add2;
L_0800add2: STEP(0x0800add2u); /* ldr r0, [pc, #0x1f4] */
    s->r[0]=read_mem(s,(0x800add4u + 0x1f4u),4);
    goto L_0800add4;
L_0800add4: STEP(0x0800add4u); /* adds r0, r1, r0 */
    s->r[0]=add(s,s->r[1],s->r[0]);
    goto L_0800add6;
L_0800add6: STEP(0x0800add6u); /* ldrh r0, [r0, #0xc] */
    s->r[0]=read_mem(s,(s->r[0] + 0xcu),2);
    goto L_0800add8;
L_0800add8: STEP(0x0800add8u); /* cmp r0, r6 */
    (void)sub(s,s->r[0],s->r[6]);
    goto L_0800adda;
L_0800adda: STEP(0x0800addau); /* bhi #0x800adf6 */
    if(C&&!Z)goto L_0800adf6;
    goto L_0800addc;
L_0800addc: STEP(0x0800addcu); /* ldr r0, [pc, #0x1f0] */
    s->r[0]=read_mem(s,(0x800ade0u + 0x1f0u),4);
    goto L_0800adde;
L_0800adde: STEP(0x0800addeu); /* lsls r1, r4, #1 */
    s->r[1]=lsl(s,s->r[4],0x1u);
    goto L_0800ade0;
L_0800ade0: STEP(0x0800ade0u); /* adds r0, r1, r0 */
    s->r[0]=add(s,s->r[1],s->r[0]);
    goto L_0800ade2;
L_0800ade2: STEP(0x0800ade2u); /* ldrh r1, [r0, #0x2a] */
    s->r[1]=read_mem(s,(s->r[0] + 0x2au),2);
    goto L_0800ade4;
L_0800ade4: STEP(0x0800ade4u); /* cmp r1, #0 */
    (void)sub(s,s->r[1],0x0u);
    goto L_0800ade6;
L_0800ade6: STEP(0x0800ade6u); /* beq #0x800adee */
    if(Z)goto L_0800adee;
    goto L_0800ade8;
L_0800ade8: STEP(0x0800ade8u); /* ldr r1, [sp, #0x38] */
    s->r[1]=read_mem(s,(s->r[13] + 0x38u),4);
    goto L_0800adea;
L_0800adea: STEP(0x0800adeau); /* cmp r1, #0 */
    (void)sub(s,s->r[1],0x0u);
    goto L_0800adec;
L_0800adec: STEP(0x0800adecu); /* beq #0x800adf6 */
    if(Z)goto L_0800adf6;
    goto L_0800adee;
L_0800adee: STEP(0x0800adeeu); /* movs r1, #2 */
    s->r[1]=nz(s,0x2u);
    goto L_0800adf0;
L_0800adf0: STEP(0x0800adf0u); /* strh r1, [r0, #0x2a] */
    write_mem(s,(s->r[0] + 0x2au),2,s->r[1]);
    goto L_0800adf2;
L_0800adf2: STEP(0x0800adf2u); /* movs r0, #0 */
    s->r[0]=nz(s,0x0u);
    goto L_0800adf4;
L_0800adf4: STEP(0x0800adf4u); /* str r0, [sp, #0x38] */
    write_mem(s,(s->r[13] + 0x38u),4,s->r[0]);
    goto L_0800adf6;
L_0800adf6: STEP(0x0800adf6u); /* ldr r0, [pc, #0x1d8] */
    s->r[0]=read_mem(s,(0x800adf8u + 0x1d8u),4);
    goto L_0800adf8;
L_0800adf8: STEP(0x0800adf8u); /* lsls r1, r4, #1 */
    s->r[1]=lsl(s,s->r[4],0x1u);
    goto L_0800adfa;
L_0800adfa: STEP(0x0800adfau); /* adds r1, r1, r0 */
    s->r[1]=add(s,s->r[1],s->r[0]);
    goto L_0800adfc;
L_0800adfc: STEP(0x0800adfcu); /* mov r0, r1 */
    s->r[0]=s->r[1];
    goto L_0800adfe;
L_0800adfe: STEP(0x0800adfeu); /* adds r0, #0x40 */
    s->r[0]=add(s,s->r[0],0x40u);
    goto L_0800ae00;
L_0800ae00: STEP(0x0800ae00u); /* ldrh r2, [r0, #2] */
    s->r[2]=read_mem(s,(s->r[0] + 0x2u),2);
    goto L_0800ae02;
L_0800ae02: STEP(0x0800ae02u); /* cmp r2, #0 */
    (void)sub(s,s->r[2],0x0u);
    goto L_0800ae04;
L_0800ae04: STEP(0x0800ae04u); /* ldrb r2, [r5, #0x16] */
    s->r[2]=read_mem(s,(s->r[5] + 0x16u),1);
    goto L_0800ae06;
L_0800ae06: STEP(0x0800ae06u); /* b #0x800ae0a */
    goto L_0800ae0a;
L_0800ae08: STEP(0x0800ae08u); /* b #0x800aed4 */
    goto L_0800aed4;
L_0800ae0a: STEP(0x0800ae0au); /* beq #0x800ae38 */
    if(Z)goto L_0800ae38;
    goto L_0800ae0c;
L_0800ae0c: STEP(0x0800ae0cu); /* cmp r2, #2 */
    (void)sub(s,s->r[2],0x2u);
    goto L_0800ae0e;
L_0800ae0e: STEP(0x0800ae0eu); /* bne #0x800aed4 */
    if(!Z)goto L_0800aed4;
    goto L_0800ae10;
L_0800ae10: STEP(0x0800ae10u); /* ldr r2, [pc, #0x1b4] */
    s->r[2]=read_mem(s,(0x800ae14u + 0x1b4u),4);
    goto L_0800ae12;
L_0800ae12: STEP(0x0800ae12u); /* ldrh r2, [r2, #0x12] */
    s->r[2]=read_mem(s,(s->r[2] + 0x12u),2);
    goto L_0800ae14;
L_0800ae14: STEP(0x0800ae14u); /* cmp r2, r6 */
    (void)sub(s,s->r[2],s->r[6]);
    goto L_0800ae16;
L_0800ae16: STEP(0x0800ae16u); /* bls #0x800ae3c */
    if(!C||Z)goto L_0800ae3c;
    goto L_0800ae18;
L_0800ae18: STEP(0x0800ae18u); /* ldrh r2, [r0, #0x1a] */
    s->r[2]=read_mem(s,(s->r[0] + 0x1au),2);
    goto L_0800ae1a;
L_0800ae1a: STEP(0x0800ae1au); /* adds r2, r2, #5 */
    s->r[2]=add(s,s->r[2],0x5u);
    goto L_0800ae1c;
L_0800ae1c: STEP(0x0800ae1cu); /* cmp r2, #0x1e */
    (void)sub(s,s->r[2],0x1eu);
    goto L_0800ae1e;
L_0800ae1e: STEP(0x0800ae1eu); /* bhs #0x800ae3c */
    if(C)goto L_0800ae3c;
    goto L_0800ae20;
L_0800ae20: STEP(0x0800ae20u); /* ldrh r2, [r1, #0x2a] */
    s->r[2]=read_mem(s,(s->r[1] + 0x2au),2);
    goto L_0800ae22;
L_0800ae22: STEP(0x0800ae22u); /* cmp r2, #0 */
    (void)sub(s,s->r[2],0x0u);
    goto L_0800ae24;
L_0800ae24: STEP(0x0800ae24u); /* beq #0x800ae2c */
    if(Z)goto L_0800ae2c;
    goto L_0800ae26;
L_0800ae26: STEP(0x0800ae26u); /* ldr r2, [sp, #0x38] */
    s->r[2]=read_mem(s,(s->r[13] + 0x38u),4);
    goto L_0800ae28;
L_0800ae28: STEP(0x0800ae28u); /* cmp r2, #3 */
    (void)sub(s,s->r[2],0x3u);
    goto L_0800ae2a;
L_0800ae2a: STEP(0x0800ae2au); /* beq #0x800ae3c */
    if(Z)goto L_0800ae3c;
    goto L_0800ae2c;
L_0800ae2c: STEP(0x0800ae2cu); /* movs r2, #2 */
    s->r[2]=nz(s,0x2u);
    goto L_0800ae2e;
L_0800ae2e: STEP(0x0800ae2eu); /* strh r2, [r1, #0x2a] */
    write_mem(s,(s->r[1] + 0x2au),2,s->r[2]);
    goto L_0800ae30;
L_0800ae30: STEP(0x0800ae30u); /* movs r2, #3 */
    s->r[2]=nz(s,0x3u);
    goto L_0800ae32;
L_0800ae32: STEP(0x0800ae32u); /* str r2, [sp, #0x38] */
    write_mem(s,(s->r[13] + 0x38u),4,s->r[2]);
    goto L_0800ae34;
L_0800ae34: STEP(0x0800ae34u); /* b #0x800ae3c */
    goto L_0800ae3c;
L_0800ae36: STEP(0x0800ae36u); /* b #0x800aed6 */
    goto L_0800aed6;
L_0800ae38: STEP(0x0800ae38u); /* cmp r2, #2 */
    (void)sub(s,s->r[2],0x2u);
    goto L_0800ae3a;
L_0800ae3a: STEP(0x0800ae3au); /* bne #0x800af22 */
    if(!Z)goto L_0800af22;
    goto L_0800ae3c;
L_0800ae3c: STEP(0x0800ae3cu); /* ldr r2, [pc, #0x188] */
    s->r[2]=read_mem(s,(0x800ae40u + 0x188u),4);
    goto L_0800ae3e;
L_0800ae3e: STEP(0x0800ae3eu); /* ldrh r3, [r2, #0x1c] */
    s->r[3]=read_mem(s,(s->r[2] + 0x1cu),2);
    goto L_0800ae40;
L_0800ae40: STEP(0x0800ae40u); /* cmp r3, #0 */
    (void)sub(s,s->r[3],0x0u);
    goto L_0800ae42;
L_0800ae42: STEP(0x0800ae42u); /* beq #0x800af22 */
    if(Z)goto L_0800af22;
    goto L_0800ae44;
L_0800ae44: STEP(0x0800ae44u); /* ldrh r3, [r0, #0x1a] */
    s->r[3]=read_mem(s,(s->r[0] + 0x1au),2);
    goto L_0800ae46;
L_0800ae46: STEP(0x0800ae46u); /* mov ip, r3 */
    s->r[12]=s->r[3];
    goto L_0800ae48;
L_0800ae48: STEP(0x0800ae48u); /* adds r3, #0xa */
    s->r[3]=add(s,s->r[3],0xau);
    goto L_0800ae4a;
L_0800ae4a: STEP(0x0800ae4au); /* cmp r3, #0x1e */
    (void)sub(s,s->r[3],0x1eu);
    goto L_0800ae4c;
L_0800ae4c: STEP(0x0800ae4cu); /* bhs #0x800af22 */
    if(C)goto L_0800af22;
    goto L_0800ae4e;
L_0800ae4e: STEP(0x0800ae4eu); /* ldr r3, [sp, #0x20] */
    s->r[3]=read_mem(s,(s->r[13] + 0x20u),4);
    goto L_0800ae50;
L_0800ae50: STEP(0x0800ae50u); /* ldrb r3, [r3, #0x12] */
    s->r[3]=read_mem(s,(s->r[3] + 0x12u),1);
    goto L_0800ae52;
L_0800ae52: STEP(0x0800ae52u); /* cmp r3, #0 */
    (void)sub(s,s->r[3],0x0u);
    goto L_0800ae54;
L_0800ae54: STEP(0x0800ae54u); /* bne #0x800af22 */
    if(!Z)goto L_0800af22;
    goto L_0800ae56;
L_0800ae56: STEP(0x0800ae56u); /* ldrh r2, [r2, #0x28] */
    s->r[2]=read_mem(s,(s->r[2] + 0x28u),2);
    goto L_0800ae58;
L_0800ae58: STEP(0x0800ae58u); /* str r2, [sp, #0x24] */
    write_mem(s,(s->r[13] + 0x24u),4,s->r[2]);
    goto L_0800ae5a;
L_0800ae5a: STEP(0x0800ae5au); /* cmp r2, r6 */
    (void)sub(s,s->r[2],s->r[6]);
    goto L_0800ae5c;
L_0800ae5c: STEP(0x0800ae5cu); /* bls #0x800ae7c */
    if(!C||Z)goto L_0800ae7c;
    goto L_0800ae5e;
L_0800ae5e: STEP(0x0800ae5eu); /* movs r2, #0x8a */
    s->r[2]=nz(s,0x8au);
    goto L_0800ae60;
L_0800ae60: STEP(0x0800ae60u); /* ldrh r2, [r2, r1] */
    s->r[2]=read_mem(s,(s->r[2] + s->r[1]),2);
    goto L_0800ae62;
L_0800ae62: STEP(0x0800ae62u); /* cmp r2, #0 */
    (void)sub(s,s->r[2],0x0u);
    goto L_0800ae64;
L_0800ae64: STEP(0x0800ae64u); /* bne #0x800ae9e */
    if(!Z)goto L_0800ae9e;
    goto L_0800ae66;
L_0800ae66: STEP(0x0800ae66u); /* ldr r2, [sp, #0x38] */
    s->r[2]=read_mem(s,(s->r[13] + 0x38u),4);
    goto L_0800ae68;
L_0800ae68: STEP(0x0800ae68u); /* cmp r2, #2 */
    (void)sub(s,s->r[2],0x2u);
    goto L_0800ae6a;
L_0800ae6a: STEP(0x0800ae6au); /* bne #0x800ae72 */
    if(!Z)goto L_0800ae72;
    goto L_0800ae6c;
L_0800ae6c: STEP(0x0800ae6cu); /* ldrh r2, [r1, #0x2a] */
    s->r[2]=read_mem(s,(s->r[1] + 0x2au),2);
    goto L_0800ae6e;
L_0800ae6e: STEP(0x0800ae6eu); /* cmp r2, #0 */
    (void)sub(s,s->r[2],0x0u);
    goto L_0800ae70;
L_0800ae70: STEP(0x0800ae70u); /* bne #0x800aeaa */
    if(!Z)goto L_0800aeaa;
    goto L_0800ae72;
L_0800ae72: STEP(0x0800ae72u); /* movs r2, #3 */
    s->r[2]=nz(s,0x3u);
    goto L_0800ae74;
L_0800ae74: STEP(0x0800ae74u); /* strh r2, [r1, #0x2a] */
    write_mem(s,(s->r[1] + 0x2au),2,s->r[2]);
    goto L_0800ae76;
L_0800ae76: STEP(0x0800ae76u); /* movs r1, #2 */
    s->r[1]=nz(s,0x2u);
    goto L_0800ae78;
L_0800ae78: STEP(0x0800ae78u); /* str r1, [sp, #0x38] */
    write_mem(s,(s->r[13] + 0x38u),4,s->r[1]);
    goto L_0800ae7a;
L_0800ae7a: STEP(0x0800ae7au); /* b #0x800aeaa */
    goto L_0800aeaa;
L_0800ae7c: STEP(0x0800ae7cu); /* ldr r2, [pc, #0x148] */
    s->r[2]=read_mem(s,(0x800ae80u + 0x148u),4);
    goto L_0800ae7e;
L_0800ae7e: STEP(0x0800ae7eu); /* ldrh r3, [r2, #0x1e] */
    s->r[3]=read_mem(s,(s->r[2] + 0x1eu),2);
    goto L_0800ae80;
L_0800ae80: STEP(0x0800ae80u); /* cmp r3, r6 */
    (void)sub(s,s->r[3],s->r[6]);
    goto L_0800ae82;
L_0800ae82: STEP(0x0800ae82u); /* bls #0x800ae96 */
    if(!C||Z)goto L_0800ae96;
    goto L_0800ae84;
L_0800ae84: STEP(0x0800ae84u); /* ldrh r3, [r0, #0x32] */
    s->r[3]=read_mem(s,(s->r[0] + 0x32u),2);
    goto L_0800ae86;
L_0800ae86: STEP(0x0800ae86u); /* cmp r3, #0 */
    (void)sub(s,s->r[3],0x0u);
    goto L_0800ae88;
L_0800ae88: STEP(0x0800ae88u); /* bne #0x800ae96 */
    if(!Z)goto L_0800ae96;
    goto L_0800ae8a;
L_0800ae8a: STEP(0x0800ae8au); /* ldrh r2, [r2, #0x20] */
    s->r[2]=read_mem(s,(s->r[2] + 0x20u),2);
    goto L_0800ae8c;
L_0800ae8c: STEP(0x0800ae8cu); /* cmp r2, #0 */
    (void)sub(s,s->r[2],0x0u);
    goto L_0800ae8e;
L_0800ae8e: STEP(0x0800ae8eu); /* bne #0x800ae94 */
    if(!Z)goto L_0800ae94;
    goto L_0800ae90;
L_0800ae90: STEP(0x0800ae90u); /* mov r2, ip */
    s->r[2]=s->r[12];
    goto L_0800ae92;
L_0800ae92: STEP(0x0800ae92u); /* adds r2, r2, #5 */
    s->r[2]=add(s,s->r[2],0x5u);
    goto L_0800ae94;
L_0800ae94: STEP(0x0800ae94u); /* strh r2, [r0, #0x32] */
    write_mem(s,(s->r[0] + 0x32u),2,s->r[2]);
    goto L_0800ae96;
L_0800ae96: STEP(0x0800ae96u); /* movs r2, #0x8a */
    s->r[2]=nz(s,0x8au);
    goto L_0800ae98;
L_0800ae98: STEP(0x0800ae98u); /* ldrh r2, [r2, r1] */
    s->r[2]=read_mem(s,(s->r[2] + s->r[1]),2);
    goto L_0800ae9a;
L_0800ae9a: STEP(0x0800ae9au); /* cmp r2, #0 */
    (void)sub(s,s->r[2],0x0u);
    goto L_0800ae9c;
L_0800ae9c: STEP(0x0800ae9cu); /* beq #0x800aeaa */
    if(Z)goto L_0800aeaa;
    goto L_0800ae9e;
L_0800ae9e: STEP(0x0800ae9eu); /* ldr r2, [sp, #0x24] */
    s->r[2]=read_mem(s,(s->r[13] + 0x24u),4);
    goto L_0800aea0;
L_0800aea0: STEP(0x0800aea0u); /* cmp r2, r6 */
    (void)sub(s,s->r[2],s->r[6]);
    goto L_0800aea2;
L_0800aea2: STEP(0x0800aea2u); /* bhi #0x800aeaa */
    if(C&&!Z)goto L_0800aeaa;
    goto L_0800aea4;
L_0800aea4: STEP(0x0800aea4u); /* movs r2, #0 */
    s->r[2]=nz(s,0x0u);
    goto L_0800aea6;
L_0800aea6: STEP(0x0800aea6u); /* adds r1, #0x80 */
    s->r[1]=add(s,s->r[1],0x80u);
    goto L_0800aea8;
L_0800aea8: STEP(0x0800aea8u); /* strh r2, [r1, #0xa] */
    write_mem(s,(s->r[1] + 0xau),2,s->r[2]);
    goto L_0800aeaa;
L_0800aeaa: STEP(0x0800aeaau); /* ldrh r1, [r0, #0x32] */
    s->r[1]=read_mem(s,(s->r[0] + 0x32u),2);
    goto L_0800aeac;
L_0800aeac: STEP(0x0800aeacu); /* cmp r1, #0 */
    (void)sub(s,s->r[1],0x0u);
    goto L_0800aeae;
L_0800aeae: STEP(0x0800aeaeu); /* beq #0x800aece */
    if(Z)goto L_0800aece;
    goto L_0800aeb0;
L_0800aeb0: STEP(0x0800aeb0u); /* ldr r1, [pc, #0x114] */
    s->r[1]=read_mem(s,(0x800aeb4u + 0x114u),4);
    goto L_0800aeb2;
L_0800aeb2: STEP(0x0800aeb2u); /* ldrh r2, [r1, #0x1e] */
    s->r[2]=read_mem(s,(s->r[1] + 0x1eu),2);
    goto L_0800aeb4;
L_0800aeb4: STEP(0x0800aeb4u); /* cmp r2, r6 */
    (void)sub(s,s->r[2],s->r[6]);
    goto L_0800aeb6;
L_0800aeb6: STEP(0x0800aeb6u); /* bhi #0x800aece */
    if(C&&!Z)goto L_0800aece;
    goto L_0800aeb8;
L_0800aeb8: STEP(0x0800aeb8u); /* ldr r2, [pc, #0x11c] */
    s->r[2]=read_mem(s,(0x800aebcu + 0x11cu),4);
    goto L_0800aeba;
L_0800aeba: STEP(0x0800aebau); /* ldrb r2, [r2, r4] */
    s->r[2]=read_mem(s,(s->r[2] + s->r[4]),1);
    goto L_0800aebc;
L_0800aebc: STEP(0x0800aebcu); /* cmp r2, #0 */
    (void)sub(s,s->r[2],0x0u);
    goto L_0800aebe;
L_0800aebe: STEP(0x0800aebeu); /* bne #0x800aeca */
    if(!Z)goto L_0800aeca;
    goto L_0800aec0;
L_0800aec0: STEP(0x0800aec0u); /* ldrh r1, [r1, #0x20] */
    s->r[1]=read_mem(s,(s->r[1] + 0x20u),2);
    goto L_0800aec2;
L_0800aec2: STEP(0x0800aec2u); /* movs r2, #0x4b */
    s->r[2]=nz(s,0x4bu);
    goto L_0800aec4;
L_0800aec4: STEP(0x0800aec4u); /* lsls r2, r2, #3 */
    s->r[2]=lsl(s,s->r[2],0x3u);
    goto L_0800aec6;
L_0800aec6: STEP(0x0800aec6u); /* cmp r1, r2 */
    (void)sub(s,s->r[1],s->r[2]);
    goto L_0800aec8;
L_0800aec8: STEP(0x0800aec8u); /* bhi #0x800aece */
    if(C&&!Z)goto L_0800aece;
    goto L_0800aeca;
L_0800aeca: STEP(0x0800aecau); /* movs r1, #0 */
    s->r[1]=nz(s,0x0u);
    goto L_0800aecc;
L_0800aecc: STEP(0x0800aeccu); /* strh r1, [r0, #0x32] */
    write_mem(s,(s->r[0] + 0x32u),2,s->r[1]);
    goto L_0800aece;
L_0800aece: STEP(0x0800aeceu); /* ldr r0, [pc, #0x108] */
    s->r[0]=read_mem(s,(0x800aed0u + 0x108u),4);
    goto L_0800aed0;
L_0800aed0: STEP(0x0800aed0u); /* movs r1, #0 */
    s->r[1]=nz(s,0x0u);
    goto L_0800aed2;
L_0800aed2: STEP(0x0800aed2u); /* strb r1, [r0, r4] */
    write_mem(s,(s->r[0] + s->r[4]),1,s->r[1]);
    goto L_0800aed4;
L_0800aed4: STEP(0x0800aed4u); /* b #0x800af22 */
    goto L_0800af22;
L_0800aed6: STEP(0x0800aed6u); /* ldr r0, [sp, #8] */
    s->r[0]=read_mem(s,(s->r[13] + 0x8u),4);
    goto L_0800aed8;
L_0800aed8: STEP(0x0800aed8u); /* cmp r7, r0 */
    (void)sub(s,s->r[7],s->r[0]);
    goto L_0800aeda;
L_0800aeda: STEP(0x0800aedau); /* ldrb r0, [r5, #0x16] */
    s->r[0]=read_mem(s,(s->r[5] + 0x16u),1);
    goto L_0800aedc;
L_0800aedc: STEP(0x0800aedcu); /* bls #0x800af12 */
    if(!C||Z)goto L_0800af12;
    goto L_0800aede;
L_0800aede: STEP(0x0800aedeu); /* cmp r0, #1 */
    (void)sub(s,s->r[0],0x1u);
    goto L_0800aee0;
L_0800aee0: STEP(0x0800aee0u); /* bne #0x800af16 */
    if(!Z)goto L_0800af16;
    goto L_0800aee2;
L_0800aee2: STEP(0x0800aee2u); /* ldr r0, [sp, #8] */
    s->r[0]=read_mem(s,(s->r[13] + 0x8u),4);
    goto L_0800aee4;
L_0800aee4: STEP(0x0800aee4u); /* subs r7, r7, r0 */
    s->r[7]=sub(s,s->r[7],s->r[0]);
    goto L_0800aee6;
L_0800aee6: STEP(0x0800aee6u); /* ldr r0, [pc, #0xe0] */
    s->r[0]=read_mem(s,(0x800aee8u + 0xe0u),4);
    goto L_0800aee8;
L_0800aee8: STEP(0x0800aee8u); /* ldrh r0, [r0, #0x1e] */
    s->r[0]=read_mem(s,(s->r[0] + 0x1eu),2);
    goto L_0800aeea;
L_0800aeea: STEP(0x0800aeeau); /* cmp r0, r6 */
    (void)sub(s,s->r[0],s->r[6]);
    goto L_0800aeec;
L_0800aeec: STEP(0x0800aeecu); /* bhi #0x800af22 */
    if(C&&!Z)goto L_0800af22;
    goto L_0800aeee;
L_0800aeee: STEP(0x0800aeeeu); /* ldrb r0, [r5, #0x17] */
    s->r[0]=read_mem(s,(s->r[5] + 0x17u),1);
    goto L_0800aef0;
L_0800aef0: STEP(0x0800aef0u); /* cmp r0, #0 */
    (void)sub(s,s->r[0],0x0u);
    goto L_0800aef2;
L_0800aef2: STEP(0x0800aef2u); /* bne #0x800af22 */
    if(!Z)goto L_0800af22;
    goto L_0800aef4;
L_0800aef4: STEP(0x0800aef4u); /* adds r0, r7, #4 */
    s->r[0]=add(s,s->r[7],0x4u);
    goto L_0800aef6;
L_0800aef6: STEP(0x0800aef6u); /* cmp r0, #0xa */
    (void)sub(s,s->r[0],0xau);
    goto L_0800aef8;
L_0800aef8: STEP(0x0800aef8u); /* bhi #0x800af22 */
    if(C&&!Z)goto L_0800af22;
    goto L_0800aefa;
L_0800aefa: STEP(0x0800aefau); /* movs r0, #1 */
    s->r[0]=nz(s,0x1u);
    goto L_0800aefc;
L_0800aefc: STEP(0x0800aefcu); /* movs r6, #0 */
    s->r[6]=nz(s,0x0u);
    goto L_0800aefe;
L_0800aefe: STEP(0x0800aefeu); /* strb r0, [r5, #0x17] */
    write_mem(s,(s->r[5] + 0x17u),1,s->r[0]);
    goto L_0800af00;
L_0800af00: STEP(0x0800af00u); /* movs r7, #0x3c */
    s->r[7]=nz(s,0x3cu);
    goto L_0800af02;
L_0800af02: STEP(0x0800af02u); /* uxtb r0, r4 */
    s->r[0]=(uint8_t)(s->r[4]);
    goto L_0800af04;
L_0800af04: STEP(0x0800af04u); /* mov r1, r6 */
    s->r[1]=s->r[6];
    goto L_0800af06;
L_0800af06: STEP(0x0800af06u); /* bl #0x800c85c */
    s->r[14]=0x0800af0bu;
    if(!s->call){s->fault=-2;s->fault_address=0x0800c85cu;return -2;}
    s->r[15]=0x0800c85cu;
    temp=(uint32_t)s->call(s->user,0x0800c85cu,s);
    if(temp){s->pc=0x0800af0au;return 1;}
    goto L_0800af0a;
L_0800af0a: STEP(0x0800af0au); /* movs r0, #0xe */
    s->r[0]=nz(s,0xeu);
    goto L_0800af0c;
L_0800af0c: STEP(0x0800af0cu); /* bl #0x800cdb8 */
    s->r[14]=0x0800af11u;
    if(!s->call){s->fault=-2;s->fault_address=0x0800cdb8u;return -2;}
    s->r[15]=0x0800cdb8u;
    temp=(uint32_t)s->call(s->user,0x0800cdb8u,s);
    if(temp){s->pc=0x0800af10u;return 1;}
    goto L_0800af10;
L_0800af10: STEP(0x0800af10u); /* b #0x800af22 */
    goto L_0800af22;
L_0800af12: STEP(0x0800af12u); /* cmp r0, #1 */
    (void)sub(s,s->r[0],0x1u);
    goto L_0800af14;
L_0800af14: STEP(0x0800af14u); /* beq #0x800af4a */
    if(Z)goto L_0800af4a;
    goto L_0800af16;
L_0800af16: STEP(0x0800af16u); /* uxtb r0, r4 */
    s->r[0]=(uint8_t)(s->r[4]);
    goto L_0800af18;
L_0800af18: STEP(0x0800af18u); /* movs r1, #0 */
    s->r[1]=nz(s,0x0u);
    goto L_0800af1a;
L_0800af1a: STEP(0x0800af1au); /* bl #0x8009e30 */
    s->r[14]=0x0800af1fu;
    if(!s->call){s->fault=-2;s->fault_address=0x08009e30u;return -2;}
    s->r[15]=0x08009e30u;
    temp=(uint32_t)s->call(s->user,0x08009e30u,s);
    if(temp){s->pc=0x0800af1eu;return 1;}
    goto L_0800af1e;
L_0800af1e: STEP(0x0800af1eu); /* movs r7, #0 */
    s->r[7]=nz(s,0x0u);
    goto L_0800af20;
L_0800af20: STEP(0x0800af20u); /* mov r6, r7 */
    s->r[6]=s->r[7];
    goto L_0800af22;
L_0800af22: STEP(0x0800af22u); /* ldr r2, [sp, #0x20] */
    s->r[2]=read_mem(s,(s->r[13] + 0x20u),4);
    goto L_0800af24;
L_0800af24: STEP(0x0800af24u); /* ldr r0, [sp, #0x38] */
    s->r[0]=read_mem(s,(s->r[13] + 0x38u),4);
    goto L_0800af26;
L_0800af26: STEP(0x0800af26u); /* strb r0, [r2, #0xc] */
    write_mem(s,(s->r[2] + 0xcu),1,s->r[0]);
    goto L_0800af28;
L_0800af28: STEP(0x0800af28u); /* ldr r1, [pc, #0xa0] */
    s->r[1]=read_mem(s,(0x800af2cu + 0xa0u),4);
    goto L_0800af2a;
L_0800af2a: STEP(0x0800af2au); /* ldr r0, [sp, #0x18] */
    s->r[0]=read_mem(s,(s->r[13] + 0x18u),4);
    goto L_0800af2c;
L_0800af2c: STEP(0x0800af2cu); /* adds r4, r4, #1 */
    s->r[4]=add(s,s->r[4],0x1u);
    goto L_0800af2e;
L_0800af2e: STEP(0x0800af2eu); /* str r7, [r1, r0] */
    write_mem(s,(s->r[1] + s->r[0]),4,s->r[7]);
    goto L_0800af30;
L_0800af30: STEP(0x0800af30u); /* uxth r4, r4 */
    s->r[4]=(uint16_t)(s->r[4]);
    goto L_0800af32;
L_0800af32: STEP(0x0800af32u); /* strh r6, [r5, #4] */
    write_mem(s,(s->r[5] + 0x4u),2,s->r[6]);
    goto L_0800af34;
L_0800af34: STEP(0x0800af34u); /* cmp r4, #0xc */
    (void)sub(s,s->r[4],0xcu);
    goto L_0800af36;
L_0800af36: STEP(0x0800af36u); /* bhs #0x800af3a */
    if(C)goto L_0800af3a;
    goto L_0800af38;
L_0800af38: STEP(0x0800af38u); /* b #0x800acb8 */
    goto L_0800acb8;

    /* Poll and debounce inputs 1..15 */
L_0800af3a: STEP(0x0800af3au); /* movs r5, #1 */
    s->r[5]=nz(s,0x1u);
    goto L_0800af3c;
L_0800af3c: STEP(0x0800af3cu); /* uxtb r0, r5 */
    s->r[0]=(uint8_t)(s->r[5]);
    goto L_0800af3e;
L_0800af3e: STEP(0x0800af3eu); /* bl #0x800a2d0 */
    s->r[14]=0x0800af43u;
    if(!s->call){s->fault=-2;s->fault_address=0x0800a2d0u;return -2;}
    s->r[15]=0x0800a2d0u;
    temp=(uint32_t)s->call(s->user,0x0800a2d0u,s);
    if(temp){s->pc=0x0800af42u;return 1;}
    goto L_0800af42;
L_0800af42: STEP(0x0800af42u); /* cmp r0, #0 */
    (void)sub(s,s->r[0],0x0u);
    goto L_0800af44;
L_0800af44: STEP(0x0800af44u); /* beq #0x800b012 */
    if(Z)goto L_0800b012;
    goto L_0800af46;
L_0800af46: STEP(0x0800af46u); /* movs r4, #0 */
    s->r[4]=nz(s,0x0u);
    goto L_0800af48;
L_0800af48: STEP(0x0800af48u); /* b #0x800af5c */
    goto L_0800af5c;
L_0800af4a: STEP(0x0800af4au); /* uxtb r0, r4 */
    s->r[0]=(uint8_t)(s->r[4]);
    goto L_0800af4c;
L_0800af4c: STEP(0x0800af4cu); /* bl #0x8009f44 */
    s->r[14]=0x0800af51u;
    if(!s->call){s->fault=-2;s->fault_address=0x08009f44u;return -2;}
    s->r[15]=0x08009f44u;
    temp=(uint32_t)s->call(s->user,0x08009f44u,s);
    if(temp){s->pc=0x0800af50u;return 1;}
    goto L_0800af50;
L_0800af50: STEP(0x0800af50u); /* b #0x800af1e */
    goto L_0800af1e;
L_0800af52: STEP(0x0800af52u); /* movs r0, #0xa */
    s->r[0]=nz(s,0xau);
    goto L_0800af54;
L_0800af54: STEP(0x0800af54u); /* bl #0x800cc64 */
    s->r[14]=0x0800af59u;
    if(!s->call){s->fault=-2;s->fault_address=0x0800cc64u;return -2;}
    s->r[15]=0x0800cc64u;
    temp=(uint32_t)s->call(s->user,0x0800cc64u,s);
    if(temp){s->pc=0x0800af58u;return 1;}
    goto L_0800af58;
L_0800af58: STEP(0x0800af58u); /* adds r4, r4, #1 */
    s->r[4]=add(s,s->r[4],0x1u);
    goto L_0800af5a;
L_0800af5a: STEP(0x0800af5au); /* uxth r4, r4 */
    s->r[4]=(uint16_t)(s->r[4]);
    goto L_0800af5c;
L_0800af5c: STEP(0x0800af5cu); /* uxtb r0, r5 */
    s->r[0]=(uint8_t)(s->r[5]);
    goto L_0800af5e;
L_0800af5e: STEP(0x0800af5eu); /* bl #0x800a2d0 */
    s->r[14]=0x0800af63u;
    if(!s->call){s->fault=-2;s->fault_address=0x0800a2d0u;return -2;}
    s->r[15]=0x0800a2d0u;
    temp=(uint32_t)s->call(s->user,0x0800a2d0u,s);
    if(temp){s->pc=0x0800af62u;return 1;}
    goto L_0800af62;
L_0800af62: STEP(0x0800af62u); /* cmp r0, #0 */
    (void)sub(s,s->r[0],0x0u);
    goto L_0800af64;
L_0800af64: STEP(0x0800af64u); /* beq #0x800af6a */
    if(Z)goto L_0800af6a;
    goto L_0800af66;
L_0800af66: STEP(0x0800af66u); /* cmp r4, #2 */
    (void)sub(s,s->r[4],0x2u);
    goto L_0800af68;
L_0800af68: STEP(0x0800af68u); /* blo #0x800af52 */
    if(!C)goto L_0800af52;
    goto L_0800af6a;
L_0800af6a: STEP(0x0800af6au); /* cmp r5, #4 */
    (void)sub(s,s->r[5],0x4u);
    goto L_0800af6c;
L_0800af6c: STEP(0x0800af6cu); /* beq #0x800af74 */
    if(Z)goto L_0800af74;
    goto L_0800af6e;
L_0800af6e: STEP(0x0800af6eu); /* cmp r4, #2 */
    (void)sub(s,s->r[4],0x2u);
    goto L_0800af70;
L_0800af70: STEP(0x0800af70u); /* beq #0x800afc0 */
    if(Z)goto L_0800afc0;
    goto L_0800af72;
L_0800af72: STEP(0x0800af72u); /* b #0x800aff4 */
    goto L_0800aff4;
L_0800af74: STEP(0x0800af74u); /* cmp r4, #2 */
    (void)sub(s,s->r[4],0x2u);
    goto L_0800af76;
L_0800af76: STEP(0x0800af76u); /* beq #0x800af84 */
    if(Z)goto L_0800af84;
    goto L_0800af78;
L_0800af78: STEP(0x0800af78u); /* b #0x800aff4 */
    goto L_0800aff4;
L_0800af7a: STEP(0x0800af7au); /* movs r0, #0x14 */
    s->r[0]=nz(s,0x14u);
    goto L_0800af7c;
L_0800af7c: STEP(0x0800af7cu); /* bl #0x800cc64 */
    s->r[14]=0x0800af81u;
    if(!s->call){s->fault=-2;s->fault_address=0x0800cc64u;return -2;}
    s->r[15]=0x0800cc64u;
    temp=(uint32_t)s->call(s->user,0x0800cc64u,s);
    if(temp){s->pc=0x0800af80u;return 1;}
    goto L_0800af80;
L_0800af80: STEP(0x0800af80u); /* adds r4, r4, #1 */
    s->r[4]=add(s,s->r[4],0x1u);
    goto L_0800af82;
L_0800af82: STEP(0x0800af82u); /* uxth r4, r4 */
    s->r[4]=(uint16_t)(s->r[4]);
    goto L_0800af84;
L_0800af84: STEP(0x0800af84u); /* uxtb r0, r5 */
    s->r[0]=(uint8_t)(s->r[5]);
    goto L_0800af86;
L_0800af86: STEP(0x0800af86u); /* bl #0x800a2d0 */
    s->r[14]=0x0800af8bu;
    if(!s->call){s->fault=-2;s->fault_address=0x0800a2d0u;return -2;}
    s->r[15]=0x0800a2d0u;
    temp=(uint32_t)s->call(s->user,0x0800a2d0u,s);
    if(temp){s->pc=0x0800af8au;return 1;}
    goto L_0800af8a;
L_0800af8a: STEP(0x0800af8au); /* cmp r0, #0 */
    (void)sub(s,s->r[0],0x0u);
    goto L_0800af8c;
L_0800af8c: STEP(0x0800af8cu); /* beq #0x800af94 */
    if(Z)goto L_0800af94;
    goto L_0800af8e;
L_0800af8e: STEP(0x0800af8eu); /* cmp r4, #0xc8 */
    (void)sub(s,s->r[4],0xc8u);
    goto L_0800af90;
L_0800af90: STEP(0x0800af90u); /* blo #0x800af7a */
    if(!C)goto L_0800af7a;
    goto L_0800af92;
L_0800af92: STEP(0x0800af92u); /* b #0x800af98 */
    goto L_0800af98;
L_0800af94: STEP(0x0800af94u); /* cmp r4, #0xc8 */
    (void)sub(s,s->r[4],0xc8u);
    goto L_0800af96;
L_0800af96: STEP(0x0800af96u); /* blo #0x800afc0 */
    if(!C)goto L_0800afc0;
    goto L_0800af98;
L_0800af98: STEP(0x0800af98u); /* cmp r4, #0xc8 */
    (void)sub(s,s->r[4],0xc8u);
    goto L_0800af9a;
L_0800af9a: STEP(0x0800af9au); /* beq #0x800afaa */
    if(Z)goto L_0800afaa;
    goto L_0800af9c;
L_0800af9c: STEP(0x0800af9cu); /* b #0x800aff4 */
    goto L_0800aff4;
L_0800af9e: STEP(0x0800af9eu); /* movs r0, #0xc8 */
    s->r[0]=nz(s,0xc8u);
    goto L_0800afa0;
L_0800afa0: STEP(0x0800afa0u); /* bl #0x800cc64 */
    s->r[14]=0x0800afa5u;
    if(!s->call){s->fault=-2;s->fault_address=0x0800cc64u;return -2;}
    s->r[15]=0x0800cc64u;
    temp=(uint32_t)s->call(s->user,0x0800cc64u,s);
    if(temp){s->pc=0x0800afa4u;return 1;}
    goto L_0800afa4;
L_0800afa4: STEP(0x0800afa4u); /* adds r4, r4, #1 */
    s->r[4]=add(s,s->r[4],0x1u);
    goto L_0800afa6;
L_0800afa6: STEP(0x0800afa6u); /* uxth r4, r4 */
    s->r[4]=(uint16_t)(s->r[4]);
    goto L_0800afa8;
L_0800afa8: STEP(0x0800afa8u); /* b #0x800afae */
    goto L_0800afae;
L_0800afaa: STEP(0x0800afaau); /* movs r6, #0x7d */
    s->r[6]=nz(s,0x7du);
    goto L_0800afac;
L_0800afac: STEP(0x0800afacu); /* lsls r6, r6, #4 */
    s->r[6]=lsl(s,s->r[6],0x4u);
    goto L_0800afae;
L_0800afae: STEP(0x0800afaeu); /* uxtb r0, r5 */
    s->r[0]=(uint8_t)(s->r[5]);
    goto L_0800afb0;
L_0800afb0: STEP(0x0800afb0u); /* bl #0x800a2d0 */
    s->r[14]=0x0800afb5u;
    if(!s->call){s->fault=-2;s->fault_address=0x0800a2d0u;return -2;}
    s->r[15]=0x0800a2d0u;
    temp=(uint32_t)s->call(s->user,0x0800a2d0u,s);
    if(temp){s->pc=0x0800afb4u;return 1;}
    goto L_0800afb4;
L_0800afb4: STEP(0x0800afb4u); /* cmp r0, #0 */
    (void)sub(s,s->r[0],0x0u);
    goto L_0800afb6;
L_0800afb6: STEP(0x0800afb6u); /* beq #0x800afbc */
    if(Z)goto L_0800afbc;
    goto L_0800afb8;
L_0800afb8: STEP(0x0800afb8u); /* cmp r4, r6 */
    (void)sub(s,s->r[4],s->r[6]);
    goto L_0800afba;
L_0800afba: STEP(0x0800afbau); /* blo #0x800af9e */
    if(!C)goto L_0800af9e;
    goto L_0800afbc;
L_0800afbc: STEP(0x0800afbcu); /* cmp r4, r6 */
    (void)sub(s,s->r[4],s->r[6]);
    goto L_0800afbe;
L_0800afbe: STEP(0x0800afbeu); /* bhs #0x800afdc */
    if(C)goto L_0800afdc;
    goto L_0800afc0;
L_0800afc0: STEP(0x0800afc0u); /* uxtb r0, r5 */
    s->r[0]=(uint8_t)(s->r[5]);
    goto L_0800afc2;
L_0800afc2: STEP(0x0800afc2u); /* bl #0x8007904 */
    s->r[14]=0x0800afc7u;
    if(!s->call){s->fault=-2;s->fault_address=0x08007904u;return -2;}
    s->r[15]=0x08007904u;
    temp=(uint32_t)s->call(s->user,0x08007904u,s);
    if(temp){s->pc=0x0800afc6u;return 1;}
    goto L_0800afc6;
L_0800afc6: STEP(0x0800afc6u); /* b #0x800aff4 */
    goto L_0800aff4;
L_0800afdc: STEP(0x0800afdcu); /* uxtb r0, r5 */
    s->r[0]=(uint8_t)(s->r[5]);
    goto L_0800afde;
L_0800afde: STEP(0x0800afdeu); /* bl #0x8007cf0 */
    s->r[14]=0x0800afe3u;
    if(!s->call){s->fault=-2;s->fault_address=0x08007cf0u;return -2;}
    s->r[15]=0x08007cf0u;
    temp=(uint32_t)s->call(s->user,0x08007cf0u,s);
    if(temp){s->pc=0x0800afe2u;return 1;}
    goto L_0800afe2;
L_0800afe2: STEP(0x0800afe2u); /* b #0x800afea */
    goto L_0800afea;
L_0800afe4: STEP(0x0800afe4u); /* movs r0, #0xc8 */
    s->r[0]=nz(s,0xc8u);
    goto L_0800afe6;
L_0800afe6: STEP(0x0800afe6u); /* bl #0x800cc64 */
    s->r[14]=0x0800afebu;
    if(!s->call){s->fault=-2;s->fault_address=0x0800cc64u;return -2;}
    s->r[15]=0x0800cc64u;
    temp=(uint32_t)s->call(s->user,0x0800cc64u,s);
    if(temp){s->pc=0x0800afeau;return 1;}
    goto L_0800afea;
L_0800afea: STEP(0x0800afeau); /* uxtb r0, r5 */
    s->r[0]=(uint8_t)(s->r[5]);
    goto L_0800afec;
L_0800afec: STEP(0x0800afecu); /* bl #0x800a2d0 */
    s->r[14]=0x0800aff1u;
    if(!s->call){s->fault=-2;s->fault_address=0x0800a2d0u;return -2;}
    s->r[15]=0x0800a2d0u;
    temp=(uint32_t)s->call(s->user,0x0800a2d0u,s);
    if(temp){s->pc=0x0800aff0u;return 1;}
    goto L_0800aff0;
L_0800aff0: STEP(0x0800aff0u); /* cmp r0, #0 */
    (void)sub(s,s->r[0],0x0u);
    goto L_0800aff2;
L_0800aff2: STEP(0x0800aff2u); /* bne #0x800afe4 */
    if(!Z)goto L_0800afe4;
    goto L_0800aff4;
L_0800aff4: STEP(0x0800aff4u); /* movs r6, #0x7d */
    s->r[6]=nz(s,0x7du);
    goto L_0800aff6;
L_0800aff6: STEP(0x0800aff6u); /* lsls r6, r6, #3 */
    s->r[6]=lsl(s,s->r[6],0x3u);
    goto L_0800aff8;
L_0800aff8: STEP(0x0800aff8u); /* uxtb r0, r5 */
    s->r[0]=(uint8_t)(s->r[5]);
    goto L_0800affa;
L_0800affa: STEP(0x0800affau); /* bl #0x800a2d0 */
    s->r[14]=0x0800afffu;
    if(!s->call){s->fault=-2;s->fault_address=0x0800a2d0u;return -2;}
    s->r[15]=0x0800a2d0u;
    temp=(uint32_t)s->call(s->user,0x0800a2d0u,s);
    if(temp){s->pc=0x0800affeu;return 1;}
    goto L_0800affe;
L_0800affe: STEP(0x0800affeu); /* cmp r0, #0 */
    (void)sub(s,s->r[0],0x0u);
    goto L_0800b000;
L_0800b000: STEP(0x0800b000u); /* beq #0x800b012 */
    if(Z)goto L_0800b012;
    goto L_0800b002;
L_0800b002: STEP(0x0800b002u); /* cmp r4, r6 */
    (void)sub(s,s->r[4],s->r[6]);
    goto L_0800b004;
L_0800b004: STEP(0x0800b004u); /* bhs #0x800b012 */
    if(C)goto L_0800b012;
    goto L_0800b006;
L_0800b006: STEP(0x0800b006u); /* movs r0, #0xc8 */
    s->r[0]=nz(s,0xc8u);
    goto L_0800b008;
L_0800b008: STEP(0x0800b008u); /* bl #0x800cc64 */
    s->r[14]=0x0800b00du;
    if(!s->call){s->fault=-2;s->fault_address=0x0800cc64u;return -2;}
    s->r[15]=0x0800cc64u;
    temp=(uint32_t)s->call(s->user,0x0800cc64u,s);
    if(temp){s->pc=0x0800b00cu;return 1;}
    goto L_0800b00c;
L_0800b00c: STEP(0x0800b00cu); /* adds r4, r4, #1 */
    s->r[4]=add(s,s->r[4],0x1u);
    goto L_0800b00e;
L_0800b00e: STEP(0x0800b00eu); /* uxth r4, r4 */
    s->r[4]=(uint16_t)(s->r[4]);
    goto L_0800b010;
L_0800b010: STEP(0x0800b010u); /* b #0x800aff8 */
    goto L_0800aff8;
L_0800b012: STEP(0x0800b012u); /* adds r5, r5, #1 */
    s->r[5]=add(s,s->r[5],0x1u);
    goto L_0800b014;
L_0800b014: STEP(0x0800b014u); /* uxth r5, r5 */
    s->r[5]=(uint16_t)(s->r[5]);
    goto L_0800b016;
L_0800b016: STEP(0x0800b016u); /* cmp r5, #0xf */
    (void)sub(s,s->r[5],0xfu);
    goto L_0800b018;
L_0800b018: STEP(0x0800b018u); /* bls #0x800af3c */
    if(!C||Z)goto L_0800af3c;
    goto L_0800b01a;

    /* Consume both UART reception paths */
L_0800b01a: STEP(0x0800b01au); /* ldr r0, [sp, #0x30] */
    s->r[0]=read_mem(s,(s->r[13] + 0x30u),4);
    goto L_0800b01c;
L_0800b01c: STEP(0x0800b01cu); /* ldrb r0, [r0, #2] */
    s->r[0]=read_mem(s,(s->r[0] + 0x2u),1);
    goto L_0800b01e;
L_0800b01e: STEP(0x0800b01eu); /* cmp r0, #1 */
    (void)sub(s,s->r[0],0x1u);
    goto L_0800b020;
L_0800b020: STEP(0x0800b020u); /* bne #0x800b030 */
    if(!Z)goto L_0800b030;
    goto L_0800b022;
L_0800b022: STEP(0x0800b022u); /* ldr r1, [sp, #0x30] */
    s->r[1]=read_mem(s,(s->r[13] + 0x30u),4);
    goto L_0800b024;
L_0800b024: STEP(0x0800b024u); /* movs r0, #0 */
    s->r[0]=nz(s,0x0u);
    goto L_0800b026;
L_0800b026: STEP(0x0800b026u); /* strb r0, [r1, #2] */
    write_mem(s,(s->r[1] + 0x2u),1,s->r[0]);
    goto L_0800b028;
L_0800b028: STEP(0x0800b028u); /* ldrh r1, [r1] */
    s->r[1]=read_mem(s,(s->r[1]),2);
    goto L_0800b02a;
L_0800b02a: STEP(0x0800b02au); /* ldr r0, [pc, #0x9c] */
    s->r[0]=read_mem(s,(0x800b02cu + 0x9cu),4);
    goto L_0800b02c;
L_0800b02c: STEP(0x0800b02cu); /* bl #0x8008e84 */
    s->r[14]=0x0800b031u;
    if(!s->call){s->fault=-2;s->fault_address=0x08008e84u;return -2;}
    s->r[15]=0x08008e84u;
    temp=(uint32_t)s->call(s->user,0x08008e84u,s);
    if(temp){s->pc=0x0800b030u;return 1;}
    goto L_0800b030;
L_0800b030: STEP(0x0800b030u); /* ldr r0, [sp, #0x34] */
    s->r[0]=read_mem(s,(s->r[13] + 0x34u),4);
    goto L_0800b032;
L_0800b032: STEP(0x0800b032u); /* ldrb r0, [r0, #2] */
    s->r[0]=read_mem(s,(s->r[0] + 0x2u),1);
    goto L_0800b034;
L_0800b034: STEP(0x0800b034u); /* cmp r0, #1 */
    (void)sub(s,s->r[0],0x1u);
    goto L_0800b036;
L_0800b036: STEP(0x0800b036u); /* bne #0x800b056 */
    if(!Z)goto L_0800b056;
    goto L_0800b038;
L_0800b038: STEP(0x0800b038u); /* movs r1, #0 */
    s->r[1]=nz(s,0x0u);
    goto L_0800b03a;
L_0800b03a: STEP(0x0800b03au); /* ldr r0, [sp, #0x34] */
    s->r[0]=read_mem(s,(s->r[13] + 0x34u),4);
    goto L_0800b03c;
L_0800b03c: STEP(0x0800b03cu); /* mov r4, r1 */
    s->r[4]=s->r[1];
    goto L_0800b03e;
L_0800b03e: STEP(0x0800b03eu); /* strb r1, [r0, #2] */
    write_mem(s,(s->r[0] + 0x2u),1,s->r[1]);
    goto L_0800b040;
L_0800b040: STEP(0x0800b040u); /* ldr r5, [pc, #0x88] */
    s->r[5]=read_mem(s,(0x800b044u + 0x88u),4);
    goto L_0800b042;
L_0800b042: STEP(0x0800b042u); /* b #0x800b04e */
    goto L_0800b04e;
L_0800b044: STEP(0x0800b044u); /* ldrb r0, [r5, r4] */
    s->r[0]=read_mem(s,(s->r[5] + s->r[4]),1);
    goto L_0800b046;
L_0800b046: STEP(0x0800b046u); /* bl #0x8008eac */
    s->r[14]=0x0800b04bu;
    if(!s->call){s->fault=-2;s->fault_address=0x08008eacu;return -2;}
    s->r[15]=0x08008eacu;
    temp=(uint32_t)s->call(s->user,0x08008eacu,s);
    if(temp){s->pc=0x0800b04au;return 1;}
    goto L_0800b04a;
L_0800b04a: STEP(0x0800b04au); /* adds r4, r4, #1 */
    s->r[4]=add(s,s->r[4],0x1u);
    goto L_0800b04c;
L_0800b04c: STEP(0x0800b04cu); /* uxth r4, r4 */
    s->r[4]=(uint16_t)(s->r[4]);
    goto L_0800b04e;
L_0800b04e: STEP(0x0800b04eu); /* ldr r0, [sp, #0x34] */
    s->r[0]=read_mem(s,(s->r[13] + 0x34u),4);
    goto L_0800b050;
L_0800b050: STEP(0x0800b050u); /* ldrh r0, [r0] */
    s->r[0]=read_mem(s,(s->r[0]),2);
    goto L_0800b052;
L_0800b052: STEP(0x0800b052u); /* cmp r0, r4 */
    (void)sub(s,s->r[0],s->r[4]);
    goto L_0800b054;
L_0800b054: STEP(0x0800b054u); /* bhi #0x800b044 */
    if(C&&!Z)goto L_0800b044;
    goto L_0800b056;

    /* Queued pulse-command output */
L_0800b056: STEP(0x0800b056u); /* ldr r0, [sp, #0x2c] */
    s->r[0]=read_mem(s,(s->r[13] + 0x2cu),4);
    goto L_0800b058;
L_0800b058: STEP(0x0800b058u); /* ldrb r0, [r0, #0x18] */
    s->r[0]=read_mem(s,(s->r[0] + 0x18u),1);
    goto L_0800b05a;
L_0800b05a: STEP(0x0800b05au); /* cmp r0, #1 */
    (void)sub(s,s->r[0],0x1u);
    goto L_0800b05c;
L_0800b05c: STEP(0x0800b05cu); /* bne #0x800b0a6 */
    if(!Z)goto L_0800b0a6;
    goto L_0800b05e;
L_0800b05e: STEP(0x0800b05eu); /* ldr r7, [pc, #0x70] */
    s->r[7]=read_mem(s,(0x800b060u + 0x70u),4);
    goto L_0800b060;
L_0800b060: STEP(0x0800b060u); /* movs r1, #4 */
    s->r[1]=nz(s,0x4u);
    goto L_0800b062;
L_0800b062: STEP(0x0800b062u); /* mov r0, r7 */
    s->r[0]=s->r[7];
    goto L_0800b064;
L_0800b064: STEP(0x0800b064u); /* bl #0x8005d3c */
    s->r[14]=0x0800b069u;
    if(!s->call){s->fault=-2;s->fault_address=0x08005d3cu;return -2;}
    s->r[15]=0x08005d3cu;
    temp=(uint32_t)s->call(s->user,0x08005d3cu,s);
    if(temp){s->pc=0x0800b068u;return 1;}
    goto L_0800b068;
L_0800b068: STEP(0x0800b068u); /* cmp r0, #0 */
    (void)sub(s,s->r[0],0x0u);
    goto L_0800b06a;
L_0800b06a: STEP(0x0800b06au); /* beq #0x800b0a6 */
    if(Z)goto L_0800b0a6;
    goto L_0800b06c;
L_0800b06c: STEP(0x0800b06cu); /* movs r4, #0 */
    s->r[4]=nz(s,0x0u);
    goto L_0800b06e;
L_0800b06e: STEP(0x0800b06eu); /* ldr r5, [pc, #0x64] */
    s->r[5]=read_mem(s,(0x800b070u + 0x64u),4);
    goto L_0800b070;
L_0800b070: STEP(0x0800b070u); /* mov r6, r4 */
    s->r[6]=s->r[4];
    goto L_0800b072;
L_0800b072: STEP(0x0800b072u); /* b #0x800b090 */
    goto L_0800b090;
L_0800b074: STEP(0x0800b074u); /* movs r1, #4 */
    s->r[1]=nz(s,0x4u);
    goto L_0800b076;
L_0800b076: STEP(0x0800b076u); /* mov r0, r7 */
    s->r[0]=s->r[7];
    goto L_0800b078;
L_0800b078: STEP(0x0800b078u); /* bl #0x8005d3c */
    s->r[14]=0x0800b07du;
    if(!s->call){s->fault=-2;s->fault_address=0x08005d3cu;return -2;}
    s->r[15]=0x08005d3cu;
    temp=(uint32_t)s->call(s->user,0x08005d3cu,s);
    if(temp){s->pc=0x0800b07cu;return 1;}
    goto L_0800b07c;
L_0800b07c: STEP(0x0800b07cu); /* cmp r0, #0 */
    (void)sub(s,s->r[0],0x0u);
    goto L_0800b07e;
L_0800b07e: STEP(0x0800b07eu); /* beq #0x800b098 */
    if(Z)goto L_0800b098;
    goto L_0800b080;
L_0800b080: STEP(0x0800b080u); /* ldrb r0, [r5, r4] */
    s->r[0]=read_mem(s,(s->r[5] + s->r[4]),1);
    goto L_0800b082;
L_0800b082: STEP(0x0800b082u); /* cmp r0, #0 */
    (void)sub(s,s->r[0],0x0u);
    goto L_0800b084;
L_0800b084: STEP(0x0800b084u); /* beq #0x800b08c */
    if(Z)goto L_0800b08c;
    goto L_0800b086;
L_0800b086: STEP(0x0800b086u); /* bl #0x800cdb8 */
    s->r[14]=0x0800b08bu;
    if(!s->call){s->fault=-2;s->fault_address=0x0800cdb8u;return -2;}
    s->r[15]=0x0800cdb8u;
    temp=(uint32_t)s->call(s->user,0x0800cdb8u,s);
    if(temp){s->pc=0x0800b08au;return 1;}
    goto L_0800b08a;
L_0800b08a: STEP(0x0800b08au); /* strb r6, [r5, r4] */
    write_mem(s,(s->r[5] + s->r[4]),1,s->r[6]);
    goto L_0800b08c;
L_0800b08c: STEP(0x0800b08cu); /* adds r4, r4, #1 */
    s->r[4]=add(s,s->r[4],0x1u);
    goto L_0800b08e;
L_0800b08e: STEP(0x0800b08eu); /* uxth r4, r4 */
    s->r[4]=(uint16_t)(s->r[4]);
    goto L_0800b090;
L_0800b090: STEP(0x0800b090u); /* ldr r0, [sp, #0x2c] */
    s->r[0]=read_mem(s,(s->r[13] + 0x2cu),4);
    goto L_0800b092;
L_0800b092: STEP(0x0800b092u); /* ldrb r0, [r0, #0x19] */
    s->r[0]=read_mem(s,(s->r[0] + 0x19u),1);
    goto L_0800b094;
L_0800b094: STEP(0x0800b094u); /* cmp r0, r4 */
    (void)sub(s,s->r[0],s->r[4]);
    goto L_0800b096;
L_0800b096: STEP(0x0800b096u); /* bhi #0x800b074 */
    if(C&&!Z)goto L_0800b074;
    goto L_0800b098;
L_0800b098: STEP(0x0800b098u); /* ldr r0, [sp, #0x2c] */
    s->r[0]=read_mem(s,(s->r[13] + 0x2cu),4);
    goto L_0800b09a;
L_0800b09a: STEP(0x0800b09au); /* ldrb r0, [r0, #0x19] */
    s->r[0]=read_mem(s,(s->r[0] + 0x19u),1);
    goto L_0800b09c;
L_0800b09c: STEP(0x0800b09cu); /* cmp r0, r4 */
    (void)sub(s,s->r[0],s->r[4]);
    goto L_0800b09e;
L_0800b09e: STEP(0x0800b09eu); /* bne #0x800b0a6 */
    if(!Z)goto L_0800b0a6;
    goto L_0800b0a0;
L_0800b0a0: STEP(0x0800b0a0u); /* ldr r0, [sp, #0x2c] */
    s->r[0]=read_mem(s,(s->r[13] + 0x2cu),4);
    goto L_0800b0a2;
L_0800b0a2: STEP(0x0800b0a2u); /* strb r6, [r0, #0x19] */
    write_mem(s,(s->r[0] + 0x19u),1,s->r[6]);
    goto L_0800b0a4;
L_0800b0a4: STEP(0x0800b0a4u); /* strb r6, [r0, #0x18] */
    write_mem(s,(s->r[0] + 0x18u),1,s->r[6]);
    goto L_0800b0a6;

    /* Flush outputs, displays, input status, final processing */
L_0800b0a6: STEP(0x0800b0a6u); /* bl #0x8007474 */
    s->r[14]=0x0800b0abu;
    if(!s->call){s->fault=-2;s->fault_address=0x08007474u;return -2;}
    s->r[15]=0x08007474u;
    temp=(uint32_t)s->call(s->user,0x08007474u,s);
    if(temp){s->pc=0x0800b0aau;return 1;}
    goto L_0800b0aa;
L_0800b0aa: STEP(0x0800b0aau); /* movs r0, #1 */
    s->r[0]=nz(s,0x1u);
    goto L_0800b0ac;
L_0800b0ac: STEP(0x0800b0acu); /* bl #0x800890c */
    s->r[14]=0x0800b0b1u;
    if(!s->call){s->fault=-2;s->fault_address=0x0800890cu;return -2;}
    s->r[15]=0x0800890cu;
    temp=(uint32_t)s->call(s->user,0x0800890cu,s);
    if(temp){s->pc=0x0800b0b0u;return 1;}
    goto L_0800b0b0;
L_0800b0b0: STEP(0x0800b0b0u); /* bl #0x80087b8 */
    s->r[14]=0x0800b0b5u;
    if(!s->call){s->fault=-2;s->fault_address=0x080087b8u;return -2;}
    s->r[15]=0x080087b8u;
    temp=(uint32_t)s->call(s->user,0x080087b8u,s);
    if(temp){s->pc=0x0800b0b4u;return 1;}
    goto L_0800b0b4;
L_0800b0b4: STEP(0x0800b0b4u); /* bl #0x80087ac */
    s->r[14]=0x0800b0b9u;
    if(!s->call){s->fault=-2;s->fault_address=0x080087acu;return -2;}
    s->r[15]=0x080087acu;
    temp=(uint32_t)s->call(s->user,0x080087acu,s);
    if(temp){s->pc=0x0800b0b8u;return 1;}
    goto L_0800b0b8;
L_0800b0b8: STEP(0x0800b0b8u); /* bl #0x80094e8 */
    s->r[14]=0x0800b0bdu;
    if(!s->call){s->fault=-2;s->fault_address=0x080094e8u;return -2;}
    s->r[15]=0x080094e8u;
    temp=(uint32_t)s->call(s->user,0x080094e8u,s);
    if(temp){s->pc=0x0800b0bcu;return 1;}
    goto L_0800b0bc;
L_0800b0bc: STEP(0x0800b0bcu); /* ldr r1, [pc, #0x18] */
    s->r[1]=read_mem(s,(0x800b0c0u + 0x18u),4);
    goto L_0800b0be;
L_0800b0be: STEP(0x0800b0beu); /* strb r0, [r1] */
    write_mem(s,(s->r[1]),1,s->r[0]);
    goto L_0800b0c0;
L_0800b0c0: STEP(0x0800b0c0u); /* bl #0x8004dcc */
    s->r[14]=0x0800b0c5u;
    if(!s->call){s->fault=-2;s->fault_address=0x08004dccu;return -2;}
    s->r[15]=0x08004dccu;
    temp=(uint32_t)s->call(s->user,0x08004dccu,s);
    if(temp){s->pc=0x0800b0c4u;return 1;}
    goto L_0800b0c4;
L_0800b0c4: STEP(0x0800b0c4u); /* bl #0x800a7d4 */
    s->r[14]=0x0800b0c9u;
    goto L_0800a7d4;
}
