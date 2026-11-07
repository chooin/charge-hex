// rea decompile_all
// name: fw_080094e8
// address: 0x80094e8
// body: available
// range: 0x80094e8-0x800956b inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


void fw_080094e8(void)

{
  byte bVar1;
  uint uVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  
  uVar2 = 0;
  do {
    if (*(ushort *)(uVar2 * 0x34 + 0x200005e8) < 3) {
      *(undefined1 *)(uVar2 + 0x20000aee) = 0;
      bVar1 = *(byte *)(uVar2 + 0x20000afa);
      if (bVar1 != 0) {
        uVar4 = 0;
        do {
          if (bVar1 < *(byte *)(uVar4 + 0x20000aee)) {
            *(byte *)(uVar4 + 0x20000aee) = *(byte *)(uVar4 + 0x20000aee) - 1;
          }
          uVar4 = uVar4 + 1 & 0xff;
        } while (uVar4 < 0xc);
        *(undefined1 *)(uVar2 + 0x20000afa) = 0;
      }
    }
    else if (*(char *)(uVar2 + 0x20000aee) == '\0') {
      uVar4 = 0;
      uVar5 = uVar2;
      do {
        if (*(byte *)(uVar5 + 0x20000aee) < *(byte *)(uVar4 + 0x20000aee)) {
          uVar5 = uVar4;
        }
        uVar4 = uVar4 + 1 & 0xff;
      } while (uVar4 < 0xc);
      if (*(char *)(uVar5 + 0x20000aee) == '\0') {
        cVar3 = '\x01';
      }
      else {
        cVar3 = *(char *)(uVar5 + 0x20000aee) + '\x01';
      }
      *(char *)(uVar2 + 0x20000aee) = cVar3;
      *(char *)(uVar2 + 0x20000afa) = cVar3;
    }
    uVar2 = uVar2 + 1 & 0xff;
  } while (uVar2 < 0xc);
  uVar2 = 0;
  uVar4 = 0;
  do {
    if (*(byte *)(uVar2 + 0x20000aee) < *(byte *)(uVar4 + 0x20000aee)) {
      uVar2 = uVar4;
    }
    uVar4 = uVar4 + 1 & 0xff;
  } while (uVar4 < 0xc);
  return;
}

