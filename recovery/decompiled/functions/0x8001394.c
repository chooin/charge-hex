// rea decompile_all
// name: fw_08001394
// address: 0x8001394
// body: available
// range: 0x8001394-0x800170d inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong fw_08001394(byte *param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  bool bVar6;
  bool bVar7;
  uint local_20;
  
  bVar6 = param_1 == (byte *)0x0;
  while( true ) {
    local_20 = param_2;
    if (bVar6) goto LAB_08001706;
    if ((*param_1 & 1) == 0) goto LAB_08001438;
    if (((_DAT_40021004 & 0xf) >> 2 != 1) &&
       (((_DAT_40021004 & 0xf) >> 2 != 2 || (-1 < (int)(_DAT_40021004 << 0xf))))) break;
    if ((-1 < (int)(_DAT_40021000 << 0xe)) || (bVar6 = *(int *)(param_1 + 4) == 0, !bVar6))
    goto LAB_08001438;
  }
  iVar5 = *(int *)(param_1 + 4);
  if (iVar5 == 1) {
LAB_080013fa:
    _DAT_40021000 = _DAT_40021000 | 0x10000;
  }
  else {
    if ((iVar5 != 0) && (iVar5 == 5)) {
      _DAT_40021000 = _DAT_40021000 | 0x40000;
      goto LAB_080013fa;
    }
    _DAT_40021000 = _DAT_40021000 & 0xfffaffff;
  }
  if (*(int *)(param_1 + 4) != 0) {
    iVar5 = fw_08000a88();
    goto LAB_08001418;
  }
  iVar5 = fw_08000a88();
  while ((int)(_DAT_40021000 << 0xe) < 0) {
    iVar1 = fw_08000a88();
    uVar3 = iVar1 - iVar5;
    bVar7 = 99 < uVar3;
    bVar6 = uVar3 == 100;
    if (100 < uVar3) goto LAB_08001416;
  }
LAB_08001438:
  iVar5 = 1;
  if ((int)((uint)*param_1 * 0x40000000) < 0) {
    if (((_DAT_40021004 & 0xf) >> 2 == 0) ||
       (((_DAT_40021004 & 0xf) >> 2 == 2 && (-1 < (int)(_DAT_40021004 << 0xf))))) {
      if (((int)(_DAT_40021000 << 0x1e) < 0) && (*(int *)(param_1 + 0xc) != 1)) goto LAB_08001706;
LAB_0800148e:
      _DAT_40021000 = _DAT_40021000 & 0xffffff07 | *(int *)(param_1 + 0x10) << 3;
      goto LAB_080014bc;
    }
    if (*(int *)(param_1 + 0xc) == 0) {
      _DAT_40021000 = _DAT_40021000 & 0xfffffffe;
      iVar1 = fw_08000a88();
      do {
        if (-1 < (int)(_DAT_40021000 << 0x1e)) goto LAB_080014bc;
        iVar2 = fw_08000a88();
        uVar3 = iVar2 - iVar1;
        bVar7 = 1 < uVar3;
        bVar6 = uVar3 == 2;
      } while (uVar3 < 3);
    }
    else {
      _DAT_40021000 = _DAT_40021000 | 1;
      iVar1 = fw_08000a88();
      do {
        if ((int)(_DAT_40021000 << 0x1e) < 0) goto LAB_0800148e;
        iVar2 = fw_08000a88();
        uVar3 = iVar2 - iVar1;
        bVar7 = 1 < uVar3;
        bVar6 = uVar3 == 2;
      } while (uVar3 < 3);
    }
  }
  else {
LAB_080014bc:
    if (-1 < (int)((uint)*param_1 << 0x1c)) {
LAB_08001508:
      if ((int)((uint)*param_1 * 0x20000000) < 0) {
        bVar6 = -1 < (int)(_DAT_4002101c << 3);
        if (bVar6) {
          _DAT_4002101c = _DAT_4002101c | 0x10000000;
        }
        if ((int)(_DAT_40007000 << 0x17) < 0) {
LAB_0800155a:
          iVar5 = *(int *)(param_1 + 8);
          if (iVar5 == 1) {
LAB_08001576:
            _DAT_40021020 = _DAT_40021020 | 1;
          }
          else {
            if ((iVar5 != 0) && (iVar5 == 5)) {
              _DAT_40021020 = _DAT_40021020 | 4;
              goto LAB_08001576;
            }
            _DAT_40021020 = _DAT_40021020 & 0xfffffffa;
          }
          if (*(int *)(param_1 + 8) == 0) {
            local_20 = fw_08000a88();
            do {
              if (-1 < (int)(_DAT_40021020 << 0x1e)) {
LAB_080015c4:
                if (bVar6) {
                  _DAT_4002101c = _DAT_4002101c & 0xefffffff;
                }
                goto LAB_080015d4;
              }
              iVar5 = fw_08000a88();
            } while (iVar5 - local_20 < 0x1389);
          }
          else {
            local_20 = fw_08000a88();
            do {
              if ((int)(_DAT_40021020 << 0x1e) < 0) goto LAB_080015c4;
              iVar5 = fw_08000a88();
            } while (iVar5 - local_20 < 0x1389);
          }
        }
        else {
          _DAT_40007000 = _DAT_40007000 | 0x100;
          local_20 = fw_08000a88();
          do {
            if ((int)(_DAT_40007000 << 0x17) < 0) goto LAB_0800155a;
            iVar5 = fw_08000a88();
          } while (iVar5 - local_20 < 0x65);
        }
        goto LAB_080016d0;
      }
LAB_080015d4:
      if ((int)((uint)*param_1 << 0x1b) < 0) {
        if (*(int *)(param_1 + 0x14) == 1) {
          _DAT_40021034 = _DAT_40021034 | 5;
          iVar5 = fw_08000a88();
          do {
            if ((int)(_DAT_40021034 << 0x1e) < 0) goto LAB_0800161e;
            iVar1 = fw_08000a88();
          } while ((uint)(iVar1 - iVar5) < 3);
        }
        else {
          if (*(int *)(param_1 + 0x14) == -5) {
            _DAT_40021034 = _DAT_40021034 & 0xfffffffb;
LAB_0800161e:
            _DAT_40021034 = _DAT_40021034 & 0xffffff07 | *(int *)(param_1 + 0x18) << 3;
            goto LAB_08001646;
          }
          _DAT_40021034 = _DAT_40021034 & 0xfffffffe | 4;
          iVar5 = fw_08000a88();
          do {
            if (-1 < (int)(_DAT_40021034 << 0x1e)) goto LAB_08001646;
            iVar1 = fw_08000a88();
          } while ((uint)(iVar1 - iVar5) < 3);
        }
      }
      else {
LAB_08001646:
        iVar5 = *(int *)(param_1 + 0x20);
        if (iVar5 == 0) {
LAB_0800170a:
          return (ulonglong)local_20 << 0x20;
        }
        if ((_DAT_40021004 & 0xf) >> 2 == 2) {
          uVar4 = 1;
          if (iVar5 == 1) goto LAB_080016d2;
          if ((((_DAT_40021004 & 0x10000) == *(uint *)(param_1 + 0x24)) &&
              ((_DAT_4002102c & 0xf) == *(uint *)(param_1 + 0x2c))) &&
             ((_DAT_40021004 & 0x3c0000) == *(uint *)(param_1 + 0x28))) goto LAB_0800170a;
LAB_08001706:
          return CONCAT44(local_20,1);
        }
        if (iVar5 == 2) {
          _DAT_40021000 = _DAT_40021000 & 0xfeffffff;
          iVar5 = fw_08000a88();
          do {
            if (-1 < (int)(_DAT_40021000 << 6)) {
              _DAT_4002102c = _DAT_4002102c & 0xfffffff0 | *(uint *)(param_1 + 0x2c);
              _DAT_40021004 =
                   *(uint *)(param_1 + 0x28) | *(uint *)(param_1 + 0x24) |
                   _DAT_40021004 & 0xffc2ffff;
              _DAT_40021000 = _DAT_40021000 | 0x1000000;
              iVar5 = fw_08000a88();
              do {
                if ((int)(_DAT_40021000 << 6) < 0) goto LAB_0800170a;
                iVar1 = fw_08000a88();
              } while ((uint)(iVar1 - iVar5) < 3);
              break;
            }
            iVar1 = fw_08000a88();
          } while ((uint)(iVar1 - iVar5) < 3);
        }
        else {
          _DAT_40021000 = _DAT_40021000 & 0xfeffffff;
          iVar5 = fw_08000a88();
          do {
            if (-1 < (int)(_DAT_40021000 << 6)) goto LAB_0800170a;
            iVar1 = fw_08000a88();
          } while ((uint)(iVar1 - iVar5) < 3);
        }
      }
LAB_080016d0:
      uVar4 = 3;
LAB_080016d2:
      return CONCAT44(local_20,uVar4);
    }
    if (*(int *)(param_1 + 0x1c) == 0) {
      _DAT_40021024 = _DAT_40021024 & 0xfffffffe;
      iVar1 = fw_08000a88();
      do {
        if (-1 < (int)(_DAT_40021024 << 0x1e)) goto LAB_08001508;
        iVar2 = fw_08000a88();
        uVar3 = iVar2 - iVar1;
        bVar7 = 1 < uVar3;
        bVar6 = uVar3 == 2;
      } while (uVar3 < 3);
    }
    else {
      _DAT_40021024 = _DAT_40021024 | 1;
      iVar1 = fw_08000a88();
      do {
        if ((int)(_DAT_40021024 << 0x1e) < 0) goto LAB_08001508;
        iVar2 = fw_08000a88();
        uVar3 = iVar2 - iVar1;
        bVar7 = 1 < uVar3;
        bVar6 = uVar3 == 2;
      } while (uVar3 < 3);
    }
  }
LAB_08001416:
  while( true ) {
    if (bVar7 && !bVar6) goto LAB_080016d0;
LAB_08001418:
    if ((int)(_DAT_40021000 << 0xe) < 0) break;
    iVar1 = fw_08000a88();
    bVar7 = 99 < (uint)(iVar1 - iVar5);
    bVar6 = iVar1 - iVar5 == 100;
  }
  goto LAB_08001438;
}

