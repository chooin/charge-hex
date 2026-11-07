// rea decompile_all
// name: fw_08001df0
// address: 0x8001df0
// body: available
// range: 0x8001df0-0x8001ec7 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


undefined4 fw_08001df0(uint param_1,int param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  if (param_3 <= 0x10000 - param_1) {
    uVar5 = 0x80 - (param_1 & 0x7f);
    if (uVar5 < param_3) {
      iVar1 = param_3 - uVar5;
      uVar2 = iVar1 % 0x80 & 0xffff;
      iVar4 = param_2;
      iVar3 = fw_08000e40(&DAT_20000850,0xa0,param_1,2,param_2,uVar5,500,uVar2,param_1,param_2,
                          param_3);
      if (iVar3 != 0) {
        return 1;
      }
      uVar6 = param_3;
      iVar3 = fw_08001dbc();
      if (iVar3 != 0) {
        return 1;
      }
      param_1 = param_1 + uVar5;
      param_2 = param_2 + uVar5;
      uVar5 = (((uint)(iVar1 >> 0x1f) >> 0x19) + iVar1 & 0x7fffff) >> 7;
      param_3 = uVar2;
      while( true ) {
        param_1 = param_1 & 0xffff;
        if (uVar5 == 0) break;
        iVar1 = fw_08000e40(&DAT_20000850,0xa0,param_1,2,param_2,0x80,500,param_3,param_1,iVar4,
                            uVar6);
        if (iVar1 != 0) {
          return 1;
        }
        iVar1 = fw_08001dbc();
        if (iVar1 != 0) {
          return 1;
        }
        param_1 = param_1 + 0x80;
        param_2 = param_2 + 0x80;
        uVar5 = uVar5 - 1 & 0xffff;
      }
      if (param_3 == 0) {
        return 0;
      }
    }
    iVar4 = fw_08000e40(&DAT_20000850,0xa0,param_1,2,param_2,param_3,500);
    if ((iVar4 == 0) && (iVar4 = fw_08001dbc(), iVar4 == 0)) {
      return 0;
    }
  }
  return 1;
}

