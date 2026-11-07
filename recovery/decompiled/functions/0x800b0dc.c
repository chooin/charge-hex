// rea decompile_all
// name: app_dispatch_frame
// address: 0x800b0dc
// body: available
// range: 0x800b0dc-0x800b10d inclusive
// range: 0x800b126-0x800b141 inclusive
// range: 0x800b14a-0x800b2eb inclusive
// range: 0x800b2ee-0x800b4db inclusive
// range: 0x800b524-0x800b6b1 inclusive
// non_contiguous: true
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; Ghidra Listing reports a terminal call at 0x800b10a to 0x800b23e (callee identity unknown), 0x800b29e (callee identity unknown), 0x800b2d8 (callee identity unknown), 0x80095d2 __ARM_common_switch8 (external=false, thunk=false, hasNoReturn=false), 0x800b150 (callee identity unknown), 0x800b270 (callee identity unknown), 0x800b24e (callee identity unknown), 0x800b2ce (callee identity unknown), 0x800b2ee (callee identity unknown), 0x800b22a (callee identity unknown), 0x800b2ea (callee identity unknown), 0x800b2e8 (callee identity unknown), 0x800b2e6 (callee identity unknown); fallthrough is excluded by Ghidra's flow model. The reason for the terminal flow is not established by this observation.; Ghidra Listing reports a terminal call at 0x800b13e to 0x800b16c (callee identity unknown), 0x800b18a (callee identity unknown), 0x800b178 (callee identity unknown), 0x800b174 (callee identity unknown), 0x80095d2 __ARM_common_switch8 (external=false, thunk=false, hasNoReturn=false), 0x800b150 (callee identity unknown), 0x800b170 (callee identity unknown); fallthrough is excluded by Ghidra's flow model. The reason for the terminal flow is not established by this observation.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Function: __ARM_common_switch8 replaced with injection: switch8_r3 */
/* WARNING (jumptable): Removing unreachable block (ram,0x0800b10a) */
/* WARNING (jumptable): Removing unreachable block (ram,0x0800b13e) */
/* WARNING: Removing unreachable block (ram,0x0800b10a) */
/* WARNING: Removing unreachable block (ram,0x0800b13e) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void app_dispatch_frame(char *param_1)

{
  undefined2 uVar1;
  ushort uVar2;
  char cVar3;
  undefined2 uVar4;
  uint uVar5;
  int iVar6;
  undefined *puVar7;
  uint *puVar8;
  char *pcVar9;
  ushort *puVar10;
  uint uVar11;
  uint uVar12;
  char cVar13;
  char local_6c;
  undefined1 local_6b;
  char local_6a;
  char local_69;
  char local_68;
  char local_67 [55];
  uint local_30;
  uint local_2c;
  uint local_28;
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  uint local_1c;
  
  uVar1 = _DAT_20000890;
  local_30 = (uint)(byte)param_1[2];
  _DAT_200000c0 = 0x2ee;
  DAT_200000bc = 1;
  cVar13 = '\0';
  if (*param_1 == 'U') {
    if (local_30 == 0x10) {
      fw_0800be24(param_1 + 4);
      return;
    }
    if (local_30 == 0x2c) {
      if (_DAT_20000878 != 3) {
        DAT_200000bc = 1;
        _DAT_200000c0 = 0x2ee;
        return;
      }
      fw_0800c20c(param_1 + 4);
      return;
    }
    if (local_30 == 0x2d) {
      if (_DAT_20000878 != 3) {
        DAT_200000bc = 1;
        _DAT_200000c0 = 0x2ee;
        return;
      }
      fw_0800c1c8(param_1 + 4);
      return;
    }
    if (local_30 != 0x36) {
      DAT_200000bc = 1;
      _DAT_200000c0 = 0x2ee;
      return;
    }
    switch(param_1[4]) {
    default:
      DAT_200000bc = 1;
      _DAT_200000c0 = 0x2ee;
      return;
    case '\x01':
      DAT_200000bc = 1;
      _DAT_200000c0 = 0x2ee;
      _DAT_20000acc = 0;
      return;
    case '\x02':
      DAT_200000bc = 1;
      _DAT_200000c0 = 0x2ee;
      _DAT_20000ace = 0;
      return;
    case '\x03':
      DAT_200000bc = 1;
      _DAT_200000c0 = 0x2ee;
      _DAT_20000ad0 = 0;
      return;
    case '\x04':
      goto switchD_0800b13e_caseD_4;
    case '\x05':
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
  if (local_30 == 0x18) {
    fw_0800bcd8(param_1 + 4,1);
    goto LAB_0800b66a;
  }
  local_24._0_2_ = local_24._1_2_;
  local_20._0_2_ = local_20._1_2_;
  if (0x18 < local_30) {
    uVar11 = local_30;
    if (local_30 != 0x34) {
      if (local_30 < 0x35) {
        if (local_30 == 0x27) {
          if (_DAT_20000878 != 3) {
            DAT_200000bc = 1;
            _DAT_200000c0 = 0x2ee;
            return;
          }
          local_1c = (uint)(byte)param_1[4];
          iVar6 = CONCAT31(CONCAT21(CONCAT11(param_1[0xb],param_1[0xc]),param_1[0xd]),param_1[0xe]);
          if (iVar6 != _DAT_200000d8) {
            local_2c = (uint)CONCAT11(param_1[7],param_1[8]);
            local_28 = (uint)CONCAT11(param_1[9],param_1[10]);
            DAT_200000cc = fw_0800ca80(local_1c,CONCAT11(param_1[5],param_1[6]),local_2c);
            DAT_200000be = 0;
            DAT_200000bf = 0;
            _DAT_200008de = 0;
            _DAT_200000d8 = iVar6;
          }
          cVar3 = '\x06';
          local_6b = DAT_200000cc;
          local_6a = param_1[0xb];
          local_69 = param_1[0xc];
          local_68 = param_1[0xd];
          local_67[0] = param_1[0xe];
          uVar11 = local_30;
          local_6c = (char)local_1c;
        }
        else if (local_30 < 0x28) {
          if (local_30 == 0x1e) {
            cVar3 = '\x17';
            fw_0800b7a8(&local_6c);
            uVar11 = local_30;
          }
          else {
            if (local_30 != 0x23) {
              DAT_200000bc = 1;
              _DAT_200000c0 = 0x2ee;
              return;
            }
            local_6c = '\x18';
            local_6b = 0;
            local_6a = '\x03';
            local_69 = '\0';
            local_68 = '\x06';
            uVar12 = 0;
            do {
              uVar5 = uVar12 + 1 & 0xff;
              local_67[uVar12] = '\0';
              uVar12 = uVar5;
            } while (uVar5 < 0xc);
            cVar3 = '\x11';
          }
        }
        else if (local_30 == 0x2e) {
          if (_DAT_20000878 != 3) {
            DAT_200000bc = 1;
            _DAT_200000c0 = 0x2ee;
            return;
          }
          cVar3 = '\x0f';
          iVar6 = fw_0800b74c(param_1[4],&local_2c,local_24,&local_28);
          uVar1 = *(undefined2 *)(iVar6 * 0x34 + 0x200005c0);
          uVar4 = *(undefined2 *)(iVar6 * 0x34 + 0x200005c2);
          local_6b = (undefined1)(local_2c >> 8);
          local_6a = (char)local_2c;
          local_69 = SUB21(local_24._0_2_,1);
          local_68 = (char)local_24._0_2_;
          local_67[0] = (char)(local_28 >> 8);
          local_67[1] = (char)local_28;
          local_67[2] = SUB21(local_20._0_2_,1);
          local_67[3] = (char)local_20._0_2_;
          local_67[4] = (char)((ushort)uVar1 >> 8);
          local_67[5] = (char)uVar1;
          local_67[6] = (char)((ushort)uVar4 >> 8);
          local_67[7] = (char)uVar4;
          local_67[8] = 0xff;
          local_67[9] = 0xff;
          uVar11 = local_30;
          local_6c = (char)iVar6;
        }
        else {
          if (local_30 != 0x32) {
            DAT_200000bc = 1;
            _DAT_200000c0 = 0x2ee;
            return;
          }
          cVar13 = param_1[4];
          if (cVar13 == '\x01') {
            DAT_20000102 = param_1[8];
            uVar11 = (uint)(ushort)(short)DAT_20000102;
            puVar7 = &DAT_0800fc58;
LAB_0800b4d0:
            fw_0800a4a8(puVar7,uVar11);
          }
          else {
            if (cVar13 == '\x02') {
              _DAT_2000010c = CONCAT11(param_1[7],param_1[8]);
              uVar11 = (uint)_DAT_2000010c;
              puVar7 = &DAT_0800fc5a;
              goto LAB_0800b4d0;
            }
            if (cVar13 == '\x03') {
              uVar11 = (uint)CONCAT11(param_1[7],param_1[8]);
              puVar7 = &DAT_0800fc5c;
              _DAT_20000118 = uVar11;
              goto LAB_0800b4d0;
            }
          }
          local_6c = '\0';
          cVar3 = '\x01';
          uVar11 = local_30;
        }
      }
      else {
        if (local_30 == 0x35) {
          cVar13 = param_1[4];
          if (cVar13 != '\x01') {
            if (cVar13 != '\x02') {
              if (cVar13 == '\x03') {
                puVar8 = (uint *)&DAT_20000118;
                goto LAB_0800b58a;
              }
              goto LAB_0800b572;
            }
            puVar10 = (ushort *)&DAT_2000010c;
            goto LAB_0800b5bc;
          }
          pcVar9 = &DAT_20000102;
          goto LAB_0800b5a6;
        }
        if (local_30 == 0x38) {
          _DAT_20000878 = (ushort)(byte)param_1[4];
          _DAT_20000866 = *(ushort *)(param_1 + 5) << 8 | *(ushort *)(param_1 + 5) >> 8;
          if (0x9c4 < _DAT_20000866) {
            _DAT_20000866 = 0x9c4;
          }
          _DAT_20000870 = (ushort)(byte)param_1[7];
          _DAT_20000872 = (ushort)(byte)param_1[8];
          _DAT_20000874 = (ushort)(byte)param_1[9] * 0x3c;
          if (0x3840 < _DAT_20000874) {
            _DAT_20000874 = 0x3840;
          }
          _DAT_2000087c = (ushort)(byte)param_1[10];
          if (0x14 < (byte)param_1[10]) {
            _DAT_2000087c = 0x14;
          }
          _DAT_2000087a = *(ushort *)(param_1 + 0xb) << 8 | *(ushort *)(param_1 + 0xb) >> 8;
          if (0x1e0 < _DAT_2000087a) {
            _DAT_2000087a = 0x1e0;
          }
          DAT_200008cb = param_1[0xd];
          fw_0800a4a8(&DAT_0800fc24);
          fw_0800a4a8(&DAT_0800fc12,_DAT_20000866);
          fw_0800a4a8(&DAT_0800fc1c,_DAT_20000870);
          fw_0800a4a8(&DAT_0800fc1e,_DAT_20000872);
          fw_0800a4a8(&DAT_0800fc20,_DAT_20000874);
          fw_0800a4a8(&DAT_0800fc28,_DAT_2000087c);
          fw_0800a4a8(&DAT_0800fc26,_DAT_2000087a);
          fw_0800a4a8(&DAT_0800fc2a,DAT_200008cb);
          goto LAB_0800b66a;
        }
        if (local_30 != 0x39) {
          if (local_30 != 0x3b) {
            DAT_200000bc = 1;
            _DAT_200000c0 = 0x2ee;
            return;
          }
          local_6c = '\0';
          fw_0800c7c4(0x3b,1,1,&local_6c);
          if (param_1[4] != '\0') {
            if (param_1[4] != '\x01') {
              return;
            }
            fw_0800a4a8(&DAT_0800f802,0xaaaa);
            return;
          }
          fw_0800a4a8(&DAT_0800f802,0xaaaa);
          fw_080063ec();
          return;
        }
        local_6c = (char)_DAT_20000878;
        local_6b = (undefined1)(_DAT_20000866 >> 8);
        local_6a = (char)_DAT_20000866;
        local_69 = DAT_20000870;
        local_68 = DAT_20000872;
        local_67[0] = fw_080040e8(_DAT_20000874,0x3c);
        local_67[1] = (char)_DAT_2000087c;
        local_67[2] = (char)(_DAT_2000087a >> 8);
        local_67[3] = (char)_DAT_2000087a;
        local_67[4] = DAT_200008cb;
        cVar3 = '\n';
        uVar11 = local_30;
      }
      goto LAB_0800b336;
    }
    cVar13 = param_1[4];
    if (cVar13 == '\x01') {
      pcVar9 = &DAT_20000101;
LAB_0800b5a6:
      local_69 = '\0';
      local_6a = '\0';
      local_6b = 0;
      local_6c = '\x01';
      local_68 = *pcVar9;
LAB_0800b5aa:
      local_67[0] = '\0';
    }
    else {
      if (cVar13 == '\x02') {
        puVar10 = (ushort *)&DAT_2000010a;
LAB_0800b5bc:
        local_6a = '\0';
        local_6b = 0;
        local_6c = '\x02';
        uVar12 = (uint)*puVar10;
        local_69 = (char)(*puVar10 >> 8);
LAB_0800b55c:
        local_68 = (char)uVar12;
        goto LAB_0800b5aa;
      }
      if (cVar13 == '\x03') {
        puVar8 = (uint *)&DAT_20000114;
LAB_0800b58a:
        local_6c = '\x03';
        uVar12 = *puVar8;
        local_6b = (undefined1)(uVar12 >> 0x18);
        local_6a = (char)(uVar12 >> 0x10);
        local_69 = (char)(uVar12 >> 8);
        goto LAB_0800b55c;
      }
      if (cVar13 == '\x04') {
        local_6c = '\x04';
        local_6b = 0;
        local_6a = '\0';
        local_69 = '\0';
        local_68 = '\0';
        local_67[0] = '\x02';
      }
    }
LAB_0800b572:
    cVar3 = '\x06';
    goto LAB_0800b336;
  }
  switch(local_30) {
  default:
    goto switchD_0800b10a_caseD_0;
  case 1:
    local_6c = '\f';
    local_6b = 1;
    cVar3 = '\x02';
    uVar11 = 1;
    break;
  case 2:
    fw_0800bc38(&local_6c);
    cVar3 = local_6c + '\x01';
    uVar11 = local_30;
    break;
  case 4:
    cVar13 = param_1[4];
    uVar1 = CONCAT11(param_1[5],param_1[6]);
    uVar2 = CONCAT11(param_1[7],param_1[8]);
    uVar11 = 0;
    goto LAB_0800b3fa;
  case 5:
    cVar3 = '\x05';
    local_6c = fw_0800b74c(param_1[4],&local_2c,local_24,&local_28);
    local_6b = (undefined1)(local_2c >> 8);
    local_6a = (char)local_2c;
    local_69 = SUB21(local_24._0_2_,1);
    local_68 = (char)local_24._0_2_;
    uVar11 = local_30;
    break;
  case 7:
    uVar4 = fw_080040e8(_DAT_2000088c,10);
    local_6b = (undefined1)uVar1;
    local_6a = (char)((ushort)uVar4 >> 8);
    local_69 = (char)uVar4;
    cVar3 = '\x04';
    uVar11 = local_30;
    local_6c = (char)((ushort)uVar1 >> 8);
    break;
  case 9:
    fw_0800bcac(param_1[4],param_1[5]);
    goto LAB_0800b66a;
  case 0xc:
    cVar13 = param_1[4];
    fw_0800bc74(cVar13,param_1[5]);
LAB_0800b66a:
    cVar3 = '\x01';
    uVar11 = local_30;
    local_6c = cVar13;
    break;
  case 0xd:
    cVar13 = param_1[4];
    fw_0800b6d4(cVar13,param_1[5],&local_2c);
    local_6b = (undefined1)(local_2c >> 8);
    local_6a = (char)local_2c;
    local_6c = cVar13;
    fw_0800c7c4(local_30,3,1,&local_6c);
    fw_08009e30(cVar13 + -1,4);
    return;
  case 0xf:
    cVar3 = '\x19';
    fw_0800b708(&local_6c);
    uVar11 = local_30;
    break;
  case 0x14:
    if (_DAT_20000878 != 0) {
      DAT_200000bc = 1;
      _DAT_200000c0 = 0x2ee;
      return;
    }
    cVar13 = param_1[4];
    uVar1 = CONCAT11(param_1[5],param_1[6]);
    uVar2 = CONCAT11(param_1[7],param_1[8]);
    uVar11 = (uint)CONCAT11(param_1[9],param_1[10]);
    local_28 = uVar11;
LAB_0800b3fa:
    local_2c = (uint)uVar2;
    local_6b = fw_0800ca80(cVar13,uVar1,local_2c,uVar11);
    cVar3 = '\x02';
    uVar11 = local_30;
    local_6c = cVar13;
    break;
  case 0x15:
    if (_DAT_20000878 != 0) {
      DAT_200000bc = 1;
      _DAT_200000c0 = 0x2ee;
      return;
    }
    cVar3 = '\t';
    local_6c = fw_0800b74c(param_1[4],&local_2c,local_24,&local_28);
    local_6b = (undefined1)(local_2c >> 8);
    local_6a = (char)local_2c;
    local_69 = SUB21(local_24._0_2_,1);
    local_68 = (char)local_24._0_2_;
    local_67[0] = (char)(local_28 >> 8);
    local_67[1] = (char)local_28;
    local_67[2] = SUB21(local_20._0_2_,1);
    local_67[3] = (char)local_20._0_2_;
    uVar11 = local_30;
  }
LAB_0800b336:
  fw_0800c7c4(uVar11,cVar3,1,&local_6c);
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

