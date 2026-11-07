// rea decompile_all
// name: fw_08002250
// address: 0x8002250
// body: available
// range: 0x8002250-0x800230b inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


int fw_08002250(byte *param_1,int *param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  byte local_28 [4];
  int local_24;
  byte *pbStack_20;
  int *piStack_1c;
  undefined4 local_18;
  
  iVar3 = 0;
  *param_2 = 0;
  pbStack_20 = param_1;
  piStack_1c = param_2;
  local_18 = param_3;
  iVar1 = fw_08001bb8(&DAT_20000ba0,local_28,1,param_3);
  if (iVar1 != 0) goto LAB_080022ae;
  if (local_28[0] == 0x18) {
    iVar2 = fw_08001bb8(&DAT_20000ba0,local_28,1,local_18);
    if ((iVar2 == 0) && (local_28[0] == 0x18)) {
      iVar3 = 2;
    }
    else {
      iVar1 = 1;
    }
  }
  else {
    if (local_28[0] < 0x19) {
      if (local_28[0] == 1) {
        iVar3 = 0x80;
      }
      else {
        if (local_28[0] != 2) {
          if (local_28[0] != 4) goto LAB_0800228c;
          goto LAB_0800228e;
        }
        iVar3 = 0x400;
      }
      *param_1 = local_28[0];
      iVar1 = fw_08001bb8(&DAT_20000ba0,param_1 + 2,iVar3 + 4,local_18);
      if (iVar1 == 0) {
        if (param_1[2] == (param_1[3] ^ 0xff)) {
          local_24 = (uint)param_1[iVar3 + 5] + (uint)param_1[iVar3 + 4] * 0x100;
          iVar2 = fw_080001fc(param_1 + 4,iVar3);
          if (iVar2 == local_24) goto LAB_080022ae;
        }
        iVar3 = 0;
        iVar1 = 1;
      }
      else {
        iVar3 = 0;
      }
      goto LAB_080022ae;
    }
    if ((local_28[0] == 0x41) || (local_28[0] == 0x61)) {
      iVar1 = 2;
    }
    else {
LAB_0800228c:
      iVar1 = 1;
    }
  }
LAB_0800228e:
  *param_1 = local_28[0];
LAB_080022ae:
  *param_2 = iVar3;
  return iVar1;
}

