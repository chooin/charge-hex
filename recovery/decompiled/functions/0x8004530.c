// rea decompile_all
// name: fw_08004530
// address: 0x8004530
// body: available
// range: 0x8004530-0x800454b inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 fw_08004530(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  
  for (puVar6 = &DAT_0800ce78; puVar6 < &DAT_0800ce98; puVar6 = puVar6 + 4) {
    (*(code *)puVar6[3])(*puVar6,puVar6[1],puVar6[2]);
  }
  fw_080040bc();
  uVar3 = uRam000a02f6;
  uVar2 = uRam000a02f2;
  uVar1 = uRam000a02ee;
  if (((puRam00000000[2] & 3) == 1) &&
     (((*puRam00000000 & 1) != 0 || ((int)(puRam00000000[3] << 0x10) < 0)))) {
    return 0;
  }
  if ((puRam00000000[2] & 0x80000017) == 0) {
    puRam00000000[2] = puRam00000000[2] | 1;
    for (iVar4 = fw_080040e8(_DAT_20000140,1000000,0x80000017,uVar1,0,uVar2,0,0xa02fa,uVar3,
                             0x800454d); iVar4 != 0; iVar4 = iVar4 + -1) {
    }
    iVar4 = fw_08005d54();
    do {
      if ((~*puRam00000000 & 1) == 0) {
        return 0;
      }
      iVar5 = fw_08005d54();
    } while ((uint)(iVar5 - iVar4) < 3);
  }
  uRam00000038 = uRam00000038 | 0x10;
  uRam0000003c = uRam0000003c | 1;
  return 1;
}

