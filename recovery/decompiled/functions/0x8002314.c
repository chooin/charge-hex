// rea decompile_all
// name: fw_08002314
// address: 0x8002314
// body: available
// range: 0x8002314-0x8002413 inclusive
// range: 0x8002416-0x8002427 inclusive
// non_contiguous: true
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


void fw_08002314(void)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  ushort uVar4;
  uint uVar5;
  uint uVar6;
  short sVar7;
  uint uVar8;
  undefined2 local_2c [2];
  uint local_28;
  undefined4 *local_24;
  
  uVar5 = 0;
  bVar1 = false;
  local_28 = 0;
  iVar2 = fw_08002ae8(&local_28);
  if (iVar2 == 0) {
    uVar6 = local_28 & 0x3ff;
    uVar3 = local_28 >> 10;
    sVar7 = 0;
    local_24 = &DAT_08004000;
    for (uVar8 = 0; uVar8 < uVar3; uVar8 = uVar8 + 1) {
      fw_08001d90(sVar7,0x20000448,0x400);
      fw_0800042c(local_24,0x20000448,0x200);
      sVar7 = sVar7 + 0x400;
      local_24 = local_24 + 0x100;
    }
    if (uVar6 != 0) {
      fw_08001d90(sVar7,0x20000448,uVar6);
      fw_0800042c(local_24,0x20000448,uVar6 >> 1);
    }
    uVar3 = 0;
    do {
      if (*(char *)(uVar3 + 0x20000428) == '\0') {
        if (bVar1) {
          uVar4 = (short)uVar5 + 1;
        }
        else {
          uVar4 = (short)uVar5 + 2;
        }
        uVar5 = (uint)uVar4;
        break;
      }
      bVar1 = (bool)(bVar1 ^ 1);
      uVar3 = uVar3 + 1;
      uVar5 = uVar5 + 1 & 0xffff;
    } while (uVar3 < 0x20);
    fw_0800042c("app.bin",0x20000428,uVar5 >> 1);
    fw_0800042c(&DAT_0800f824,&local_28,2);
    local_2c[0] = 0x5555;
    fw_0800042c(&DAT_0800f802,local_2c,1);
    DAT_20000004 = 0;
  }
  else if (iVar2 == 5) {
    local_2c[0] = 0xa5a5;
    fw_0800042c(&DAT_0800f802,local_2c,1);
    DAT_20000004 = 4;
  }
  else if (iVar2 == 4) {
    local_2c[0] = 0xa5a5;
    fw_0800042c(&DAT_0800f802,local_2c,1);
    DAT_20000004 = 5;
  }
  else {
    if (iVar2 != 2) {
      return;
    }
    local_2c[0] = 0xa5a5;
    fw_0800042c(&DAT_0800f802,local_2c,1);
    DAT_20000004 = 6;
  }
  DAT_20000002 = 1;
  return;
}

