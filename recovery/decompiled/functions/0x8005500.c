// rea decompile_all
// name: fw_08005500
// address: 0x8005500
// body: available
// range: 0x8005500-0x80055fd inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 fw_08005500(int *param_1,int *param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  if ((char)param_1[0xd] == '\x01') {
    return 2;
  }
  *(undefined1 *)(param_1 + 0xd) = 1;
  iVar2 = *param_1;
  if (*(int *)(iVar2 + 8) << 0x1d < 0) {
    param_1[0xe] = param_1[0xe] | 0x20;
    uVar3 = 1;
  }
  else if (param_2[1] == 0x1001) {
    *(uint *)(iVar2 + 0x28) = *(uint *)(iVar2 + 0x28) & ~(1 << (sbyte)*param_2);
    iVar2 = *param_2;
    if ((iVar2 == 0x10) || (iVar2 == 0x11)) {
      if (iVar2 == 0x10) {
        uVar1 = 0x800000;
      }
      else {
        uVar1 = 0x400000;
      }
      _DAT_40012708 = _DAT_40012708 & ~uVar1;
    }
  }
  else {
    *(uint *)(iVar2 + 0x28) = *(uint *)(iVar2 + 0x28) | 1 << (sbyte)*param_2;
    iVar2 = param_1[0xb];
    if ((((((iVar2 != 0x10000000) && (iVar2 != 1)) && (iVar2 != 2)) &&
         ((iVar2 != 3 && (iVar2 != 4)))) && ((iVar2 != 5 && ((iVar2 != 6 && (iVar2 != 7)))))) &&
       (iVar2 = *param_1, param_2[2] != (*(uint *)(iVar2 + 0x14) & 7))) {
      *(uint *)(iVar2 + 0x14) = *(uint *)(iVar2 + 0x14) & 0xfffffff8;
      *(uint *)(*param_1 + 0x14) = *(uint *)(*param_1 + 0x14) | *(byte *)(param_2 + 2) & 7;
    }
    iVar2 = *param_2;
    if ((iVar2 == 0x10) || (iVar2 == 0x11)) {
      if (iVar2 == 0x10) {
        uVar1 = 0x800000;
      }
      else {
        uVar1 = 0x400000;
      }
      _DAT_40012708 = _DAT_40012708 | uVar1;
      if (*param_2 == 0x10) {
        iVar2 = fw_080040e8(_DAT_20000140,1000000,uVar1,_DAT_40012708,0);
        for (iVar2 = iVar2 * 10; iVar2 != 0; iVar2 = iVar2 + -1) {
        }
      }
    }
  }
  *(undefined1 *)(param_1 + 0xd) = 0;
  return uVar3;
}

