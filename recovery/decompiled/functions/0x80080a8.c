// rea decompile_all
// name: fw_080080a8
// address: 0x80080a8
// body: available
// range: 0x80080a8-0x8008213 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_080080a8(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  if (DAT_20000854 == '\x04') {
    fw_0800a65c();
    _DAT_200008d6 = 0;
    return;
  }
  uVar5 = param_1 - 4;
  uVar6 = uVar5 & 0xff;
  if (0xb < uVar5) {
    return;
  }
  uVar7 = (uVar5 & 0xff) + 1;
  if ((DAT_20000854 == '\x02') || (DAT_20000854 == '\x03')) {
    fw_08004b10(uVar6);
    goto LAB_0800820c;
  }
  if (DAT_20000854 != '\x01') {
    if (DAT_20000854 == '\x1f') {
      if (DAT_200008c6 == uVar7) {
        fw_080078a0(uVar6);
      }
    }
    else if (DAT_20000854 == ' ') {
      fw_0800ca34(uVar6);
    }
    goto LAB_0800820c;
  }
  if ((uint)_DAT_20000882 + (uint)_DAT_20000884 != 0) {
LAB_080080fc:
    fw_08004b10(uVar6);
    goto LAB_080081e8;
  }
  if (DAT_200008c6 == uVar7) {
    iVar2 = uVar6 * 0x34;
    cVar1 = *(char *)(iVar2 + 0x200005fa);
    iVar3 = (param_1 - 4U & 0xff) * 2;
    if (((cVar1 == '\x02') || (cVar1 == '\x04')) && (DAT_200008c2 == '\x02')) {
      if (*(short *)(iVar3 + 0x2000095e) == 0) {
        cVar1 = (&DAT_20000611)[iVar2];
        if (_DAT_20000876 == 0) {
          bVar4 = cVar1 + 1U & 3;
LAB_0800817c:
          (&DAT_20000611)[iVar2] = bVar4;
        }
        else {
          if (cVar1 != '\0') {
            if (cVar1 == '\x02') {
              bVar4 = 1;
            }
            else {
              if (cVar1 != '\x03') {
                if (cVar1 == '\x01') {
                  (&DAT_20000611)[iVar2] = 0;
                }
                goto LAB_08008182;
              }
              bVar4 = 2;
            }
            goto LAB_0800817c;
          }
          (&DAT_20000611)[iVar2] = 3;
        }
LAB_08008182:
        *(undefined2 *)(iVar3 + 0x200008e6) = 5;
        iVar2 = (byte)(&DAT_20000611)[iVar2] + 5;
        goto LAB_080081f4;
      }
      *(undefined2 *)(iVar3 + 0x2000095e) = 1;
    }
    else if (cVar1 == '\0') {
      if (_DAT_20000878 == 1) {
        _DAT_20000884 = 1;
        goto LAB_080080fc;
      }
      if (*(char *)(iVar2 + 0x20000614) == '\x01') {
        *(undefined1 *)(iVar2 + 0x20000614) = 0;
      }
      else if ((DAT_200008c2 == '\x02') && (*(short *)(iVar3 + 0x20000976) == 0)) {
        fw_0800a1e8(uVar6);
      }
    }
  }
  else {
    if (uVar6 < 9) {
      DAT_200008cc = 0;
      iVar2 = uVar6 + 0x36;
    }
    else {
      if (uVar6 != 9) {
        fw_0800cdb8(0x43);
        DAT_200005d4 = (char)uVar5 + ',';
        DAT_200008cd = 1;
        DAT_200008cc = 1;
        goto LAB_080081e8;
      }
      DAT_200008cc = 0;
      iVar2 = 0x43;
    }
LAB_080081f4:
    fw_0800cdb8(iVar2);
  }
LAB_080081e8:
  _DAT_200008d8 = 0xb4;
LAB_0800820c:
  DAT_200008c6 = (char)uVar7;
  DAT_200008c2 = 2;
  return;
}

