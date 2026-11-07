// rea decompile_all
// name: fw_08004554
// address: 0x8004554
// body: available
// range: 0x8004554-0x80045cb inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 fw_08004554(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  
  puVar1 = (uint *)*param_1;
  if (((puVar1[2] & 3) == 1) && (((*puVar1 & 1) != 0 || ((int)(puVar1[3] << 0x10) < 0)))) {
    return 0;
  }
  if ((puVar1[2] & 0x80000017) == 0) {
    puVar1[2] = puVar1[2] | 1;
    for (iVar2 = fw_080040e8(_DAT_20000140,1000000,0x80000017,param_4,0); iVar2 != 0;
        iVar2 = iVar2 + -1) {
    }
    iVar2 = fw_08005d54();
    do {
      if ((~*(uint *)*param_1 & 1) == 0) {
        return 0;
      }
      iVar3 = fw_08005d54();
    } while ((uint)(iVar3 - iVar2) < 3);
  }
  param_1[0xe] = param_1[0xe] | 0x10;
  param_1[0xf] = param_1[0xf] | 1;
  return 1;
}

