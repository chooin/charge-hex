// rea decompile_all
// name: fw_08002cf4
// address: 0x8002cf4
// body: available
// range: 0x8002cf4-0x8002e49 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_08002cf4(undefined4 param_1,undefined4 param_2,undefined2 *param_3,int param_4)

{
  byte bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined2 *local_10;
  int local_c;
  
  local_10 = param_3;
  local_c = param_4;
  fw_08001038();
  fw_080024c4();
  fw_0800215c();
  fw_08002134();
  fw_080021b4();
  fw_0800220c();
  fw_0800175c(&DAT_20000ba0,0x2000099c,0x200);
  fw_08000280();
  iVar4 = fw_08000a7c(0x48000400,1);
  if ((iVar4 == 0) && (iVar4 = fw_080003a0(&DAT_0800f802), iVar4 != 0xaaaa)) {
    local_10 = (undefined2 *)CONCAT22(local_10._2_2_,0xaaaa);
    fw_0800042c(&DAT_0800f802,&local_10,1);
  }
  iVar4 = fw_080003a0(&DAT_0800f802);
  if (iVar4 == 0xaaaa) {
    DAT_20000000 = 6;
    local_c = _DAT_20000010;
    local_10 = (undefined2 *)&DAT_20000b9c;
    iVar4 = _DAT_20000010;
    while( true ) {
      iVar3 = _DAT_20000010;
      uVar6 = _DAT_20000010 - iVar4;
      if (uVar6 != 0) {
        uVar5 = 0;
        do {
          bVar1 = *(byte *)(uVar5 + 0x20000000);
          if (bVar1 != 0) {
            if (uVar6 < bVar1) {
              *(byte *)(uVar5 + 0x20000000) = bVar1 - (char)uVar6;
            }
            else {
              *(undefined1 *)(uVar5 + 0x20000000) = 0;
              if (uVar5 == 0) {
                fw_08002e96();
                DAT_20000000 = 10;
              }
              else if (uVar5 == 1) {
                fw_08002e80();
                DAT_20000001 = 0x23;
              }
              else if (uVar5 == 2) {
                fw_08002eac(DAT_20000004);
                DAT_20000002 = 10;
              }
            }
          }
          uVar5 = uVar5 + 1 & 0xff;
        } while (uVar5 < 3);
      }
      if (299 < (uint)(_DAT_20000010 - local_c)) break;
      if (*(char *)(local_10 + 1) == '\x01') {
        fw_080029f8(0x2000099c,*local_10);
        *(undefined1 *)(local_10 + 1) = 0;
      }
      if (DAT_20000005 == '\x01') break;
      iVar4 = iVar3;
      if (DAT_20000003 == '\x01') {
        DAT_20000003 = '\0';
        fw_080017e0(&DAT_20000ba0);
        fw_08002314();
        fw_0800175c(&DAT_20000ba0,0x2000099c,0x200);
      }
    }
  }
  _DAT_20000008 = (code *)0x80040cd;
  _DAT_2000000c = (code *)0x80040cd;
  fw_0800174c();
  disableIRQinterrupts();
  fw_08000f8c(&DAT_20000850);
  fw_08001ad8(&DAT_20000ba0);
  _DAT_e000e280 = 0xffffffff;
  enableIRQinterrupts();
  bVar2 = (bool)isCurrentModePrivileged();
  if (bVar2) {
    setMainStackPointer(0x20001680);
  }
  (*_DAT_2000000c)();
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

