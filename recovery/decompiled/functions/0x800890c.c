// rea decompile_all
// name: fw_0800890c
// address: 0x800890c
// body: available
// range: 0x800890c-0x8008939 inclusive
// range: 0x800895e-0x8008d13 inclusive
// range: 0x8008d28-0x8008dc7 inclusive
// non_contiguous: true
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; Ghidra Listing reports a terminal call at 0x8008936 to 0x800895e (callee identity unknown), 0x8008b1e (callee identity unknown), 0x80089dc (callee identity unknown), 0x8008b1c (callee identity unknown), 0x8008b1a (callee identity unknown), 0x8008b18 (callee identity unknown), 0x8008b16 (callee identity unknown), 0x8008b14 (callee identity unknown), 0x80095d2 __ARM_common_switch8 (external=false, thunk=false, hasNoReturn=false), 0x8008b12 (callee identity unknown), 0x8008b10 (callee identity unknown), 0x8008b0e (callee identity unknown), 0x8008b0c (callee identity unknown), 0x8008b0a (callee identity unknown), 0x8008b08 (callee identity unknown), 0x8008b06 (callee identity unknown), 0x8008b04 (callee identity unknown), 0x8008b02 (callee identity unknown), 0x8008b00 (callee identity unknown), 0x8008afe (callee identity unknown), 0x8008afc (callee identity unknown), 0x8008afa (callee identity unknown), 0x8008af8 (callee identity unknown), 0x8008af6 (callee identity unknown), 0x8008b22 (callee identity unknown), 0x8008b20 (callee identity unknown); fallthrough is excluded by Ghidra's flow model. The reason for the terminal flow is not established by this observation.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Function: __ARM_common_switch8 replaced with injection: switch8_r3 */
/* WARNING (jumptable): Removing unreachable block (ram,0x08008936) */
/* WARNING: Removing unreachable block (ram,0x08008936) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_0800890c(void)

{
  char cVar1;
  ushort uVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  undefined1 uVar6;
  byte bVar7;
  undefined2 uVar8;
  uint uVar9;
  int iVar10;
  undefined4 uVar11;
  int extraout_r1;
  int extraout_r1_00;
  int extraout_r1_01;
  int extraout_r1_02;
  undefined4 extraout_r1_03;
  uint uVar12;
  uint uVar13;
  int iVar14;
  bool bVar15;
  uint local_28;
  
  bVar7 = fw_0800a6cc();
  uVar2 = _DAT_200008dc;
  bVar3 = DAT_200000f3;
  bVar7 = bVar7 & 1;
  if (DAT_200000dc != '\0') {
    return;
  }
  DAT_200000dc = 1;
  uVar9 = (uint)DAT_20000854;
  iVar14 = 0x200008b4;
  switch(uVar9) {
  default:
switchD_08008936_caseD_0:
    break;
  case 1:
    if (DAT_200008c2 == '\0') goto LAB_0800896c;
    if (DAT_200008c2 == '\x01') goto LAB_0800896c;
    bVar15 = DAT_200008c2 == '\x02';
    do {
      if (!bVar15) goto switchD_08008936_caseD_0;
LAB_0800896c:
      fw_0800a3f4(0,_DAT_200008c4);
      uVar9 = *(byte *)(iVar14 + 0x12) - 1;
      uVar12 = uVar9 & 0xffff;
      fw_0800a3f4(0);
      iVar10 = uVar12 * 0x34;
      iVar14 = iVar10 + 0x200005e4;
      cVar1 = *(char *)(iVar10 + 0x200005fa);
      if (cVar1 == '\0') {
        iVar14 = fw_0800a690(uVar9 & 0xff);
        if (iVar14 != 0) {
          DAT_200000dc = 0;
          DAT_200000e3 = DAT_200000f0;
          DAT_200000e4 = DAT_200000f2;
          DAT_200000e5 = DAT_200000f0;
          return;
        }
        if (*(short *)(uVar12 * 2 + 0x20000976) == 0) {
          if (*(char *)(iVar10 + 0x20000614) == '\x01') {
            DAT_200000dc = 0;
            DAT_200000e3 = DAT_200000f0;
            DAT_200000e4 = DAT_200000f6;
            DAT_200000e5 = DAT_200000f0;
            return;
          }
LAB_080089ee:
          fw_0800a3d8(1,10);
          DAT_200000dc = 0;
          return;
        }
        fw_0800a450(1);
        fw_080040e8(*(undefined2 *)(uVar12 * 2 + 0x20000976),3);
        (&DAT_200000e3)[extraout_r1] = DAT_200000f5;
        goto switchD_08008936_caseD_0;
      }
      if (cVar1 == '\x01') {
        if (bVar7 != 0) goto LAB_080089ee;
        goto LAB_080089fe;
      }
      if (cVar1 == '\x02') {
        cVar1 = (&DAT_20000611)[iVar10];
        if (cVar1 == '\0') {
          local_28 = 0xea24;
          if ((0xea24 < *(uint *)(iVar10 + 0x200005e4)) ||
             (local_28 = *(uint *)(iVar10 + 0x200005e4) & 0xffff, 0x3b < local_28)) {
            uVar11 = 0x3c;
            goto LAB_08008a4e;
          }
        }
        else {
          if (cVar1 == '\x01') {
            uVar2 = *(ushort *)(iVar10 + 0x200005e8);
          }
          else {
            if (cVar1 != '\x02') {
              if (cVar1 == '\x03') {
                local_28 = (uint)*(ushort *)(iVar10 + 0x200005f2);
              }
              goto LAB_08008a54;
            }
            uVar2 = *(ushort *)(iVar10 + 0x200005ea);
          }
          local_28 = (uint)uVar2;
          if (999 < local_28) {
            uVar11 = 10;
LAB_08008a4e:
            local_28 = fw_080040e8(local_28,uVar11);
          }
        }
LAB_08008a54:
        fw_0800a38c(1,local_28);
        cVar1 = (&DAT_20000611)[iVar10];
        if (cVar1 != '\0') {
          if (cVar1 == '\x01') {
            if (*(ushort *)(iVar10 + 0x200005e8) < 1000) goto switchD_08008936_caseD_0;
          }
          else {
            if (cVar1 != '\x02') {
              if (cVar1 == '\x03') goto LAB_08008ad6;
              goto switchD_08008936_caseD_0;
            }
            if (999 < _DAT_2000061e) goto LAB_08008ad6;
          }
          DAT_200000dc = 0;
          DAT_200000e5 = DAT_200000e5 | DAT_200000f4;
          return;
        }
        iVar14 = fw_0800a018(uVar9 & 0xff);
        if (iVar14 == 1) {
          fw_0800a450(1);
          fw_080040e8(*(undefined2 *)(uVar12 * 2 + 0x2000092e),3);
          (&DAT_200000e3)[extraout_r1_00] = DAT_200000f0;
        }
        else {
          DAT_200000e3 = DAT_200000e3 + bVar7;
        }
        if ((&DAT_20000611)[iVar10] != '\0') {
          DAT_200000dc = 0;
          return;
        }
        if (*(short *)(uVar12 * 2 + 0x2000095e) != 0) goto LAB_08008af2;
        if (*(short *)(uVar12 * 2 + 0x20000946) == 0) {
          DAT_200000dc = 0;
          return;
        }
        bVar3 = DAT_200000e3;
        bVar4 = DAT_200000e4;
        bVar5 = DAT_200000e5;
        if (_DAT_20000872 <= *(ushort *)(iVar10 + 0x200005e8)) {
          DAT_200000dc = 0;
          return;
        }
        break;
      }
      bVar15 = cVar1 == '\x04';
      bVar3 = DAT_200000f0;
      bVar4 = DAT_200000f1;
      bVar5 = DAT_200000f0;
    } while (!bVar15);
    if (bVar7 != 0) {
      DAT_200000dc = 0;
      DAT_200000e3 = bVar3;
      DAT_200000e4 = bVar4;
      DAT_200000e5 = bVar5;
      return;
    }
LAB_08008af2:
    if (bVar7 != 0) {
      DAT_200000dc = 0;
      DAT_200000e3 = DAT_200000f0;
      DAT_200000e4 = DAT_200000f2;
      DAT_200000e5 = DAT_200000f0;
      return;
    }
    goto LAB_080089fe;
  case 2:
    fw_0800a38c(0,_DAT_20000882);
LAB_080089fe:
    fw_0800a450(1);
    break;
  case 3:
  case 4:
    if (DAT_200008c0 == '\x04') {
      DAT_200000e0 = DAT_200000f0;
      DAT_200000e1 = DAT_200000f0;
      DAT_200000e2 = DAT_200000e0;
    }
    else {
      fw_0800a38c(0,_DAT_20000886);
      DAT_200000e1 = DAT_200000e1 | DAT_200000f4;
    }
    uVar9 = (uint)_DAT_20000888;
    if (999 < uVar9) {
      uVar11 = 10;
LAB_08008d34:
      uVar9 = fw_080040e8(uVar9,uVar11);
      goto LAB_08008d86;
    }
    fw_0800a38c(1,uVar9);
    goto LAB_08008ad6;
  case 5:
    if (_DAT_200008dc < 0xf) {
      uVar9 = 0;
      do {
        iVar14 = uVar9 * 3;
        (&DAT_200000e0)[iVar14] = bVar3;
        (&DAT_200000e1)[iVar14] = bVar3;
        uVar9 = uVar9 + 1 & 0xffff;
        (&DAT_200000e2)[iVar14] = bVar3;
      } while (uVar9 < 2);
      fw_080040e8(uVar2,3);
      uVar6 = DAT_200000f5;
      (&DAT_200000e0)[extraout_r1_01] = DAT_200000f5;
      (&DAT_200000e3)[extraout_r1_01] = uVar6;
    }
    break;
  case 6:
    uVar12 = 1;
    uVar2 = _DAT_20000856;
    goto LAB_08008bce;
  case 7:
    uVar12 = 2;
    uVar2 = _DAT_20000858;
LAB_08008bce:
    uVar13 = 0;
    uVar9 = (uint)uVar2;
    uVar11 = 1;
    goto LAB_08008bd0;
  case 8:
    uVar12 = 1;
    uVar2 = _DAT_2000085c;
    goto LAB_08008be4;
  case 9:
    uVar12 = 2;
    uVar2 = _DAT_2000085e;
LAB_08008be4:
    uVar13 = 1;
    uVar9 = (uint)uVar2;
    uVar11 = 2;
    goto LAB_08008bd0;
  case 10:
    uVar12 = 1;
    uVar9 = (uint)_DAT_2000085a;
    uVar11 = 3;
    uVar13 = uVar12;
    goto LAB_08008bd0;
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
    uVar12 = uVar9 - 0xb & 0xffff;
    uVar9 = fw_080040e8(*(undefined2 *)(&DAT_20000860 + uVar12 * 2),10);
    uVar12 = uVar12 + 1 & 0xff;
    uVar11 = 4;
    uVar13 = 2;
    goto LAB_08008bd0;
  case 0xf:
  case 0x10:
  case 0x11:
    uVar12 = uVar9 - 0xf & 0xffff;
    uVar9 = (uint)*(ushort *)(&DAT_20000868 + uVar12 * 2);
    uVar12 = uVar12 + 1 & 0xff;
    uVar11 = 5;
    uVar13 = 0;
    goto LAB_08008bd0;
  case 0x12:
    DAT_200000e0 = DAT_200000e7;
    uVar8 = _DAT_2000086e;
    goto LAB_08008c8c;
  case 0x13:
    DAT_200000e0 = DAT_200000e8;
    uVar8 = _DAT_20000870;
    goto LAB_08008c8c;
  case 0x14:
    uVar9 = (uint)_DAT_20000872;
    DAT_200000e0 = DAT_200000e9;
    DAT_200000e1 = DAT_200000f0;
    DAT_200000e2 = DAT_200000ec;
    goto LAB_08008d86;
  case 0x15:
    uVar9 = fw_080040e8(_DAT_20000874,0x3c);
    DAT_200000e0 = DAT_200000ea;
    DAT_200000e1 = DAT_200000f0;
    DAT_200000e2 = DAT_200000ec;
    goto LAB_08008d86;
  case 0x16:
    DAT_200000e0 = DAT_200000eb;
    uVar8 = _DAT_20000876;
    goto LAB_08008c8c;
  case 0x17:
    DAT_200000e0 = DAT_200000ec;
    uVar8 = _DAT_20000878;
LAB_08008c8c:
    DAT_200000e2 = DAT_200000ec;
    DAT_200000e1 = DAT_200000f0;
    DAT_200000e5 = DAT_200000f3;
    DAT_200000e4 = DAT_200000f3;
    fw_080040e8(uVar8,10);
    DAT_200000e3 = (&DAT_200000e6)[extraout_r1_02];
    break;
  case 0x18:
    uVar12 = 7;
    uVar9 = (uint)_DAT_2000087a;
    goto LAB_08008cae;
  case 0x19:
    uVar12 = 8;
    uVar9 = (uint)_DAT_2000087c;
    goto LAB_08008cae;
  case 0x1a:
    uVar9 = (uint)DAT_200008cb;
    uVar12 = 9;
LAB_08008cae:
    uVar11 = 6;
    uVar13 = 0;
LAB_08008bd0:
    fw_0800c70c(uVar11,uVar12,uVar9,uVar13);
    break;
  case 0x1c:
  case 0x1d:
  case 0x1e:
    uVar9 = *(uint *)(&DAT_2000088c + (uVar9 - 0x1c & 0xffff) * 4);
    uVar8 = fw_080040e8(uVar9,1000);
    fw_0800a38c(0,uVar8);
    fw_0800a38c(1,uVar9 & 0xffff);
    fw_080040e8(uVar9,100);
    iVar14 = fw_080040e8(extraout_r1_03,10);
    DAT_200000e4 = (&DAT_200000e6)[iVar14];
LAB_08008ad6:
    DAT_200000e4 = DAT_200000e4 | DAT_200000f4;
    break;
  case 0x1f:
    if (((DAT_200008c2 != '\0') && (DAT_200008c2 != '\x01')) && (DAT_200008c2 != '\x02')) {
      DAT_200000dc = 0;
      return;
    }
    uVar12 = (uint)DAT_200008c6;
    fw_0800a3f4(0);
    uVar13 = *(uint *)((uVar12 - 1 & 0xffff) * 0x34 + 0x200005e4);
    uVar9 = 0xea24;
    if ((0xea24 < uVar13) || (uVar9 = uVar13 & 0xffff, 0x3b < uVar9)) {
      uVar11 = 0x3c;
      goto LAB_08008d34;
    }
    if (uVar9 == 0) {
      DAT_200000e5 = DAT_200000f0;
      iVar14 = fw_0800a690(uVar12 - 1 & 0xff);
      if (iVar14 == 0) {
        DAT_200000dc = 0;
        DAT_200000e3 = DAT_200000f0;
        DAT_200000e4 = DAT_200000f0;
        return;
      }
      DAT_200000dc = 0;
      DAT_200000e3 = DAT_200000f0;
      DAT_200000e4 = DAT_200000f2;
      return;
    }
    goto LAB_08008d86;
  case 0x20:
    if (((DAT_200008c2 != '\0') && (DAT_200008c2 != '\x01')) && (DAT_200008c2 != '\x02')) {
      DAT_200000dc = 0;
      return;
    }
    uVar9 = DAT_200008c6 - 1 & 0xffff;
    fw_0800a3f4(0);
    if (DAT_20000855 != uVar9) {
      uVar11 = fw_080040e8(*(undefined2 *)(uVar9 * 2 + 0x200008a0),100);
      fw_0800a38c(1,uVar11);
      DAT_200000dc = 0;
      DAT_200000e3 = DAT_200000e3 | DAT_200000f4;
      return;
    }
    uVar9 = (uint)*(ushort *)(uVar9 * 0x34 + 0x200005e8);
LAB_08008d86:
    fw_0800a38c(1,uVar9);
    break;
  case 0x21:
    DAT_200000e1 = DAT_200000e6;
    DAT_200000e0 = DAT_200000e9;
    DAT_200000e2 = DAT_200000e1;
    DAT_200000e3 = DAT_200000ec;
    DAT_200000e4 = DAT_200000e1;
    DAT_200000e5 = DAT_200000e1;
  }
  DAT_200000dc = 0;
  return;
}

