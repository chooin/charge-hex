// rea decompile_all
// name: fw_0800be24
// address: 0x800be24
// body: available
// range: 0x800be24-0x800c19d inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_0800be24(char *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  short sVar5;
  ushort uVar6;
  undefined4 uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  char extraout_r1;
  uint uVar11;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 extraout_r1_02;
  uint uVar12;
  uint extraout_r1_03;
  int extraout_r1_04;
  int iVar13;
  bool bVar14;
  
  sVar5 = _DAT_200008dc;
  if (param_1 == (char *)0x0) {
    return;
  }
  uVar11 = (uint)_DAT_200008e0;
  if (_DAT_200008dc == 0) {
    if (uVar11 == 0) {
      return;
    }
  }
  else if (DAT_20000854 != '\x05') {
    return;
  }
  uVar6 = (ushort)(byte)param_1[1] * 0x100 + (ushort)(byte)param_1[2];
  if (*param_1 != '\0') {
    _DAT_20000128 = 0;
    if (*param_1 == '\x01') {
      uVar7 = 10;
    }
    else {
      uVar7 = 0x28;
    }
    fw_0800cdb8(uVar7);
    fw_0800cc44(500);
    fw_0800a644();
    _DAT_200008dc = 0;
    DAT_20000854 = '\x01';
    goto LAB_0800be74;
  }
  if (_DAT_200008dc != 0) {
    DAT_20000854 = '\x03';
    _DAT_2000012a = 800;
    _DAT_200008dc = 0;
    _DAT_20000888 = uVar6;
    fw_080040e8(uVar6,10000,sVar5,(ushort)(byte)param_1[1] * 0x100,param_2,uVar11,param_4);
    DAT_200008ce = fw_080040e8(extraout_r1_00,1000);
    fw_080040e8(uVar6,1000);
    DAT_200008cf = fw_080040e8(extraout_r1_01,100);
    fw_080040e8(uVar6,100);
    DAT_200008d0 = fw_080040e8(extraout_r1_02,10);
    fw_080040e8(uVar6,10);
    DAT_200008d1 = extraout_r1;
  }
  uVar1 = _DAT_20000890;
  iVar13 = _DAT_2000088c;
  uVar12 = (uint)_DAT_20001020;
  if (DAT_20001018 == 'U') {
    if (_DAT_20000888 < _DAT_20000886) {
      fw_0800cdb8(10);
      goto LAB_0800c12e;
    }
    if (_DAT_2000101c == _DAT_2000089c) {
      _DAT_20000886 = _DAT_20000886 + _DAT_20001020;
    }
    else {
      _DAT_20000886 = _DAT_20001020;
      _DAT_20000884 = 0;
    }
    _DAT_2000089c = _DAT_2000101c;
    _DAT_20000884 = _DAT_20000884 + 1;
    if (DAT_200008c0 == '\x01') {
      if (*(int *)((uint)DAT_20000990 * 4 + 0x200009ac) != _DAT_2000101c) {
        if (DAT_20000990 < 0xc) {
          DAT_20000990 = DAT_20000990 + 1;
        }
        else {
          DAT_20000990 = 0;
        }
      }
      *(int *)((uint)DAT_20000990 * 4 + 0x200009ac) = _DAT_2000101c;
      *(ushort *)((uint)DAT_20000990 * 2 + 0x20000992) = _DAT_20000886;
    }
    fw_080040e8(uVar1 + uVar12,1000000);
    _DAT_20000890 = extraout_r1_03;
    fw_080040e8(iVar13 + extraout_r1_03,1000000);
    _DAT_20000894 = extraout_r1_04;
    fw_0800cdb8(0xb);
    cVar3 = DAT_200008cf;
    cVar2 = DAT_200008ce;
    DAT_200005d4 = 0x42;
    iVar13 = 1;
    if (DAT_200008ce != '\0') {
      DAT_200005d5 = DAT_200008ce + '5';
      DAT_200005d6 = 0x44;
      iVar13 = 3;
    }
    if (DAT_200008cf == '\0') {
      if (DAT_200008ce == '\0') goto LAB_0800c008;
      if (DAT_200008d0 != '\0') {
        (&DAT_200005d4)[iVar13] = 0x3f;
        iVar13 = iVar13 + 1;
        goto LAB_0800c00e;
      }
LAB_0800c024:
      (&DAT_200005d4)[iVar13] = 0x46;
      iVar13 = iVar13 + 1;
    }
    else {
      if ((DAT_200008ce != '\0') || (DAT_200008cf != '\x01')) {
        (&DAT_200005d4)[iVar13] = DAT_200008cf + '5';
        iVar13 = iVar13 + 1;
      }
      (&DAT_200005d4)[iVar13] = 0x43;
      iVar13 = iVar13 + 1;
LAB_0800c008:
      if (DAT_200008d0 != '\0') {
LAB_0800c00e:
        (&DAT_200005d4)[iVar13] = DAT_200008d0 + '5';
        iVar13 = iVar13 + 1;
      }
      if (((cVar2 != '\0') || (cVar3 != '\0')) || (DAT_200008d0 != '\0')) goto LAB_0800c024;
    }
    cVar4 = DAT_200008d1;
    if (DAT_200008d1 != '\0') {
      (&DAT_200005d4)[iVar13] = DAT_200008d1 + '5';
      (&DAT_200005d5)[iVar13] = 0x47;
      iVar13 = iVar13 + 2;
    }
    if (((cVar2 != '\0') || (cVar3 != '\0')) || ((DAT_200008d0 != '\0' || (cVar4 != '\0')))) {
      (&DAT_200005d4)[iVar13] = 0x49;
      iVar13 = iVar13 + 1;
    }
    DAT_200008cd = (undefined1)iVar13;
    DAT_200008cc = 1;
    _DAT_200008da = 300;
  }
  else {
    uVar8 = _DAT_20000890 - _DAT_20001020;
    uVar9 = (uint)DAT_20001022;
    iVar10 = uVar9 * 0x34;
    if (uVar11 == 0) {
      _DAT_20000886 = _DAT_20001020;
      _DAT_20000884 = 0;
      if (DAT_20000854 != '\x04') {
        DAT_20000854 = '\x04';
      }
      if ((uVar9 < 0xc) && (DAT_20000991 == 0xc)) {
        *(undefined4 *)(iVar10 + 0x20000604) = 0;
        *(undefined2 *)(iVar10 + 0x200005f2) = 0;
        *(undefined1 *)(iVar10 + 0x20000614) = 0;
        fw_08009e30(uVar9,1);
        if (_DAT_20000890 < _DAT_20001020) {
          _DAT_20000890 = 0;
        }
        else {
          _DAT_20000890 = _DAT_20000890 - _DAT_20001020;
        }
        _DAT_20000894 = _DAT_2000088c + _DAT_20000890;
        DAT_20000991 = 0;
      }
      else {
        if (uVar12 == 0) goto LAB_0800c12e;
        *(undefined4 *)((uint)DAT_20000991 * 4 + 0x200009ac) = 0;
        *(undefined2 *)((uint)DAT_20000991 * 2 + 0x20000992) = 0;
        bVar14 = _DAT_20000890 < uVar12;
        _DAT_20000890 = uVar8;
        if (bVar14) {
          _DAT_20000890 = 0;
        }
        _DAT_20000894 = iVar13 - _DAT_20000890;
        _DAT_2000012a = 800;
      }
      fw_0800cdb8(0x10);
      cVar3 = DAT_200008cf;
      cVar2 = DAT_200008ce;
      DAT_200005d4 = 0x42;
      iVar13 = 1;
      if (DAT_200008ce != '\0') {
        DAT_200005d5 = DAT_200008ce + '5';
        DAT_200005d6 = 0x44;
        iVar13 = 3;
      }
      if (DAT_200008cf == '\0') {
        if (DAT_200008ce == '\0') goto LAB_0800c17c;
        if (DAT_200008d0 != '\0') {
          (&DAT_200005d4)[iVar13] = 0x3f;
          iVar13 = iVar13 + 1;
          goto LAB_0800c182;
        }
LAB_0800c192:
        (&DAT_200005d4)[iVar13] = 0x46;
        iVar13 = iVar13 + 1;
      }
      else {
        if ((DAT_200008ce != '\0') || (DAT_200008cf != '\x01')) {
          (&DAT_200005d4)[iVar13] = DAT_200008cf + '5';
          iVar13 = iVar13 + 1;
        }
        (&DAT_200005d4)[iVar13] = 0x43;
        iVar13 = iVar13 + 1;
LAB_0800c17c:
        if (DAT_200008d0 != '\0') {
LAB_0800c182:
          (&DAT_200005d4)[iVar13] = DAT_200008d0 + '5';
          iVar13 = iVar13 + 1;
        }
        if (((cVar2 != '\0') || (cVar3 != '\0')) || (DAT_200008d0 != '\0')) goto LAB_0800c192;
      }
      if (DAT_200008d1 != '\0') {
        (&DAT_200005d4)[iVar13] = DAT_200008d1 + '5';
        (&DAT_200005d5)[iVar13] = 0x47;
        iVar13 = iVar13 + 2;
      }
      DAT_200008cd = (undefined1)iVar13;
      DAT_200008cc = 1;
    }
    else {
      if (uVar9 < 0xc) {
        *(undefined4 *)(iVar10 + 0x20000604) = 0;
        *(undefined2 *)(iVar10 + 0x200005f2) = 0;
        *(undefined1 *)(iVar10 + 0x20000614) = 0;
        *(undefined1 *)(iVar10 + 0x20000612) = 1;
      }
      if (uVar12 != 0) {
        _DAT_20000890 = uVar8;
        if (uVar1 < uVar12) {
          _DAT_20000890 = 0;
        }
        _DAT_20000894 = iVar13 + _DAT_20000890;
      }
      _DAT_200008e0 = 0;
    }
  }
LAB_0800c12e:
  _DAT_200008d6 = 10;
  fw_0800a4b4(&DAT_0800fc30,_DAT_20000890);
LAB_0800be74:
  fw_0800c6d8();
  return;
}

