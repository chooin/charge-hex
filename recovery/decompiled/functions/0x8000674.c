// rea decompile_all
// name: fw_08000674
// address: 0x8000674
// body: available
// range: 0x8000674-0x80006dd inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


undefined4 fw_08000674(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char *pcVar1;
  uint *puVar2;
  uint uVar3;
  undefined4 uVar4;
  
  pcVar1 = (char *)(param_1 + 8);
  uVar4 = 0;
  if (*pcVar1 != '\x01') {
    *pcVar1 = '\x01';
    if (*(char *)((int)param_1 + 0x21) == '\x01') {
      *(undefined1 *)((int)param_1 + 0x21) = 2;
      param_1[0xe] = 0;
      *(uint *)*param_1 = *(uint *)*param_1 & 0xfffffffe;
      fw_08000254(param_1,param_2,param_3,param_4,param_4);
      puVar2 = (uint *)*param_1;
      if (param_1[0xb] == 0) {
        *puVar2 = *puVar2 | 10;
        puVar2 = (uint *)*param_1;
        uVar3 = *puVar2 & 0xfffffffb;
      }
      else {
        uVar3 = *puVar2 | 0xe;
      }
      *puVar2 = uVar3;
      *(uint *)*param_1 = *(uint *)*param_1 | 1;
    }
    else {
      *pcVar1 = '\0';
      uVar4 = 2;
    }
    return uVar4;
  }
  return 2;
}

