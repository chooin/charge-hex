// rea decompile_all
// name: fw_08002788
// address: 0x8002788
// body: available
// range: 0x8002788-0x80028a1 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 fw_08002788(int *param_1)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  
  uVar5 = 0;
  *(uint *)*param_1 =
       *(uint *)*param_1 & 0xffff69f3 | param_1[2] | param_1[4] | param_1[5] | param_1[7];
  *(uint *)(*param_1 + 4) = *(uint *)(*param_1 + 4) & 0xffffcfff | param_1[3];
  *(uint *)(*param_1 + 8) = *(uint *)(*param_1 + 8) & 0xfffff4ff | param_1[8] | param_1[6];
  if (*param_1 == 0x40013800) {
    uVar2 = _DAT_40021030 & 3;
    if (uVar2 == 0) {
LAB_080027fc:
      iVar4 = 0;
    }
    else if (uVar2 == 1) {
      iVar4 = 4;
    }
    else if (uVar2 == 2) {
      iVar4 = 8;
    }
    else {
      if (uVar2 != 3) goto LAB_08002800;
      iVar4 = 2;
    }
  }
  else {
    if (*param_1 == 0x40004400) goto LAB_080027fc;
LAB_08002800:
    iVar4 = 0x10;
  }
  iVar3 = 0x8000;
  if (param_1[7] == 0x8000) {
    if (iVar4 == 0) {
      iVar3 = fw_080012f4();
LAB_08002830:
      if (iVar3 == 0) goto LAB_08002898;
    }
    else {
      if (iVar4 != 2) {
        if (iVar4 != 4) {
          if (iVar4 == 8) goto LAB_08002834;
          goto LAB_08002890;
        }
        iVar3 = fw_08001314();
        goto LAB_08002830;
      }
      iVar3 = 8000000;
    }
LAB_08002834:
    uVar1 = fw_080000e4(iVar3 * 2 + ((uint)param_1[1] >> 1));
    uVar2 = (uint)uVar1;
    if (0xffef < uVar2 - 0x10) {
LAB_08002890:
      uVar5 = 1;
      goto LAB_08002898;
    }
    uVar2 = (uVar2 & 0xf) >> 1 | uVar2 & 0xfff0;
  }
  else {
    if (iVar4 == 0) {
      iVar3 = fw_080012f4();
LAB_08002878:
      if (iVar3 == 0) goto LAB_08002898;
    }
    else if (iVar4 == 2) {
      iVar3 = 8000000;
    }
    else {
      if (iVar4 == 4) {
        iVar3 = fw_08001314();
        goto LAB_08002878;
      }
      if (iVar4 != 8) goto LAB_08002890;
    }
    uVar1 = fw_080000e4(((uint)param_1[1] >> 1) + iVar3);
    uVar2 = (uint)uVar1;
    if (0xffef < uVar2 - 0x10) goto LAB_08002890;
  }
  *(uint *)(*param_1 + 0xc) = uVar2;
LAB_08002898:
  param_1[0x19] = 0;
  param_1[0x1a] = 0;
  return uVar5;
}

