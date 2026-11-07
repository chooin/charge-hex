// rea decompile_all
// name: fw_0800a7d4
// address: 0x800a7d4
// body: available
// range: 0x800a7d4-0x800a88d inclusive
// range: 0x800a8e2-0x800ab03 inclusive
// range: 0x800ab58-0x800afc7 inclusive
// range: 0x800afdc-0x800b0c7 inclusive
// non_contiguous: true
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; Ghidra Listing reports a terminal call at 0x800a88a to 0x800aa1e (callee identity unknown), 0x800a9da (callee identity unknown), 0x800a914 (callee identity unknown), 0x800aa74 (callee identity unknown), 0x80095d2 __ARM_common_switch8 (external=false, thunk=false, hasNoReturn=false), 0x800a912 (callee identity unknown), 0x800a9f2 (callee identity unknown), 0x800aa72 (callee identity unknown), 0x800aa70 (callee identity unknown), 0x800aa2e (callee identity unknown), 0x800a96c (callee identity unknown), 0x800aa4a (callee identity unknown), 0x800a966 (callee identity unknown), 0x800a8e2 (callee identity unknown), 0x800a982 (callee identity unknown); fallthrough is excluded by Ghidra's flow model. The reason for the terminal flow is not established by this observation.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Function: __ARM_common_switch8 replaced with injection: switch8_r3 */
/* WARNING (jumptable): Removing unreachable block (ram,0x0800b13e) */
/* WARNING (jumptable): Removing unreachable block (ram,0x0800b10a) */
/* WARNING (jumptable): Removing unreachable block (ram,0x0800a88a) */
/* WARNING: Removing unreachable block (ram,0x0800b13e) */
/* WARNING: Removing unreachable block (ram,0x0800b10a) */
/* WARNING: Removing unreachable block (ram,0x0800a88a) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_0800a7d4(void)

{
  undefined1 uVar1;
  char cVar2;
  ushort uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  byte *pbVar9;
  int iVar10;
  undefined *puVar11;
  uint *puVar12;
  ushort *puVar13;
  byte bVar14;
  uint uVar15;
  int extraout_r1;
  int extraout_r1_00;
  int extraout_r1_01;
  int extraout_r1_02;
  int extraout_r1_03;
  int extraout_r1_04;
  int extraout_r2;
  uint uVar16;
  byte bVar17;
  undefined1 *puVar18;
  uint unaff_r6;
  int iVar19;
  int unaff_r7;
  uint uStack00000008;
  uint in_stack_0000001c;
  int in_stack_0000002c;
  undefined2 *in_stack_00000030;
  ushort *in_stack_00000034;
  uint in_stack_0000003c;
  byte bStack_6c;
  undefined1 uStack_6b;
  undefined1 uStack_6a;
  byte bStack_69;
  undefined1 uStack_68;
  undefined1 auStack_67 [55];
  uint uStack_30;
  uint uStack_2c;
  uint uStack_28;
  undefined1 auStack_24 [4];
  undefined1 auStack_20 [4];
  uint uStack_1c;
  int iStack_14;
  undefined1 *puStack_10;
  uint uStack_c;
  int iStack_8;
  undefined4 uStack_4;
  
  fw_08006320(&DAT_20000bb8);
  uVar6 = fw_0800a6cc();
  if (uVar6 < in_stack_0000001c) {
    uStack00000008 = 1;
LAB_0800a7f8:
    uVar16 = 0;
    do {
      iVar19 = uVar16 * 2;
      uVar7 = (uint)*(ushort *)(&DAT_200008d4 + iVar19);
      if (uVar7 == 0) goto LAB_0800ac5a;
      if (uStack00000008 < uVar7) {
        uVar15 = uVar16 - 0x21;
        *(short *)(&DAT_200008d4 + iVar19) = (short)(uVar7 - uStack00000008);
        if (uVar15 < 10) {
          fw_080040e8(uVar7 - uStack00000008 & 0xffff,10);
          if (extraout_r1 == 0) {
            *(undefined2 *)((uVar15 & 0xffff) * 2 + 0x2000092e) = 0x1e;
            iVar19 = (uVar15 & 0xffff) * 0x34;
            *(undefined2 *)(iVar19 + 0x200005e8) = 0;
            *(undefined1 *)(iVar19 + 0x200005fa) = 2;
            fw_0800c85c(uVar15 & 0xff,1);
          }
        }
        else if (uVar16 - 0x2d < 10) {
          iVar10 = fw_0800a018(uVar16 - 0x2d & 0xff);
          if ((iVar10 == 1) &&
             (fw_080040e8(*(undefined2 *)(&DAT_200008d4 + iVar19),5), extraout_r1_00 == 0)) {
            uVar8 = 0x33;
LAB_0800a87e:
            fw_0800cdb8(uVar8);
          }
        }
        else if ((uVar16 == 4) && (fw_080040e8(_DAT_200008dc,5), extraout_r1_01 == 0)) {
          uVar8 = 0x34;
          goto LAB_0800a87e;
        }
        goto LAB_0800ac5a;
      }
      *(undefined2 *)(&DAT_200008d4 + iVar19) = 0;
      switch(uVar16) {
      case 0:
        DAT_20000854 = '\x01';
        fw_0800a644();
        if (_DAT_200008bc != 0) {
          fw_0800cc64(1);
        }
        fw_0800cdb8(0x26);
        _DAT_200008d4 = 0;
        fw_0800a488(DAT_20000855);
      default:
switchD_0800a88a_caseD_6:
        break;
      case 1:
        uVar7 = 0;
        do {
          if ((*(char *)(uVar7 * 0x34 + 0x200005fa) == '\x01') &&
             (*(char *)(uVar7 * 0x34 + 0x200005fb) == '\x01')) {
            fw_08004b10(uVar7 & 0xff);
          }
          uVar7 = uVar7 + 1 & 0xffff;
        } while (uVar7 < 0xc);
        if (DAT_20000854 == '\x03') {
          if (_DAT_20000884 != 0) goto LAB_0800a946;
LAB_0800a956:
          fw_0800a65c();
        }
        else {
          if (DAT_20000854 == '\x04') goto LAB_0800a956;
LAB_0800a946:
          if (*(char *)(in_stack_0000002c + 0xc) == '\x04') goto LAB_0800a956;
        }
        DAT_20000991 = 0;
        DAT_20000854 = '\x01';
        break;
      case 2:
switchD_0800a88a_caseD_2:
        fw_0800a644();
        break;
      case 3:
        _DAT_20000882 = 0;
        _DAT_20000886 = 0;
        _DAT_20000884 = 0;
        _DAT_2000089c = 0;
        _DAT_20000888 = 0;
        *(undefined1 *)(in_stack_0000002c + 0xc) = 0;
        break;
      case 4:
        if (DAT_20000854 == '\x05') {
          _DAT_2000089c = 0;
          *(undefined1 *)(in_stack_0000002c + 0xc) = 0;
          DAT_20000854 = '\x01';
          goto switchD_0800a88a_caseD_2;
        }
        goto switchD_0800a88a_caseD_6;
      case 5:
        if ((_DAT_20000878 == 3) && (DAT_200000be != '\0')) {
          DAT_200000be = DAT_200000be + -1;
          if (DAT_200000bf == ',') {
            fw_0800bb7c(0,0,0);
          }
          else if (DAT_200000bf == '-') {
            fw_0800bab4(0,0,0,0);
          }
          if (DAT_200000be != '\0') {
            _DAT_200008de = 0x14;
            break;
          }
        }
        goto switchD_0800a88a_caseD_6;
      case 7:
        if (_DAT_20000878 == 3) {
          fw_0800b960(DAT_20000122);
        }
        else if (_DAT_20000878 == 0) {
          fw_0800b87c(DAT_20000122);
        }
        pbVar9 = &DAT_20000122;
        bVar14 = ~DAT_20000122 & 1;
LAB_0800aa2a:
        *pbVar9 = bVar14;
        break;
      case 8:
        pbVar9 = &DAT_20000854;
        if (DAT_20000854 == '!') {
          bVar14 = 1;
          goto LAB_0800aa2a;
        }
        break;
      case 9:
      case 10:
      case 0xb:
      case 0xc:
      case 0xd:
      case 0xe:
      case 0xf:
      case 0x10:
      case 0x11:
      case 0x12:
      case 0x13:
      case 0x14:
        uVar1 = 0;
        if (_DAT_20000876 != 0) {
          uVar1 = 2;
        }
        *(undefined1 *)(uVar16 * 0x34 + 0x2000043d) = uVar1;
        break;
      case 0x15:
      case 0x16:
      case 0x17:
      case 0x18:
      case 0x19:
      case 0x1a:
      case 0x1b:
      case 0x1c:
      case 0x1d:
      case 0x1e:
      case 0x1f:
      case 0x20:
        uVar7 = uVar16 - 0x15;
        uVar15 = uVar7 & 0xffff;
        iVar19 = uVar15 * 0x34;
        if (*(char *)(iVar19 + 0x20000610) == '\x01') {
          if (_DAT_20000866 <= *(ushort *)(iVar19 + 0x200005e8)) {
            fw_08008224(uVar7 & 0xff);
          }
        }
        else {
          iVar10 = fw_0800a068();
          if ((iVar10 == 1) && (*(char *)(iVar19 + 0x20000610) == '\0')) {
            uVar3 = *(ushort *)(iVar19 + 0x200005e8);
            if (*(ushort *)(&DAT_20000860 + (uint)*(byte *)(iVar19 + 0x200005f9) * 2) <= uVar3) {
              if ((uVar3 < _DAT_20000860) || (_DAT_20000862 <= uVar3)) {
                if ((_DAT_20000862 <= uVar3) && (uVar3 < _DAT_20000864)) {
                  uVar1 = 2;
                  goto LAB_0800aae8;
                }
                if ((_DAT_20000864 <= uVar3) && (uVar3 < _DAT_20000866)) {
                  uVar1 = 3;
                  goto LAB_0800aae8;
                }
              }
              else {
                uVar1 = 1;
LAB_0800aae8:
                *(undefined1 *)(iVar19 + 0x200005f9) = uVar1;
              }
              uVar15 = *(byte *)(iVar19 + 0x200005f9) - 1 & 0xffff;
              if ((*(ushort *)(&DAT_20000860 + uVar15 * 2) <= *(ushort *)(iVar19 + 0x200005e8)) &&
                 (uVar15 < 3)) {
                if (*(char *)(iVar19 + 0x20000615) == '\x01') {
                  uVar4 = *(undefined2 *)(&DAT_20000868 + in_stack_0000003c * 2);
                  iVar10 = fw_080040e8(*(undefined4 *)(iVar19 + 0x200005e4),uVar4);
                  *(int *)(iVar19 + 0x200005e4) = iVar10 * 100;
                  iVar10 = fw_080040e8(*(undefined4 *)(iVar19 + 0x20000608),uVar4);
                  *(int *)(iVar19 + 0x20000608) = iVar10 * 100;
                }
                iVar10 = fw_080040e8(*(undefined4 *)(iVar19 + 0x200005e4),100);
                uVar3 = *(ushort *)(&DAT_20000868 + uVar15 * 2);
                *(uint *)(iVar19 + 0x200005e4) = (uint)uVar3 * iVar10 + 0x3c;
                iVar10 = fw_080040e8(*(undefined4 *)(iVar19 + 0x20000608),100);
                *(uint *)(iVar19 + 0x20000608) = (uint)uVar3 * iVar10;
                *(undefined1 *)(iVar19 + 0x20000615) = 1;
                fw_0800a5b0(uVar7 & 0xff);
                in_stack_0000003c = uVar15;
              }
            }
          }
          else if (*(char *)(iVar19 + 0x20000610) == '\x02') {
            if ((*(ushort *)(iVar19 + 0x200005e8) < _DAT_2000087c) &&
               (*(ushort *)(uVar15 * 2 + 0x2000095e) =
                     _DAT_2000087a + *(short *)(uVar15 * 2 + 0x2000092e),
               *(byte *)(iVar19 + 0x20000617) < 4)) {
              fw_0800cdb8(3);
              *(char *)(iVar19 + 0x20000617) = *(char *)(iVar19 + 0x20000617) + '\x01';
            }
          }
          else if (((*(char *)(iVar19 + 0x20000610) == '\x03') &&
                   (*(char *)(iVar19 + 0x200005fa) == '\x02')) &&
                  (*(ushort *)(iVar19 + 0x200005e8) < _DAT_20000866)) {
            *(undefined2 *)(uVar15 * 2 + 0x20000916) = 0;
          }
        }
        break;
      case 0x21:
      case 0x22:
      case 0x23:
      case 0x24:
      case 0x25:
      case 0x26:
      case 0x27:
      case 0x28:
      case 0x29:
      case 0x2a:
      case 0x2b:
      case 0x2c:
        uVar7 = uVar16 - 0x21 & 0xff;
        uVar8 = 3;
        goto LAB_0800ac56;
      case 0x39:
      case 0x3a:
      case 0x3b:
      case 0x3c:
      case 0x3d:
      case 0x3e:
      case 0x3f:
      case 0x40:
      case 0x41:
      case 0x42:
      case 0x43:
      case 0x44:
        uVar7 = uVar16 - 0x39 & 0xff;
        uVar8 = 2;
        goto LAB_0800ac56;
      case 0x45:
      case 0x46:
      case 0x47:
      case 0x48:
      case 0x49:
      case 0x4a:
      case 0x4b:
      case 0x4c:
      case 0x4d:
      case 0x4e:
      case 0x4f:
      case 0x50:
        uVar7 = uVar16 - 0x45;
        iVar19 = fw_0800a128(uVar7 & 0xff);
        if (iVar19 == 0) {
          uVar7 = uVar7 & 0xff;
          uVar8 = 1;
        }
        else {
          uVar7 = uVar7 & 0xff;
          uVar8 = 0xb;
        }
LAB_0800ac56:
        fw_08009e30(uVar7,uVar8);
      }
LAB_0800ac5a:
      uVar16 = uVar16 + 1 & 0xffff;
    } while (uVar16 < 0x5d);
    if (((_DAT_20000878 == 2) && ((uint)_DAT_20000882 + (uint)_DAT_20000884 != 0)) &&
       (DAT_20000855 < 0xc)) {
      uVar1 = 0;
      if (_DAT_20000876 != 0) {
        uVar1 = 2;
      }
      (&DAT_20000611)[(uint)DAT_20000855 * 0x34] = uVar1;
      fw_08004b10();
    }
    if (_DAT_200008e2 == 0) {
      _DAT_200008e2 = 0x96;
    }
    if (*(char *)(in_stack_0000002c + 0x16) != '\0') {
      fw_0800cc80();
    }
    uVar16 = 0;
    fw_080040e8(uVar6,0x96);
    do {
      iVar19 = uVar16 * 0x34;
      uVar6 = *(uint *)(iVar19 + 0x200005e4);
      unaff_r6 = (uint)*(ushort *)(iVar19 + 0x200005e8);
      cVar2 = *(char *)(iVar19 + 0x20000610);
      if (*(char *)(iVar19 + 0x20000612) == '\x01') {
        fw_0800a5b0(uVar16 & 0xff);
        *(undefined1 *)(iVar19 + 0x20000612) = 0;
      }
      if (extraout_r1_02 == 0) {
        fw_0800a24c(uVar16 & 0xff);
      }
      if ((DAT_20000854 == ' ') && (DAT_20000855 == uVar16)) {
        uVar3 = fw_08008278(uVar16 & 0xff);
        unaff_r6 = (uint)uVar3;
      }
      if (uVar6 == 0) {
        unaff_r7 = 0;
        goto LAB_0800af22;
      }
      uVar3 = fw_08008278(uVar16 & 0xff);
      unaff_r6 = (uint)uVar3;
      uVar7 = unaff_r6 * uStack00000008;
      uVar15 = *(uint *)(iVar19 + 0x200005ec);
      if (*(char *)(iVar19 + 0x20000613) == '\0') {
        if (uVar15 < uVar7) {
          iVar10 = 0;
        }
        else {
          iVar10 = uVar15 - uVar7;
        }
      }
      else {
        iVar10 = uVar15 + uVar7;
      }
      *(int *)(iVar19 + 0x200005ec) = iVar10;
      fw_080040e8(uVar6,3);
      if (extraout_r1_03 == 0) {
        uVar4 = fw_08009468(uVar16 & 0xff);
        *(undefined2 *)(iVar19 + 0x200005f4) = uVar4;
        uVar4 = fw_08007840(uVar16 & 0xff);
        *(undefined2 *)(iVar19 + 0x200005f6) = uVar4;
      }
      iVar10 = fw_08009fec(uVar16 & 0xff);
      if ((iVar10 == 0) || (uVar6 <= uStack00000008)) {
        if (uStack00000008 < uVar6) {
          if (*(char *)(iVar19 + 0x200005fa) == '\x01') {
            unaff_r7 = uVar6 - uStack00000008;
            if (((_DAT_20000872 <= unaff_r6) && (*(char *)(iVar19 + 0x200005fb) == '\0')) &&
               (unaff_r7 + 4U < 0xb)) {
              unaff_r6 = 0;
              *(undefined1 *)(iVar19 + 0x200005fb) = 1;
              unaff_r7 = 0x3c;
              fw_0800c85c(uVar16 & 0xff,0);
              fw_0800cdb8(0xe);
            }
            goto LAB_0800af22;
          }
LAB_0800af16:
          fw_08009e30(uVar16 & 0xff,0);
        }
        else {
          if (*(char *)(iVar19 + 0x200005fa) != '\x01') goto LAB_0800af16;
          fw_08009f44(uVar16 & 0xff);
        }
        unaff_r7 = 0;
        unaff_r6 = 0;
      }
      else {
        if (*(int *)(iVar19 + 0x200005ec) != 0) {
          uVar4 = fw_080040e8(*(int *)(iVar19 + 0x200005ec),36000);
          *(undefined2 *)(iVar19 + 0x200005ea) = uVar4;
        }
        uVar4 = fw_0800a090(uVar16 & 0xff);
        *(undefined2 *)(iVar19 + 0x200005f2) = uVar4;
        unaff_r7 = uVar6 - uStack00000008;
        fw_080040e8(unaff_r7,0x3c);
        if (extraout_r1_04 == 0) {
          fw_0800a5b0(uVar16 & 0xff);
        }
        if (unaff_r6 < (uint)_DAT_20000866 * 3) {
          if (unaff_r6 < _DAT_20000866) {
            iVar10 = fw_0800a068();
            if (((iVar10 == 1) &&
                (*(ushort *)(&DAT_20000860 + (uint)*(byte *)(iVar19 + 0x200005f9) * 2) <= unaff_r6))
               && ((*(short *)(uVar16 * 2 + 0x200008fe) == 0 || (cVar2 != '\0')))) {
              *(undefined2 *)(uVar16 * 2 + 0x200008fe) = 2;
              cVar2 = '\0';
            }
          }
          else if ((*(short *)(uVar16 * 2 + 0x200008fe) == 0) || (cVar2 != '\x01')) {
            *(undefined2 *)(uVar16 * 2 + 0x200008fe) = 2;
            cVar2 = '\x01';
            uVar1 = fw_08009fa4(unaff_r6);
            *(undefined1 *)(iVar19 + 0x200005f8) = uVar1;
          }
        }
        else {
          fw_08008224(uVar16 & 0xff);
        }
        iVar10 = uVar16 * 2;
        if (*(short *)(iVar10 + 0x20000916) == 0) {
          if (*(char *)(iVar19 + 0x200005fa) == '\x02') goto LAB_0800ae3c;
        }
        else if (*(char *)(iVar19 + 0x200005fa) == '\x02') {
          if (((unaff_r6 < _DAT_20000866) && (*(ushort *)(iVar10 + 0x2000092e) + 5 < 0x1e)) &&
             ((*(short *)(iVar10 + 0x200008fe) == 0 || (cVar2 != '\x03')))) {
            *(undefined2 *)(iVar10 + 0x200008fe) = 2;
            cVar2 = '\x03';
          }
LAB_0800ae3c:
          if (((_DAT_20000870 != 0) && (*(ushort *)(iVar10 + 0x2000092e) + 10 < 0x1e)) &&
             (*(char *)(iVar19 + 0x20000616) == '\0')) {
            uVar6 = (uint)_DAT_2000087c;
            if (unaff_r6 < uVar6) {
              if (*(short *)(iVar10 + 0x2000095e) == 0) {
                if ((cVar2 != '\x02') || (*(short *)(iVar10 + 0x200008fe) == 0)) {
                  *(undefined2 *)(iVar10 + 0x200008fe) = 3;
                  cVar2 = '\x02';
                }
              }
              else {
LAB_0800ae9e:
                if (uVar6 <= unaff_r6) {
                  *(undefined2 *)(iVar10 + 0x2000095e) = 0;
                }
              }
            }
            else {
              if ((unaff_r6 < _DAT_20000872) && (*(short *)(iVar10 + 0x20000946) == 0)) {
                uVar3 = _DAT_20000874;
                if (_DAT_20000874 == 0) {
                  uVar3 = *(ushort *)(iVar10 + 0x2000092e) + 5;
                }
                *(ushort *)(iVar10 + 0x20000946) = uVar3;
              }
              if (*(short *)(iVar10 + 0x2000095e) != 0) goto LAB_0800ae9e;
            }
            if (((*(short *)(iVar10 + 0x20000946) != 0) && (_DAT_20000872 <= unaff_r6)) &&
               ((*(char *)(uVar16 + 0x20000ac0) != '\0' || (_DAT_20000874 < 0x259)))) {
              *(undefined2 *)(iVar10 + 0x20000946) = 0;
            }
            *(undefined1 *)(uVar16 + 0x20000ac0) = 0;
          }
        }
      }
LAB_0800af22:
      *(char *)(iVar19 + 0x20000610) = cVar2;
      *(int *)(iVar19 + 0x200005e4) = unaff_r7;
      uVar16 = uVar16 + 1 & 0xffff;
      *(short *)(iVar19 + 0x200005e8) = (short)unaff_r6;
    } while (uVar16 < 0xc);
  }
  else {
    uStack00000008 = uVar6 - in_stack_0000001c & 0xffff;
    if (uStack00000008 != 0) goto LAB_0800a7f8;
  }
  puVar18 = (undefined1 *)0x1;
  do {
    iVar19 = fw_0800a2d0((uint)puVar18 & 0xff);
    if (iVar19 != 0) {
      for (uVar3 = 0; (iVar19 = fw_0800a2d0((uint)puVar18 & 0xff), iVar19 != 0 && (uVar3 < 2));
          uVar3 = uVar3 + 1) {
        fw_0800cc64(10);
      }
      if (puVar18 == (undefined1 *)0x4) {
        if (uVar3 == 2) {
          while (iVar19 = fw_0800a2d0(4), iVar19 != 0) {
            if (199 < uVar3) goto LAB_0800af98;
            fw_0800cc64(0x14);
            uVar3 = uVar3 + 1;
          }
          if (uVar3 < 200) {
LAB_0800afc0:
            fw_08007904((uint)puVar18 & 0xff);
          }
          else {
LAB_0800af98:
            if (uVar3 == 200) {
              for (; (iVar19 = fw_0800a2d0(4), iVar19 != 0 && (uVar3 < 2000)); uVar3 = uVar3 + 1) {
                fw_0800cc64(200);
              }
              if (uVar3 < 2000) goto LAB_0800afc0;
              fw_08007cf0(4);
              while (iVar19 = fw_0800a2d0(4), iVar19 != 0) {
                fw_0800cc64(200);
              }
            }
          }
        }
      }
      else if (uVar3 == 2) goto LAB_0800afc0;
      unaff_r6 = 1000;
      for (; (iVar19 = fw_0800a2d0((uint)puVar18 & 0xff), iVar19 != 0 && (uVar3 < 1000));
          uVar3 = uVar3 + 1) {
        fw_0800cc64(200);
      }
    }
    puVar18 = (undefined1 *)((uint)(puVar18 + 1) & 0xffff);
  } while (puVar18 < (undefined1 *)0x10);
  if (*(char *)(in_stack_00000030 + 1) == '\x01') {
    *(undefined1 *)(in_stack_00000030 + 1) = 0;
    fw_08008e84(0x20000c10,*in_stack_00000030);
  }
  if ((char)in_stack_00000034[1] == '\x01') {
    *(undefined1 *)(in_stack_00000034 + 1) = 0;
    puVar18 = (undefined1 *)0x20000e14;
    for (uVar6 = 0; uVar6 < *in_stack_00000034; uVar6 = uVar6 + 1 & 0xffff) {
      fw_08008eac(*(undefined1 *)(uVar6 + 0x20000e14));
    }
  }
  if (*(char *)(in_stack_0000002c + 0x18) == '\x01') {
    unaff_r7 = 0x48000400;
    iVar19 = fw_08005d3c(0x48000400,4);
    if (iVar19 != 0) {
      uVar6 = 0;
      puVar18 = &DAT_200005d4;
      unaff_r6 = 0;
      while( true ) {
        if (*(byte *)(in_stack_0000002c + 0x19) <= uVar6) break;
        iVar19 = fw_08005d3c(0x48000400,4);
        if (iVar19 == 0) break;
        if ((&DAT_200005d4)[uVar6] != '\0') {
          fw_0800cdb8();
          (&DAT_200005d4)[uVar6] = 0;
        }
        uVar6 = uVar6 + 1 & 0xffff;
      }
      if (*(byte *)(in_stack_0000002c + 0x19) == uVar6) {
        *(undefined1 *)(in_stack_0000002c + 0x19) = 0;
        *(undefined1 *)(in_stack_0000002c + 0x18) = 0;
      }
    }
  }
  fw_08007474();
  fw_0800890c(1);
  fw_080087b8();
  fw_080087ac();
  DAT_20000103 = fw_080094e8();
  fw_08004dcc();
  fw_0800a7d4();
  uVar4 = _DAT_20000890;
  bVar14 = bRam00000004;
  iStack_14 = extraout_r2 << 0x17;
  uStack_4 = 0x800b0c9;
  uStack_30 = (uint)bRam00000002;
  _DAT_200000c0 = 0x2ee;
  DAT_200000bc = 1;
  bVar17 = 0;
  puStack_10 = puVar18;
  uStack_c = unaff_r6;
  iStack_8 = unaff_r7;
  if (cRam00000000 == 'U') {
    if (uStack_30 == 0x10) {
      fw_0800be24(4,_DAT_20000878,0x55,0);
      return;
    }
    if (uStack_30 == 0x2c) {
      if (_DAT_20000878 != 3) {
        DAT_200000bc = 1;
        _DAT_200000c0 = 0x2ee;
        return;
      }
      fw_0800c20c(4);
      return;
    }
    if (uStack_30 == 0x2d) {
      if (_DAT_20000878 != 3) {
        DAT_200000bc = 1;
        _DAT_200000c0 = 0x2ee;
        return;
      }
      fw_0800c1c8(4);
      return;
    }
    if (uStack_30 != 0x36) {
      DAT_200000bc = 1;
      _DAT_200000c0 = 0x2ee;
      return;
    }
    switch(bRam00000004) {
    default:
      DAT_200000bc = 1;
      _DAT_200000c0 = 0x2ee;
      return;
    case 1:
      DAT_200000bc = 1;
      _DAT_200000c0 = 0x2ee;
      _DAT_20000acc = 0;
      return;
    case 2:
      DAT_200000bc = 1;
      _DAT_200000c0 = 0x2ee;
      _DAT_20000ace = 0;
      return;
    case 3:
      DAT_200000bc = 1;
      _DAT_200000c0 = 0x2ee;
      _DAT_20000ad0 = 0;
      return;
    case 4:
      goto switchD_0800b13e_caseD_4;
    case 5:
      if (_DAT_20000ad4 == 0) {
        DAT_200000bc = 1;
        _DAT_200000c0 = 0x2ee;
        return;
      }
      DAT_200000bc = 1;
      _DAT_200000c0 = 0x2ee;
      _DAT_20000ad4 = _DAT_20000ad4 & ~(ushort)(1 << DAT_20000104);
      return;
    }
  }
  if (uStack_30 == 0x18) {
    fw_0800bcd8(4,1);
    bStack_6c = bVar17;
    goto LAB_0800b66a;
  }
  auStack_24._0_2_ = auStack_24._1_2_;
  auStack_20._0_2_ = auStack_20._1_2_;
  if (0x18 < uStack_30) {
    uVar6 = uStack_30;
    if (uStack_30 != 0x34) {
      if (uStack_30 < 0x35) {
        if (uStack_30 == 0x27) {
          if (_DAT_20000878 != 3) {
            DAT_200000bc = 1;
            _DAT_200000c0 = 0x2ee;
            return;
          }
          uStack_1c = (uint)bRam00000004;
          iVar19 = CONCAT31(CONCAT21(CONCAT11(uRam0000000b,bRam0000000c),uRam0000000d),uRam0000000e)
          ;
          if (iVar19 != _DAT_200000d8) {
            uStack_2c = (uint)CONCAT11(bRam00000007,bRam00000008);
            uStack_28 = (uint)CONCAT11(bRam00000009,bRam0000000a);
            DAT_200000cc = fw_0800ca80(uStack_1c,CONCAT11(uRam00000005,bRam00000006),uStack_2c);
            DAT_200000be = '\0';
            DAT_200000bf = '\0';
            _DAT_200008de = 0;
            _DAT_200000d8 = iVar19;
          }
          bStack_6c = (byte)uStack_1c;
          cVar2 = '\x06';
          uStack_6b = DAT_200000cc;
          uStack_6a = uRam0000000b;
          bStack_69 = bRam0000000c;
          uStack_68 = uRam0000000d;
          auStack_67[0] = uRam0000000e;
          uVar6 = uStack_30;
        }
        else if (uStack_30 < 0x28) {
          if (uStack_30 == 0x1e) {
            cVar2 = '\x17';
            fw_0800b7a8(&bStack_6c);
            uVar6 = uStack_30;
          }
          else {
            if (uStack_30 != 0x23) {
              DAT_200000bc = 1;
              _DAT_200000c0 = 0x2ee;
              return;
            }
            bStack_6c = 0x18;
            uStack_6b = 0;
            uStack_6a = 3;
            bStack_69 = 0;
            uStack_68 = 6;
            uVar16 = 0;
            do {
              uVar7 = uVar16 + 1 & 0xff;
              auStack_67[uVar16] = 0;
              uVar16 = uVar7;
            } while (uVar7 < 0xc);
            cVar2 = '\x11';
          }
        }
        else if (uStack_30 == 0x2e) {
          if (_DAT_20000878 != 3) {
            DAT_200000bc = 1;
            _DAT_200000c0 = 0x2ee;
            return;
          }
          cVar2 = '\x0f';
          iVar19 = fw_0800b74c(bRam00000004,&uStack_2c,auStack_24,&uStack_28);
          uVar4 = *(undefined2 *)(iVar19 * 0x34 + 0x200005c0);
          uVar5 = *(undefined2 *)(iVar19 * 0x34 + 0x200005c2);
          bStack_6c = (byte)iVar19;
          uStack_6b = (undefined1)(uStack_2c >> 8);
          uStack_6a = (undefined1)uStack_2c;
          bStack_69 = SUB21(auStack_24._0_2_,1);
          uStack_68 = (undefined1)auStack_24._0_2_;
          auStack_67[0] = (undefined1)(uStack_28 >> 8);
          auStack_67[1] = (undefined1)uStack_28;
          auStack_67[2] = SUB21(auStack_20._0_2_,1);
          auStack_67[3] = (undefined1)auStack_20._0_2_;
          auStack_67[4] = (undefined1)((ushort)uVar4 >> 8);
          auStack_67[5] = (undefined1)uVar4;
          auStack_67[6] = (undefined1)((ushort)uVar5 >> 8);
          auStack_67[7] = (undefined1)uVar5;
          auStack_67[8] = 0xff;
          auStack_67[9] = 0xff;
          uVar6 = uStack_30;
        }
        else {
          if (uStack_30 != 0x32) {
            DAT_200000bc = 1;
            _DAT_200000c0 = 0x2ee;
            return;
          }
          if (bRam00000004 == 1) {
            DAT_20000102 = bRam00000008;
            uVar6 = (uint)(ushort)(short)(char)bRam00000008;
            puVar11 = &DAT_0800fc58;
LAB_0800b4d0:
            fw_0800a4a8(puVar11,uVar6);
          }
          else {
            if (bRam00000004 == 2) {
              _DAT_2000010c = CONCAT11(bRam00000007,bRam00000008);
              uVar6 = (uint)_DAT_2000010c;
              puVar11 = &DAT_0800fc5a;
              goto LAB_0800b4d0;
            }
            if (bRam00000004 == 3) {
              uVar6 = (uint)CONCAT11(bRam00000007,bRam00000008);
              puVar11 = &DAT_0800fc5c;
              _DAT_20000118 = uVar6;
              goto LAB_0800b4d0;
            }
          }
          bStack_6c = 0;
          cVar2 = '\x01';
          uVar6 = uStack_30;
        }
      }
      else {
        if (uStack_30 == 0x35) {
          if (bRam00000004 != 1) {
            if (bRam00000004 != 2) {
              if (bRam00000004 == 3) {
                puVar12 = (uint *)&DAT_20000118;
                goto LAB_0800b58a;
              }
              goto LAB_0800b572;
            }
            puVar13 = (ushort *)&DAT_2000010c;
            goto LAB_0800b5bc;
          }
          puVar18 = &DAT_20000102;
          goto LAB_0800b5a6;
        }
        if (uStack_30 == 0x38) {
          _DAT_20000878 = (ushort)bRam00000004;
          _DAT_20000866 = CONCAT11(bRam00000006,uRam00000005) << 8 | (ushort)bRam00000006;
          if (0x9c4 < _DAT_20000866) {
            _DAT_20000866 = 0x9c4;
          }
          _DAT_20000870 = (ushort)bRam00000007;
          _DAT_20000872 = (ushort)bRam00000008;
          _DAT_20000874 = (ushort)bRam00000009 * 0x3c;
          if (0x3840 < _DAT_20000874) {
            _DAT_20000874 = 0x3840;
          }
          _DAT_2000087c = (ushort)bRam0000000a;
          if (0x14 < bRam0000000a) {
            _DAT_2000087c = 0x14;
          }
          _DAT_2000087a = CONCAT11(bRam0000000c,uRam0000000b) << 8 | (ushort)bRam0000000c;
          if (0x1e0 < _DAT_2000087a) {
            _DAT_2000087a = 0x1e0;
          }
          DAT_200008cb = uRam0000000d;
          fw_0800a4a8(&DAT_0800fc24);
          fw_0800a4a8(&DAT_0800fc12,_DAT_20000866);
          fw_0800a4a8(&DAT_0800fc1c,_DAT_20000870);
          fw_0800a4a8(&DAT_0800fc1e,_DAT_20000872);
          fw_0800a4a8(&DAT_0800fc20,_DAT_20000874);
          fw_0800a4a8(&DAT_0800fc28,_DAT_2000087c);
          fw_0800a4a8(&DAT_0800fc26,_DAT_2000087a);
          fw_0800a4a8(&DAT_0800fc2a,DAT_200008cb);
          bStack_6c = bVar17;
          goto LAB_0800b66a;
        }
        if (uStack_30 != 0x39) {
          if (uStack_30 != 0x3b) {
            DAT_200000bc = 1;
            _DAT_200000c0 = 0x2ee;
            return;
          }
          bStack_6c = 0;
          fw_0800c7c4(0x3b,1,1,&bStack_6c);
          if (bRam00000004 != 0) {
            if (bRam00000004 != 1) {
              return;
            }
            fw_0800a4a8(&DAT_0800f802,0xaaaa);
            return;
          }
          fw_0800a4a8(&DAT_0800f802,0xaaaa);
          fw_080063ec();
          return;
        }
        bStack_6c = (byte)_DAT_20000878;
        uStack_6b = (undefined1)(_DAT_20000866 >> 8);
        uStack_6a = (undefined1)_DAT_20000866;
        bStack_69 = DAT_20000870;
        uStack_68 = DAT_20000872;
        auStack_67[0] = fw_080040e8(_DAT_20000874,0x3c);
        auStack_67[1] = (undefined1)_DAT_2000087c;
        auStack_67[2] = (undefined1)(_DAT_2000087a >> 8);
        auStack_67[3] = (undefined1)_DAT_2000087a;
        auStack_67[4] = DAT_200008cb;
        cVar2 = '\n';
        uVar6 = uStack_30;
      }
      goto LAB_0800b336;
    }
    if (bRam00000004 == 1) {
      puVar18 = &DAT_20000101;
LAB_0800b5a6:
      bStack_69 = 0;
      uStack_6a = 0;
      uStack_6b = 0;
      bStack_6c = 1;
      uStack_68 = *puVar18;
LAB_0800b5aa:
      auStack_67[0] = 0;
    }
    else {
      if (bRam00000004 == 2) {
        puVar13 = (ushort *)&DAT_2000010a;
LAB_0800b5bc:
        uStack_6a = 0;
        uStack_6b = 0;
        bStack_6c = 2;
        uVar16 = (uint)*puVar13;
        bStack_69 = (byte)(*puVar13 >> 8);
LAB_0800b55c:
        uStack_68 = (undefined1)uVar16;
        goto LAB_0800b5aa;
      }
      if (bRam00000004 == 3) {
        puVar12 = (uint *)&DAT_20000114;
LAB_0800b58a:
        bStack_6c = 3;
        uVar16 = *puVar12;
        uStack_6b = (undefined1)(uVar16 >> 0x18);
        uStack_6a = (undefined1)(uVar16 >> 0x10);
        bStack_69 = (byte)(uVar16 >> 8);
        goto LAB_0800b55c;
      }
      if (bRam00000004 == 4) {
        bStack_6c = 4;
        uStack_6b = 0;
        uStack_6a = 0;
        bStack_69 = 0;
        uStack_68 = 0;
        auStack_67[0] = 2;
      }
    }
LAB_0800b572:
    cVar2 = '\x06';
    goto LAB_0800b336;
  }
  switch(uStack_30) {
  default:
    goto switchD_0800b10a_caseD_0;
  case 1:
    bStack_6c = 0xc;
    uStack_6b = 1;
    cVar2 = '\x02';
    uVar6 = 1;
    break;
  case 2:
    fw_0800bc38(&bStack_6c);
    cVar2 = bStack_6c + 1;
    uVar6 = uStack_30;
    break;
  case 4:
    uVar6 = 0;
    goto LAB_0800b3fa;
  case 5:
    cVar2 = '\x05';
    bStack_6c = fw_0800b74c(bRam00000004,&uStack_2c,auStack_24,&uStack_28);
    uStack_6b = (undefined1)(uStack_2c >> 8);
    uStack_6a = (undefined1)uStack_2c;
    bStack_69 = SUB21(auStack_24._0_2_,1);
    uStack_68 = (undefined1)auStack_24._0_2_;
    uVar6 = uStack_30;
    break;
  case 7:
    uVar5 = fw_080040e8(_DAT_2000088c,10);
    bStack_6c = (byte)((ushort)uVar4 >> 8);
    uStack_6b = (undefined1)uVar4;
    uStack_6a = (undefined1)((ushort)uVar5 >> 8);
    bStack_69 = (byte)uVar5;
    cVar2 = '\x04';
    uVar6 = uStack_30;
    break;
  case 9:
    fw_0800bcac(bRam00000004,uRam00000005);
    bStack_6c = bVar17;
    goto LAB_0800b66a;
  case 0xc:
    fw_0800bc74(bRam00000004,uRam00000005);
    bStack_6c = bVar14;
LAB_0800b66a:
    cVar2 = '\x01';
    uVar6 = uStack_30;
    break;
  case 0xd:
    fw_0800b6d4(bRam00000004,uRam00000005,&uStack_2c);
    bStack_6c = bVar14;
    uStack_6b = (undefined1)(uStack_2c >> 8);
    uStack_6a = (undefined1)uStack_2c;
    fw_0800c7c4(uStack_30,3,1,&bStack_6c);
    fw_08009e30(bVar14 - 1,4);
    return;
  case 0xf:
    cVar2 = '\x19';
    fw_0800b708(&bStack_6c);
    uVar6 = uStack_30;
    break;
  case 0x14:
    if (_DAT_20000878 != 0) {
      DAT_200000bc = 1;
      _DAT_200000c0 = 0x2ee;
      return;
    }
    uVar6 = (uint)CONCAT11(bRam00000009,bRam0000000a);
    uStack_28 = uVar6;
LAB_0800b3fa:
    uStack_2c = (uint)CONCAT11(bRam00000007,bRam00000008);
    uStack_6b = fw_0800ca80(bRam00000004,CONCAT11(uRam00000005,bRam00000006),uStack_2c,uVar6);
    bStack_6c = bVar14;
    cVar2 = '\x02';
    uVar6 = uStack_30;
    break;
  case 0x15:
    if (_DAT_20000878 != 0) {
      DAT_200000bc = 1;
      _DAT_200000c0 = 0x2ee;
      return;
    }
    cVar2 = '\t';
    bStack_6c = fw_0800b74c(bRam00000004,&uStack_2c,auStack_24,&uStack_28);
    uStack_6b = (undefined1)(uStack_2c >> 8);
    uStack_6a = (undefined1)uStack_2c;
    bStack_69 = SUB21(auStack_24._0_2_,1);
    uStack_68 = (undefined1)auStack_24._0_2_;
    auStack_67[0] = (undefined1)(uStack_28 >> 8);
    auStack_67[1] = (undefined1)uStack_28;
    auStack_67[2] = SUB21(auStack_20._0_2_,1);
    auStack_67[3] = (undefined1)auStack_20._0_2_;
    uVar6 = uStack_30;
  }
LAB_0800b336:
  fw_0800c7c4(uVar6,cVar2,1,&bStack_6c);
switchD_0800b10a_caseD_0:
  return;
switchD_0800b13e_caseD_4:
  if (_DAT_20000ad2 == 0) {
    DAT_200000bc = 1;
    _DAT_200000c0 = 0x2ee;
    return;
  }
  DAT_200000bc = 1;
  _DAT_200000c0 = 0x2ee;
  _DAT_20000ad2 = _DAT_20000ad2 & ~(ushort)(1 << DAT_20000121);
  return;
}

