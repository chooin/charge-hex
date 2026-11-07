// rea decompile_all
// name: fw_08007fc4
// address: 0x8007fc4
// body: available
// range: 0x8007fc4-0x8008027 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_08007fc4(void)

{
  int iVar1;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  _DAT_20000bc8 = 0x40012c00;
  _DAT_20000bd0 = 0;
  _DAT_20000bcc = 0x2f;
  _DAT_20000bd8 = 0;
  _DAT_20000bdc = 0;
  _DAT_20000bd4 = 999;
  _DAT_20000be0 = 0x80;
  iVar1 = fw_08006ab0();
  if (iVar1 != 0) {
    fw_0800529c();
  }
  local_20 = 0x1000;
  iVar1 = fw_08006b7c(&DAT_20000bc8,&local_20);
  if (iVar1 != 0) {
    fw_0800529c();
  }
  local_10 = 0;
  local_c = 0;
  iVar1 = fw_08006a54(&DAT_20000bc8,&local_10);
  if (iVar1 != 0) {
    fw_0800529c();
  }
  return;
}

