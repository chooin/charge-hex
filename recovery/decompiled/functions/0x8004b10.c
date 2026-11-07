// rea decompile_all
// name: fw_08004b10
// address: 0x8004b10
// body: available
// range: 0x8004b10-0x8004d9f inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_08004b10(int param_1)

{
  short sVar1;
  char cVar2;
  char cVar3;
  undefined2 uVar4;
  int iVar5;
  undefined1 *puVar6;
  undefined4 uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  undefined4 local_28;
  uint local_24;
  
  uVar4 = 0;
  local_24 = 0;
  _DAT_20000128 = 0;
  if (DAT_20000854 == '\x03') {
    if (_DAT_20000884 == 0) goto LAB_08004b48;
  }
  else if (DAT_20000854 == '\x04') {
LAB_08004b48:
    if (((param_1 == 0) && (_DAT_20000878 == 0)) && (9 < _DAT_200008d6 + 1)) {
      _DAT_20000128 = 0;
      return;
    }
    fw_0800a65c();
    return;
  }
  iVar5 = fw_0800a690(param_1);
  if (iVar5 == 0) {
    if (((_DAT_20000884 == 0) || (_DAT_20000882 != 0)) ||
       (iVar5 = fw_08009d50(_DAT_2000089c,param_1), iVar5 != 0)) {
      iVar5 = param_1 * 0x34;
      if (*(char *)(iVar5 + 0x200005fb) == '\x01') {
        *(undefined4 *)(iVar5 + 0x200005e4) = 0;
        *(undefined1 *)(iVar5 + 0x200005fb) = 0;
      }
      _DAT_200008d6 = 0;
      _DAT_200008da = 0;
      uVar8 = (uint)_DAT_20000884;
      puVar6 = &DAT_200008d4 + param_1 * 2;
      if ((uVar8 == 0) || (DAT_200008c0 != 4)) {
        *(undefined4 *)((uint)DAT_20000990 * 4 + 0x200009ac) = 0;
        *(undefined2 *)((uint)DAT_20000990 * 2 + 0x20000992) = 0;
        sVar1 = *(short *)(iVar5 + 0x200005f2);
        if ((sVar1 != 0) &&
           ((iVar10 = *(int *)(iVar5 + 0x20000604), iVar10 != 0 && (iVar10 != _DAT_2000089c)))) {
          *(int *)((uint)DAT_20000990 * 4 + 0x200009ac) = iVar10;
          *(short *)((uint)DAT_20000990 * 2 + 0x20000992) = sVar1;
          *(undefined4 *)(iVar5 + 0x20000604) = 0;
          *(undefined2 *)(iVar5 + 0x200005f2) = 0;
        }
        if (*(int *)(iVar5 + 0x200005e4) == 0) {
          *(undefined2 *)(param_1 * 2 + 0x2000092e) = 0x1e;
        }
        iVar10 = ((uint)_DAT_20000882 * (uint)_DAT_20000856 + uVar8 * _DAT_20000858) * 0x3c;
        uVar9 = (uint)_DAT_20000882 * (uint)_DAT_2000085c + _DAT_2000085e * uVar8 & 0xffff;
        *(ushort *)(iVar5 + 0x200005fc) =
             *(short *)(iVar5 + 0x200005fc) + _DAT_20000882 * 10 + _DAT_20000886;
        uVar8 = (uint)*(byte *)(iVar5 + 0x200005f9);
        if (uVar8 != 0) {
          iVar10 = fw_080040e8(iVar10,100);
          iVar10 = (uint)*(ushort *)(&DAT_20000866 + uVar8 * 2) * iVar10;
        }
        uVar4 = fw_080040e8(iVar10,0x3c);
        *(int *)(iVar5 + 0x20000608) = *(int *)(iVar5 + 0x20000608) + iVar10;
        *(int *)(iVar5 + 0x200005e4) = *(int *)(iVar5 + 0x200005e4) + iVar10;
        if (0x92784 < *(uint *)(iVar5 + 0x20000608)) {
          *(undefined4 *)(iVar5 + 0x20000608) = 0x92784;
        }
        if (0x92784 < *(uint *)(iVar5 + 0x200005e4)) {
          *(undefined4 *)(iVar5 + 0x200005e4) = 0x92784;
        }
        uVar8 = 999;
        if (uVar9 < 1000) {
          uVar8 = uVar9;
        }
        local_24 = uVar8 * 10 & 0xffff;
        sVar1 = (short)(uVar8 * 10);
        *(short *)(iVar5 + 0x200005f0) = *(short *)(iVar5 + 0x200005f0) + sVar1;
        *(short *)(iVar5 + 0x200005ea) = *(short *)(iVar5 + 0x200005ea) + sVar1;
        iVar10 = *(int *)(iVar5 + 0x200005ec) + local_24 * 36000;
        *(int *)(iVar5 + 0x200005ec) = iVar10;
        *(undefined1 *)(iVar5 + 0x20000613) = 0;
        if ((*(int *)(iVar5 + 0x200005e4) != 0) && (iVar10 != 0)) {
          iVar10 = fw_0800a018(param_1);
          if (iVar10 == 1) {
            uVar7 = 0x33;
          }
          else {
            uVar7 = 2;
          }
          fw_0800cdb8(uVar7);
          *(undefined1 *)(iVar5 + 0x200005fa) = 2;
          *(undefined1 *)(iVar5 + 0x20000617) = 0;
          fw_0800c85c(param_1,1);
        }
        local_28 = 0;
      }
      else {
        if (*(char *)(iVar5 + 0x200005fa) == '\x01') {
          fw_08009f44(param_1);
        }
        if (*(char *)(iVar5 + 0x200005fa) != '\0') {
          return;
        }
        _DAT_20000886 = 0;
        *(undefined2 *)(puVar6 + 0xa2) = 0x28;
      }
      if (_DAT_2000089c != 0) {
        if (*(int *)(iVar5 + 0x20000604) == _DAT_2000089c) {
          *(short *)(iVar5 + 0x200005fe) = *(short *)(iVar5 + 0x200005fe) + _DAT_20000886;
        }
        else {
          *(int *)(iVar5 + 0x20000604) = _DAT_2000089c;
          *(short *)(iVar5 + 0x200005fe) = _DAT_20000886;
          *(ushort *)(iVar5 + 0x2000060e) = (ushort)DAT_200008c0;
        }
        local_28 = 1;
      }
      cVar2 = (char)param_1 + '\x01';
      cVar3 = (char)_DAT_20000882 * '\n' + (char)_DAT_20000886;
      if (_DAT_20000878 == 3) {
        _DAT_200000c8 = _DAT_200000c8 + 1;
        fw_0800bab4(cVar2,uVar4,local_24,local_28,cVar3,_DAT_200000c8);
        DAT_200000be = 3;
        DAT_200000bf = 0x2d;
        _DAT_200008de = 0x14;
      }
      else if (_DAT_20000878 == 0) {
        fw_0800ba80(cVar2,uVar4,local_24,local_28,cVar3);
      }
      fw_0800a65c();
      _DAT_200008c4 = 0;
      DAT_200008c2 = 2;
      DAT_200008c6 = cVar2;
      fw_0800a5b0(param_1);
    }
  }
  else {
    fw_0800cdb8(0xf);
  }
  return;
}

