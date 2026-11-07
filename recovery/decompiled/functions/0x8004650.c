// rea decompile_all
// name: fw_08004650
// address: 0x8004650
// body: available
// range: 0x8004650-0x80047c9 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


undefined8 fw_08004650(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  byte bVar5;
  uint local_20;
  
  local_20 = 0x82;
  uVar4 = 0;
  uVar2 = 0;
  fw_0800462c(param_1);
  fw_08004600(0x14);
  bVar5 = 0;
  do {
    fw_08005d46(0x48000800,0x2000);
    fw_08005d46(0x48000800,0x8000,(int)(local_20 << 0x18) < 0);
    local_20 = (local_20 & 0x7f) << 1;
    fw_08004600(0x50);
    fw_08005d46(0x48000800,0x2000,0);
    fw_08004600(0x50);
    bVar5 = bVar5 + 1;
  } while (bVar5 < 8);
  bVar5 = 0;
  uVar3 = param_2;
  do {
    fw_08005d46(0x48000800,0x2000);
    fw_08005d46(0x48000800,0x8000,(int)(uVar3 << 0x18) < 0);
    uVar3 = (uVar3 & 0x7f) << 1;
    fw_08004600(0x50);
    fw_08005d46(0x48000800,0x2000,0);
    fw_08004600(0x50);
    bVar5 = bVar5 + 1;
  } while (bVar5 < 8);
  bVar5 = 0;
  do {
    fw_08005d46(0x48000800,0x2000);
    fw_08004600(0x50);
    uVar2 = uVar2 << 1;
    iVar1 = fw_08005d3c(0x48000800,0x4000);
    if (iVar1 == 1) {
      uVar2 = uVar2 | 1;
    }
    fw_08005d46(0x48000800,0x2000,0);
    fw_08004600(0x50);
    bVar5 = bVar5 + 1;
  } while (bVar5 < 0x18);
  bVar5 = 0;
  do {
    fw_08005d46(0x48000800,0x2000);
    fw_08004600(0x50);
    uVar4 = (uVar4 & 0x7f) << 1;
    iVar1 = fw_08005d3c(0x48000800,0x4000);
    if (iVar1 == 1) {
      uVar4 = uVar4 | 1;
    }
    fw_08005d46(0x48000800,0x2000,0);
    fw_08004600(0x50);
    bVar5 = bVar5 + 1;
  } while (bVar5 < 8);
  fw_0800460a(param_1);
  param_1 = param_1 * 0xc;
  if (uVar4 == (~(param_2 + uVar2 + (uVar2 >> 8) + (uVar2 >> 0x10) + 0x82) & 0xff)) {
    if (param_2 < 0x23) {
      if (param_2 == 0x16) {
        *(uint *)(param_1 + 0x20000148) = uVar2;
      }
      else {
        *(uint *)(param_1 + 0x2000014c) = uVar2;
      }
    }
    else {
      *(uint *)(param_1 + 0x20000144) = uVar2;
    }
  }
  else if (param_2 < 0x23) {
    if (param_2 == 0x16) {
      uVar2 = *(uint *)(param_1 + 0x20000148);
    }
    else {
      uVar2 = *(uint *)(param_1 + 0x2000014c);
    }
  }
  else {
    uVar2 = *(uint *)(param_1 + 0x20000144);
  }
  return CONCAT44(local_20,uVar2);
}

