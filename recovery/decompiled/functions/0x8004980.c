// rea decompile_all
// name: fw_08004980
// address: 0x8004980
// body: available
// range: 0x8004980-0x8004a9f inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_08004980(void)

{
  ushort uVar1;
  int in_r3;
  int iVar2;
  uint uVar3;
  
  uVar1 = _DAT_20000106;
  if (((short)_DAT_20000106 + 0x78 < (int)(uint)_DAT_2000010e) && (DAT_20000120 == '\0')) {
    uVar3 = 0;
    iVar2 = in_r3;
    do {
      if (((_DAT_20000ad4 >> uVar3 & 1) == 0) || (*(char *)(uVar3 + 0x20000ae2) == '\0')) {
        if (uVar3 == 0xb) {
          DAT_20000120 = '\x01';
          iVar2 = _DAT_20000106 - 10;
          _DAT_20000106 = (ushort)iVar2;
        }
      }
      else if (*(char *)(uVar3 + 0x20000b06) != '\x01') {
        fw_08005210(5,*(undefined1 *)(uVar3 + 0x20000ae2),0x20000ae2,iVar2,in_r3);
        *(undefined1 *)(uVar3 + 0x20000b06) = 1;
        DAT_20000104 = (undefined1)uVar3;
        uVar1 = _DAT_20000106 + 10;
        if (uVar3 == 0xb) {
          DAT_20000120 = '\x01';
          uVar1 = _DAT_20000106;
        }
        break;
      }
      uVar3 = uVar3 + 1 & 0xff;
      uVar1 = _DAT_20000106;
    } while (uVar3 < 0xc);
  }
  _DAT_20000106 = uVar1;
  if (((short)_DAT_20000106 + 0x82 < (int)(uint)_DAT_2000010e) && (DAT_2000011e == '\0')) {
    if (_DAT_20000ad0 == 1) {
      fw_08005210(3,0);
      DAT_2000011e = '\x01';
    }
    else if (_DAT_20000ad0 == 0) {
      DAT_2000011e = '\x01';
      _DAT_20000106 = _DAT_20000106 - 10;
    }
  }
  if (((short)_DAT_20000106 + 0x8c < (int)(uint)_DAT_2000010e) && (DAT_2000011d == '\0')) {
    if (_DAT_20000ace == 1) {
      fw_08005210(2,0);
      DAT_2000011d = '\x01';
    }
    else if (_DAT_20000ace == 0) {
      DAT_2000011d = '\x01';
      _DAT_20000106 = _DAT_20000106 - 10;
    }
  }
  if ((short)_DAT_20000106 + 0x96 < (int)(uint)_DAT_2000010e) {
    if ((DAT_2000011c == '\0') && (_DAT_20000acc == 1)) {
      fw_08005210(1,0);
      DAT_2000011c = '\x01';
    }
    uVar3 = 0;
    do {
      (&DAT_2000011c)[uVar3] = 0;
      do {
        *(undefined1 *)(uVar3 + 0x20000b06) = 0;
        uVar3 = uVar3 + 1 & 0xff;
        if (0xb < uVar3) {
          _DAT_20000106 = 0;
          _DAT_2000010e = 0;
          return;
        }
      } while (4 < uVar3);
    } while( true );
  }
  return;
}

