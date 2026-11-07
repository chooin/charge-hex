// rea decompile_all
// name: fw_08009e30
// address: 0x8009e30
// body: available
// range: 0x8009e30-0x8009f33 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_08009e30(int param_1,int param_2)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = param_1 * 0x34;
  iVar3 = *(int *)(iVar4 + 0x200005e4);
  uVar2 = fw_080040e8(iVar3,0x3c);
  uVar1 = *(undefined2 *)(iVar4 + 0x200005ea);
  if ((*(short *)(iVar4 + 0x20000600) != 0) &&
     ((uint)(*(int *)(iVar4 + 0x20000608) - iVar3) < (uint)_DAT_2000087a * 2 + 0x3c)) {
    uVar2 = 0xffff;
  }
  *(undefined4 *)(iVar4 + 0x200005e4) = 0;
  *(undefined2 *)(iVar4 + 0x200005e8) = 0;
  *(undefined2 *)(iVar4 + 0x200005ea) = 0;
  *(undefined4 *)(iVar4 + 0x200005ec) = 0;
  *(undefined1 *)(iVar4 + 0x20000617) = 0;
  *(undefined1 *)(iVar4 + 0x20000615) = 0;
  *(undefined1 *)(iVar4 + 0x20000616) = 0;
  *(undefined1 *)(iVar4 + 0x200005f9) = 0;
  if (_DAT_20000876 == 0) {
    (&DAT_20000611)[iVar4] = 0;
  }
  else {
    (&DAT_20000611)[iVar4] = 2;
  }
  fw_08009e14(param_1);
  iVar3 = param_1 * 2;
  *(undefined2 *)(iVar3 + 0x200008e6) = 0;
  *(undefined2 *)(iVar3 + 0x200008fe) = 0;
  *(undefined2 *)(iVar3 + 0x20000916) = 0;
  *(undefined2 *)(iVar3 + 0x2000092e) = 0;
  *(undefined2 *)(iVar3 + 0x20000946) = 0;
  *(undefined2 *)(iVar3 + 0x2000095e) = 0;
  *(undefined2 *)(iVar3 + 0x20000976) = 0;
  *(undefined1 *)(iVar4 + 0x200005fa) = 0;
  if (*(short *)(iVar4 + 0x200005f2) != 0) {
    *(undefined1 *)(iVar4 + 0x20000614) = 1;
  }
  fw_0800c85c(param_1,0);
  if ((param_2 == 4) || (param_2 == 1)) {
    fw_0800cc44(10);
    *(undefined1 *)(iVar4 + 0x20000612) = 1;
  }
  else {
    fw_0800a5b0(param_1);
  }
  if (param_2 != 0xb) {
    if (_DAT_20000878 == 3) {
      _DAT_200000c8 = _DAT_200000c8 + 1;
      fw_0800bb7c(param_1 + 1U & 0xff,uVar2,param_2,uVar1,_DAT_200000c8);
      DAT_200000be = 3;
      DAT_200000bf = 0x2c;
      _DAT_200008de = 0x14;
    }
    else if (_DAT_20000878 == 0) {
      fw_0800bb44(param_1 + 1U & 0xff,uVar2,param_2,uVar1);
    }
  }
  *(undefined1 *)(iVar4 + 0x20000613) = 0;
  return;
}

