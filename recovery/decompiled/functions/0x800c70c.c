// rea decompile_all
// name: fw_0800c70c
// address: 0x800c70c
// body: available
// range: 0x800c70c-0x800c783 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


void fw_0800c70c(int param_1,int param_2,undefined4 param_3,int param_4)

{
  byte bVar1;
  int iVar2;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  int extraout_r1_01;
  undefined8 uVar3;
  
  bVar1 = DAT_200000f4;
  DAT_200000e2 = (&DAT_200000e6)[param_1];
  DAT_200000e1 = DAT_200000f0;
  DAT_200000e0 = (&DAT_200000e6)[param_2];
  if (param_4 != 0) {
    if (param_4 == 1) {
      DAT_200000e5 = DAT_200000f3;
      uVar3 = fw_080040e8(param_3,10);
      iVar2 = (int)((ulonglong)uVar3 >> 0x20);
      DAT_200000e4 = (&DAT_200000e6)[(int)uVar3] | bVar1;
    }
    else {
      fw_080040e8(param_3,1000);
      iVar2 = fw_080040e8(extraout_r1,100);
      DAT_200000e5 = (&DAT_200000e6)[iVar2] | bVar1;
      fw_080040e8(param_3,100);
      iVar2 = fw_080040e8(extraout_r1_00,10);
      DAT_200000e4 = (&DAT_200000e6)[iVar2];
      fw_080040e8(param_3,10);
      iVar2 = extraout_r1_01;
    }
    DAT_200000e3 = (&DAT_200000e6)[iVar2];
    return;
  }
  fw_0800a38c(1,param_3,param_3,0,0);
  return;
}

