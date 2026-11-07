/* Manual C reconstruction of 0800B0DC and 08009694.
 * Every command branch was checked against Thumb and the __switch8 tables.
 * Names and physical meanings are inferred; external firmware routines remain
 * address-named dependencies. This is not original source or a standalone build.
 * Memory pointers model the original absolute SRAM layout.
 */
#include <stdint.h>
#include <stddef.h>
#define B(a) (*(volatile uint8_t *)(uintptr_t)(a))
#define H(a) (*(volatile uint16_t *)(uintptr_t)(a))
#define W(a) (*(volatile uint32_t *)(uintptr_t)(a))
#define CFG 0x20000854u
#define REC 0x20001018u
#define HIST 0x20000990u
#define CH 0x200005E4u
extern void bh_0800be24(const uint8_t *);
extern void bh_0800c20c(const uint8_t *);
extern void bh_0800c1c8(const uint8_t *);
extern void bh_0800bc38(uint8_t *);
extern void bh_0800b708(uint8_t *);
extern void bh_0800b7a8(uint8_t *);
extern void bh_0800bcac(uint32_t, uint32_t);
extern void bh_0800bc74(uint32_t, uint32_t);
extern void bh_0800b6d4(uint32_t, uint32_t, uint32_t *);
extern uint32_t bh_0800b74c(uint32_t, uint32_t *, uint32_t *, uint32_t *, uint32_t *);
extern uint32_t bh_0800ca80(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
extern void bh_0800bcd8(const uint8_t *, uint32_t);
extern void bh_0800c7c4(uint32_t, uint32_t, uint32_t, const uint8_t *, uint32_t);
extern void bh_0800a4a8(uint32_t, uint32_t);
extern void bh_0800a4b4(uint32_t, uint32_t);
extern void bh_080063ec(void);
extern void bh_08009e30(uint32_t, uint32_t);
extern uint32_t bh_0800cd40(uint32_t);
extern uint32_t bh_08009d04(uint32_t);
extern void bh_0800a65c(void);
extern void bh_0800cdb8(uint32_t);
extern void bh_0800cc44(uint32_t);
extern void bh_080094b4(const uint8_t *, uint32_t);
extern void bh_0800964e(const uint8_t *, const uint8_t *);

static uint16_t be16(const uint8_t *p) { return (uint16_t)((uint16_t)p[0]*256u+p[1]); }
static uint32_t be32(const uint8_t *p) { return (uint32_t)p[0]<<24 | (uint32_t)p[1]<<16 | (uint32_t)p[2]<<8 | p[3]; }
static void put16(uint8_t *p, uint32_t v) { p[0]=(uint8_t)(v>>8); p[1]=(uint8_t)v; }
static void put32(uint8_t *p, uint32_t v) { p[0]=(uint8_t)(v>>24);p[1]=(uint8_t)(v>>16);put16(p+2,v); }
static uint32_t arm_bit(uint8_t n) { return n<32 ? 1u<<n : 0; }
static uint16_t clamp16(uint16_t v, uint16_t maximum) { return v>maximum ? maximum : v; }

/* 0800B0DC..0800B6B0. frame has already passed the outer XOR checker.
 * scratch[60] explicitly represents the incoming stack payload area. For invalid
 * subselectors in commands34/35, the original transmits six uninitialized stack
 * bytes. Passing scratch makes that behavior defined and reproducible in C;
 * zero-initializing it would be a deliberate behavior change. External readers
 * must initialize their outputs as the original functions do.
 */
void recovered_dispatch_command(const uint8_t *frame, uint8_t scratch[60])
{
    uint32_t a,b,c,d,selected;
    uint8_t command=frame[2], n=0;
    W(0x200000C0)=750;
    B(0x200000BC)=1;
    uint16_t mode=H(CFG+36);
    if(frame[0]==0x55) {
        switch(command) {
        case 0x10: bh_0800be24(frame+4); break;
        case 0x2c: if(mode==3) bh_0800c20c(frame+4); break;
        case 0x2d: if(mode==3) bh_0800c1c8(frame+4); break;
        case 0x36:
            switch(frame[4]) {
            case 1: H(0x20000ACC)=0; break;
            case 2: H(0x20000ACE)=0; break;
            case 3: H(0x20000AD0)=0; break;
            case 4: if(H(0x20000AD2)) H(0x20000AD2)&=(uint16_t)~arm_bit(B(0x20000121)); break;
            case 5: if(H(0x20000AD4)) H(0x20000AD4)&=(uint16_t)~arm_bit(B(0x20000104)); break;
            default: break;
            } break;
        default: break;
        }
        return;
    }
    /* Original accepts any non-55 header, not only AA. */
    switch(command) {
    case 1: scratch[0]=12;scratch[1]=1;n=2;break;
    case 2: bh_0800bc38(scratch);n=(uint8_t)(scratch[0]+1);break;
    case 4:
        scratch[1]=(uint8_t)bh_0800ca80(frame[4],be16(frame+5),be16(frame+7),0,0);
        scratch[0]=frame[4];n=2;break;
    case 5:
    case 0x15:
    case 0x2e:
        if((command==0x15 && mode!=0)||(command==0x2e && mode!=3))return;
        selected=bh_0800b74c(frame[4],&a,&b,&c,&d);
        scratch[0]=(uint8_t)selected;put16(scratch+1,a);put16(scratch+3,b);
        n=5;
        if(command!=5) {put16(scratch+5,c);put16(scratch+7,d);n=9;}
        if(command==0x2e) {
            put16(scratch+9,H(CH+selected*52u-36));
            put16(scratch+11,H(CH+selected*52u-34));
            scratch[13]=255;scratch[14]=255;n=15;
        } break;
    case 7: put16(scratch,H(CFG+60));put16(scratch+2,W(CFG+56)/10u);n=4;break;
    case 9: bh_0800bcac(frame[4],frame[5]);scratch[0]=0;n=1;break;
    case 0x0c: bh_0800bc74(frame[4],frame[5]);scratch[0]=frame[4];n=1;break;
    case 0x0d:
        bh_0800b6d4(frame[4],frame[5],&a);
        scratch[0]=frame[4];put16(scratch+1,a);
        bh_0800c7c4(command,3,1,scratch,0x55);
        bh_08009e30((uint8_t)(frame[4]-1u),4);return;
    case 0x0f: bh_0800b708(scratch);n=25;break;
    case 0x14:
        if(mode!=0)return;
        scratch[1]=(uint8_t)bh_0800ca80(frame[4],be16(frame+5),be16(frame+7),be16(frame+9),0);
        scratch[0]=frame[4];n=2;break;
    case 0x18: bh_0800bcd8(frame+4,1);scratch[0]=0;n=1;break;
    case 0x1e: bh_0800b7a8(scratch);n=23;break;
    case 0x23:
        scratch[0]=24;scratch[1]=0;scratch[2]=3;scratch[3]=0;scratch[4]=6;
        for(unsigned i=5;i<17;i++)scratch[i]=0;
        n=17;break;
    case 0x27:
        if(mode!=3)return;
        a=be32(frame+11);
        if(a!=W(0x200000D8)) {
            B(0x200000CC)=(uint8_t)bh_0800ca80(frame[4],be16(frame+5),be16(frame+7),be16(frame+9),frame[15]);
            W(0x200000D8)=a;B(0x200000BE)=0;B(0x200000BF)=0;H(0x200008DE)=0;
        }
        scratch[0]=frame[4];scratch[1]=B(0x200000CC);
        for(unsigned i=0;i<4;i++)scratch[i+2]=frame[i+11];
        n=6;break;
    case 0x32:
        switch(frame[4]) {
        case 1: B(0x20000102)=frame[8];bh_0800a4a8(0x0800FC58,(uint16_t)(int16_t)(int8_t)frame[8]);break;
        case 2: a=be16(frame+7);H(0x2000010C)=(uint16_t)a;bh_0800a4a8(0x0800FC5A,a);break;
        case 3: a=be16(frame+7);W(0x20000118)=a;bh_0800a4a8(0x0800FC5C,a);break;
        default:break;
        }scratch[0]=0;n=1;break;
    case 0x34:
    case 0x35:
        switch(frame[4]) {
        case 1:
            scratch[0]=1;scratch[1]=0;scratch[2]=0;scratch[3]=0;
            scratch[4]=B(command==0x34?0x20000101:0x20000102);scratch[5]=0;break;
        case 2:
            scratch[0]=2;scratch[1]=0;scratch[2]=0;
            put16(scratch+3,H(command==0x34?0x2000010A:0x2000010C));scratch[5]=0;break;
        case 3:
            scratch[0]=3;put32(scratch+1,W(command==0x34?0x20000114:0x20000118));scratch[5]=0;break;
        case 4:
            if(command==0x34){scratch[0]=4;for(unsigned i=1;i<5;i++)scratch[i]=0;scratch[5]=2;}break;
        default:break;
        }n=6;break;
    case 0x38:
        H(CFG+36)=frame[4];H(CFG+18)=clamp16(be16(frame+5),2500);
        H(CFG+28)=frame[7];H(CFG+30)=frame[8];H(CFG+32)=clamp16((uint16_t)(frame[9]*60u),14400);
        H(CFG+40)=clamp16(frame[10],20);H(CFG+38)=clamp16(be16(frame+11),480);B(CFG+119)=frame[13];
        bh_0800a4a8(0x0800FC24,frame[4]);bh_0800a4a8(0x0800FC12,H(CFG+18));
        bh_0800a4a8(0x0800FC1C,H(CFG+28));bh_0800a4a8(0x0800FC1E,H(CFG+30));
        bh_0800a4a8(0x0800FC20,H(CFG+32));bh_0800a4a8(0x0800FC28,H(CFG+40));
        bh_0800a4a8(0x0800FC26,H(CFG+38));bh_0800a4a8(0x0800FC2A,B(CFG+119));
        scratch[0]=0;n=1;break;
    case 0x39:
        scratch[0]=(uint8_t)mode;put16(scratch+1,H(CFG+18));scratch[3]=B(CFG+28);scratch[4]=B(CFG+30);
        scratch[5]=(uint8_t)(H(CFG+32)/60u);scratch[6]=(uint8_t)H(CFG+40);put16(scratch+7,H(CFG+38));
        scratch[9]=B(CFG+119);n=10;break;
    case 0x3b:
        scratch[0]=0;bh_0800c7c4(command,1,1,scratch,0x55);
        if(frame[4]==0 || frame[4]==1)bh_0800a4a8(0x0800F802,0xAAAA);
        if(frame[4]==0)bh_080063ec();
        return;
    default:return;
    }
    bh_0800c7c4(command,n,1,scratch,0x55);
}

/* 0800C6D8, inlined for 9694: it preserves R2/R3 in the original assembly. */
static void clear_identifier_record(void)
{
    B(REC)=0;H(REC+2)=0;W(REC+4)=0;H(REC+8)=0;
}

/* Number-token production from 08009AC0..9B9A and 08009C5C..9CE2.
 * Token meanings intentionally unnamed; append49 distinguishes the two paths.
 */
static void make_number_tokens(uint16_t value, uint8_t append49)
{
    unsigned thousands=(value%10000u)/1000u,hundreds=(value%1000u)/100u;
    unsigned tens=(value%100u)/10u,ones=value%10u,n=1;
    B(CFG+122)=(uint8_t)thousands;B(CFG+123)=(uint8_t)hundreds;
    B(CFG+124)=(uint8_t)tens;B(CFG+125)=(uint8_t)ones;
    B(0x200005D4)=0x42;
    if(thousands){B(0x200005D4+n++)=(uint8_t)(thousands+0x35);B(0x200005D4+n++)=0x44;}
    if(hundreds){
        if(thousands || hundreds!=1)B(0x200005D4+n++)=(uint8_t)(hundreds+0x35);
        B(0x200005D4+n++)=0x43;
    }else if(thousands && tens)B(0x200005D4+n++)=0x3f;
    if(tens)B(0x200005D4+n++)=(uint8_t)(tens+0x35);
    if(thousands || hundreds || tens)B(0x200005D4+n++)=0x46;
    if(ones){B(0x200005D4+n++)=(uint8_t)(ones+0x35);B(0x200005D4+n++)=0x47;}
    if(append49 && (thousands || hundreds || tens || ones))B(0x200005D4+n++)=0x49;
    B(CFG+121)=(uint8_t)n;B(CFG+120)=1;
}

/* 08009694..08009CE2. Handler for fixed 55 AA frame in 20001024.
 * Identifiers/counters have neutral names: physical units remain unverified.
 * External calls retain observed order; register-return division is expressed
 * as unsigned quotient/remainder. Complete entry-level control flow translated.
 */
void recovered_handle_identifier_frame(void)
{
    const uint8_t *frame=(const uint8_t *)(uintptr_t)0x20001024;
    uint16_t amount=be16(frame+6);
    uint32_t identifier=be32(frame+2);
    if(H(CFG+106)==0)return;
    if(H(0x2000012A)){H(0x2000012A)=800;return;}
    if(H(0x200008E0) || H(0x200008DC))return;
    if(amount>5000 && amount!=0xAA33)return;
    uint32_t pending=H(REC+8),old_amount=H(REC+2),old_identifier=W(REC+4);
    uint8_t record_mode=B(REC);
    if(H(0x20000128)==0) {
        if(old_identifier==identifier && pending!=0 &&
           ((record_mode==0x55 && old_amount==pending+amount) ||
            (record_mode==0x66 && old_amount+pending==amount))) {
            H(0x20000128)=2000;H(0x200008D6)=10;
        } else {
            B(REC)=0x55;H(REC+8)=0;
            for(unsigned i=0;i<12 && H(CFG+26)!=0;i++) {
                uintptr_t ch=CH+i*52u;
                uint16_t value=H(ch+14);
                if(W(ch+32)==identifier && value!=0 && bh_0800cd40(i)!=0) {
                    B(REC)=0x66;H(REC+8)=value;B(REC+10)=(uint8_t)i;B(HIST+1)=12;break;
                }
            }
            if(H(CFG+36)==2) {
                if(B(CFG)==1 && H(CFG+48)==0 && H(CFG+46)==0 && B(CFG+1)==255) {
                    bh_0800a65c();B(CFG)=4;H(0x200008D6)=10;
                }else if(B(CFG)!=4)B(REC)=0x55;
            }
            if(B(CFG)==4){B(REC)=0x66;if(H(REC+8)==0)B(REC+10)=24;}
            for(unsigned i=0;i<12;i++) {
                if(B(HIST+1)==12 || (B(CFG)!=1 && B(CFG)!=4))break;
                if(W(HIST+28+4*i)==identifier) {
                    B(REC)=0x66;H(REC+8)=H(HIST+2+2*i);B(HIST+1)=(uint8_t)i;
                    goto prepare_reply;
                }
            }
            if(B(REC)==0x55) {
                if(bh_08009d04(identifier)==0)return;
                if(H(CFG+4)!=0 && H(CFG+42)/H(CFG+4)<=H(CFG+48) && W(CFG+72)==identifier)return;
                H(REC+8)=H(CFG+6);
                if(amount!=0xAA33 && amount<H(CFG+6)){bh_0800cdb8(10);bh_0800cc44(100);}
            }
prepare_reply:
            if(B(CFG)!=1 && B(CFG)!=2 && B(CFG)!=3 && B(CFG)!=4)return;
            H(REC+2)=amount;W(REC+4)=identifier;
            B(0x2000012D)=B(REC);B(0x2000012E)=(uint8_t)(H(REC+8)>>8);B(0x2000012F)=(uint8_t)H(REC+8);
            B(0x20000130)=B(0x2000012C)^B(0x2000012D)^B(0x2000012E)^B(0x2000012F);
            if(amount!=0xAA33){bh_080094b4((const uint8_t *)0x2000012C,5);H(0x20000128)=2000;return;}
            if(H(CFG+36)==3) {
                if(B(0x200000BE)!=0)return;
                if(B(REC)==0x55 && H(CFG+116)==1){B(0x2000012E)=0;B(0x2000012F)=0;}
            }
            bh_0800964e(frame+2,(const uint8_t *)0x2000012D);H(0x20000128)=2000;
            B(CFG+108)=(H(CFG+116)!=0 && H(CFG+36)==3)?4:1;
            if(H(0x200008D6)!=0)H(0x200008D6)=0;
            H(0x200008DC)=15;H(0x2000012A)=800;B(CFG)=5;bh_0800cdb8(0x34);return;
        }
    }
    if(amount==0xAA33)return;
    uint32_t base_total=W(CFG+56),old_total=W(CFG+60);
    if(record_mode==0x55) {
        if(old_identifier==0 || old_amount!=pending+amount)return;
        if(H(0x200008DA)!=0) {
            H(CFG+46)=0;H(CFG+50)=0;H(CFG+48)=0;W(CFG+72)=0;H(CFG+52)=0;H(0x200008DA)=0;
        }
        B(CFG)=3;H(CFG+52)=amount;
        if(old_identifier==W(CFG+72))H(CFG+50)=(uint16_t)(H(CFG+50)+pending);
        else{H(CFG+50)=(uint16_t)pending;H(CFG+48)=0;}
        H(CFG+48)++;
        W(CFG+72)=identifier;
        uint8_t index=B(HIST);
        if(W(HIST+28+index*4u)!=identifier){index=index<12?(uint8_t)(index+1):0;B(HIST)=index;}
        W(HIST+28+index*4u)=identifier;H(HIST+2+B(HIST)*2u)=H(CFG+50);
        B(CFG+108)=0;
        W(CFG+60)=(old_total+pending)%1000000u;
        W(CFG+64)=(base_total+W(CFG+60))%1000000u;
        bh_0800a4b4(0x0800FC30,W(CFG+60));clear_identifier_record();H(0x2000012A)=800;
        if(H(CFG+36)==2){H(0x200008D6)=10;return;}
        bh_0800cdb8(11);make_number_tokens(H(CFG+52),1);H(0x200008D6)=10;return;
    }
    if(record_mode!=0x66 || old_identifier==0 || old_amount+pending!=amount)return;
    if(B(CFG)!=4)B(CFG)=4;
    H(CFG+52)=amount;H(CFG+50)=(uint16_t)pending;H(CFG+48)=0;
    unsigned selected=B(REC+10);
    if(selected<12 && B(HIST+1)==12) {
        uintptr_t ch=CH+selected*52u;W(ch+32)=0;H(ch+14)=0;B(ch+48)=0;
        bh_08009e30(selected,1);
        uint32_t value=H(REC+8),total=W(CFG+60);
        W(CFG+60)=total<value?0:total-value;W(CFG+64)=W(CFG+56)+W(CFG+60);
        clear_identifier_record();B(HIST+1)=0;
    } else {
        if(pending==0){H(0x200008D6)=10;return;}
        W(HIST+28+B(HIST+1)*4u)=0;H(HIST+2+B(HIST+1)*2u)=0;
        W(CFG+60)=old_total<pending?0:old_total-pending;
        /* Original subtracts here (9C44), but adds in selected-channel path. */
        W(CFG+64)=base_total-W(CFG+60);clear_identifier_record();B(HIST+1)=0;
    }
    H(0x2000012A)=800;bh_0800cdb8(0x10);make_number_tokens(H(CFG+52),0);
    bh_0800a4b4(0x0800FC30,W(CFG+60));H(0x200008D6)=10;
}
