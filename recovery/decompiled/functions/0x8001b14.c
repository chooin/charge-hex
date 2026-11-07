// rea decompile_all
// name: fw_08001b14
// address: 0x8001b14
// body: available
// range: 0x8001b14-0x8001ba5 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_08001b14(int *param_1)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  fw_080001a0(&local_28,0x14);
  if (*param_1 == 0x40013800) {
    _DAT_40021018 = _DAT_40021018 | 0x4000;
    _DAT_40021014 = _DAT_40021014 | 0x20000;
    local_14 = 0x20000;
    local_28 = 0x600;
    local_24 = 2;
    local_1c = 3;
    local_18 = 1;
    local_20 = 0;
    fw_0800090c(0x48000000,&local_28);
    _DAT_20000c24 = 0x40020030;
    _DAT_20000c28 = 0;
    _DAT_20000c2c = 0;
    _DAT_20000c34 = 0;
    _DAT_20000c38 = 0;
    _DAT_20000c3c = 0;
    _DAT_20000c40 = 0;
    _DAT_20000c30 = 0x80;
    iVar1 = fw_08000620(&DAT_20000c24);
    if (iVar1 != 0) {
      fw_0800027c();
    }
    param_1[0x1c] = (int)&DAT_20000c24;
    _DAT_20000c48 = param_1;
    fw_080010fc(0x1b,0);
    fw_080010e4(0x1b);
  }
  return;
}

