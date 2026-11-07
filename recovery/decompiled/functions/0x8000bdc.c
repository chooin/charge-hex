// rea decompile_all
// name: fw_08000bdc
// address: 0x8000bdc
// body: available
// range: 0x8000bdc-0x8000cdb inclusive
// range: 0x8000cde-0x8000ce1 inclusive
// non_contiguous: true
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


undefined4
fw_08000bdc(int *param_1,undefined4 param_2,int param_3,undefined2 param_4,undefined4 param_5)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 uVar4;
  undefined4 uVar5;
  int *piVar6;
  undefined4 uVar7;
  int *piVar8;
  
  piVar6 = param_1 + 0x10;
  if ((*(char *)((int)param_1 + 0x41) == ' ') && ((char)*piVar6 != '\x01')) {
    *(char *)piVar6 = '\x01';
    piVar8 = param_1;
    uVar2 = fw_08000a88();
    iVar3 = fw_08002048(param_1,0x8000,1,0x19,uVar2,piVar8);
    if (iVar3 == 0) {
      *(undefined1 *)((int)param_1 + 0x41) = 0x21;
      *(undefined1 *)((int)param_1 + 0x42) = 0x10;
      param_1[0x11] = 0;
      param_1[9] = param_3;
      *(undefined2 *)((int)param_1 + 0x2a) = param_4;
      param_1[0xd] = 0;
      if (*(ushort *)((int)param_1 + 0x2a) < 0x100) {
        *(undefined2 *)(param_1 + 10) = *(undefined2 *)((int)param_1 + 0x2a);
        uVar7 = 0x80002000;
        goto LAB_08000cb8;
      }
      *(undefined2 *)(param_1 + 10) = 0xff;
      uVar7 = 0x80002000;
      do {
        uVar4 = 0xff;
        uVar5 = 0x1000000;
        while( true ) {
          fw_08002020(param_1,param_2,uVar4,uVar5,uVar7);
          do {
            if (*(short *)((int)param_1 + 0x2a) == 0) {
              iVar3 = fw_08002096();
              if (iVar3 == 0) {
                *(undefined4 *)(*param_1 + 0x1c) = 0x20;
                *(uint *)(*param_1 + 4) = *(uint *)(*param_1 + 4) & 0xfe00e800;
                *(undefined1 *)((int)param_1 + 0x41) = 0x20;
                *(undefined1 *)((int)param_1 + 0x42) = 0;
                *(char *)piVar6 = '\0';
                return 0;
              }
              goto LAB_08000c88;
            }
            iVar3 = fw_080020e2(param_1,param_5,uVar2);
            if (iVar3 != 0) goto LAB_08000c88;
            *(uint *)(*param_1 + 0x28) = (uint)*(byte *)param_1[9];
            param_1[9] = param_1[9] + 1;
            *(short *)((int)param_1 + 0x2a) = *(short *)((int)param_1 + 0x2a) + -1;
            sVar1 = (short)param_1[10] + -1;
            *(short *)(param_1 + 10) = sVar1;
          } while ((*(short *)((int)param_1 + 0x2a) == 0) || (sVar1 != 0));
          iVar3 = fw_08002048(param_1,0x80,0,param_5,uVar2);
          if (iVar3 != 0) goto LAB_08000c88;
          if (0xff < *(ushort *)((int)param_1 + 0x2a)) break;
          *(undefined2 *)(param_1 + 10) = *(undefined2 *)((int)param_1 + 0x2a);
          uVar7 = 0;
LAB_08000cb8:
          uVar4 = (undefined1)(short)param_1[10];
          uVar5 = 0x2000000;
        }
        *(undefined2 *)(param_1 + 10) = 0xff;
        uVar7 = 0;
      } while( true );
    }
LAB_08000c88:
    uVar2 = 1;
  }
  else {
    uVar2 = 2;
  }
  return uVar2;
}

