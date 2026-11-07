// rea decompile_all
// name: fw_08007904
// address: 0x8007904
// body: available
// range: 0x8007904-0x8007915 inclusive
// range: 0x8007928-0x80079cf inclusive
// range: 0x80079f4-0x8007baf inclusive
// range: 0x8007bb2-0x8007cd9 inclusive
// non_contiguous: true
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; Ghidra Listing reports a terminal call at 0x8007912 to 0x800796e (callee identity unknown), 0x8007928 (callee identity unknown), 0x80095d2 __ARM_common_switch8 (external=false, thunk=false, hasNoReturn=false), 0x80079c2 (callee identity unknown), 0x8007b00 (callee identity unknown); fallthrough is excluded by Ghidra's flow model. The reason for the terminal flow is not established by this observation.; Ghidra Listing reports a terminal call at 0x80079cc to 0x8007b1e (callee identity unknown), 0x8007a3c (callee identity unknown), 0x8007ada (callee identity unknown), 0x8007b3a (callee identity unknown), 0x8007a58 (callee identity unknown), 0x8007b58 (callee identity unknown), 0x8007b78 (callee identity unknown), 0x8007bb8 (callee identity unknown), 0x80079f6 (callee identity unknown), 0x8007a76 (callee identity unknown), 0x80079f4 (callee identity unknown), 0x8007a94 (callee identity unknown), 0x80095d2 __ARM_common_switch8 (external=false, thunk=false, hasNoReturn=false), 0x8007ab2 (callee identity unknown), 0x8007bae (callee identity unknown), 0x8007bac (callee identity unknown), 0x8007baa (callee identity unknown), 0x8007ba8 (callee identity unknown), 0x8007ba6 (callee identity unknown), 0x8007a22 (callee identity unknown), 0x8007b02 (callee identity unknown); fallthrough is excluded by Ghidra's flow model. The reason for the terminal flow is not established by this observation.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Function: __ARM_common_switch8 replaced with injection: switch8_r3 */
/* WARNING (jumptable): Removing unreachable block (ram,0x08007912) */
/* WARNING (jumptable): Removing unreachable block (ram,0x080079cc) */
/* WARNING: Removing unreachable block (ram,0x08007912) */
/* WARNING: Removing unreachable block (ram,0x080079cc) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_08007904(int param_1)

{
  ushort uVar1;
  undefined2 uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  ushort uVar7;
  undefined1 local_1c;
  undefined1 local_1b;
  byte local_1a;
  byte local_19;
  byte local_18;
  
  switch(param_1) {
  default:
    goto switchD_08007912_caseD_0;
  case 1:
    fw_0800a644();
    uVar3 = (uint)DAT_20000854;
    if (uVar3 == 1) {
      DAT_20000855 = 0xff;
      fw_0800cc64(1);
      fw_0800a65c();
      DAT_20000854 = 6;
      uVar5 = 0x11;
    }
    else {
      if (0x18 < uVar3 - 6) {
        if (uVar3 == 0x20) {
          fw_0800a488(DAT_20000855);
        }
        else if ((uVar3 != 0x1f) && (uVar3 != 0x1a)) {
          return;
        }
        local_1c = 0xaa;
        local_1b = 0x88;
        local_18 = local_1a ^ local_19 ^ 0x22;
        fw_080094b4(&local_1c,5);
        DAT_20000854 = 1;
        if (_DAT_200008bc != 0) {
          fw_0800cc64(1);
        }
        fw_0800cdb8(0x26);
        _DAT_200008d4 = 0;
        return;
      }
      uVar4 = uVar3 + 1 & 0xff;
      DAT_20000854 = (byte)(uVar3 + 1);
      if (uVar4 == 0x17) {
        uVar4 = 0x1c;
        DAT_20000854 = 0x1c;
      }
      uVar5 = fw_0800a6dc(uVar4);
    }
    fw_0800cdb8(uVar5);
    goto LAB_0800796a;
  case 2:
  case 3:
    break;
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
    fw_080080a8();
    goto switchD_08007912_caseD_0;
  }
  switch(DAT_20000854) {
  default:
    break;
  case 1:
    DAT_20000855 = 0xff;
    fw_0800cc64(1);
    fw_0800a65c();
    if (param_1 == 2) {
      DAT_20000854 = 0x1f;
      uVar5 = 0x25;
    }
    else {
      DAT_20000854 = 0x20;
      uVar5 = 0x27;
    }
    fw_0800cdb8(uVar5);
    fw_0800a644();
    goto LAB_0800796a;
  case 6:
    _DAT_20000856 = fw_0800c788(_DAT_20000856,param_1,0x1e,1,_DAT_2000087e,1,&DAT_0800fc02);
    break;
  case 7:
    _DAT_20000858 = fw_0800c788(_DAT_20000858,param_1,0x1e,1,_DAT_2000087e,1,&DAT_0800fc04);
    break;
  case 8:
    _DAT_2000085c = fw_0800c788(_DAT_2000085c,param_1,1,1,0xfa,1,&DAT_0800fc06);
    break;
  case 9:
    _DAT_2000085e = fw_0800c788(_DAT_2000085e,param_1,10,1,0xfa,1,&DAT_0800fc08);
    break;
  case 10:
    _DAT_2000085a = fw_0800c788(_DAT_2000085a,param_1,10,1,0xfa,0,&DAT_0800fc0a);
    break;
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
    iVar6 = (uint)(byte)(DAT_20000854 - 0xb) * 2;
    uVar2 = fw_0800c788(*(undefined2 *)(&DAT_20000860 + iVar6),param_1,0x32,5,0x9c4,0x32,
                        &DAT_0800fc0c + iVar6);
    *(undefined2 *)(&DAT_20000860 + iVar6) = uVar2;
    break;
  case 0xf:
  case 0x10:
  case 0x11:
    iVar6 = (uint)(byte)(DAT_20000854 - 0xf) * 2;
    uVar2 = fw_0800c788(*(undefined2 *)(&DAT_20000868 + iVar6),param_1,1,1,100,1,
                        &DAT_0800fc14 + iVar6);
    *(undefined2 *)(&DAT_20000868 + iVar6) = uVar2;
    break;
  case 0x12:
    _DAT_2000086e = fw_0800c788(_DAT_2000086e,param_1,1,1,1,0,&DAT_0800fc1a);
    break;
  case 0x13:
    _DAT_20000870 = fw_0800c788(_DAT_20000870,param_1,1,1,1,0,&DAT_0800fc1c);
    break;
  case 0x14:
    _DAT_20000872 = fw_0800c788(_DAT_20000872,param_1,10,10,300,10,&DAT_0800fc1e);
    break;
  case 0x15:
    _DAT_20000874 = fw_0800c788(_DAT_20000874,param_1,0x708,0x708,0x3840,0,&DAT_0800fc20);
    break;
  case 0x16:
    iVar6 = fw_0800c788(_DAT_20000876,param_1,1,1,1,0,&DAT_0800fc22);
    _DAT_20000876 = (undefined2)iVar6;
    if (iVar6 == 0) {
      DAT_20000611 = 0;
      DAT_20000645 = 0;
    }
    else {
      DAT_20000611 = 2;
      DAT_20000645 = 2;
    }
    break;
  case 0x17:
    if (param_1 == 2) {
      if ((_DAT_20000878 == 0) || (_DAT_20000878 == 3)) {
        uVar5 = 1;
      }
      else {
        if (_DAT_20000878 != 1) {
          return;
        }
        uVar5 = 2;
      }
      _DAT_20000878 = fw_0800c788(_DAT_20000878,2,uVar5,1,3,0,&DAT_0800fc24);
    }
    else if (param_1 == 3) {
      if ((_DAT_20000878 == 0) || (_DAT_20000878 == 3)) {
        uVar5 = 2;
      }
      else {
        if (_DAT_20000878 != 1) {
          return;
        }
        uVar5 = 1;
      }
      _DAT_20000878 = fw_0800c788(_DAT_20000878,3,1,uVar5,3,0,&DAT_0800fc24);
    }
    break;
  case 0x18:
    _DAT_2000087a = fw_0800c788(_DAT_2000087a,param_1,10,1,0x1e0,5,&DAT_0800fc26);
    break;
  case 0x19:
    _DAT_2000087c = fw_0800c788(_DAT_2000087c,param_1,1,1,0x14,0,&DAT_0800fc28);
    break;
  case 0x1a:
    DAT_200008cb = fw_0800c788(DAT_200008cb,param_1,1,1,7,0,&DAT_0800fc2a);
    fw_0800cdb8(DAT_200008cb + 0xe0);
    break;
  case 0x1f:
    if (param_1 != 3) {
      return;
    }
    DAT_20000854 = 0x17;
LAB_0800796a:
    _DAT_200008d4 = 0x1e;
    break;
  case 0x20:
    if (DAT_20000855 < 0xc) {
      iVar6 = (uint)DAT_20000855 * 2;
      uVar1 = *(ushort *)(iVar6 + 0x200008a0);
      if (param_1 == 2) {
        uVar7 = uVar1 + 1;
        if (2000 < (ushort)(uVar1 + 1)) {
          uVar7 = 2000;
        }
      }
      else {
        uVar7 = uVar1;
        if (uVar1 != 0) {
          uVar7 = uVar1 - 1;
        }
      }
      fw_0800a4a8(&DAT_0800fc40 + iVar6,uVar7);
      *(ushort *)(iVar6 + 0x200008a0) = uVar7;
    }
    _DAT_200008d4 = 300;
  }
switchD_08007912_caseD_0:
  return;
}

