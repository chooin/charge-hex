// rea decompile_all
// name: fw_08007114
// address: 0x8007114
// body: available
// range: 0x8007114-0x8007265 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_08007114(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  fw_080041cc(&local_30,0x14);
  if (*param_1 == 0x40013800) {
    _DAT_40021018 = _DAT_40021018 | 0x4000;
    _DAT_40021014 = _DAT_40021014 | 0x20000;
    local_1c = 0x20000;
    local_24 = 3;
    local_30 = 0x600;
    uStack_2c = 2;
    uStack_28 = 0;
    local_20 = 1;
    fw_08005bcc(0x48000000,&local_30);
    _DAT_2000114c = 0x40020030;
    _DAT_20001150 = 0;
    _DAT_20001154 = 0;
    _DAT_2000115c = 0;
    _DAT_20001160 = 0;
    _DAT_20001164 = 0;
    _DAT_20001158 = 0x80;
    _DAT_20001168 = 0;
    iVar1 = fw_08005968(&DAT_2000114c);
    if (iVar1 != 0) {
      fw_0800529c();
    }
    param_1[0x1c] = (int)&DAT_2000114c;
    _DAT_20001190 = 0x4002001c;
    _DAT_20001194 = 0x10;
    _DAT_20001198 = 0;
    _DAT_2000119c = 0x80;
    _DAT_200011a0 = 0;
    _DAT_200011a4 = 0;
    _DAT_200011a8 = 0;
    _DAT_200011ac = 0;
    _DAT_20001170 = param_1;
    iVar1 = fw_08005968(&DAT_20001190,&DAT_200011a0);
    if (iVar1 != 0) {
      fw_0800529c();
    }
    param_1[0x1b] = (int)&DAT_20001190;
    _DAT_200011b4 = param_1;
    fw_080063e4(0x1b,0);
    uVar2 = 0x1b;
  }
  else {
    if (*param_1 != 0x40004400) {
      return;
    }
    _DAT_4002101c = _DAT_4002101c | 0x20000;
    _DAT_40021014 = _DAT_40021014 | 0x20000;
    local_1c = 0x20000;
    local_24 = 3;
    local_30 = 0xc;
    uStack_2c = 2;
    uStack_28 = 0;
    local_20 = 1;
    fw_08005bcc(0x48000000,&local_30);
    _DAT_200011d4 = 0x40020058;
    _DAT_200011d8 = 0;
    _DAT_200011dc = 0;
    _DAT_200011e4 = 0;
    _DAT_200011e8 = 0;
    _DAT_200011ec = 0;
    _DAT_200011e0 = 0x80;
    _DAT_200011f0 = 0;
    iVar1 = fw_08005968(&DAT_200011d4);
    if (iVar1 != 0) {
      fw_0800529c();
    }
    param_1[0x1c] = (int)&DAT_200011d4;
    _DAT_20001218 = 0x40020044;
    _DAT_2000121c = 0x10;
    _DAT_20001220 = 0;
    _DAT_20001224 = 0x80;
    _DAT_20001228 = 0;
    _DAT_2000122c = 0;
    _DAT_20001230 = 0;
    _DAT_20001234 = 0;
    _DAT_200011f8 = param_1;
    iVar1 = fw_08005968(&DAT_20001218,&DAT_20001228);
    if (iVar1 != 0) {
      fw_0800529c();
    }
    param_1[0x1b] = (int)&DAT_20001218;
    _DAT_2000123c = param_1;
    fw_080063e4(0x1c,0);
    uVar2 = 0x1c;
  }
  fw_080063cc(uVar2);
  return;
}

