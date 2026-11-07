// rea decompile_all
// name: fw_08000b28
// address: 0x8000b28
// body: available
// range: 0x8000b28-0x8000bd7 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


undefined4 fw_08000b28(int *param_1)

{
  uint uVar1;
  
  if (param_1 == (int *)0x0) {
    return 1;
  }
  if (*(char *)((int)param_1 + 0x41) == '\0') {
    *(undefined1 *)(param_1 + 0x10) = 0;
    fw_08000fc4(param_1);
  }
  *(undefined1 *)((int)param_1 + 0x41) = 0x24;
  *(uint *)*param_1 = *(uint *)*param_1 & 0xfffffffe;
  *(uint *)(*param_1 + 0x10) = param_1[1] & 0xf0ffffff;
  uVar1 = 0x8000;
  *(uint *)(*param_1 + 8) = *(uint *)(*param_1 + 8) & 0xffff7fff;
  if (param_1[3] != 1) {
    uVar1 = 0x8400;
  }
  *(uint *)(*param_1 + 8) = param_1[2] | uVar1;
  if (param_1[3] == 2) {
    *(undefined4 *)(*param_1 + 4) = 0x800;
  }
  *(uint *)(*param_1 + 4) = *(uint *)(*param_1 + 4) | 0x2008000;
  *(uint *)(*param_1 + 0xc) = *(uint *)(*param_1 + 0xc) & 0xffff7fff;
  *(int *)(*param_1 + 0xc) = param_1[4] | param_1[5] | param_1[6] << 8;
  *(int *)*param_1 = param_1[7] | param_1[8];
  *(uint *)*param_1 = *(uint *)*param_1 | 1;
  param_1[0x11] = 0;
  *(undefined1 *)((int)param_1 + 0x41) = 0x20;
  param_1[0xc] = 0;
  *(undefined1 *)((int)param_1 + 0x42) = 0;
  return 0;
}

