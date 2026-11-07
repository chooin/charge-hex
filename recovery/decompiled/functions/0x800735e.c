// rea decompile_all
// name: fw_0800735e
// address: 0x800735e
// body: available
// range: 0x800735e-0x80073e7 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


uint fw_0800735e(void)

{
  byte bVar1;
  int iVar2;
  byte bVar3;
  undefined4 in_r3;
  uint uVar4;
  
  uVar4 = 0;
  fw_08005d46(0x48000000,0x8000,0,in_r3,in_r3);
  bVar3 = 0;
  do {
    bVar3 = bVar3 + 1;
  } while (bVar3 < 100);
  fw_08005d46(0x48000000,0x8000,1);
  bVar3 = 0;
  do {
    bVar3 = bVar3 + 1;
  } while (bVar3 < 100);
  bVar3 = 0;
  do {
    uVar4 = (uVar4 & 0x7fff) << 1;
    iVar2 = fw_08005d3c(0x48000000,0x800);
    if (iVar2 != 0) {
      uVar4 = uVar4 | 1;
    }
    fw_08005d46(0x48000000,0x1000,0);
    bVar1 = 0;
    do {
      bVar1 = bVar1 + 1;
    } while (bVar1 < 100);
    fw_08005d46(0x48000000,0x1000,1);
    bVar1 = 0;
    do {
      bVar1 = bVar1 + 1;
    } while (bVar1 < 100);
    bVar3 = bVar3 + 1;
  } while (bVar3 < 0x10);
  return (uVar4 & 0xff) << 8 | uVar4 >> 8;
}

