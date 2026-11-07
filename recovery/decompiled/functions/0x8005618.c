// rea decompile_all
// name: fw_08005618
// address: 0x8005618
// body: available
// range: 0x8005618-0x8005785 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


undefined4 fw_08005618(int *param_1)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  if (param_1 == (int *)0x0) {
    return 1;
  }
  if (param_1[0xe] == 0) {
    param_1[0xf] = 0;
    *(undefined1 *)(param_1 + 0xd) = 0;
    fw_08005790(param_1);
  }
  if ((param_1[0xe] * 0x8000000 < 0) || (puVar1 = (uint *)*param_1, (int)(puVar1[2] << 0x1d) < 0)) {
    param_1[0xe] = param_1[0xe] | 0x10;
  }
  else {
    param_1[0xe] = param_1[0xe] & 0xfffffeffU | 2;
    if (((puVar1[2] & 3) != 1) || (((*puVar1 & 1) == 0 && (-1 < (int)(puVar1[3] << 0x10))))) {
      puVar1[3] = puVar1[3] & 0xffffffe7 | param_1[2];
      *(uint *)(*param_1 + 0x10) = *(uint *)(*param_1 + 0x10) & 0x3fffffff | param_1[1];
    }
    *(uint *)(*param_1 + 0xc) = *(uint *)(*param_1 + 0xc) & 0xfffe0219;
    if (param_1[10] == 1) {
      uVar3 = 0;
    }
    else {
      uVar3 = 0x1000;
    }
    if (param_1[4] == 2) {
      uVar4 = 4;
    }
    else {
      uVar4 = 0;
    }
    uVar3 = (uint)*(byte *)(param_1 + 6) << 0xe | (uint)*(byte *)((int)param_1 + 0x19) << 0xf |
            (uint)*(byte *)((int)param_1 + 0x1a) << 0xd | uVar3 | param_1[3] | uVar4 |
            (uint)*(byte *)(param_1 + 9) << 1;
    if (*(char *)((int)param_1 + 0x1b) == '\x01') {
      if (*(byte *)((int)param_1 + 0x1a) == 0) {
        uVar3 = uVar3 | 0x10000;
      }
      else {
        param_1[0xe] = param_1[0xe] | 0x20;
        param_1[0xf] = param_1[0xf] | 1;
      }
    }
    if (param_1[7] != 0x1c1) {
      uVar3 = uVar3 | param_1[7] | param_1[8];
    }
    *(uint *)(*param_1 + 0xc) = *(uint *)(*param_1 + 0xc) | uVar3;
    iVar2 = param_1[0xb];
    if (((((iVar2 == 0x10000000) || (iVar2 == 1)) || (iVar2 == 2)) || ((iVar2 == 3 || (iVar2 == 4)))
        ) || ((iVar2 == 5 || ((iVar2 == 6 || (iVar2 == 7)))))) {
      *(uint *)(*param_1 + 0x14) = *(uint *)(*param_1 + 0x14) & 0xfffffff8;
      *(uint *)(*param_1 + 0x14) = *(uint *)(*param_1 + 0x14) | *(ushort *)(param_1 + 0xb) & 7;
    }
    if ((*(uint *)(*param_1 + 0xc) & 0x833fffe7) == uVar3) {
      param_1[0xf] = 0;
      param_1[0xe] = (param_1[0xe] & 0xfffffffcU) + 1;
      return 0;
    }
    param_1[0xe] = param_1[0xe] & 0xfffffffdU | 0x10;
    param_1[0xf] = param_1[0xf] | 1;
  }
  return 1;
}

