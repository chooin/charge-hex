// rea decompile_all
// name: fw_080028bc
// address: 0x80028bc
// body: available
// range: 0x80028bc-0x800293b inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


undefined4 fw_080028bc(int *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  param_1[0x15] = param_2;
  *(short *)(param_1 + 0x16) = (short)param_3;
  param_1[0x20] = 0;
  param_1[0x1f] = 0x22;
  if (param_1[0x1c] != 0) {
    *(undefined4 *)(param_1[0x1c] + 0x28) = 0x80026cd;
    *(undefined4 *)(param_1[0x1c] + 0x2c) = 0x8002729;
    *(undefined4 *)(param_1[0x1c] + 0x30) = 0x8002681;
    *(undefined4 *)(param_1[0x1c] + 0x34) = 0;
    iVar1 = fw_08000674(param_1[0x1c],*param_1 + 0x24,param_1[0x15],param_3,param_4);
    if (iVar1 != 0) {
      param_1[0x20] = 0x10;
      *(undefined1 *)(param_1 + 0x1d) = 0;
      param_1[0x1e] = 0x20;
      return 1;
    }
  }
  *(undefined1 *)(param_1 + 0x1d) = 0;
  *(uint *)*param_1 = *(uint *)*param_1 | 0x100;
  *(uint *)(*param_1 + 8) = *(uint *)(*param_1 + 8) | 1;
  *(uint *)(*param_1 + 8) = *(uint *)(*param_1 + 8) | 0x40;
  return 0;
}

