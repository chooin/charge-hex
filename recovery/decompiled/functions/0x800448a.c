// rea decompile_all
// name: fw_0800448a
// address: 0x800448a
// body: available
// range: 0x800448a-0x800452d inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


uint fw_0800448a(undefined4 param_1,int param_2,int param_3,int param_4,uint param_5,int param_6,
                int param_7)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  ulonglong uVar4;
  undefined8 uVar5;
  longlong lVar6;
  
  if (param_2 == 0) {
    iVar1 = fw_08009574();
    iVar1 = iVar1 + 0x20;
  }
  else {
    iVar1 = fw_08009574(param_2);
  }
  uVar4 = fw_080043ce(param_1,param_2,iVar1);
  uVar2 = (uint)(uVar4 >> 0x20);
  uVar3 = (uint)uVar4;
  if ((uVar3 != 0 || param_3 != 0) || (uVar2 != 0 || param_4 != 0)) {
    if (param_3 != 0 || param_4 != 0) {
      uVar5 = fw_0800419c(param_3,param_4,0x40 - iVar1);
      lVar6 = fw_080043ce(param_3,param_4,iVar1);
      uVar4 = CONCAT44(uVar2 | (uint)((ulonglong)uVar5 >> 0x20),
                       uVar3 | (uint)uVar5 | (uint)(lVar6 != 0));
    }
    uVar3 = (uint)(uVar4 >> 0xb);
    iVar1 = (param_7 - iVar1) + 10;
    if (iVar1 < 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = fw_08004470(uVar3 + param_5,
                          iVar1 * 0x100000 + (int)((uVar4 >> 0xb) >> 0x20) + param_6 +
                          (uint)CARRY4(uVar3,param_5),0,(int)uVar4 << 0x15);
    }
  }
  return uVar3;
}

