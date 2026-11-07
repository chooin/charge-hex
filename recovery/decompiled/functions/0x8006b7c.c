// rea decompile_all
// name: fw_08006b7c
// address: 0x8006b7c
// body: available
// range: 0x8006b7c-0x8006c4b inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


undefined4 fw_08006b7c(int *param_1,int *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  if ((char)param_1[0xf] == '\x01') {
    return 2;
  }
  *(undefined1 *)(param_1 + 0xf) = 1;
  *(undefined1 *)((int)param_1 + 0x3d) = 2;
  *(uint *)(*param_1 + 8) = *(uint *)(*param_1 + 8) & 0xffff0088;
  iVar2 = *param_2;
  if (iVar2 == 0x50) {
    fw_080085ca(*param_1,param_2[1],param_2[3],0xff00,param_4);
    iVar2 = 0x50;
    iVar1 = *param_1;
  }
  else if (iVar2 < 0x51) {
    if (iVar2 != 0x20) {
      if (iVar2 < 0x21) {
        if ((iVar2 != 0) && (iVar2 != 0x10)) goto LAB_08006c2e;
      }
      else if (iVar2 != 0x30) {
        if (iVar2 != 0x40) goto LAB_08006c2e;
        fw_080085ca(*param_1,param_2[1],param_2[3],0xff00,param_4);
        iVar2 = 0x40;
        iVar1 = *param_1;
        goto LAB_08006c2a;
      }
    }
    iVar1 = *param_1;
  }
  else {
    if (iVar2 != 0x60) {
      if (iVar2 == 0x70) {
        fw_080085a4(*param_1,param_2[2],param_2[1],param_2[3]);
        *(uint *)(*param_1 + 8) = *(uint *)(*param_1 + 8) | 0x77;
      }
      else if ((iVar2 != 0x1000) && (iVar2 == 0x2000)) {
        fw_080085a4(*param_1,param_2[2],param_2[1],param_2[3]);
        *(uint *)(*param_1 + 8) = *(uint *)(*param_1 + 8) | 0x4000;
      }
      goto LAB_08006c2e;
    }
    fw_080085ec(*param_1,param_2[1],param_2[3]);
    iVar2 = 0x60;
    iVar1 = *param_1;
  }
LAB_08006c2a:
  fw_080085ba(iVar1,iVar2);
LAB_08006c2e:
  *(undefined1 *)((int)param_1 + 0x3d) = 1;
  *(undefined1 *)(param_1 + 0xf) = 0;
  return 0;
}

