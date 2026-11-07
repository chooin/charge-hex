// rea decompile_all
// name: fw_08005210
// address: 0x8005210
// body: available
// range: 0x8005210-0x8005289 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_08005210(uint param_1,undefined1 param_2)

{
  uint uVar1;
  ushort uVar2;
  undefined4 local_14;
  undefined4 local_10;
  
  local_10 = 0;
  local_14 = param_1 & 0xff;
  uVar1 = local_14;
  local_14._0_1_ = (undefined1)param_1;
  if (param_1 == 1) {
    local_10._0_1_ = 0;
    uVar2 = (ushort)DAT_20000101;
  }
  else {
    if (param_1 != 2) {
      if (param_1 == 3) {
        local_14._0_3_ = CONCAT12((char)((uint)_DAT_20000114 >> 0x18),0xff03);
        local_14 = CONCAT13((char)((uint)_DAT_20000114 >> 0x10),(undefined3)local_14);
        local_10._0_2_ = CONCAT11((char)_DAT_20000114,(char)((uint)_DAT_20000114 >> 8));
        local_10 = (uint)(ushort)local_10;
        uVar1 = local_14;
      }
      else if ((param_1 == 4) || (param_1 == 5)) {
        local_14._0_3_ = CONCAT12(0xff,CONCAT11(param_2,(undefined1)local_14));
        local_14 = CONCAT13(0xff,(undefined3)local_14);
        local_10 = 0xffff;
        uVar1 = local_14;
      }
      goto LAB_08005278;
    }
    local_10._0_1_ = (undefined1)(_DAT_2000010a >> 8);
    uVar2 = _DAT_2000010a;
  }
  local_14 = (uint)CONCAT11(0xff,(undefined1)local_14);
  local_10._0_2_ = CONCAT11((char)uVar2,(undefined1)local_10);
  local_10 = (uint)(ushort)local_10;
  uVar1 = local_14;
LAB_08005278:
  local_14 = uVar1;
  fw_0800c7c4(0x36,6,1,&local_14,0xaa);
  return;
}

