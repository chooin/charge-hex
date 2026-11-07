// rea decompile_all
// name: fw_0800a090
// address: 0x800a090
// body: available
// range: 0x800a090-0x800a11d inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint fw_0800a090(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  short sVar1;
  short sVar2;
  ushort uVar3;
  int iVar4;
  uint uVar5;
  uint extraout_r2;
  uint uVar6;
  undefined8 uVar7;
  
  param_1 = param_1 * 0x34;
  if (*(char *)(param_1 + 0x20000613) == '\x01') {
    return 0;
  }
  sVar1 = *(short *)(param_1 + 0x200005fc);
  if (sVar1 == 0) {
LAB_0800a0be:
    sVar2 = 1;
  }
  else {
    sVar2 = fw_080040e8(*(undefined4 *)(param_1 + 0x20000608),sVar1,param_3,param_4,param_4);
    if (sVar2 == 0) goto LAB_0800a0be;
  }
  uVar3 = fw_080040e8(*(undefined4 *)(param_1 + 0x200005e4),sVar2);
  uVar6 = (uint)uVar3;
  if ((sVar1 == 0) || (iVar4 = fw_080040e8(*(undefined2 *)(param_1 + 0x200005f0),sVar1), iVar4 == 0)
     ) {
    iVar4 = 1;
  }
  uVar7 = fw_080040e8(*(undefined2 *)(param_1 + 0x200005ea),iVar4);
  iVar4 = fw_0800a054((int)uVar7,(int)((ulonglong)uVar7 >> 0x20),(int)uVar7);
  if (iVar4 == 0) {
    if (uVar6 <= extraout_r2) goto LAB_0800a0fa;
  }
  else if (iVar4 != 2) goto LAB_0800a0fa;
  uVar6 = extraout_r2;
LAB_0800a0fa:
  uVar5 = (uint)*(ushort *)(param_1 + 0x200005fe);
  if ((uVar5 < uVar6) ||
     (((uint)(*(int *)(param_1 + 0x20000608) - *(int *)(param_1 + 0x200005e4)) <
       (uint)_DAT_2000087a * 2 + 0x3c && (uVar6 + 1 == uVar5)))) {
    uVar6 = uVar5;
  }
  return uVar6;
}

