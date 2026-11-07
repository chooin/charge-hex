// rea decompile_all
// name: fw_08004dcc
// address: 0x8004dcc
// body: available
// range: 0x8004dcc-0x8004fd1 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_08004dcc(void)

{
  ushort uVar1;
  char cVar2;
  undefined4 uVar3;
  byte bVar4;
  uint uVar5;
  uint uVar6;
  
  cVar2 = '\0';
  if (0x13 < _DAT_20000110) {
    fw_08004aa8();
    uVar6 = 0;
    _DAT_20000110 = 0;
    do {
      if (*(char *)(uVar6 + 0x20000ad6) == '\x01') {
        if (((_DAT_20000108 >> uVar6 & 1) == 0) &&
           (bVar4 = *(char *)(uVar6 + 0x20000b12) + 1, *(byte *)(uVar6 + 0x20000b12) = bVar4,
           4 < bVar4)) {
          *(undefined1 *)(uVar6 + 0x20000b12) = 0;
          fw_08005210(5,uVar6 + 1 & 0xff);
          uVar1 = (ushort)(1 << uVar6);
          _DAT_20000108 = _DAT_20000108 | uVar1;
          *(char *)(uVar6 + 0x20000ae2) = (char)(uVar6 + 1);
          _DAT_20000ad4 = _DAT_20000ad4 | uVar1;
          *(undefined1 *)(uVar6 + 0x20000b1e) = 1;
          cVar2 = cVar2 + '\x01';
          if (cVar2 == '\x01') {
            DAT_20000104 = (undefined1)uVar6;
          }
          _DAT_2000010e = 0;
          fw_08004960(uVar6);
          uVar5 = fw_0800a46c(0xf114);
          uVar5 = uVar5 & ~(1 << uVar6);
          goto LAB_08004e9c;
        }
      }
      else {
        *(undefined1 *)(uVar6 + 0x20000b12) = 0;
        if (*(char *)(uVar6 + 0x20000b1e) == '\x01') {
          _DAT_20000108 = _DAT_20000108 & ~(ushort)(1 << uVar6);
          *(undefined1 *)(uVar6 + 0x20000ae2) = 0;
          *(undefined1 *)(uVar6 + 0x20000b1e) = 0;
          fw_08004940(uVar6);
          uVar5 = fw_0800a46c(0xf114);
          uVar5 = (1 << uVar6 | uVar5) & 0xffff;
LAB_08004e9c:
          fw_0800a47c(0xf114,uVar5);
        }
      }
      uVar6 = uVar6 + 1 & 0xff;
    } while (uVar6 < 0xc);
  }
  if (DAT_200000ff == '\0') {
    if (1 < DAT_200000fa) {
      fw_080050c8();
      DAT_200000ff = '\x01';
    }
  }
  else {
    DAT_20000101 = fw_080050c8();
  }
  uVar3 = fw_080045d8();
  fw_080041e2(uVar3,0x45c5e800);
  _DAT_2000010a = fw_0800436e();
  _DAT_20000114 = 0;
  uVar6 = 0;
  do {
    uVar5 = (uint)*(ushort *)(uVar6 * 0x34 + 0x200005e8);
    if (uVar5 < _DAT_20000866) {
      _DAT_20000114 = uVar5 + _DAT_20000114;
    }
    uVar6 = uVar6 + 1 & 0xff;
  } while (uVar6 < 0xc);
  if (0x28 < DAT_200000f9) {
    if (DAT_200000fe == '\0') {
      DAT_200000fe = '\x01';
      fw_080057e8(&DAT_20000b2c);
    }
    DAT_200000f9 = 0;
  }
  if (_DAT_20000118 < _DAT_20000114) {
    if (DAT_200000fc == '\0') {
      fw_08005210(3,0);
      DAT_200000fc = '\x01';
      _DAT_20000ad0 = 1;
      _DAT_2000010e = 0;
    }
    _DAT_200000b8 = _DAT_200000b8 & ~(1 << DAT_20000103);
    fw_08007474();
  }
  else {
    DAT_200000fc = '\0';
  }
  if ((int)DAT_20000102 < (int)DAT_20000101) {
    DAT_20000100 = DAT_20000100 + 1;
    if ((DAT_200000fb == '\0') && (4 < DAT_20000100)) {
      fw_08005210(1);
      _DAT_200000b8 = _DAT_200000b8 & 0xfffff000;
      fw_08007474();
      DAT_200000fb = '\x01';
      DAT_200000f8 = 0;
      _DAT_20000acc = 1;
      _DAT_2000010e = 0;
    }
  }
  else if ((int)DAT_20000101 < DAT_20000102 + -2) {
    DAT_200000fb = '\0';
    DAT_20000100 = 0;
  }
  if ((uint)_DAT_2000010c < (uint)_DAT_2000010a) {
    if (DAT_200000fd == '\0') {
      fw_08005210(2,0);
      _DAT_200000b8 = _DAT_200000b8 & 0xfffff000;
      fw_08007474();
      DAT_200000fd = '\x01';
      DAT_200000f8 = 0;
      _DAT_20000ace = 1;
      _DAT_2000010e = 0;
      goto LAB_08004fcc;
    }
  }
  else if ((int)(uint)_DAT_2000010a < (int)(_DAT_2000010c - 400)) {
    DAT_200000fd = '\0';
  }
  if (0x1d < DAT_200000f8) {
    DAT_200000f8 = 0;
  }
LAB_08004fcc:
  fw_08004980();
  return;
}

