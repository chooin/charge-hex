// rea decompile_all
// name: fw_0800ca80
// address: 0x800ca80
// body: available
// range: 0x800ca80-0x800cc27 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 fw_0800ca80(char param_1,uint param_2,uint param_3,uint param_4,int param_5)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int local_2c;
  uint local_20;
  uint local_1c;
  uint local_18;
  
  uVar2 = (uint)(byte)(param_1 - 1);
  iVar3 = fw_0800a690();
  if (iVar3 != 0) {
    fw_0800cdb8(0xf);
    return 0xb;
  }
  if (param_5 == 2) {
    uVar5 = 2;
LAB_0800cad4:
    fw_0800cdb8(0xf);
    return uVar5;
  }
  iVar3 = (uint)(byte)(param_1 - 1) * 0x34;
  local_1c = param_3;
  if (param_5 == 3) {
    if (*(char *)(iVar3 + 0x200005fa) != '\0') {
      uVar5 = 0xc;
      goto LAB_0800cad4;
    }
LAB_0800cade:
    if (param_3 == 0) {
      local_1c = (uint)_DAT_2000087e;
    }
    *(undefined1 *)(iVar3 + 0x20000613) = 1;
    local_18 = 0;
    local_20 = 0;
    _DAT_200008e2 = 0x1e;
    DAT_20000122 = 5 < uVar2;
    *(undefined1 *)(iVar3 + 0x200005f9) = 3;
    if (param_5 == 4) {
      *(undefined1 *)(iVar3 + 0x20000616) = 1;
    }
  }
  else if ((param_5 == 1) || (local_20 = param_2, local_18 = param_4, param_5 == 4))
  goto LAB_0800cade;
  if (*(int *)(iVar3 + 0x200005e4) == 0) {
    *(undefined2 *)(uVar2 * 2 + 0x2000092e) = 0x1e;
  }
  _DAT_200008d6 = 0;
  local_2c = local_1c * 0x3c;
  *(short *)(iVar3 + 0x200005fc) = *(short *)(iVar3 + 0x200005fc) + (short)local_20;
  *(short *)(iVar3 + 0x20000600) = *(short *)(iVar3 + 0x20000600) + (short)local_20;
  if (local_18 == 0) {
    local_18 = 0;
    if (*(char *)(iVar3 + 0x20000613) != '\0') goto LAB_0800cb7c;
    if (local_20 < 10) {
      local_20 = 10;
    }
    iVar4 = fw_080040e8(local_20,10);
    local_18 = (uint)_DAT_2000085c * iVar4 * 10;
  }
  if (0x2706 < local_18) {
    local_18 = 0x2706;
  }
LAB_0800cb7c:
  if ((param_5 == 0) && (bVar1 = *(byte *)(iVar3 + 0x200005f9), bVar1 != 0)) {
    local_2c = fw_080040e8(local_2c,100);
    local_2c = (uint)*(ushort *)(&DAT_20000866 + (uint)bVar1 * 2) * local_2c;
  }
  *(int *)(iVar3 + 0x20000608) = *(int *)(iVar3 + 0x20000608) + local_2c;
  *(int *)(iVar3 + 0x200005e4) = *(int *)(iVar3 + 0x200005e4) + local_2c;
  if (0x92784 < *(uint *)(iVar3 + 0x20000608)) {
    *(undefined4 *)(iVar3 + 0x20000608) = 0x92784;
  }
  if (0x92784 < *(uint *)(iVar3 + 0x200005e4)) {
    *(undefined4 *)(iVar3 + 0x200005e4) = 0x92784;
  }
  if (*(char *)(iVar3 + 0x20000613) == '\0') {
    *(short *)(iVar3 + 0x200005f0) = *(short *)(iVar3 + 0x200005f0) + (short)local_18;
    *(short *)(iVar3 + 0x200005ea) = *(short *)(iVar3 + 0x200005ea) + (short)local_18;
    *(uint *)(iVar3 + 0x200005ec) = *(int *)(iVar3 + 0x200005ec) + local_18 * 36000;
  }
  iVar4 = fw_08009fec(uVar2);
  if (iVar4 != 0) {
    iVar4 = fw_0800a018(uVar2);
    if (iVar4 == 1) {
      uVar5 = 0x33;
    }
    else {
      uVar5 = 2;
    }
    fw_0800cdb8(uVar5);
    *(undefined1 *)(iVar3 + 0x200005fa) = 2;
    *(undefined1 *)(iVar3 + 0x20000617) = 0;
    fw_0800c85c(uVar2,1);
  }
  fw_0800a65c();
  _DAT_200008c4 = 0;
  DAT_200008c2 = 2;
  DAT_200008c6 = param_1;
  *(undefined1 *)(iVar3 + 0x20000612) = 1;
  return 1;
}

