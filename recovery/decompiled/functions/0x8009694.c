// rea decompile_all
// name: app_handle_identifier_frame
// address: 0x8009694
// body: available
// range: 0x8009694-0x8009a8f inclusive
// range: 0x8009ac0-0x8009ce3 inclusive
// non_contiguous: true
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void app_handle_identifier_frame(void)

{
  ushort uVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  ushort uVar8;
  uint uVar9;
  uint uVar10;
  int extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 extraout_r1_02;
  undefined4 extraout_r1_03;
  int extraout_r1_04;
  undefined4 extraout_r1_05;
  undefined4 extraout_r1_06;
  undefined4 extraout_r1_07;
  int extraout_r1_08;
  undefined1 extraout_r2;
  uint uVar11;
  int extraout_r3;
  uint uVar12;
  uint uVar13;
  
  uVar11 = _DAT_20000890;
  iVar7 = _DAT_2000088c;
  uVar8 = (ushort)DAT_2000102a * 0x100 + (ushort)DAT_2000102b;
  uVar12 = (uint)uVar8;
  uVar13 = ((_DAT_20001026 & 0xff) << 8 | (uint)(_DAT_20001026 >> 8)) << 0x10 |
           (uint)DAT_20001028 << 8 | (uint)DAT_20001029;
  if (_DAT_200008be == 0) {
    return;
  }
  if (_DAT_2000012a != 0) {
    _DAT_2000012a = 800;
    return;
  }
  if (_DAT_200008e0 != 0) {
    return;
  }
  if (_DAT_200008dc != 0) {
    return;
  }
  if ((5000 < uVar12) && (uVar12 != 0xaa33)) {
    return;
  }
  uVar5 = (uint)_DAT_20001020;
  uVar9 = uVar5 + (ushort)((ushort)DAT_2000102a * 0x100 + (ushort)DAT_2000102b);
  uVar10 = (uint)_DAT_2000101a;
  if (_DAT_20000128 == 0) {
    if ((_DAT_2000101c != uVar13) ||
       ((((uVar10 != uVar9 || (DAT_20001018 != 'U')) || (uVar5 == 0)) &&
        (((uVar10 + uVar5 != uVar12 || (DAT_20001018 != 'f')) || (uVar5 == 0)))))) {
      DAT_20001018 = 0x55;
      _DAT_20001020 = 0;
      uVar11 = 0;
      do {
        if (_DAT_2000086e == 0) break;
        uVar1 = *(ushort *)(uVar11 * 0x34 + 0x200005f2);
        if ((*(uint *)(uVar11 * 0x34 + 0x20000604) == uVar13) && (uVar1 != 0)) {
          iVar7 = fw_0800cd40(uVar11 & 0xff);
          if (iVar7 != 0) {
            DAT_20001018 = 0x66;
            DAT_20000991 = 0xc;
            _DAT_20001020 = uVar1;
            DAT_20001022 = (byte)uVar11;
            break;
          }
        }
        uVar11 = uVar11 + 1 & 0xffff;
      } while (uVar11 < 0xc);
      if (_DAT_20000878 == 2) {
        if (DAT_20000854 == '\x01') {
          if (((_DAT_20000884 != 0) || (_DAT_20000882 != 0)) || (DAT_20000855 != -1))
          goto LAB_0800982c;
          fw_0800a65c();
          DAT_20000854 = '\x04';
          _DAT_200008d6 = 10;
        }
        else if (DAT_20000854 != '\x04') {
LAB_0800982c:
          DAT_20001018 = 0x55;
          goto LAB_08009834;
        }
      }
      else {
LAB_08009834:
        if (DAT_20000854 != '\x04') goto LAB_08009872;
      }
      DAT_20001018 = 0x66;
      if (_DAT_20001020 == 0) {
        DAT_20001022 = 0x18;
      }
LAB_08009872:
      uVar11 = 0;
      do {
        if ((DAT_20000991 == 0xc) || ((DAT_20000854 != '\x01' && (DAT_20000854 != '\x04')))) break;
        if (*(uint *)(uVar11 * 4 + 0x200009ac) == uVar13) {
          DAT_20001018 = 0x66;
          _DAT_20001020 = *(ushort *)(uVar11 * 2 + 0x20000992);
          DAT_20000991 = (byte)uVar11;
          goto LAB_0800990a;
        }
        uVar11 = uVar11 + 1 & 0xffff;
      } while (uVar11 < 0xc);
      if (DAT_20001018 == 0x55) {
        iVar7 = fw_08009d04(uVar13);
        if (iVar7 == 0) {
          return;
        }
        if (((_DAT_20000858 != 0) && (uVar11 = fw_080040e8(_DAT_2000087e), uVar11 <= _DAT_20000884))
           && (_DAT_2000089c == uVar13)) {
          return;
        }
        _DAT_20001020 = _DAT_2000085a;
        if ((uVar12 != 0xaa33) && (uVar12 < _DAT_2000085a)) {
          fw_0800cdb8(10);
          fw_0800cc44(100);
        }
      }
LAB_0800990a:
      if ((((DAT_20000854 != '\x03') && (DAT_20000854 != '\x01')) && (DAT_20000854 != '\x02')) &&
         (DAT_20000854 != '\x04')) {
        return;
      }
      DAT_2000012d = DAT_20001018;
      DAT_2000012e = (byte)(_DAT_20001020 >> 8);
      DAT_2000012f = (byte)_DAT_20001020;
      DAT_20000130 = DAT_2000012c ^ DAT_20001018 ^ DAT_2000012e ^ DAT_2000012f;
      _DAT_2000101a = uVar8;
      _DAT_2000101c = uVar13;
      if (uVar12 != 0xaa33) {
        fw_080094b4(&DAT_2000012c,5);
        _DAT_20000128 = 2000;
        return;
      }
      if (_DAT_20000878 == 3) {
        if (DAT_200000be != '\0') {
          return;
        }
        if ((DAT_20001018 == 0x55) && (_DAT_200008c8 == 1)) {
          DAT_2000012e = 0;
          DAT_2000012f = 0;
        }
      }
      fw_0800964e(&DAT_20001026,&DAT_2000012d);
      _DAT_20000128 = 2000;
      if ((_DAT_200008c8 == 0) || (_DAT_20000878 != 3)) {
        DAT_200008c0 = 1;
      }
      else {
        DAT_200008c0 = 4;
      }
      if (_DAT_200008d6 != 0) {
        _DAT_200008d6 = 0;
      }
      _DAT_200008dc = 0xf;
      _DAT_2000012a = 800;
      DAT_20000854 = 5;
      fw_0800cdb8(0x34);
      return;
    }
    _DAT_20000128 = 2000;
    _DAT_200008d6 = 10;
  }
  if (uVar12 == 0xaa33) {
    return;
  }
  if (DAT_20001018 == 'U') {
    if ((_DAT_2000101c == 0) || (uVar10 != uVar9)) {
      return;
    }
    if (_DAT_200008da != 0) {
      _DAT_20000882 = 0;
      _DAT_20000886 = 0;
      _DAT_20000884 = 0;
      _DAT_2000089c = 0;
      _DAT_200008da = 0;
    }
    DAT_20000854 = 3;
    if (_DAT_2000101c == _DAT_2000089c) {
      _DAT_20000886 = _DAT_20000886 + _DAT_20001020;
    }
    else {
      _DAT_20000886 = _DAT_20001020;
      _DAT_20000884 = 0;
    }
    _DAT_20000884 = _DAT_20000884 + 1;
    uVar12 = (uint)DAT_20000990;
    if (*(uint *)(uVar12 * 4 + 0x200009ac) != uVar13) {
      if (uVar12 < 0xc) {
        uVar12 = uVar12 + 1;
      }
      else {
        uVar12 = 0;
      }
      DAT_20000990 = (byte)uVar12;
    }
    _DAT_20000888 = uVar8;
    _DAT_2000089c = uVar13;
    *(uint *)((uVar12 & 0xff) * 4 + 0x200009ac) = uVar13;
    *(ushort *)((uint)DAT_20000990 * 2 + 0x20000992) = _DAT_20000886;
    DAT_200008c0 = 0;
    fw_080040e8(uVar11 + uVar5,1000000);
    _DAT_20000890 = extraout_r1;
    fw_080040e8(iVar7 + extraout_r1,1000000);
    _DAT_20000894 = extraout_r1_00;
    fw_0800a4b4(&DAT_0800fc30,extraout_r1);
    fw_0800c6d8();
    _DAT_2000012a = 800;
    if (_DAT_20000878 == 2) {
      _DAT_2000012a = 800;
      _DAT_200008d6 = 10;
      return;
    }
    fw_0800cdb8(0xb);
    uVar8 = _DAT_20000888;
    fw_080040e8(_DAT_20000888,10000);
    cVar3 = fw_080040e8(extraout_r1_01,1000);
    DAT_200008ce = cVar3;
    fw_080040e8(uVar8,1000);
    cVar4 = fw_080040e8(extraout_r1_02,100);
    DAT_200008cf = cVar4;
    fw_080040e8(uVar8,100);
    iVar7 = fw_080040e8(extraout_r1_03,10);
    DAT_200008d0 = (char)iVar7;
    fw_080040e8(uVar8,10);
    cVar2 = (char)extraout_r1_04;
    DAT_200005d4 = 0x42;
    iVar6 = 1;
    if (cVar3 != '\0') {
      DAT_200005d5 = cVar3 + '5';
      DAT_200005d6 = 0x44;
      iVar6 = 3;
    }
    DAT_200008d1 = cVar2;
    if (cVar4 == '\0') {
      if (cVar3 == '\0') goto LAB_08009b48;
      if (iVar7 != 0) {
        (&DAT_200005d4)[iVar6] = 0x3f;
        iVar6 = iVar6 + 1;
        goto LAB_08009b4c;
      }
    }
    else {
      if ((cVar3 != '\0') || (cVar4 != '\x01')) {
        (&DAT_200005d4)[iVar6] = cVar4 + '5';
        iVar6 = iVar6 + 1;
      }
      (&DAT_200005d4)[iVar6] = 0x43;
      iVar6 = iVar6 + 1;
LAB_08009b48:
      if (iVar7 != 0) {
LAB_08009b4c:
        (&DAT_200005d4)[iVar6] = (char)iVar7 + '5';
        iVar6 = iVar6 + 1;
      }
      if (((cVar3 == '\0') && (cVar4 == '\0')) && (iVar7 == 0)) goto LAB_08009b66;
    }
    (&DAT_200005d4)[iVar6] = 0x46;
    iVar6 = iVar6 + 1;
LAB_08009b66:
    if (extraout_r1_04 != 0) {
      (&DAT_200005d4)[iVar6] = cVar2 + '5';
      (&DAT_200005d5)[iVar6] = 0x47;
      iVar6 = iVar6 + 2;
    }
    if (((cVar3 != '\0') || (cVar4 != '\0')) || ((iVar7 != 0 || (extraout_r1_04 != 0)))) {
      (&DAT_200005d4)[iVar6] = 0x49;
      iVar6 = iVar6 + 1;
    }
    DAT_200008cc = 1;
    DAT_200008cd = (char)iVar6;
    _DAT_200008d6 = 10;
    return;
  }
  if (DAT_20001018 != 'f') {
    return;
  }
  if (_DAT_2000101c == 0) {
    return;
  }
  if (uVar10 + uVar5 != uVar12) {
    return;
  }
  if (DAT_20000854 != '\x04') {
    DAT_20000854 = '\x04';
  }
  _DAT_20000886 = _DAT_20001020;
  _DAT_20000884 = 0;
  uVar11 = (uint)DAT_20001022;
  if ((uVar11 < 0xc) && (DAT_20000991 == 0xc)) {
    iVar7 = uVar11 * 0x34;
    _DAT_20000888 = uVar8;
    *(undefined4 *)(iVar7 + 0x20000604) = 0;
    *(undefined2 *)(iVar7 + 0x200005f2) = 0;
    *(undefined1 *)(iVar7 + 0x20000614) = 0;
    fw_08009e30(uVar11,1);
    if (_DAT_20000890 < _DAT_20001020) {
      _DAT_20000890 = 0;
    }
    else {
      _DAT_20000890 = _DAT_20000890 - _DAT_20001020;
    }
    _DAT_20000894 = _DAT_2000088c + _DAT_20000890;
    fw_0800c6d8();
    DAT_20000991 = 0;
  }
  else {
    if (uVar5 == 0) {
      _DAT_20000884 = 0;
      _DAT_20000888 = uVar8;
      _DAT_200008d6 = 10;
      return;
    }
    _DAT_20000888 = uVar8;
    *(undefined4 *)((uint)DAT_20000991 * 4 + 0x200009ac) = 0;
    *(undefined2 *)((uint)DAT_20000991 * 2 + 0x20000992) = 0;
    if (_DAT_20000890 < uVar5) {
      _DAT_20000890 = 0;
    }
    else {
      _DAT_20000890 = _DAT_20000890 - uVar5;
    }
    _DAT_20000894 = iVar7 - _DAT_20000890;
    fw_0800c6d8();
    *(undefined1 *)(extraout_r3 + 1) = extraout_r2;
  }
  _DAT_2000012a = 800;
  fw_0800cdb8(0x10);
  uVar8 = _DAT_20000888;
  fw_080040e8(_DAT_20000888,10000);
  cVar3 = fw_080040e8(extraout_r1_05,1000);
  DAT_200008ce = cVar3;
  fw_080040e8(uVar8,1000);
  cVar4 = fw_080040e8(extraout_r1_06,100);
  DAT_200008cf = cVar4;
  fw_080040e8(uVar8,100);
  iVar6 = fw_080040e8(extraout_r1_07,10);
  DAT_200008d0 = (char)iVar6;
  fw_080040e8(uVar8,10);
  cVar2 = (char)extraout_r1_08;
  DAT_200005d4 = 0x42;
  iVar7 = 1;
  if (cVar3 != '\0') {
    DAT_200005d5 = cVar3 + '5';
    DAT_200005d6 = 0x44;
    iVar7 = 3;
  }
  DAT_200008d1 = cVar2;
  if (cVar4 == '\0') {
    if (cVar3 == '\0') goto LAB_08009cca;
    if (iVar6 != 0) {
      (&DAT_200005d4)[iVar7] = 0x3f;
      iVar7 = iVar7 + 1;
      goto LAB_08009cce;
    }
  }
  else {
    if ((cVar3 != '\0') || (cVar4 != '\x01')) {
      (&DAT_200005d4)[iVar7] = cVar4 + '5';
      iVar7 = iVar7 + 1;
    }
    (&DAT_200005d4)[iVar7] = 0x43;
    iVar7 = iVar7 + 1;
LAB_08009cca:
    if (iVar6 != 0) {
LAB_08009cce:
      (&DAT_200005d4)[iVar7] = (char)iVar6 + '5';
      iVar7 = iVar7 + 1;
    }
    if (((cVar3 == '\0') && (cVar4 == '\0')) && (iVar6 == 0)) goto LAB_08009c1a;
  }
  (&DAT_200005d4)[iVar7] = 0x46;
  iVar7 = iVar7 + 1;
LAB_08009c1a:
  if (extraout_r1_08 != 0) {
    (&DAT_200005d4)[iVar7] = cVar2 + '5';
    (&DAT_200005d5)[iVar7] = 0x47;
    iVar7 = iVar7 + 2;
  }
  DAT_200008cd = (undefined1)iVar7;
  DAT_200008cc = 1;
  fw_0800a4b4(&DAT_0800fc30,_DAT_20000890);
  _DAT_200008d6 = 10;
  return;
}

