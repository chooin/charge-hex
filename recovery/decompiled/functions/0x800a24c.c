// rea decompile_all
// name: fw_0800a24c
// address: 0x800a24c
// body: available
// range: 0x800a24c-0x800a2b9 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_0800a24c(int param_1)

{
  short sVar1;
  int iVar2;
  undefined1 local_20;
  undefined1 local_1f;
  undefined1 local_1e;
  undefined1 local_14;
  undefined1 local_13;
  undefined1 local_12;
  undefined1 local_11;
  
  if ((((_DAT_200008e0 == 0) && (_DAT_2000086e != 0)) &&
      (iVar2 = param_1 * 0x34, *(char *)(iVar2 + 0x200005fa) == '\0')) &&
     (((sVar1 = *(short *)(iVar2 + 0x200005f2), sVar1 != 0 && (_DAT_200008dc == 0)) &&
      (*(short *)(iVar2 + 0x2000060e) != 0)))) {
    _DAT_2000101a = 0xaa33;
    _DAT_2000101c = *(undefined4 *)(iVar2 + 0x20000604);
    DAT_20001018 = 0x66;
    DAT_20001022 = (undefined1)param_1;
    _DAT_200008e0 = 0xf;
    local_14 = (undefined1)((uint)_DAT_2000101c >> 0x18);
    local_13 = (undefined1)((uint)_DAT_2000101c >> 0x10);
    local_12 = (undefined1)((uint)_DAT_2000101c >> 8);
    local_11 = (undefined1)_DAT_2000101c;
    local_20 = 0x66;
    local_1f = (undefined1)((ushort)sVar1 >> 8);
    local_1e = (undefined1)sVar1;
    _DAT_20001020 = sVar1;
    fw_0800964e(&local_14,&local_20);
  }
  return;
}

