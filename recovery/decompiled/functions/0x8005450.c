// rea decompile_all
// name: fw_08005450
// address: 0x8005450
// body: available
// range: 0x8005450-0x80054ff inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


undefined4 fw_08005450(int *param_1)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  
  uVar5 = 0;
  if ((char)param_1[0xd] == '\x01') {
    return 2;
  }
  *(undefined1 *)(param_1 + 0xd) = 1;
  puVar1 = (uint *)*param_1;
  if (((puVar1[2] & 3) == 1) && (((*puVar1 & 1) != 0 || ((int)(puVar1[3] << 0x10) < 0)))) {
    param_1[0xe] = param_1[0xe] | 0x20;
    uVar5 = 1;
  }
  else {
    param_1[0xe] = param_1[0xe] & 0xfffffeffU | 2;
    uVar4 = puVar1[3];
    puVar1[3] = puVar1[3] & 0xfffffffc;
    *(uint *)(*param_1 + 8) = *(uint *)(*param_1 + 8) | 0x80000000;
    iVar2 = fw_08005d54();
    while (*(int *)(*param_1 + 8) < 0) {
      iVar3 = fw_08005d54();
      if (2 < (uint)(iVar3 - iVar2)) {
        param_1[0xe] = param_1[0xe] & 0xfffffffdU | 0x10;
        *(undefined1 *)(param_1 + 0xd) = 0;
        return 1;
      }
    }
    *(uint *)(*param_1 + 0xc) = *(uint *)(*param_1 + 0xc) | uVar4 & 3;
    param_1[0xe] = (param_1[0xe] & 0xfffffffcU) + 1;
  }
  *(undefined1 *)(param_1 + 0xd) = 0;
  return uVar5;
}

