// rea decompile_all
// name: fw_080026cc
// address: 0x80026cc
// body: available
// range: 0x80026cc-0x8002727 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


void fw_080026cc(int param_1)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 0x24);
  if (*(int *)(param_1 + 0x18) != 0x20) {
    *(undefined2 *)((int)piVar1 + 0x5a) = 0;
    *(uint *)*piVar1 = *(uint *)*piVar1 & 0xfffffeff;
    *(uint *)(*piVar1 + 8) = *(uint *)(*piVar1 + 8) & 0xfffffffe;
    *(uint *)(*piVar1 + 8) = *(uint *)(*piVar1 + 8) & 0xffffffbf;
    piVar1[0x1f] = 0x20;
    if (piVar1[0x18] == 1) {
      *(uint *)*piVar1 = *(uint *)*piVar1 & 0xffffffef;
    }
  }
  if (piVar1[0x18] != 1) {
    fw_08001cb4();
    return;
  }
  fw_080017bc(piVar1,(short)piVar1[0x16]);
  return;
}

